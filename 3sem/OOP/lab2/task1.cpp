#include <iostream>

using namespace std;

void printArray2D(int** arr, int N);
int** mallocArray2D(int N);
void randArray2D(int** arr, int N);
void rightDiagonal(int** arr2d, int* arr, int N);

int main(void)
{
    srand(time(0));

    int size = rand() % 10;
    int** array2d = mallocArray2D(size);
    randArray2D(array2d, size);
    printArray2D(array2d, size);

    int* array = (int*)malloc(sizeof(int) * size * size);
    rightDiagonal(array2d, array, size);

    if (array2d)
        free(array2d);
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

void printArray2D(int** arr, int N)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

// void rightDiagonal(int** arr2d, int* arr, int N)
// {
//     for (int i = 0; i < N; ++i) {
//         for (int j = N; j >= 0; --j) {

//         }
//     }
// }