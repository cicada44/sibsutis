#include <stdio.h>
#include <omp.h>

#include <math.h>

#include <stdlib.h>

double getrand()
{
    return (double)rand() / RAND_MAX;
}

double getrand_r(unsigned int *seed)
{
    return (double)rand_r(seed) / RAND_MAX;
}

double func(double x, double y)
{
    return exp((x + y) * 2);
}

double MC_serial(const int n)
{

    double t = omp_get_wtime();
    int in = 0;
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        double x = getrand(); /* x in [0, 1] */
        double y = getrand(); /* y in [0, 1 - x] */
        if (y <= 1 - x)
        {
            in++;
            s += func(x, y);
        }
    }
    double v = M_PI * in / n;
    double res = v * s / in;
    printf("Result: %.12f, n %d\n", res, n);
    t = omp_get_wtime() - t;

    return t;
}

double MC_parallel(const int n, const int n_threads)
{

    double t = omp_get_wtime();

    int in = 0;
    double s = 0;
#pragma omp parallel num_threads(n_threads)
    {
        double s_loc = 0;
        int in_loc = 0;
        unsigned int seed = omp_get_thread_num();

#pragma omp for nowait
        for (int i = 0; i < n; i++)
        {
            double x = getrand_r(&seed); /* x in [0, 1] */
            double y = getrand_r(&seed); /* y in [0, 1 - x] */
            if (y <= 1 - x)
            {
                in_loc++;
                s_loc += func(x, y);
            }
        }

#pragma omp atomic
        s += s_loc;

#pragma omp atomic
        in += in_loc;
    }

    double v = M_PI * in / n;
    __attribute_maybe_unused__ double res = v * s / in;
    // printf("Result: %.12f, n %d\n", res, n);

    t = omp_get_wtime() - t;

    return t;
}

void inspect()
{

    int n;

    n = 10000000;
    MC_serial(n);
    for (int i = 2; i <= 6; ++i)
    {
        MC_parallel(n, i);
    }
}

void benchmark()
{
    int n = 10000000;
    double t_serial = MC_serial(n);
    for (int i = 2; i <= 6; ++i)
    {
        printf("%f\t%d\n", t_serial / MC_parallel(n, i), i);
    }

    n = 100000000;
    t_serial = MC_serial(n);
    for (int i = 2; i <= 6; ++i)
    {
        printf("%f\t%d\n", t_serial / MC_parallel(n, i), i);
    }
}

int main()
{
    // inspect();
    benchmark();
}