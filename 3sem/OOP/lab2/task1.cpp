#include <cmath>
#include <iostream>

using namespace std;

void printArray2D(int **arr, int N);
void printArray(int *arr, int N);
int *copyArray(int *array, int size);
int **mallocArray2D(int N);
void randArray2D(int **arr, int N);
void randArray(int *arr, int N);
void spiral_ext(int *array, int **arr, int N);
void rightDiagonal(int **arr2d, int *arr, int N);

int main(void) {
  srand(time(0));

  int size = rand() % 10;

  int **array2d = mallocArray2D(size);
  randArray2D(array2d, size);

  cout << "---array---" << endl;
  printArray2D(array2d, size);

  int *array = (int *)malloc(sizeof(int) * size * size);
  //   rightDiagonal(array2d, array, size);

  spiral_ext(array, array2d, size);

  cout << "---spiral---" << endl;
  printArray(array, size);

  if (array2d)
    free(array2d);
  return 0;
}

int **mallocArray2D(int N) {
  int **arr = (int **)malloc(N * sizeof(int *) + N * N * sizeof(int));
  int *ptr = (int *)(arr + N);

  for (int i = 0; i < N; ++i) {
    arr[i] = ptr + N * i;
  }

  return arr;
}

void randArray2D(int **arr, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      arr[i][j] = rand() % 10;
    }
  }
}

void randArray(int *arr, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      arr[i * N + j] = rand() % 10;
    }
  }
}

void printArray2D(int **arr, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << arr[i][j] << ' ';
    }
    cout << endl;
  }
}

void printArray(int *arr, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << arr[i * N + j] << ' ';
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

void spiral_ext(int *array, int **arr, int beg, int end) {
  int cnter_2d_str;
  for (int i = beg; i < end; i++)
    array[i] = arr[];
}

int *copyArray(int *arr, int size) {
  int *copy = (int *)malloc(sizeof(int) * size);
  for (int i = 0; i < size; ++i) {
    copy[i] = arr[i];
  }
  return copy;
}