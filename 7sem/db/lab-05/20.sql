-- 20. Заказы, содержащие компьютер с максимальной стоимостью
SELECT Orders.Ord_ID, Orders.Rec_Date, Orders.Ex_Date, Orders.Cust_ID
FROM Order_Items
JOIN Computers ON Order_Items.Comp_ID = Computers.Comp_ID
JOIN Orders ON Order_Items.Ord_ID = Orders.Ord_ID
WHERE Computers.Price = (SELECT MAX(Price) FROM Computers);

