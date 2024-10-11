-- 23. Компьютеры указанного типа с ценой из заданного диапазона
SET @TypeName = 'Моноблоки';
SET @MinPrice = 100;
SET @MaxPrice = 200;

SELECT Computers.Comp_ID, Computers.Name, Computers.Price
FROM Computers
JOIN Comp_Types ON Computers.Type_ID = Comp_Types.Type_ID
WHERE Comp_Types.Name = @TypeName
AND Computers.Price BETWEEN @MinPrice AND @MaxPrice;


