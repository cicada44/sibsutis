-- 5. Полные данные о департаментах, в которых работает более 5 сотрудников
SELECT d.*
FROM HR.DEPARTMENTS d
JOIN HR.EMPLOYEES e ON d.department_id = e.department_id
GROUP BY d.department_id
HAVING COUNT(e.employee_id) > 5;
