-- 17. Количество заказов от каждого клиента
SELECT Customers.Cust_ID, Customers.Name, COUNT(DISTINCT Orders.Ord_ID) AS Total_Orders
FROM Customers
JOIN Orders ON Customers.Cust_ID = Orders.Cust_ID
GROUP BY Customers.Cust_ID, Customers.Name;

