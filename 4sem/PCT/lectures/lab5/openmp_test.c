#include <omp.h>
#include <stdio.h>

int main()
{
#pragma omp parallel num_threads(3)
    {
        printf("%d\t%d\n", omp_get_thread_num(), omp_get_thread_limit());
    }
}