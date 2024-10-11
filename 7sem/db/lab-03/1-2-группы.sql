CREATE TABLE `Группы` (
    `Группа` VARCHAR(10) PRIMARY KEY,
    `Курс` TINYINT,
    `Кол-во человек` INT,
    `Факультет` VARCHAR(50),
    FOREIGN KEY (`Факультет`) REFERENCES `Факультеты`(`Факультет`) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT `Курс_ограничение` CHECK (`Курс` BETWEEN 1 AND 6)
);
INSERT INTO Группы (`Группа`, `Курс`, `Кол-во человек`, `Факультет`)
VALUES 
('ИВ-121', 4, 15, 'ИВТ'),
('ИС-242', 3, 13, 'ИВТ'),
('ТП-429', 1, 22, 'ИТ');


