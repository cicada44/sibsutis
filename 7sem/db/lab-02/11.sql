SELECT `ФИО`, `Группа`, (`Размер стипендии` * 1.12) AS `К-Выдаче`
FROM `lab-02`.`студенты-к`
WHERE `Размер стипендии` != 0