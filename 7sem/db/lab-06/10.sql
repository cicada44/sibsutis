-- 10. Список сотрудников с низкой зарплатой (не более 2500$)
SELECT employee_id, first_name, last_name, salary
FROM hr.employees
WHERE salary <= 2500;
