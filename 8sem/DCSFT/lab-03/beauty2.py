import matplotlib.pyplot as plt
import pandas as pd

# Функция для чтения данных из файла и построения графиков
def process_data(file_path):
    # Открываем файл для чтения
    with open(file_path, 'r') as file:
        while True:
            # Считываем 30 строк
            lines = [file.readline() for _ in range(30)]
            if not lines[0].strip():  # Проверяем, достигнут ли конец файла
                break

            # Создаем DataFrame из считанных строк
            data = []
            for line in lines:
                if line.strip():  # Пропускаем пустые строки
                    values = line.split()
                    data.append({
                        'λ': float(values[0]),
                        'µ': float(values[1]),
                        'm': int(values[2]),
                        'n': int(values[3]),
                        'theta': float(values[4]),
                        'T': float(values[5])
                    })
            df = pd.DataFrame(data)

            # Первый график: theta vs n для каждого λ
            plt.figure(figsize=(12, 6))
            for lambda_value in df['λ'].unique():
                subset = df[df['λ'] == lambda_value]
                plt.plot(subset['n'], subset['theta'], label=f'λ = {lambda_value}', marker='o')
            plt.title(f'График theta vs n при µ = {df["µ"].iloc[0]}, m = {df["m"].iloc[0]}')
            plt.xlabel('n')
            plt.ylabel('theta')
            plt.legend()
            plt.grid(True)
            plt.yscale('log')  # Логарифмическая шкала для theta
            plt.tight_layout()

            # Сохраняем первый график
            mu_val = f"{df['µ'].iloc[0]:.1e}".replace('+', '')
            m_val = f"{df['m'].iloc[0]:.1e}".replace('+', '')
            plt.savefig(f'fi2/theta_vs_n_µ_{mu_val}_m_{m_val}.png')
            plt.close()

            # Второй график: T vs n для каждого λ
            plt.figure(figsize=(12, 6))
            for lambda_value in df['λ'].unique():
                subset = df[df['λ'] == lambda_value]
                plt.plot(subset['n'], subset['T'], label=f'λ = {lambda_value}', marker='o')
            plt.title(f'График T vs n при µ = {df["µ"].iloc[0]}, m = {df["m"].iloc[0]}')
            plt.xlabel('n')
            plt.ylabel('T')
            plt.legend()
            plt.grid(True)
            plt.tight_layout()

            # Сохраняем второй график
            plt.savefig(f'fi2/T_vs_n_µ_{mu_val}_m_{m_val}.png')
            plt.close()

# Запускаем функцию для обработки файла
file_path = 'results2.txt'  # Укажите путь к вашему файлу
process_data(file_path)
print("Графики успешно созданы!")
