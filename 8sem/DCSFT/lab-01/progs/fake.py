import numpy as np
import matplotlib.pyplot as plt

# Параметры
N = 65536
lambd = 1e-5
m = 1
n_values = np.arange(65527, 65537)
mu_values = [1, 10, 100, 1000]

# Функция для генерации данных
def generate_data(n_values, mu):
    return (N - n_values) * mu / lambd

# Создание графика
plt.figure(figsize=(10, 6))
for mu in mu_values:
    theta_values = generate_data(n_values, mu)
    if mu == 1:
        plt.plot(n_values, theta_values, 'r-', label=f"µ = {mu} 1/hours")
    elif mu == 10:
        plt.plot(n_values, theta_values, 'g--', label=f"µ = {mu} 1/hours")
    elif mu == 100:
        plt.plot(n_values, theta_values, 'b-.', label=f"µ = {mu} 1/hours")
    else:
        plt.plot(n_values, theta_values, 'm:', label=f"µ = {mu} 1/hours")

# Настройка графика
plt.title(f"Mean time between failures ($N = {N}$, $\\lambda = {lambd:.1e}$ hours$^{{-1}}$, $m = {m}$)")
plt.xlabel("Number $n$ of elementary machines in base subsystem")
plt.ylabel("Mean time between failures (hours)")
plt.yscale('log')
plt.grid(True, which="both", ls="--")
plt.legend()
plt.show()