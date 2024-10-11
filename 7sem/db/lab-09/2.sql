-- 2. Список сотрудников с указанием фамилии, имени и телефона начальника
SELECT e.last_name AS employee_last_name,
       e.first_name AS employee_first_name,
       m.last_name AS manager_last_name,
       m.first_name AS manager_first_name,
       e.phone_number AS employee_phone_number
FROM HR.EMPLOYEES e
LEFT JOIN HR.EMPLOYEES m ON e.manager_id = m.employee_id;
