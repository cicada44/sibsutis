import sys
import time

import matplotlib.pyplot as plt
import numpy as np

# Отключаем научную нотацию в NumPy
np.set_printoptions(suppress=True, precision=6)

# Генерация матрицы платежей
def generate_payoff_matrix(n, c1, c2, c3):
    matrix = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            matrix[i][j] = i * c1 + j * c2 + abs(i - j) * c3
    return matrix

# Функция для вероятностного выбора стратегии на основе регретов
def probabilistic_choice(regrets):
    exp_regrets = np.exp(regrets - np.max(regrets))  # Экспоненциальное сглаживание
    probabilities = exp_regrets / np.sum(exp_regrets)
    return np.random.choice(len(regrets), p=probabilities)

# Мягкое обновление регретов для сглаживания изменений
def update_regrets(cumulative_payoff, mean_payoff, learning_rate=0.1):
    return (cumulative_payoff - mean_payoff) * learning_rate

# Метод Брауна с мягкими изменениями
def brown_method(matrix, epsilon):
    n = len(matrix)

    # Инициализация стратегий с равномерным распределением
    strategies_dispatcher = np.ones(n) / n
    strategies_vc = np.ones(n) / n

    # Накопленные выигрыши
    dispatcher_cumulative_payoff = np.zeros(n)
    vc_cumulative_payoff = np.zeros(n)

    dispatcher_regret = np.zeros(n)
    vc_regret = np.zeros(n)

    V = 0  # начальная цена игры
    l = 0  # счетчик итераций

    learning_rate = 0.01  # Небольшая скорость обучения для сглаживания изменений

    for _ in range(1500000):  # Ограничим итерации
        l += 1

        # 1. Диспетчер выбирает стратегию на основе вероятностного выбора
        dispatcher_choice = probabilistic_choice(-dispatcher_regret)  # Минимизация регретов
        dispatcher_cumulative_payoff += matrix[dispatcher_choice]  # Накопленный выигрыш диспетчера

        # 2. ВЦ выбирает стратегию на основе вероятностного выбора
        vc_choice = probabilistic_choice(vc_regret)  # Максимизация регретов
        vc_cumulative_payoff += matrix[:, vc_choice]  # Накопленный выигрыш ВЦ

        # 3. Обновляем регреты с мягким изменением
        dispatcher_regret += update_regrets(dispatcher_cumulative_payoff, np.mean(dispatcher_cumulative_payoff), learning_rate)
        vc_regret += update_regrets(vc_cumulative_payoff, np.mean(vc_cumulative_payoff), learning_rate)

        # 4. Обновляем частоты выбора стратегий
        strategies_dispatcher[dispatcher_choice] += 1
        strategies_vc[vc_choice] += 1

        # 5. Нормализуем стратегии для корректного учета вероятностей
        strategies_dispatcher /= np.sum(strategies_dispatcher)
        strategies_vc /= np.sum(strategies_vc)

        # 6. Обновляем цену игры с усреднением
        new_V = np.dot(strategies_dispatcher, np.dot(matrix, strategies_vc))

        # Отладочный вывод для контроля с фиксированным форматом
        print(f"Iteration {l}: V = {V:.6f}, new_V = {new_V:.6f}, abs(new_V - V) = {abs(new_V - V):.6f}, epsilon = {epsilon:.6f}")

        # Проверяем, если разница между V и new_V меньше, чем epsilon
        if abs(new_V - V) < epsilon:
            print(f"Converged after {l} iterations.")
            break
        
        V = new_V

    return strategies_dispatcher, strategies_vc, l, V

def plot_execution_time(c1, c2, c3):
    times = []
    machines = range(5, 501, 5)
    for n in machines:
        start = time.time()
        payoff_matrix = generate_payoff_matrix(n, c1, c2, c3)  # Генерация матрицы платежей
        brown_method(payoff_matrix, 0.01)
        end = time.time()
        times.append(end - start)
    
    plt.figure(figsize=(12, 6))  # Устанавливаем размер графика
    plt.plot(machines, times, color='red')
    plt.xlabel('Number of systems')
    plt.ylabel('Elapsed time (s)')
    plt.grid(True)
    plt.show()

# Основная функция
def main():
    # Аргументы командной строки
    if len(sys.argv) != 5:
        print("Использование: python script.py <n> <c1> <c2> <c3>")
        sys.exit(1)
    n = int(sys.argv[1])
    c1 = float(sys.argv[2])
    c2 = float(sys.argv[3])
    c3 = float(sys.argv[4])

    # Генерация матрицы платежей
    payoff_matrix = generate_payoff_matrix(n, c1, c2, c3)
    print("Матрица платежей:")
    print(payoff_matrix)
    print()

    # Решение методом Брауна
    epsilon = 0.01
    strategies_dispatcher, strategies_vc, iterations, V = brown_method(payoff_matrix, epsilon)
    
    # Вывод результатов с форматированием
    print("\nОптимальные смешанные стратегии диспетчера:")
    print(np.array2string(strategies_dispatcher, formatter={'float_kind': lambda x: f"{x:.6f}"}))
    print("\nОптимальные смешанные стратегии ВЦ:")
    print(np.array2string(strategies_vc, formatter={'float_kind': lambda x: f"{x:.6f}"}))
    print(f"\nКоличество итераций: {iterations}")
    print(f"Цена игры V: {V:.6f}")

    # Построение графика времени работы
    plot_execution_time(c1, c2, c3)

# Запуск программы
if __name__ == "__main__":
    main()