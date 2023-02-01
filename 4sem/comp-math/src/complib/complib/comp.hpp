#include <iostream>

#include <vector>

#include <cmath>

using std::cout;

using std::vector;

vector<double> matrix_solution(std::vector<std::vector<double>> &arr) {
  vector<double> answer(arr.size());

  int n = arr.size();

  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      double ratio = arr[j][i] / arr[i][i];
      for (int k = 0; k < n + 1; ++k) {
        arr[j][k] -= arr[i][k] * ratio;
      }
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    answer[i] = arr[i][n];
    for (int j = i + 1; j < n; ++j) {
      if (i != j) {
        answer[i] -= arr[i][j] * answer[j];
      }
    }
    answer[i] /= arr[i][i];
    if (answer[i] == -0) {
      answer[i] = 0;
    }
  }

  return answer;
}
