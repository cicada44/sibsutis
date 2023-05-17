#include <fstream>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <string>
#include <vector>

void partition(int* v, int& i, int& j, int low, int high)
{
    i = low;
    j = high;
    int pivot = v[(low + high) / 2];
    do {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    } while (i <= j);
}

void quicksort(int* v, int low, int high)
{
    int i, j;
    partition(v, i, j, low, high);
    if (low < j)
        quicksort(v, low, j);
    if (i < high)
        quicksort(v, i, high);
}

void fill_array(std::vector<int>& v, char* filepath)
{
    std::ifstream f(filepath);
    int x;
    while (f >> x)
        v.push_back(x);
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    std::vector<int> v;
    std::cout << "File: " << std::string(argv[1]) << '\n';
    fill_array(v, argv[1]);

    int* p = v.data();
    int low = 0, high = static_cast<int>(v.size() - 1);
    double t = omp_get_wtime();
    quicksort(p, low, high);
    t = omp_get_wtime() - t;
    std::cout << "Time: " << std::fixed << std::setprecision(9) << t << '\n';
    // for (const auto& i : v)
    //     std::cout << i << ' ';
    // std::cout << '\n';

    return 0;
}
