#include <iostream>

#include <vector>

#include <complib/comp.hpp>

using std::cout;

using std::vector;

int main() {
  vector<double> solution;

  vector<vector<double>> matr1 = {{2, 1, 1, 1}, {1, -1, 0, 1}, {3, -1, 2, 1}};

  matrix_solution(matr1);

  // cout << "\n\nMATRIX\n\n";
  // for (const auto &i : matr1) {
  //   for (const auto &j : i) {
  //     cout << j << ' ';
  //   }
  //   cout << '\n';
  // }

  return 0;
}