#include <gtest/gtest.h>

#include <complib/comp.hpp>

#include <vector>

#include <cmath>

// just for testing
bool compare_vector_doubles(std::vector<double> v1, std::vector<double> v2,
                            double epsilon = 0.01f) {
  for (auto x1 = v1.begin(), x2 = v2.begin(); x1 != v1.end() && x2 != v2.end();
       ++x1, ++x2) {
    if (fabs(*x1 - *x2) < epsilon)
      return true;
  }
  return false;
}

TEST(test_matrix_solve, matrix_solve) {

  // vector<vector<double>> matr1 = {{1, -2, 1, 0}, {2, 2, -1, 3}, {3, -1, 1,
  // 5}}; vector<double> sol_matr1 = matrix_solution(matr1); vector<double>
  // expected1 = {1, 3, 5}; ASSERT_EQ(compare_vector_doubles(sol_matr1,
  // expected1), true);

  // vector<vector<double>> matr2 = {{3, 4, 10}, {5, -7, 3}};
  // vector<double> sol_matr2 = matrix_solution(matr2);
  // vector<double> expected2 = {2, 1};
  // ASSERT_EQ(compare_vector_doubles(sol_matr2, expected2), true);

  // vector<vector<double>> matr3 = {{1, 2, -3, -4}, {2, 5, -4, 0}, {-3, 1, 3,
  // 5}}; vector<double> sol_matr3 = matrix_solution(matr3); vector<double>
  // expected3 = {2.05, 1.7, 3.15}; ASSERT_EQ(compare_vector_doubles(sol_matr3,
  // expected3), true);

  // vector<vector<double>> matr4 = {
  //     {1, 2, 3, -2, 6}, {2, 4, -2, -3, 18}, {3, 2, -1, 2, 4}, {2, -3, 2, 1,
  //     8}};
  // vector<double> sol_matr4 = matrix_solution(matr4);
  // vector<double> expected4 = {4.82905982906, -1.69230769231, -1.2735042735,
  //                             4.18803418803};
  // ASSERT_EQ(compare_vector_doubles(sol_matr4, expected4), true);

  vector<vector<double>> matr5 = {
      {5, -3, 2, -8, 1}, {1, 1, 1, 1, 0}, {3, 5, 1, 4, 0}, {4, 2, 3, 1, 3}};
  vector<double> sol_matr5 = matrix_solution(matr5);
  for (int x = 0; x < 4; ++x) {
    cout << sol_matr5[x] << '\n';
  }

  // vector<double> expected5 = {2.05, 1.7, 3.15};
  // ASSERT_EQ(compare_vector_doubles(sol_matr5, expected5), true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
