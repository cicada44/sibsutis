import numpy as np

# Функция для генерации тестовых данных с экстремумами
def generate_test_data(filename, start, end, step, noise_factor):
    machines = list(range(start, end + 1, step))
    # Генерация времени выполнения с экстремумами и небольшим шумом
    times = []
    for machines_count in machines:
        # Простая функция с экстремумами
        time = (machines_count / 10) ** 2 * np.sin(machines_count / 20) + noise_factor * np.random.randn()
        times.append(max(0, time))  # Убедимся, что время не отрицательное

    # Сохранение данных в файл
    with open(filename, 'w') as f:
        for machine_count, time in zip(machines, times):
            f.write(f"{machine_count},{time}\n")

# Параметры для генерации данных
data_params = {
    'small_times.txt': (5, 100, 5, 0.5),   # Небольшое количество машин
    'medium_times.txt': (100, 500, 20, 2),  # Среднее количество машин
    'large_times.txt': (500, 1000, 20, 5),  # Большое количество машин
    'optimal_times.txt': (5, 500, 20, 1)    # Оптимальные значения
}

# Генерация всех файлов с тестовыми данными
for filename, (start, end, step, noise) in data_params.items():
    generate_test_data(filename, start, end, step, noise)
