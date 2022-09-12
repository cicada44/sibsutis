#include <cmath>
#include <iostream>

using namespace std;

void spiral(int** arr2d, int* arr, int N);
void printArray2D(int** arr, int N);
void printArray(int* arr, int N);
int** mallocArray2D(int N);

int main(void)
{
    int size = 3;
    int** arr2d = mallocArray2D(size);
    int* arr = (int*)malloc(sizeof(int) * size * size);

    spiral(arr2d, arr, size);
    printArray2D(arr2d, size);
    cout << endl;
    printArray(arr, size * size);

    free(arr2d);
    free(arr);

    return 0;
}

void spiral(int** arr2d, int* arr, int N)
{
    int count = 1;
    for (int step = 0; step < sqrt(N); ++step) {
        for (int j = step; j < N - step; ++j) {
            arr2d[step][j] = count++;
        }
        for (int i = step + 1; i < N - step; ++i) {
            arr2d[i][N - step - 1] = count++;
        }
        for (int j = N - step - 2; j >= step; --j) {
            arr2d[N - step - 1][j] = count++;
        }
        for (int i = N - step - 2; i > step; --i) {
            arr2d[i][step] = count++;
        }
    }

    int k = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[k++] = arr2d[i][j];
        }
    }
}

int** mallocArray2D(int N)
{
    int** arr = (int**)malloc(N * sizeof(int*) + N * N * sizeof(int));
    int* ptr = (int*)(arr + N);

    for (int i = 0; i < N; ++i) {
        arr[i] = ptr + N * i;
    }

    return arr;
}

void printArray(int* array, int N)
{
    for (int i = 0; i < N; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

void printArray2D(int** arr, int N)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}