import os
import tkinter as tk
from PIL import Image, ImageTk
import time

class SlideShow:
    def __init__(self, root, directory, delay):
        self.root = root
        self.directory = directory
        self.delay = delay  # Временной шаг в миллисекундах
        self.images = []
        self.index = 0

        # Получение списка изображений из директории
        self.load_images()

        # Создание метки для отображения изображений
        self.label = tk.Label(root)
        self.label.pack()

        # Запуск слайд-шоу
        self.show_slides()

    def load_images(self):
        """Загрузка изображений из указанной директории."""
        supported_formats = ['.jpg', '.jpeg', '.png', '.gif', '.bmp']
        for filename in os.listdir(self.directory):
            if any(filename.lower().endswith(fmt) for fmt in supported_formats):
                filepath = os.path.join(self.directory, filename)
                try:
                    img = Image.open(filepath)
                    self.images.append(img)
                except Exception as e:
                    print(f"Не удалось загрузить изображение {filename}: {e}")

        if not self.images:
            raise ValueError("В указанной директории нет изображений!")

    def show_slides(self):
        """Отображение текущего изображения и переход к следующему."""
        if self.images:
            # Отображение текущего изображения
            current_image = self.images[self.index]
            resized_image = current_image.resize((800, 600))  # Масштабирование
            photo = ImageTk.PhotoImage(resized_image)
            self.label.config(image=photo)
            self.label.image = photo  # Сохранение ссылки на изображение

            # Переход к следующему изображению
            self.index = (self.index + 1) % len(self.images)
            self.root.after(self.delay, self.show_slides)

def main():
    # Запрос директории у пользователя
    directory = input("Path: ")
    if not os.path.isdir(directory):
        print("Empty!")
        return

    # Запрос временного шага
    try:
        delay = int(input("Ms: "))
        if delay <= 0:
            raise ValueError
    except ValueError:
        print("Incorrect!")
        return

    # Создание окна Tkinter
    root = tk.Tk()
    root.title("Slide-show")
    slideshow = SlideShow(root, directory, delay)
    root.mainloop()

if __name__ == "__main__":
    main()