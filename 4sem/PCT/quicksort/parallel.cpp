#include <fstream>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <string>
#include <vector>

int threshold;
int nthrds;

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

void quicksort_tasks(int* v, int low, int high)
{
    int i, j;
    partition(v, i, j, low, high);
    if (high - low < threshold || (j - low < threshold || high - i < threshold)) {
        if (low < j)
            quicksort_tasks(v, low, j);
        if (i < high)
            quicksort_tasks(v, i, high);
    } else {
#pragma omp task untied // Открепить задачу от потока
        {
            quicksort_tasks(v, low, j);
        }
        quicksort_tasks(v, i, high);
    }
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
    if (argc < 3)
        return 1;

    nthrds = atoi(argv[1]);
    threshold = atoi(argv[2]);
    std::vector<int> v;
    std::cout << "File: " << std::string(argv[3]) << '\n';
    fill_array(v, argv[3]);

    int* p = v.data();
    int low = 0, high = static_cast<int>(v.size() - 1);
    double t = omp_get_wtime();
#pragma omp parallel num_threads(nthrds)
    {
#pragma omp single
        quicksort_tasks(p, low, high);
    }
    t = omp_get_wtime() - t;
    std::cout << "Time: " << std::fixed << std::setprecision(9) << t << '\n';
    // for (const auto& i : v)
    //     std::cout << i << ' ';
    // std::cout << '\n';

    return 0;
}
