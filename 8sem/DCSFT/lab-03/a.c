#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вычисления mu_l
double calculate_mu_l(int l, int N, int m, double mu) {
    if ((N - m) <= l && l <= N) {
        return (N - l) * mu;
    } else if (0 <= l && l < (N - m)) {
        return m * mu;
    } else {
        printf("Ошибка: некорректное значение l\n");
        exit(1);
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
            double product_j = 1.0;
            for (int l = j; l < n; l++) {
                double mu_l = calculate_mu_l(l, N, m, mu);
                product_j *= (l * lambda_ / mu_l);
            }
            T += 1 / (j * lambda_) * product_j;
        }
        return T;
    }
}

int main() {
    const int N = 65536;
    double lambdas[] = {1e-6, 1e-7, 1e-5};
    double mus[] = {1, 10, 100, 1000};
    int ms[] = {1, 2, 3};
    int ns[] = {65527, 65528, 65529, 65530, 65531, 65532, 65533, 65534, 65535, 65536};

    // Размеры массивов
    const int num_lambdas = sizeof(lambdas) / sizeof(lambdas[0]);
    const int num_mus = sizeof(mus) / sizeof(mus[0]);
    const int num_ms = sizeof(ms) / sizeof(ms[0]);
    const int num_ns = sizeof(ns) / sizeof(ns[0]);

    // Открываем файл для записи результатов
    FILE *file = fopen("results.txt", "w");
    if (!file) {
        perror("Не удалось открыть файл для записи");
        return 1;
    }

    // Записываем заголовок
    fprintf(file, "# λ\tµ\tm\tn\ttheta\tT\n");

    for (int i_lambda = 0; i_lambda < num_lambdas; i_lambda++) {
        for (int i_mu = 0; i_mu < num_mus; i_mu++) {
            for (int i_m = 0; i_m < num_ms; i_m++) {
                for (int i_n = 0; i_n < num_ns; i_n++) {
                    double lambda_ = lambdas[i_lambda];
                    double mu = mus[i_mu];
                    int m = ms[i_m];
                    int n = ns[i_n];

                    double theta = calculate_theta(N, n, lambda_, mu, m);
                    double T = calculate_T(N, n, lambda_, mu, m);

                    // Записываем результаты в файл
                    fprintf(file, "%e\t%e\t%d\t%d\t%e\t%e\n",
                            lambda_, mu, m, n, theta, T);
                    printf("%-10.2e %-10.0f %-5d %-10d %-20.5f %-20.5f\n",
                           lambda_, mu, m, n, theta, T);
                }
            }
        }
    }

    fclose(file);
    printf("Результаты успешно записаны в файл results.txt\n");
    return 0;
}