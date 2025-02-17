-- 24. Средняя зарплата сотрудников, работающих в разных городах
SELECT l.city,
       AVG(e.salary) AS average_salary
FROM HR.EMPLOYEES e
JOIN HR.DEPARTMENTS d ON e.department_id = d.department_id
JOIN HR.LOCATIONS l ON d.location_id = l.location_id
GROUP BY l.city;
