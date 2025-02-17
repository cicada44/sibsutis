import matplotlib.pyplot as plt

# Данные
data = {
    'n': [8092, 8102, 8112, 8122, 8132, 8142, 8152, 8162, 8172, 8182, 8192],
    'lambda_1e-05': [1.088032, 1.088150, 1.088268, 1.088387, 1.088505, 1.088624, 1.088742, 1.088861, 1.088980, 1.089098, 1.089217],
    'lambda_1e-06': [1.008157, 1.008167, 1.008177, 1.008187, 1.008198, 1.008208, 1.008218, 1.008228, 1.008238, 1.008248, 1.008259],
    'lambda_1e-07': [1.000810, 1.000811, 1.000812, 1.000813, 1.000814, 1.000815, 1.000816, 1.000817, 1.000818, 1.000819, 1.000820],
    'lambda_1e-08': [1.000081, 1.000081, 1.000081, 1.000081, 1.000081, 1.000081, 1.000082, 1.000082, 1.000082, 1.000082, 1.000082],
    'lambda_1e-09': [1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008, 1.000008]
}

# Построение графика
plt.figure(figsize=(12, 8))
plt.plot(data['n'], data['lambda_1e-05'], label=r'$\lambda = 10^{-5} \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['lambda_1e-06'], label=r'$\lambda = 10^{-6} \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['lambda_1e-07'], label=r'$\lambda = 10^{-7} \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['lambda_1e-08'], label=r'$\lambda = 10^{-8} \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['lambda_1e-09'], label=r'$\lambda = 10^{-9} \, \text{hours}^{-1}$', marker='o')

# Настройка графика
plt.xlabel('Number n of elementary machines in base subsystem', fontsize=14)
plt.ylabel('Mean time to recovery (hours)', fontsize=14)
plt.title(r'Mean time to recovery ($N = 8192$, $\mu = 1 \, \text{hours}^{-1}$, $m = 1$)')
plt.xticks(data['n'])  # Метки по горизонтальной оси
plt.legend()
plt.grid(True)

# Сохранение графика в файл
plt.savefig('theta_vs_n_3.2.png')
#plt.show()
