-- 15. Клиенты, заказывавшие компьютер с минимальной стоимостью
SELECT Customers.Cust_ID, Customers.Name, Customers.Address
FROM Order_Items
JOIN Computers ON Order_Items.Comp_ID = Computers.Comp_ID
JOIN Orders ON Order_Items.Ord_ID = Orders.Ord_ID
JOIN Customers ON Orders.Cust_ID = Customers.Cust_ID
WHERE Computers.Price = (SELECT MAX(Price) FROM Computers);


