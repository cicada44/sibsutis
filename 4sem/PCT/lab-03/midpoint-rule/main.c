#include <stdio.h>
#include <omp.h>

#include <math.h>

double f(double x)
{
    return pow(x, 4) / (0.5 * pow(x, 2) + x + 6);
}

double mrule_serial()
{
    const int n0 = 100000000;
    const double eps = 1E-5;
    const double a = 0.4;
    const double b = 1.5;

    int n = n0, k;
    double sq[2], delta = 1;

    double t = omp_get_wtime();
    for (k = 0; delta > eps; n *= 2, k ^= 1)
    {
        double h = (b - a) / n;
        double s = 0.0;
        for (int i = 0; i < n; i++)
            s += f(a + h * (i + 0.5));
        sq[k] = s * h;
        if (n > n0)
            delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
    }
    t = omp_get_wtime() - t;

    return t;
}

double mrule_parallel(const int n_threads)
{
    const double eps = 1E-5;
    const double a = 0.4;
    const double b = 1.5;
    const int n0 = 100000000;

#if 0
    printf("Numerical integration: [%.3f, %.3f], n0 = %d, EPS = %f\n", a, b, n0, eps);
#endif

    // продолжение main()
    double sq[2];

    double t = omp_get_wtime();
#pragma omp parallel num_threads(n_threads)
    {
        int n = n0, k;
        double delta = 1;

        for (k = 0; delta > eps; n *= 2, k ^= 1)
        {
            double h = (b - a) / n;
            double s = 0.0;
            sq[k] = 0;
// Ждем пока все потоки закончат обнуление sq[k], s
#pragma omp barrier

#pragma omp for nowait
            for (int i = 0; i < n; i++)
                s += f(a + h * (i + 0.5));

#pragma omp atomic
            sq[k] += s * h;

// Ждем пока все потоки обновят sq[k]
#pragma omp barrier
            if (n > n0)
                delta = fabs(sq[k] - sq[k ^ 1]) / 3.0;
            // #if 0
            // printf("n=%d i=%d sq=%.12f delta=%.12f\n", n, k, sq[k], delta);
            // #endif
        }

#if 0
#pragma omp master
        printf("Result Pi: %.12f; Runge rule: EPS %e, n %d\n", sq[k] * sq[k], eps, n / 2);
#endif
    }
    t = omp_get_wtime() - t;

    return t;
}

int main()
{
    double t_serial = mrule_serial();

    for (int i = 2; i <= 6; ++i)
    {
        printf("%f\t%d\n", t_serial / mrule_parallel(i), i);
    }
}