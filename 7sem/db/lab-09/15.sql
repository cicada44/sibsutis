-- 15. Список сотрудников, которые являются руководителями департаментов
SELECT e.first_name,
       e.last_name,
       e.salary,
       d.department_id,
       e.phone_number,
       e.email
FROM HR.EMPLOYEES e
JOIN HR.DEPARTMENTS d ON e.employee_id = d.manager_id;
