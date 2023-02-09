#include <iostream>

#include <vector>

#include <cmath>

using std::cout;

using std::vector;

vector<double> matrix_solution(std::vector<std::vector<double>> &arr) {
  vector<double> answer(arr.size());

  int n = arr.size();

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i][i] == 0) {
        std::swap(arr[i], arr[i + 1]);
      }

      float f = arr[j][i] / arr[i][i];
      for (int k = 0; k < n + 1; k++) {
        arr[j][k] = arr[j][k] - f * arr[i][k];
      }

      for (const auto &i : arr) {
        for (const auto &j : i) {
          cout << j << ' ';
        }
        cout << '\n';
      }
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    answer[i] = arr[i][n];

    for (int j = i + 1; j < n; j++) {
      if (i != j) {
        answer[i] = answer[i] - arr[i][j] * answer[j];
      }
    }
    answer[i] = answer[i] / arr[i][i];
  }

  return answer;
}
