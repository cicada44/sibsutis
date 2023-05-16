#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int nthrds;

struct particle
{
    float x, y, z;
};

const float G = 6.67e-11;

void calculate_forces(struct particle *p, struct particle *f, float *m, int n)
{
#pragma omp parallel for num_threads(nthrds)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
            float mag = (G * m[i] * m[j]) / powf(dist, 2);
            struct particle dir = {
                .x = p[j].x - p[i].x,
                .y = p[j].y - p[i].y,
                .z = p[j].z - p[i].z};
#pragma omp critical
            { /* Datarace */
                f[i].x += mag * dir.x / dist;
                f[i].y += mag * dir.y / dist;
                f[i].z += mag * dir.z / dist;
                f[j].x -= mag * dir.x / dist;
                f[j].y -= mag * dir.y / dist;
                f[j].z -= mag * dir.z / dist;
            }
        }
    }
}

void move_particles(struct particle *p, struct particle *f, struct particle *v, float *m, int n,
                    double dt)
{
    for (int i = 0; i < n; i++)
    {
        struct particle dv = {
            .x = f[i].x / m[i] * dt,
            .y = f[i].y / m[i] * dt,
            .z = f[i].z / m[i] * dt,
        };
        struct particle dp = {
            .x = (v[i].x + dv.x / 2) * dt,
            .y = (v[i].y + dv.y / 2) * dt,
            .z = (v[i].z + dv.z / 2) * dt,
        };
        v[i].x += dv.x;
        v[i].y += dv.y;
        v[i].z += dv.z;
        p[i].x += dp.x;
        p[i].y += dp.y;
        p[i].z += dp.z;
        f[i].x = f[i].y = f[i].z = 0;
    }
}

int main(int argc, char *argv[])
{
    double ttotal, tinit = 0, tforces = 0, tmove = 0;
    ttotal = omp_get_wtime();
    int n = (argc > 1) ? atoi(argv[1]) : 10;
    char *filename = (argc > 2) ? argv[2] : NULL;
    nthrds = atoi(argv[3]);
    tinit = -omp_get_wtime();
    struct particle *p = malloc(sizeof(*p) * n); // Положение частиц (x, y, z)
    struct particle *f = malloc(sizeof(*f) * n); // Сила, действующая на каждую частицу (x, y, z)
    struct particle *v = malloc(sizeof(*v) * n); // Скорость частицы (x, y, z)
    float *m = malloc(sizeof(*m) * n);           // Масса частицы
    for (int i = 0; i < n; i++)
    {
        p[i].x = rand() / (float)RAND_MAX - 0.5;
        p[i].y = rand() / (float)RAND_MAX - 0.5;
        p[i].z = rand() / (float)RAND_MAX - 0.5;
        v[i].x = rand() / (float)RAND_MAX - 0.5;
        v[i].y = rand() / (float)RAND_MAX - 0.5;
        v[i].z = rand() / (float)RAND_MAX - 0.5;
        m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
        f[i].x = f[i].y = f[i].z = 0;
    }
    tinit += omp_get_wtime();
    double dt = 1e-5;
    for (double t = 0; t <= 1; t += dt)
    { // Цикл по времени (модельному)
        tforces -= omp_get_wtime();
        calculate_forces(p, f, m, n); // Вычисление сил – O(N^2)
        tforces += omp_get_wtime();
        tmove -= omp_get_wtime();
        move_particles(p, f, v, m, n, dt); // Перемещение тел O(N)
        tmove += omp_get_wtime();
    }
    ttotal = omp_get_wtime() - ttotal;
    // fprintf(fout, "%.2f\n", 2.3 / ttotal);
    // printf("%.6f\n", tforces + tmove);
    if (filename)
    {
        FILE *fout = fopen(filename, "w");
        if (!fout)
        {
            fprintf(stderr, "Can't save file\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < n; i++)
        {
            fprintf(fout, "%.2f\n", 2.3 / ttotal);
        }
        fclose(fout);
    }
    free(m);
    free(v);
    free(f);
    free(p);
}
