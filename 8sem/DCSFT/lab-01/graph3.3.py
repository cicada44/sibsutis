import matplotlib.pyplot as plt

# Данные
data = {
    'n': [8092, 8102, 8112, 8122, 8132, 8142, 8152, 8162, 8172, 8182, 8192],
    'm_1': [1.088032, 1.088150, 1.088268, 1.088387, 1.088505, 1.088624, 1.088742, 1.088861, 1.088980, 1.089098, 1.089217],
    'm_2': [0.521080, 0.521107, 0.521134, 0.521162, 0.521189, 0.521216, 0.521243, 0.521270, 0.521297, 0.521325, 1.042704],
    'm_3': [0.342572, 0.342584, 0.342596, 0.342608, 0.342619, 0.342631, 0.342643, 0.342655, 0.342666, 0.342678, 1.042104],
    'm_4': [0.255161, 0.255168, 0.255174, 0.255181, 0.255187, 0.255194, 0.255200, 0.255207, 0.255213, 0.255220, 1.042096]
}

# Построение графика
plt.figure(figsize=(12, 8))
plt.plot(data['n'], data['m_1'], label='m = 1', marker='o')
plt.plot(data['n'], data['m_2'], label='m = 2', marker='o')
plt.plot(data['n'], data['m_3'], label='m = 3', marker='o')
plt.plot(data['n'], data['m_4'], label='m = 4', marker='o')

# Настройка графика
plt.xlabel('Number n of elementary machines in base subsystem', fontsize=14)
plt.ylabel('Mean time to recovery (hours)', fontsize=14)
plt.title(r'Mean time to recovery (N = 8192, $\lambda = 10^{-5} \, \text{hours}^{-1}$, u = 1 hours$^{-1}$)')
plt.xticks(data['n'])  # Метки по горизонтальной оси
plt.legend()
plt.grid(True)

# Сохранение графика в файл
plt.savefig('theta_vs_n_3.3.png')
#plt.show()
