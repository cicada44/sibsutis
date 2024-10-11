SELECT `Средний балл`, COUNT(*) AS 'Количество'
FROM `lab-02`.`студенты-к`
GROUP BY `Средний балл`
HAVING COUNT(*) > 1
