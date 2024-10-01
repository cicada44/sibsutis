import argparse

import matplotlib.pyplot as plt
import numpy as np


# Функция для загрузки данных из файла
def load_data(filename):
    return np.loadtxt(filename)

# Главная функция
def main(output_file=None):
    # Загрузка данных из файлов
    data_separate = load_data('separate-8.dat')
    data_singlecpu = load_data('single-8.dat')
    data_2x1 = load_data('separate-nodes-8.dat')

    # Извлечение данных для осей X и Y
    x_separate, y_separate = data_separate[:, 0], data_separate[:, 1]
    x_singlecpu, y_singlecpu = data_singlecpu[:, 0], data_singlecpu[:, 1]
    x_2x1, y_2x1 = data_2x1[:, 0], data_2x1[:, 1]

    # Построение графика
    plt.figure(figsize=(10, 6))

    plt.plot(x_separate, y_separate, label="1x8 Separate CPUs", marker='o')
    plt.plot(x_singlecpu, y_singlecpu, label="1x8 Single CPU", marker='s')
    plt.plot(x_2x1, y_2x1, label="2x4 Separate nodes", marker='^')

    # Установка логарифмической шкалы для оси X
    plt.xscale('log', base=2)

    # Настройка осей
    plt.xlabel("Message size (Mb)")
    plt.ylabel("Elapsed time (S)")
    plt.title("Dependence of execution time on message size")
    plt.grid(True, which="both", ls="--")

    # Добавление легенды
    plt.legend()

    # Сохранение в файл или показ графика
    if output_file:
        plt.savefig(output_file)
        print(f"График сохранён в файл: {output_file}")
    else:
        plt.show()

if __name__ == "__main__":
    # Обработка аргументов командной строки
    parser = argparse.ArgumentParser(description='Построение графика зависимости времени выполнения от размера сообщения.')
    parser.add_argument('output_file', nargs='?', help='Имя выходного файла для сохранения графика (например, result.png)')

    args = parser.parse_args()

    # Вызов главной функции с параметром
    main(args.output_file)