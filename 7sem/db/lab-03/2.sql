SELECT 
    `Студенты`.`Номер`,
    `Студенты`.`ФИО`,
    `Студенты`.`Пол`,
    `Студенты`.`Дата рождения`,
    `Студенты`.`Домашний адрес`,
    `Студенты`.`Средний балл`,
    `Студенты`.`Размер стипендии`,
    `Студенты`.`Военнообязан`,
    `Группы`.`Группа`,
    `Группы`.`Курс`,
    `Группы`.`Кол-во человек`,
    `Факультеты`.`Факультет`,
    `Факультеты`.`Телефон деканата`,
    `Факультеты`.`ФИО декана`
FROM `Студенты`
JOIN `Группы` ON `Студенты`.`Группа` = `Группы`.`Группа`
JOIN `Факультеты` ON `Группы`.`Факультет` = `Факультеты`.`Факультет`;
