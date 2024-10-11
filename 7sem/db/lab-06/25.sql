-- 25. Сотрудники с зарплатой не более 8000 с псевдонимами
SELECT first_name AS "Имя", last_name AS "Фамилия", department_id AS "Департамент", salary AS "Зарплата"
FROM hr.employees
WHERE salary <= 8000;
