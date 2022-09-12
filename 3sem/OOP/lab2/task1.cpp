#include <cmath>
#include <iostream>

using namespace std;

void printArray2D(int** arr, int N);
void printArray(int* arr, int N);
int* copyArray(int* array, int size);
int** copyArray2d(int** arr, int size);
int** mallocArray2D(int N);
void randArray2D(int** arr, int N);
void randArray(int* arr, int N);
void spiral_ext(int** arr2d, int* arr, int N);
void rightDiagonal(int** arr2d, int* arr, int N);
void leftDiagonal(int** arr2d, int* arr, int N);

int main(void)
{
    srand(time(0));
    int size = 3;
    int** array2d = mallocArray2D(size);
    randArray2D(array2d, size);

    cout << "---array---" << endl;
    printArray2D(array2d, size);

    int* array = (int*)malloc(sizeof(int) * size * size);

    rightDiagonal(array2d, array, size);
    cout << endl;
    cout << "rightDiagonal:" << endl;
    printArray(array, size * size);

    leftDiagonal(array2d, array, size);
    cout << endl
         << "leftDiagonal:" << endl;
    printArray(array, size * size);

    spiral_ext(array2d, array, size);
    cout << endl;
    cout << "---spiral---" << endl;
    printArray(array, size * size);

    if (array2d)
        free(array2d);
    if (array)
        free(array);
    return 0;
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

void randArray2D(int** arr, int N)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[i][j] = rand() % 10;
        }
    }
}

void randArray(int* arr, int N)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[i * N + j] = rand() % 10;
        }
    }
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

void rightDiagonal(int** arr2d, int* arr, int N)
{
    int k = 0;
    for (int j = N - 1; j >= 0; --j) {
        int i = 0;
        int l = j;
        while (l < N && i < N) {
            arr[k] = arr2d[i][l];
            ++i, ++l, ++k;
        }
    }
    for (int i = 1; i < N; ++i) {
        int j = 0;
        int m = i;
        while (j < N && m < N) {
            arr[k] = arr2d[m][j];
            ++k, ++j, ++m;
        }
    }
}

void leftDiagonal(int** arr2d, int* arr, int N)
{
    int k = 0;
    for (int i = 0; i < N; ++i) {
        int j = 0, m = i;
        while (j < N && j <= i && m >= 0) {
            arr[k] = arr2d[m][j];
            ++k, ++j, --m;
        }
    }
    for (int j = 1; j < N; ++j) {
        int i = N - 1;
        int l = j;
        int m = i;
        while (l < N) {
            arr[k] = arr2d[m][l];
            ++k, ++l, --m;
        }
    }
}

void printArray(int* array, int N)
{
    for (int i = 0; i < N; ++i) {
        cout << array[i] << ' ';
    }
    cout << endl;
}

void spiral_ext(int** arr2d, int* arr, int N)
{
    int** copy = copyArray2d(arr2d, N);
    int ci = 0, cj = 0;

    for (int step = 0; step < sqrt(N); ++step) {
        for (int j = step; j < N - step; ++j) {
            copy[step][j] = arr2d[ci][cj++];
            if (cj == N) {
                cj = 0, ++ci;
            }
        }
        for (int i = step + 1; i < N - step; ++i) {
            copy[i][N - step - 1] = arr2d[ci][cj++];
            if (cj == N) {
                cj = 0, ++ci;
            }
        }
        for (int j = N - step - 2; j >= step; --j) {
            copy[N - step - 1][j] = arr2d[ci][cj++];
            if (cj == N) {
                cj = 0, ++ci;
            }
        }
        for (int i = N - step - 2; i > step; --i) {
            copy[i][step] = arr2d[ci][cj++];
            if (cj == N) {
                cj = 0, ++ci;
            }
        }
    }

    int k = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            arr[k++] = copy[i][j];
        }
    }

    // cout << endl;
    // printArray2D(copy, N);

    free(copy);
}

int** copyArray2d(int** arr, int size)
{
    int** copy = mallocArray2D(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            copy[i][j] = arr[i][j];
        }
    }

    return copy;
}

int* copyArray(int* arr, int size)
{
    int* copy = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        copy[i] = arr[i];
    }
    return copy;
}
