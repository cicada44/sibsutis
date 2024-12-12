-- Создание таблицы Books
CREATE TABLE Books (
    Id INT AUTO_INCREMENT PRIMARY KEY,
    Title VARCHAR(255) NOT NULL,
    Author VARCHAR(255) NOT NULL,
    ISBN VARCHAR(13) NOT NULL UNIQUE, -- ISBN уникален
    Year INT NOT NULL,
    Copies INT NOT NULL CHECK (Copies >= 0) -- Количество экземпляров не может быть отрицательным
);

-- Создание таблицы Readers
CREATE TABLE Readers (
    Id INT AUTO_INCREMENT PRIMARY KEY,
    FullName VARCHAR(255) NOT NULL,
    BirthDate DATE NOT NULL
);

-- Создание промежуточной таблицы ReaderBooks для связи многие-ко-многим
CREATE TABLE ReaderBooks (
    ReaderId INT NOT NULL,
    BookId INT NOT NULL,
    PRIMARY KEY (ReaderId, BookId),
    FOREIGN KEY (ReaderId) REFERENCES Readers(Id) ON DELETE CASCADE,
    FOREIGN KEY (BookId) REFERENCES Books(Id) ON DELETE CASCADE
);
