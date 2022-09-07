#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *getRandArray(int size, int maxValue);
void print(int *arr);

int main()
{
    srand(time(NULL));
    int size = 5 + rand() % (10 - 5 + 1);
    if (size < 0)
        size *= -1;
    int maxValue = 100;

    int *arr = getRandArray(size, maxValue);
    print(arr);

    free(arr);

    return 0;
}

int *getRandArray(int size, int maxValue)
{
    int *arr = malloc((size + 1) * sizeof(int));
    if (!arr)
        exit(1);
    arr[0] = size;
    for (int x = 1; x <= arr[0]; x++)
    {
        arr[x] = (rand() * (int)time(NULL)) % maxValue;
    }
    return arr;
}

void print(int *arr)
{
    printf("%d: ", arr[0]);
    for (int x = 1; x <= arr[0]; x++)
    {
        printf("%d ", arr[x]);
    }
    printf("\n");
}