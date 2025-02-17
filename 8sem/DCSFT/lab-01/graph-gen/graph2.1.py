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
plt.figure(figsize=(14, 9))  # Увеличил размер для лучшей читаемости

# Цветовая палитра и маркеры
colors = ['red', 'blue', 'green', 'purple']
markers = ['o', 's', '^', 'D']

# Построение кривых
for i, mu in enumerate(['mu_1', 'mu_10', 'mu_100', 'mu_1000']):
    plt.plot(
        data['n'], 
        data[mu], 
        label=rf'$\mu = {int(mu.split("_")[1])} \ 1/\text{{hours}}$', 
        color=colors[i], 
        marker=markers[i], 
        linestyle='-', 
        linewidth=2.5,  # Увеличил толщину линий
        markersize=8,   # Увеличил размер маркеров
        markeredgecolor='black',  # Добавил черную границу вокруг маркеров
        markeredgewidth=0.8       # Толщина границы маркеров
    )

# Настройка заголовка и подписей осей
plt.xlabel('Number $n$ of elementary machines in base subsystem', fontsize=16)  # Увеличил размер шрифта
plt.ylabel('Mean time between failures (hours)', fontsize=16)  # Увеличил размер шрифта
plt.title(
    r'Mean time between failures ($N = 65536$, $\lambda = 10^{-5} \, \text{hours}^{-1}$, $m = 1$)', 
    fontsize=18,  # Увеличил размер шрифта
    pad=20        # Отступ от графика
)

# Логарифмическая шкала для оси Y
plt.yscale('log')

# Ограничение вертикальной оси
plt.ylim(1, 1e6)  # Расширил диапазон для лучшей видимости больших значений

# Метки по горизонтальной оси
plt.xticks(data['n'], fontsize=14)  # Увеличил размер шрифта меток
plt.yticks([1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1e6], fontsize=14)  # Добавил больше меток и увеличил размер шрифта

# Форматирование оси Y
formatter = ScalarFormatter()
formatter.set_scientific(False)
plt.gca().yaxis.set_major_formatter(formatter)

# Добавление легенды
plt.legend(
    fontsize=14, 
    loc='upper right', 
    frameon=True, 
    edgecolor='black', 
    fancybox=True, 
    shadow=True  # Стиль легенды
)

# Добавление сетки
plt.grid(
    True, 
    which="both", 
    linestyle="--", 
    alpha=0.7, 
    color='gray', 
    linewidth=0.8  # Настройки сетки
)

# Добавление дополнительных элементов
plt.minorticks_on()  # Включил промежуточные деления
plt.gca().tick_params(which='major', length=8, width=1.5, direction='in')  # Настройка основных делений
plt.gca().tick_params(which='minor', length=4, width=1, direction='in')  # Настройка промежуточных делений

# Добавление рамки вокруг графика
for spine in plt.gca().spines.values():
    spine.set_linewidth(1.5)  # Увеличил толщину рамки

# Сохранение графика в файл
plt.savefig('graphs/theta_vs_n_2.1.png', dpi=300, bbox_inches='tight')  # Добавил bbox_inches для автоматической подгонки размера

# Показ графика
# plt.show()
