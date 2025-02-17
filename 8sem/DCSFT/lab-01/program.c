#include <stdio.h>

// Функция для вычисления mu_l
double calculate_mu_l(int l, int N, int m, double mu) {
    if ((N - m) <= l && l <= N) {
        return (N - l) * mu;
    } else if (0 <= l && l < (N - m)) {
        return m * mu;
    } else {
        printf("Некорректное значение l\n");
        return -1; // Возвращаем -1 в случае ошибки
    }
}

// Функция для вычисления theta
double calculate_theta(int N, int n, double lambda_, double mu, int m) {
    double theta = 0.0;
    for (int j = n + 1; j <= N; j++) {
        double product = 1.0;
        for (int l = n; l < j; l++) {
            double mu_l = calculate_mu_l(l, N, m, mu);
            product *= (mu_l / (lambda_ * l));
        }
        theta += 1 / (j * lambda_) * product;
    }
    theta += 1 / (n * lambda_);
    return theta;
}

// Функция для вычисления T
double calculate_T(int N, int n, double lambda_, double mu, int m) {
    if (n == 1) {
        double mu_0 = calculate_mu_l(0, N, m, mu);
        return 1 / mu_0;
    } else {
        double T = 0.0;
        double product = 1.0;
        for (int l = 1; l < n; l++) {
            double mu_l = calculate_mu_l(l, N, m, mu);
            product *= (l * lambda_ / mu_l);
        }
        T += 1 / calculate_mu_l(0, N, m, mu) * product;

        for (int j = 1; j < n; j++) {
            product = 1.0;
            for (int l = j; l < n; l++) {
                double mu_l = calculate_mu_l(l, N, m, mu);
                product *= (l * lambda_ / mu_l);
            }
            T += 1 / (j * lambda_) * product;
        }
        return T;
    }
}




// 2.3


int main() {
    int N = 65536;  // Общее количество ЭМ
    double mu = 1;  // Интенсивность потока восстановления (1/ч)
    double lambda_ = 1e-5;  // Интенсивность потока отказов (1/ч)
    int m_values[] = {1, 2, 3, 4};  // Значения m
    int num_m_values = sizeof(m_values) / sizeof(m_values[0]);

    // Открываем файл для записи результатов
    FILE *file = fopen("theta_2.3_results.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

    // Заголовок файла
    fprintf(file, "n\tm\ttheta\n");

    // Перебираем значения n от 65527 до 65536
    for (int n = 65527; n <= 65536; n++) {
        // Перебираем значения m
        for (int i = 0; i < num_m_values; i++) {
            int m = m_values[i];
            double theta = calculate_theta(N, n, lambda_, mu, m);

            // Записываем результаты в файл
            fprintf(file, "%d\t%d\t%.6f\n", n, m, theta);
        }
    }

    // Закрываем файл
    fclose(file);
    printf("Результаты сохранены в файл theta_2.3_results.txt\n");

    return 0;
}




// 2.2

// int main() {
//     int N = 65536;  // Общее количество ЭМ
//     double mu = 1;  // Интенсивность потока восстановления (1/ч)
//     int m = 1;      // Количество восстанавливающих устройств
//     double lambda_values[] = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};  // Значения λ
//     int num_lambda_values = sizeof(lambda_values) / sizeof(lambda_values[0]);

//     // Открываем файл для записи результатов
//     FILE *file = fopen("theta_2.2_results.txt", "w");
//     if (file == NULL) {
//         printf("Ошибка открытия файла!\n");
//         return 1;
//     }

//     // Заголовок файла
//     fprintf(file, "n\tlambda\ttheta\n");

//     // Перебираем значения n от 65527 до 65536
//     for (int n = 65527; n <= 65536; n++) {
//         // Перебираем значения λ
//         for (int i = 0; i < num_lambda_values; i++) {
//             double lambda_ = lambda_values[i];
//             double theta = calculate_theta(N, n, lambda_, mu, m);

//             // Записываем результаты в файл
//             fprintf(file, "%d\t%.0e\t%.6f\n", n, lambda_, theta);
//         }
//     }

//     // Закрываем файл
//     fclose(file);
//     printf("Результаты сохранены в файл theta_results.txt\n");

//     return 0;
// }







// 2.1

// int main() {
//     int N = 65536;  // Общее количество ЭМ
//     double lambda_ = 0.00001;  // Интенсивность потока отказов (1/ч)
//     int m = 1;      // Количество восстанавливающих устройств
//     double mu_values[] = {1, 10, 100, 1000};  // Значения µ
//     int num_mu_values = sizeof(mu_values) / sizeof(mu_values[0]);

//     // Открываем файл для записи результатов
//     FILE *file = fopen("theta_results.txt", "w");
//     if (file == NULL) {
//         printf("Ошибка открытия файла!\n");
//         return 1;
//     }

//     // Заголовок файла
//     fprintf(file, "n\tmu\ttheta\n");

//     // Перебираем значения n от 65527 до 65536
//     for (int n = 65527; n <= 65536; n++) {
//         // Перебираем значения µ
//         for (int i = 0; i < num_mu_values; i++) {
//             double mu = mu_values[i];
//             double theta = calculate_theta(N, n, lambda_, mu, m);

//             // Записываем результаты в файл
//             fprintf(file, "%d\t%.0f\t%.6f\n", n, mu, theta);
//         }
//     }

//     // Закрываем файл
//     fclose(file);
//     printf("Результаты сохранены в файл theta_results.txt\n");

//     return 0;
// }