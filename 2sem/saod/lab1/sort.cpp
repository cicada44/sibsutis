#include <sys/time.h>

#include <cassert>
#include <iostream>

template <typename T>
size_t partition(T* arr, int low, int high) {
  size_t pivot = arr[high];
  size_t i = (low - 1);

  for (int j = low; j <= high - 1; ++j) {
    if (arr[j] < pivot) {
      i++;
      std::swap(arr[i], arr[j]);
    }
  }

  std::swap(arr[i + 1], arr[high]);

  return (i + 1);
}

/* O(nlog(n)) */
template <typename T>
void quick_sort(T* arr, int low, int high) {
  if (low < high) {
    size_t pi = partition(arr, low, high);
    quick_sort(arr, low, pi - 1);
    quick_sort(arr, pi + 1, high);
  }
}

void interactive() {
  int size;
  std::cin >> size;

  assert(size >= 0);

  int a[size];

  for (int i = 0; i != size; ++i) {
    std::cin >> a[i];
  }

  quick_sort(a, 0, 9);

  for (int i = 0; i != size; ++i) {
    std::cout << "a[" << i << "]: " << a[i] << '\n';
  }
}

void benchmark() {
  int size = 50000;

  int a[1000000];
  int cnt = 0;
  for (int i = 1000000 - 1; i >= 0; --i) {
    a[cnt++] = i;
  }

  for (; size != 1000000; size += 50000) {
    double t = time(NULL);
    quick_sort(a, 0, size - 1);
    t = time(NULL) - t;

    std::cout << size << '\t' << t << '\n';
  }
}

void find_m() {
  int size, m;

  std::cout << "size: ";
  std::cin >> size;
  std::cout << "m: ";
  std::cin >> m;

  assert(size >= 0);

  int a[size];

  for (int i = 0; i != size; ++i) {
    std::cout << "a[" << i << "]: ";
    std::cin >> a[i];
  }

  quick_sort(a, 0, 9);

  std::cout << "\nEach m in array\n";
  for (int i = 0; i != size; ++i) {
    if (a[i] == m) {
      std::cout << "a[" << i << "]: " << m << '\n';
    }
  }
}

int main() {
  // interactive();
  find_m();
}
