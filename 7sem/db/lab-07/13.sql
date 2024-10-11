-- 13. Должности, у которых максимальная зарплата превышает 8000
SELECT job_id, COUNT(employee_id) AS number_of_employees, AVG(salary) AS average_salary
FROM hr.employees
GROUP BY job_id
HAVING MAX(salary) > 8000;
