import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Данные
data = {
    'n': [65527, 65528, 65529, 65530, 65531, 65532, 65533, 65534, 65535, 65536],
    'mu_1': [195.758894, 127.274931, 82.400717, 52.996366, 33.728518, 21.102635, 12.828979, 7.407215, 3.854244, 1.525879],
    'mu_10': [73271706601.179352, 4801275118.355479, 314617955.855598, 20616599.929261, 1351005.693365, 88532.654092, 5801.621888, 380.097687, 24.809322, 1.525879],
    'mu_100': [68921460816296738816.000000, 451621656290947712.000000, 2959386389343322.500000, 19392563070727.843750, 127079465802.469620, 832764447.340164, 5457271.966310, 35763.130377, 234.360099, 1.525879],
    'mu_1000': [68514678955708481828141662208.000000, 44895613679307099383791616.000000, 29419197731776363495424.000000, 19278106081655734272.000000, 12632942915309006.000000, 8278493821831.144531, 5425062571.321384, 3555206.253864, 2329.867866, 1.525879]
}

# Построение графика
plt.figure(figsize=(12, 8))
plt.plot(data['n'], data['mu_1'], label=r'$\mu = 1 \ 1/\text{hours}$', marker='o')
plt.plot(data['n'], data['mu_10'], label=r'$\mu = 10 \ 1/\text{hours}$', marker='o')
plt.plot(data['n'], data['mu_100'], label=r'$\mu = 100 \ 1/\text{hours}$', marker='o')
plt.plot(data['n'], data['mu_1000'], label=r'$\mu = 1000 \ 1/\text{hours}$', marker='o')

# Настройка графика
plt.xlabel('Number n of elementary machines in base subsystem', fontsize=14)
plt.ylabel('Mean time between failures (hours)', fontsize=14)
plt.title(r'Mean time between failures (N = 65536, $\lambda = 10^{-5} \, \text{hours}^{-1}$, m = 1)', fontsize=16)
plt.yscale('log')  # Логарифмическая шкала для y-оси
plt.ylim(1, 100000)  # Ограничение вертикальной оси до 100,000
plt.xticks(data['n'])  # Метки по горизонтальной оси
plt.yticks([1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144])  # Установка меток по вертикальной оси
plt.legend(fontsize=12)
plt.grid(True)

# Настройка формататера для вертикальной оси
formatter = ScalarFormatter()
formatter.set_scientific(False)
plt.gca().yaxis.set_major_formatter(formatter)

# Сохранение графика в файл
plt.savefig('theta_vs_n_2.1.png')

# Показ графика
# plt.show()
