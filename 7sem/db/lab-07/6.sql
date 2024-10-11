-- 6. Менеджеры и количество сотрудников в подчинении
SELECT manager_id, COUNT(employee_id) AS number_of_employees
FROM hr.employees
WHERE manager_id IS NOT NULL
GROUP BY manager_id;

