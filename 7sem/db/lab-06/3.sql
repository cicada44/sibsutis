-- 3. Годовой доход каждого сотрудника
SELECT employee_id, first_name, last_name, salary, (salary * 12) AS annual_income
FROM hr.employees;

