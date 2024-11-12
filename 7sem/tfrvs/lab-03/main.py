import matplotlib.pyplot as plt

# Функция для чтения данных из файла
def read_execution_times(filename):
    machines = []
    times = []
    
    with open(filename, 'r') as f:
        for line in f:
            n, time = line.strip().split(',')
            machines.append(int(n))
            times.append(float(time))
    
    return machines, times

# Построение графика
def plot_execution_times():
    # Чтение данных
    machines_small, times_small = read_execution_times('execution_times_small.csv')
    machines_medium, times_medium = read_execution_times('execution_times_medium.csv')
    machines_large, times_large = read_execution_times('execution_times_large.csv')

    # Построение графиков
    plt.plot(machines_small, times_small, label="Малое количество машин")
    plt.plot(machines_medium, times_medium, label="Среднее количество машин")
    plt.plot(machines_large, times_large, label="Большое количество машин")

    plt.xlabel('Количество машин')
    plt.ylabel('Время выполнения (секунды)')
    plt.title('Зависимость времени выполнения от количества машин')
    plt.legend()
    plt.grid(True)
    plt.show()

# Запуск
if __name__ == '__main__':
    plot_execution_times()
