import matplotlib.pyplot as plt

# Данные
data = {
    'n': [900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000],
    'mu_1': [9.202867, 10.062922, 11.086639, 12.321679, 13.834620, 15.720563, 18.118745, 21.238641, 25.405003, 31.138245, 39.303213],
    'mu_2': [0.907594, 0.915893, 0.924345, 0.932954, 0.941724, 0.950661, 0.959769, 0.969052, 0.978516, 0.988167, 0.998010],
    'mu_4': [0.322447, 0.323489, 0.324539, 0.325595, 0.326658, 0.327728, 0.328805, 0.329889, 0.330981, 0.332079, 0.333185],
    'mu_6': [0.196033, 0.196418, 0.196805, 0.197193, 0.197582, 0.197973, 0.198366, 0.198760, 0.199156, 0.199553, 0.199952]
}

# Построение графика
plt.figure(figsize=(12, 8))
plt.plot(data['n'], data['mu_1'], label=r'$\mu = 1 \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['mu_2'], label=r'$\mu = 2 \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['mu_4'], label=r'$\mu = 4 \, \text{hours}^{-1}$', marker='o')
plt.plot(data['n'], data['mu_6'], label=r'$\mu = 6 \, \text{hours}^{-1}$', marker='o')

# Настройка графика
plt.xlabel('Number n of elementary machines in base subsystem', fontsize=14)
plt.ylabel('Meen time to recovery (hours)', fontsize=14)
plt.title(r'Mean time to recovery ($N = 1000$, $\lambda = 10^{-3} \, \text{hours}^{-1}$, $m = 1$)')
plt.yscale('log')  # Логарифмическая шкала для y-оси
plt.xticks(data['n'])  # Метки по горизонтальной оси
plt.legend()
plt.grid(True)
# Сохранение графика в файл
plt.savefig('theta_vs_n_3.1.png')
#plt.show()
