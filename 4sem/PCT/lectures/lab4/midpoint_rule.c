#include <stdio.h>
#include <pthread.h>
#include <math.h>

double func(void **x)
{
    return exp((double)-x * (double)x);
}

int main()
{

    const double a = -4.0;
    const double b = 4.0;
    const int n = 100;

    pthread_t npth = n / 3;

    pthread_t *pids = malloc(sizeof(pthread_t) * npth);

    double h = (b - a) / n;
    double s = 0.0;

    unsigned cpids = 0;

    for (int i = 0; i != n; i + 3)
    {
        pthread_create(pids[cpids], NULL, func, );
        s += func(a + h * (i + 0.5));
    }
    s *= h;

    printf("Result Pi: %.12f\n", s * s);
}
