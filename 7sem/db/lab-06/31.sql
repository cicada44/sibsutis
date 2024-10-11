-- 31. Зарплата после повышения на 20%
SELECT employee_id, first_name, last_name, salary, (salary * 1.2) AS increased_salary
FROM hr.employees;
