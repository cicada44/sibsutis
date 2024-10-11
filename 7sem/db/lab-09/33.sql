-- 33. Список сотрудников, которые относятся к службам Marketing, Sales и IT
SELECT e.*
FROM HR.EMPLOYEES e
JOIN HR.DEPARTMENTS d ON e.department_id = d.department_id
WHERE d.department_name IN ('Marketing', 'Sales', 'IT');
 