import matplotlib.pyplot as plt

# Данные
data = {
    'n': [65527, 65528, 65529, 65530, 65531, 65532, 65533, 65534, 65535, 65536],
    'm_1': [195.758894, 127.274931, 82.400717, 52.996366, 33.728518, 21.102635, 12.828979, 7.407215, 3.854244, 1.525879],
    'm_2': [34613.423871, 11340.069130, 3714.960250, 1216.688151, 398.147873, 129.955141, 42.081102, 13.288504, 3.854244, 1.525879],
    'm_3': [578047.053518, 126258.630920, 27577.918556, 6023.511417, 1315.402344, 286.998770, 62.358678, 13.288504, 3.854244, 1.525879],
    'm_4': [3241253.178324, 530973.742540, 86983.868503, 14249.664798, 2334.201336, 382.156369, 62.358678, 13.288504, 3.854244, 1.525879]
}

# Построение графика
plt.figure(figsize=(12, 8))
plt.plot(data['n'], data['m_1'], label='m = 1', marker='o')
plt.plot(data['n'], data['m_2'], label='m = 2', marker='o')
plt.plot(data['n'], data['m_3'], label='m = 3', marker='o')
plt.plot(data['n'], data['m_4'], label='m = 4', marker='o')

# Настройка графика
plt.xlabel('Number n of elementary machines in base subsystem', fontsize=14)
plt.ylabel('Meen time between failures (hours)', fontsize=14)
plt.title(r'Mean time between failures ($N = 65536$, $\lambda = 10^{-5} \, \text{hours}^{-1}$, $\mu = 1 \, \text{hours}^{-1}$)')
plt.yscale('log')  # Логарифмическая шкала для y-оси
plt.xticks(data['n'])  # Метки по горизонтальной оси
plt.legend()
plt.grid(True)
# Сохранение графика в файл
plt.savefig('theta_vs_n_2.3.png')
#plt.show()
