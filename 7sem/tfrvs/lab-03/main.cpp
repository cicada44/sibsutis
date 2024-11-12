#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// Функция генерации матрицы платежей
vector<vector<double>> generate_payoff_matrix(int n, double c1, double c2, double c3) {
    vector<vector<double>> matrix(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = i * c1 + j * c2 + abs(i - j) * c3;
        }
    }
    return matrix;
}

// Функция вероятностного выбора стратегии на основе регретов
int probabilistic_choice(const vector<double>& regrets) {
    vector<double> exp_regrets(regrets.size());
    double max_regret = *max_element(regrets.begin(), regrets.end());
    double sum_exp = 0.0;

    // Экспоненциальное сглаживание
    for (size_t i = 0; i < regrets.size(); ++i) {
        exp_regrets[i] = exp(regrets[i] - max_regret);
        sum_exp += exp_regrets[i];
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, sum_exp);

    double random_value = dis(gen);
    double cumulative = 0.0;

    for (size_t i = 0; i < regrets.size(); ++i) {
        cumulative += exp_regrets[i];
        if (random_value <= cumulative) {
            return i;
        }
    }
    return regrets.size() - 1; // возвращаем последний элемент, если ничего не выбрано
}

// Мягкое обновление регретов
void update_regrets(vector<double>& regrets, const vector<double>& cumulative_payoff, double mean_payoff, double learning_rate) {
    for (size_t i = 0; i < regrets.size(); ++i) {
        regrets[i] += (cumulative_payoff[i] - mean_payoff) * learning_rate;
    }
}

// Метод Брауна
void brown_method(const vector<vector<double>>& matrix, double epsilon, vector<double>& strategies_dispatcher, vector<double>& strategies_vc, int& iterations, double& V) {
    int n = matrix.size();
    strategies_dispatcher.assign(n, 1.0 / n);
    strategies_vc.assign(n, 1.0 / n);

    vector<double> dispatcher_cumulative_payoff(n, 0.0);
    vector<double> vc_cumulative_payoff(n, 0.0);
    vector<double> dispatcher_regret(n, 0.0);
    vector<double> vc_regret(n, 0.0);

    V = 0;
    iterations = 0;
    double learning_rate = 0.01;

    for (int l = 0; l < 1500000; ++l) {
        ++iterations;

        // 1. Диспетчер выбирает стратегию
        int dispatcher_choice = probabilistic_choice(dispatcher_regret);
        for (int j = 0; j < n; ++j) {
            dispatcher_cumulative_payoff[j] += matrix[dispatcher_choice][j];
        }

        // 2. ВЦ выбирает стратегию
        int vc_choice = probabilistic_choice(vc_regret);
        for (int i = 0; i < n; ++i) {
            vc_cumulative_payoff[i] += matrix[i][vc_choice];
        }

        // 3. Обновляем регреты с мягким изменением
        update_regrets(dispatcher_regret, dispatcher_cumulative_payoff, accumulate(dispatcher_cumulative_payoff.begin(), dispatcher_cumulative_payoff.end(), 0.0) / n, learning_rate);
        update_regrets(vc_regret, vc_cumulative_payoff, accumulate(vc_cumulative_payoff.begin(), vc_cumulative_payoff.end(), 0.0) / n, learning_rate);

        // 4. Обновляем частоты выбора стратегий
        strategies_dispatcher[dispatcher_choice] += 1;
        strategies_vc[vc_choice] += 1;

        // 5. Нормализуем стратегии
        double sum_dispatcher = accumulate(strategies_dispatcher.begin(), strategies_dispatcher.end(), 0.0);
        double sum_vc = accumulate(strategies_vc.begin(), strategies_vc.end(), 0.0);
        for (int i = 0; i < n; ++i) {
            strategies_dispatcher[i] /= sum_dispatcher;
            strategies_vc[i] /= sum_vc;
        }

        // 6. Обновляем цену игры
        double new_V = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                new_V += strategies_dispatcher[i] * matrix[i][j] * strategies_vc[j];
            }
        }

        if (abs(new_V - V) < epsilon) {
            break;
        }
        V = new_V;
    }
}

// Основная функция
int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: <n> <c1> <c2> <c3>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);
    double c1 = stod(argv[2]);
    double c2 = stod(argv[3]);
    double c3 = stod(argv[4]);

    // Генерация матрицы платежей
    auto payoff_matrix = generate_payoff_matrix(n, c1, c2, c3);

    // Открываем файл для записи результатов
    ofstream outfile("results.txt");

    if (!outfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    auto start = chrono::high_resolution_clock::now();

    // Решение методом Брауна
    vector<double> strategies_dispatcher, strategies_vc;
    int iterations;
    double V;
    brown_method(payoff_matrix, 0.01, strategies_dispatcher, strategies_vc, iterations, V);

    // Вывод результатов
    outfile << "Оптимальные смешанные стратегии диспетчера: ";
    for (const auto& i : strategies_dispatcher)
        std::cout << std::to_string(i) << ' ';
    std::cout << '\n';

    outfile << "Оптимальные смешанные стратегии ВЦ: ";
    for (const auto& i : strategies_vc)
        std::cout << std::to_string(i) << ' ';
    std::cout << '\n';

    outfile << "Количество итераций: " << iterations << endl;
    std::cout << "Цена игры V: " << V << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Запись времени выполнения в файл
    outfile << "Execution time: " << elapsed.count() << " seconds" << endl;

    outfile.close();
    return 0;
}
