-- Removing from Computers
-- 21 6 2 26 13
SET SQL_SAFE_UPDATES = 0;

DELETE FROM Computers WHERE Comp_ID NOT IN (2, 6, 13, 21, 26);

DELETE FROM Comp_Parts
WHERE Part_ID NOT IN (
    SELECT Part_ID FROM Comp_Config WHERE Comp_ID IN (2, 6, 13, 21, 26)
);

SET SQL_SAFE_UPDATES = 1;