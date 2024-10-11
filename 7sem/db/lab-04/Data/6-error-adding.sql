-- Error duplicating
SET SQL_SAFE_UPDATES = 0;

INSERT INTO Comp_Config (Comp_ID, Part_ID, Quantity)
VALUES
(26, 115, 1);

SET SQL_SAFE_UPDATES = 1;