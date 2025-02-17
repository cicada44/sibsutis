def calculate_mu_l(l, N, m, mu):
    if (N - m) <= l <= N:
        return (N - l) * mu
    elif 0 <= l < (N - m):
        return m * mu
    else:   
        raise ValueError("Некорректное значение l")

def calculate_theta(N, n, lambda_, mu, m):
    theta = 0.0
    for j in range(n + 1, N + 1):
        product = 1.0
        for l in range(n, j):
            mu_l = calculate_mu_l(l, N, m, mu)
            product *= (mu_l / (lambda_ * l))
        theta += 1 / (j * lambda_) * product
    theta += 1 / (n * lambda_)
    return theta

def calculate_T(N, n, lambda_, mu, m):
    if n == 1:
        mu_0 = calculate_mu_l(0, N, m, mu)
        return 1 / mu_0
    else:
        T = 0.0
        product = 1.0
        for l in range(1, n):
            mu_l = calculate_mu_l(l, N, m, mu)
            product *= (l * lambda_ / mu_l)
        T += 1 / calculate_mu_l(0, N, m, mu) * product
        
        for j in range(1, n):
            product = 1.0
            for l in range(j, n):
                mu_l = calculate_mu_l(l, N, m, mu)
                product *= (l * lambda_ / mu_l)
            T += 1 / (j * lambda_) * product
        return T

# Пример использования
N = 65536  # Общее количество ЭМ
n = 65527   # Количество ЭМ в вычислительном ядре
lambda_ = 0.00001  # Интенсивность потока отказов (1/ч)
mu = 1  # Интенсивность потока восстановления (1/ч)
m = 1    # Количество восстанавливающих устройств

theta = calculate_theta(N, n, lambda_, mu, m)
T = calculate_T(N, n, lambda_, mu, m)

print(f"Среднее время наработки до отказа (Θ): {theta:.2f} ч")
print(f"Среднее время восстановления (T): {T:.2f} ч")