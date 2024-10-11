-- 30. Сотрудники, у которых имя и фамилия начинаются с буквы "S"
SELECT employee_id, first_name, last_name
FROM hr.employees
WHERE UPPER(SUBSTR(first_name, 1, 1)) = 'S'
AND UPPER(SUBSTR(last_name, 1, 1)) = 'S';
