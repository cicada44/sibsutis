#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **getRandMatrix(int size, int maxValue);
void print(int **matrix, int size);
void print_row(int *arr);
int *getRandArray(int size, int maxValue);

int main()
{
    // srand(time(NULL));
    int size = ((int)time(NULL) * rand()) % 10;
    if (size < 0)
        size *= -1;
    int maxValue = 100;

    int **arr = getRandMatrix(size, maxValue);
    print(arr, size);

    for (int x = 0; x < size; x++)
        free(arr[x]);
    free(arr);

    return 0;
}

int **getRandMatrix(int size, int maxValue)
{
    int **matrix = malloc(size * sizeof(int *));
    for (int x = 0; x < size; x++)
    {
        int size_2 = ((int)time(NULL) * rand()) % 10;
        if (size_2 < 0)
            size_2 *= -1;
        matrix[x] = getRandArray(size_2, maxValue);
    }
    return matrix;
}

int *getRandArray(int size, int maxValue)
{
    int *arr = malloc((size + 1) * sizeof(int));
    if (!arr)
        exit(1);
    arr[0] = size;
    for (int x = 1; x <= arr[0]; x++)
    {
        arr[x] = ((int)time(NULL) * rand()) % maxValue;
    }
    return arr;
}

void print_row(int *arr)
{
    printf("%d: ", arr[0]);
    for (int x = 1; x <= arr[0]; x++)
    {
        printf("%d ", arr[x]);
    }
    printf("\n");
}

void print(int **arr, int size)
{
    printf("%d\n", size);
    for (int x = 0; x < size; x++)
    {
        print_row(arr[x]);
    }
}