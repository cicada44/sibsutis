-- 21 6 2 26 13
SET SQL_SAFE_UPDATES = 0;

UPDATE Comp_Config
SET Comp_ID = 2
WHERE Comp_ID = 8;

UPDATE Comp_Config
SET Comp_ID = 6
WHERE Comp_ID = 9;

UPDATE Comp_Config
SET Comp_ID = 13
WHERE Comp_ID = 11;

UPDATE Comp_Config
SET Comp_ID = 21
WHERE Comp_ID = 12;

SET SQL_SAFE_UPDATES = 1;