#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

enum {N = 10000000};

double wtime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1E-9;
}

/* lower_bound: Returns the first element not less than value (std::lower_bound) */
int lower_bound(int *v, int n, int value)
{
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (v[mid] >= value)
            right = mid;
        else
            left = mid + 1;
    }
    return v[left];
}

int lower_bound_opt(int *v, int n, int value)
{
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        /* TODO: remove conditional branch */
        if (v[mid] >= value)
            right = mid;
        else
            left = mid + 1;
    }
    return v[left];
}

double run()
{
    int *v = malloc(sizeof(*v) * N);
    for (int i = 0; i < N; i++) {
        v[i] = (i + 1) * 2;
    }

    double t = wtime();
    volatile int lb = lower_bound(v, N, 2 * N);
    //volatile int lb = lower_bound_opt(v, N, 2 * N);
    t = wtime() - t;

    #if 0
    printf("lb = %d\n", lb);
    #endif

    free(v);
    return t;
}

int main()
{
    double t = 0;
    int nreps = 100;
    for (int i = 0; i < nreps; i++)
        t += run();
    t /= nreps;
    printf("Time %.9f\n", t);

    return 0;
}
