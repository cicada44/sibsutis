import pandas as pd
import matplotlib.pyplot as plt

# Функция для чтения данных из файла и построения графика
def plot_execution_times(filename, label):
    # Чтение данных из файла
    data = pd.read_csv(filename, header=None, names=['Machines', 'Time'])
    
    # Создание нового графика
    plt.figure(figsize=(10, 6))
    plt.plot(data['Machines'], data['Time'], marker='o', label=label)
    plt.title(label)
    plt.xlabel('Количество машин')
    plt.ylabel('Время выполнения (секунды)')
    plt.grid(True)
    plt.legend()
    
    # Сохранение графика
    plt.savefig(f'{label}.png')
    plt.show()

# Путь к файлам
file_paths = {
    'Малое количество машин': 'small_times.txt',
    'Среднее количество машин': 'medium_times.txt',
    'Большое количество машин': 'large_times.txt',
    'Оптимальные значения': 'optimal_times.txt'
}

# Построение графиков
for label, path in file_paths.items():
    plot_execution_times(path, label)
