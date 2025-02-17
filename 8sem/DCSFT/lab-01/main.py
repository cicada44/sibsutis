import numpy as np
import matplotlib.pyplot as plt

# Функция расчета Theta (частотный метод)
def calculate_theta(n, N, lambd, mu, m):
    if n >= N:
        return 1 / lambd
    else:
        return ((N - n) * mu + m * mu) / (lambd * (N - n + m))

# Функция расчета T (частотный метод)
def calculate_T(n, N, lambd, mu, m):
    if n >= N:
        return 0
    else:
        return n / (m * mu)

# Задание 2: Графики зависимости Theta от параметров
def plot_theta_dependency():
    # 2.1. Зависимость Theta(n) при разных значениях µ
    N = 65536
    lambd = 1e-5
    m = 1
    n_values = np.arange(65527, 65537)
    mu_values = [1, 10, 100, 1000]

    plt.figure(figsize=(10, 6))
    for mu in mu_values:
        theta_values = [calculate_theta(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, theta_values, label=f"µ = {mu}")
    plt.title("Зависимость Θ(n) при разных значениях µ")
    plt.xlabel("n")
    plt.ylabel("Θ")
    plt.legend()
    plt.grid()
    plt.show()

    # 2.2. Зависимость Theta(n) при разных значениях λ
    mu = 1
    lambd_values = [1e-5, 1e-6, 1e-7, 1e-8, 1e-9]

    plt.figure(figsize=(10, 6))
    for lambd in lambd_values:
        theta_values = [calculate_theta(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, theta_values, label=f"λ = {lambd:.1e}")
    plt.title("Зависимость Θ(n) при разных значениях λ")
    plt.xlabel("n")
    plt.ylabel("Θ")
    plt.legend()
    plt.grid()
    plt.show()

    # 2.3. Зависимость Theta(n) при разных значениях m
    lambd = 1e-5
    m_values = [1, 2, 3, 4]

    plt.figure(figsize=(10, 6))
    for m in m_values:
        theta_values = [calculate_theta(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, theta_values, label=f"m = {m}")
    plt.title("Зависимость Θ(n) при разных значениях m")
    plt.xlabel("n")
    plt.ylabel("Θ")
    plt.legend()
    plt.grid()
    plt.show()

# Задание 3: Графики зависимости T от параметров
def plot_T_dependency():
    # 3.1. Зависимость T(n) при разных значениях µ
    N = 1000
    lambd = 1e-3
    m = 1
    n_values = np.arange(900, 1001)
    mu_values = [1, 2, 4, 6]

    plt.figure(figsize=(10, 6))
    for mu in mu_values:
        T_values = [calculate_T(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, T_values, label=f"µ = {mu}")
    plt.title("Зависимость T(n) при разных значениях µ")
    plt.xlabel("n")
    plt.ylabel("T")
    plt.legend()
    plt.grid()
    plt.show()

    # 3.2. Зависимость T(n) при разных значениях λ
    N = 8192
    mu = 1
    lambd_values = [1e-5, 1e-6, 1e-7, 1e-8, 1e-9]
    n_values = np.arange(8092, 8193)

    plt.figure(figsize=(10, 6))
    for lambd in lambd_values:
        T_values = [calculate_T(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, T_values, label=f"λ = {lambd:.1e}")
    plt.title("Зависимость T(n) при разных значениях λ")
    plt.xlabel("n")
    plt.ylabel("T")
    plt.legend()
    plt.grid()
    plt.show()

    # 3.3. Зависимость T(n) при разных значениях m
    lambd = 1e-5
    m_values = [1, 2, 3, 4]

    plt.figure(figsize=(10, 6))
    for m in m_values:
        T_values = [calculate_T(n, N, lambd, mu, m) for n in n_values]
        plt.plot(n_values, T_values, label=f"m = {m}")
    plt.title("Зависимость T(n) при разных значениях m")
    plt.xlabel("n")
    plt.ylabel("T")
    plt.legend()
    plt.grid()
    plt.show()

# Основная функция
if __name__ == "__main__":
    print("Начало расчета...")
    plot_theta_dependency()  # Построение графиков для Theta
    plot_T_dependency()      # Построение графиков для T
    print("Расчет завершен.")
