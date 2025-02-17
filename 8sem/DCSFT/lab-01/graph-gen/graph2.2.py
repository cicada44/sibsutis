import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Данные
data = {
    'n': [65527, 65528, 65529, 65530, 65531, 65532, 65533, 65534, 65535, 65536],
    'lambda_1e-05': [195.758894, 127.274931, 82.400717, 52.996366, 33.728518, 21.102635, 12.828979, 7.407215, 3.854244, 1.525879],
    'lambda_1e-06': [732717066011.794556, 48012751183.554840, 3146179558.555983, 206165999.292615, 13510056.933645, 885326.540919, 58016.218879, 3800.976872, 248.093218, 15.258789],
    'lambda_1e-07': [6892146081629683580928.000000, 45162165629094830080.000000, 295938638934332544.000000, 1939256307072786.750000, 12707946580246.970703, 83276444734.016434, 545727196.630956, 3576313.037682, 23436.009861, 152.587891],
    'lambda_1e-08': [68514678955708560711503885369344.000000, 44895613679307152366508179456.000000, 29419197731776384332726272.000000, 19278106081655751966720.000000, 12632942915309012992.000000, 8278493821831148.000000, 5425062571321.388672, 3555206253.864045, 2329867.866407, 1525.878906],
    'lambda_1e-09': [684742647055646799919824531863557113905152.000000, 44869131433615364034630031537034231808.000000, 2940184444581947549682389475131392.000000, 192667346469010465834414374912.000000, 12625491214114255334801408.000000, 827361064752121380864.000000, 54218625295336032.000000, 3553109171478.255859, 232849455.443656, 15258.789062]
}

# Построение графика
plt.figure(figsize=(14, 9))  # Увеличил размер для лучшей читаемости

# Цветовая палитра и маркеры
colors = ['red', 'blue', 'green', 'purple', 'orange']
markers = ['o', 's', '^', 'D', 'x']

# Построение кривых
for i, lambd in enumerate(['lambda_1e-05', 'lambda_1e-06', 'lambda_1e-07', 'lambda_1e-08', 'lambda_1e-09']):
    # Безопасное извлечение экспоненты
    exponent = lambd.split("_")[1].replace('1e-', '')
    plt.plot(
        data['n'], 
        data[lambd], 
        label=rf'$\lambda = 10^{{{exponent}}} \, 1/\text{{hours}}$', 
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
plt.ylabel('Mean time between failures (hours)', fontsize=16)  # Исправил опечатку "Meen" на "Mean", увеличил размер шрифта
plt.title(
    r'Mean time between failures ($N = 65536$, $\mu = 1 \, \text{hours}^{-1}$, $m = 1$)', 
    fontsize=18,  # Увеличил размер шрифта
    pad=20        # Отступ от графика
)

# Логарифмическая шкала для оси Y
plt.yscale('log')

# Метки по горизонтальной оси
plt.xticks(data['n'], fontsize=14)  # Увеличил размер шрифта меток
plt.yticks([1e0, 1e2, 1e4, 1e6, 1e8, 1e10, 1e12, 1e14, 1e16, 1e18, 1e20, 1e22, 1e24], fontsize=14)  # Добавил больше меток и увеличил размер шрифта

# Форматирование оси Y
formatter = ScalarFormatter()
formatter.set_scientific(True)
formatter.set_powerlimits((-3, 3))
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
plt.savefig('theta_vs_n_2.2.png', dpi=300, bbox_inches='tight')  # Добавил bbox_inches для автоматической подгонки размера

# Показ графика
# plt.show()