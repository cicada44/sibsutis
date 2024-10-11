SET SQL_SAFE_UPDATES = 0;

DELETE `Студенты`
FROM `Студенты`
JOIN `Группы` ON `Студенты`.`Группа` = `Группы`.`Группа`
JOIN `Факультеты` ON `Группы`.`Факультет` = `Факультеты`.`Факультет`
WHERE `Факультеты`.`Факультет` = 'ИТ';

DELETE FROM `Студенты`
WHERE `Группа` IN (SELECT `Группа` FROM `Группы` WHERE `Факультет` = 'ИТ');

SET SQL_SAFE_UPDATES = 1;