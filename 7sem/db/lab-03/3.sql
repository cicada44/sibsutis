UPDATE `Студенты`
JOIN `Группы` ON `Студенты`.`Группа` = `Группы`.`Группа`
JOIN `Факультеты` ON `Группы`.`Факультет` = `Факультеты`.`Факультет`
SET `Студенты`.`Размер стипендии` = `Студенты`.`Размер стипендии` * 1.30
-- WHERE `Военнообязан` = TRUE
WHERE `Факультеты`.`Факультет` = 'ИТ'
