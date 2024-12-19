import sqlite3
import requests
from bs4 import BeautifulSoup
from datetime import datetime
import time

# Подключение к базе данных SQLite
db_path = "f1news.db"  # Укажите путь к вашей БД
db_connection = sqlite3.connect(db_path)
cursor = db_connection.cursor()

# Очистка таблицы Posts
cursor.execute("DELETE FROM Posts")
db_connection.commit()
print("Таблица 'Posts' очищена.")

# Функция для парсинга новостей
def get_f1_news():
    url = "https://www.f1news.ru/"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
    }

    response = requests.get(url, headers=headers, timeout=10)
    response.raise_for_status()
    soup = BeautifulSoup(response.content, "html.parser")

    articles = soup.find_all("div", class_="news-item")  # Замените class_
    news_list = []

    for article in articles[:100]:
        try:
            title = article.find("a").text.strip()
            content_url = article.find("a")["href"]

            # Получение полного текста новости
            news_response = requests.get(content_url, headers=headers, timeout=10)
            news_response.raise_for_status()
            news_soup = BeautifulSoup(news_response.content, "html.parser")
            content = news_soup.find("div", class_="news-text").text.strip()

            created_at = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            news_list.append((title, content, created_at))
            time.sleep(1)  # Задержка
        except Exception as e:
            print(f"Ошибка при обработке новости: {e}")
            continue

    return news_list

# Получение новостей
try:
    news_data = get_f1_news()

    # Проверка полученных данных
    for news in news_data:
        print(news)

    # Вставка данных
    cursor.executemany(
        "INSERT INTO Posts (Title, Content, CreatedAt) VALUES (?, ?, ?)", news_data
    )
    db_connection.commit()

    # Проверка вставленных данных
    cursor.execute("SELECT COUNT(*) FROM Posts")
    row_count = cursor.fetchone()[0]
    print(f"Количество записей в таблице после вставки: {row_count}")

except Exception as e:
    print(f"Ошибка при выполнении: {e}")

# Закрытие соединения с БД
db_connection.close()
