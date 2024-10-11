-- Add last value
SET SQL_SAFE_UPDATES = 0;

INSERT INTO Comp_Config (Comp_ID, Part_ID, Quantity)
VALUES
(26, 112, 1),
(26, 118, 1),
(26, 119, 1);

SET SQL_SAFE_UPDATES = 1;