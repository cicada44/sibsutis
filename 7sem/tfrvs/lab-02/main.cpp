#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;

// Структура для хранения задачи
struct Task {
    int r;  // Количество ресурсов
    int t;  // Время выполнения
};

// Функция чтения задач из файла
vector<Task> read_tasks_from_file(const string &filename) {
    vector<Task> tasks;
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        exit(1);
    }
    int r, t;
    while (file >> r >> t) {
        tasks.push_back({r, t});
    }
    return tasks;
}

vector<pair<int, int>> generate_tasks_llnl(int m) {
    vector<pair<int, int>> tasks;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_proc(1, 9216);
    uniform_int_distribution<> dis_time(1, 1000);

    for (int i = 0; i < m; ++i) {
        int r_j = dis_proc(gen);
        int t_j = dis_time(gen);
        tasks.emplace_back(r_j, t_j);
    }
    return tasks;
}

// Сортировка подсчетом
void counting_sort(vector<Task> &tasks, int max_r) {
    vector<int> count(max_r + 1, 0);
    vector<Task> output(tasks.size());
    
    // Подсчитываем количество задач для каждого значения r
    for (const auto &task : tasks) {
        count[task.r]++;
    }
    
    // Накопление счетчиков
    for (int i = 1; i <= max_r; i++) {
        count[i] += count[i - 1];
    }
    
    // Размещаем задачи по упорядоченным индексам
    for (int i = tasks.size() - 1; i >= 0; i--) {
        output[count[tasks[i].r] - 1] = tasks[i];
        count[tasks[i].r]--;
    }
    
    tasks = output;
}

// Класс для реализации бинарного дерева турнира
class TournamentTree {
    vector<int> tree;
    int size;

public:
    TournamentTree(int n) {
        size = n;
        tree.resize(2 * n, 0);  // Листья - это уровни, каждый с n ресурсами
    }

    // Обновление дерева при размещении задачи
    void update(int index, int value) {
        index += size;
        tree[index] = value;
        while (index > 1) {
            index /= 2;
            tree[index] = max(tree[2 * index], tree[2 * index + 1]);
        }
    }

    // Поиск первого подходящего уровня с достаточным количеством ресурсов
    int find_fit(int value) {
        int index = 1;
        while (index < size) {
            if (tree[2 * index] >= value) {
                index = 2 * index;
            } else {
                index = 2 * index + 1;
            }
        }
        return index - size;  // Возвращаем индекс уровня
    }

    int get_max() {
        return tree[1];  // Корень дерева - максимальный ресурс среди всех уровней
    }
};

// Алгоритм NFDH
int NFDH(vector<Task> &tasks, int n) {
    counting_sort(tasks, n);  // Сортировка задач по r
    int total_time = 0;
    int current_level_capacity = n;  // Свободные ресурсы на уровне
    int current_level_time = 0;

    for (const auto &task : tasks) {
        if (task.r <= current_level_capacity) {
            current_level_capacity -= task.r;
            current_level_time = max(current_level_time, task.t);
        } else {
            total_time += current_level_time;
            current_level_capacity = n - task.r;
            current_level_time = task.t;
        }
    }
    total_time += current_level_time;  // Добавляем время последнего уровня
    return total_time;
}

// Алгоритм FFDH
int FFDH(vector<Task> &tasks, int n) {
    counting_sort(tasks, n);  // Сортировка задач по r
    TournamentTree tree(n);   // Создаем дерево с n уровнями

    // Инициализируем дерево - на каждом уровне n свободных ресурсов
    for (int i = 0; i < n; i++) {
        tree.update(i, n);
    }

    int total_time = 0;

    for (const auto &task : tasks) {
        int level = tree.find_fit(task.r);
        tree.update(level, tree.get_max() - task.r);  // Обновляем количество ресурсов на уровне
        total_time = max(total_time, task.t);
    }

    return total_time;
}

// Функция вычисления отклонения ε
double calculate_epsilon(int T, int T_prime) {
    return static_cast<double>(T - T_prime) / T_prime;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <n> <algorithm(NFDH/FFDH)>" << endl;
        return 1;
    }

    string filename = argv[1];
    int n = stoi(argv[2]);
    string algorithm = argv[3];

    vector<Task> tasks = read_tasks_from_file(filename);

    clock_t start_time = clock();  // Засекаем время выполнения

    int T = 0;
    if (algorithm == "NFDH") {
        T = NFDH(tasks, n);
    } else if (algorithm == "FFDH") {
        T = FFDH(tasks, n);
    } else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        return 1;
    }

    clock_t end_time = clock();  // Засекаем время окончания
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    // Для примера, нижняя граница целевой функции T'
    int T_prime = accumulate(tasks.begin(), tasks.end(), 0, [](int sum, const Task &task) {
        return sum + task.t;
    }) / n;

    double epsilon = calculate_epsilon(T, T_prime);

    cout << "Расписание задач выполнено с алгоритмом " << algorithm << endl;
    cout << "T(S) = " << T_prime << endl;
    cout << "Отклонение ε = " << epsilon << endl;
    cout << "Время выполнения алгоритма: " << elapsed_time << " секунд" << endl;

    return 0;
}
