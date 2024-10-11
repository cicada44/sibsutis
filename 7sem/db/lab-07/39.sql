-- 39. Департаменты с менее чем 4 сотрудниками, получающими зарплату от 7000 до 10000
SELECT department_id, COUNT(employee_id) AS employee_count
FROM hr.employees
WHERE salary BETWEEN 7000 AND 10000
GROUP BY department_id
HAVING COUNT(employee_id) < 4;
