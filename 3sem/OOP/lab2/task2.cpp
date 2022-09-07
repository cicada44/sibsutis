#include <cstdlib>
#include <iostream>

void print_2d_arr(int **arr, unsigned rowcnt);
int **init_2d_arr(int rowCount);
void fill_random(int **arr, unsigned rowcnt);

int main() {
  int rowCount = ((int)time(NULL) * rand()) % 10;
  if (rowCount < 0)
    rowCount *= -1;

  int **arr = init_2d_arr(rowCount);

  fill_random(arr, rowCount);

  print_2d_arr(arr, rowCount);

  return 0;
}

int **init_2d_arr(int rowCount) {
  int **a = new int *[rowCount];
  for (int i = 0; i < rowCount; ++i)
    a[i] = new int[rowCount];

  return a;
}

void fill_random(int **arr, unsigned rowcnt) {
  for (unsigned x = 0; x < rowcnt; x++) {
    for (unsigned i = 0; i < rowcnt; i++) {
      arr[x][i] = ((int)time(NULL) * rand()) % 10;
    }
  }
}

void print_2d_arr(int **arr, unsigned rowcnt) {
  for (unsigned x = 0; x < rowcnt; x++) {
    for (unsigned i = 0; i < rowcnt; i++) {
      std::cout << arr[x][i] << " ";
    }
    std::cout << std::endl;
  }
}
