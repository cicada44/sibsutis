-- Adding last value into Order_Items
SET SQL_SAFE_UPDATES = 0;

INSERT INTO Order_Items (Ord_ID, Comp_ID, Quantity)
VALUES
(2, 26, 1);

SET SQL_SAFE_UPDATES = 1;