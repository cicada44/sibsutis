-- 44. Общее количество заказов для компьютеров каждого типа
SELECT Comp_Types.Name, COUNT(DISTINCT Orders.Ord_ID) AS Total_Orders
FROM Order_Items
JOIN Computers ON Order_Items.Comp_ID = Computers.Comp_ID
JOIN Comp_Types ON Computers.Type_ID = Comp_Types.Type_ID
JOIN Orders ON Order_Items.Ord_ID = Orders.Ord_ID
GROUP BY Comp_Types.Name;

