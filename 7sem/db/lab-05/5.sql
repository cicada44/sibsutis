-- 5. Общая стоимость заказа с заданным номером
SET @OrderID = 2;

SELECT SUM(Order_Items.Quantity * Computers.Price) AS Total_Order_Cost
FROM Order_Items
JOIN Computers ON Order_Items.Comp_ID = Computers.Comp_ID
WHERE Order_Items.Ord_ID = @OrderID;

