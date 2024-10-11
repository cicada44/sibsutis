-- 16. Количество сотрудников и средняя зарплата по департаментам
SELECT department_id, COUNT(employee_id) AS number_of_employees, AVG(salary) AS average_salary
FROM hr.employees
GROUP BY department_id;
