-- 39. Полные данные о расположении рабочего места сотрудника с идентификатором 105
SELECT l.*
FROM HR.LOCATIONS l
JOIN HR.DEPARTMENTS d ON l.LOCATION_ID = d.LOCATION_ID
JOIN HR.EMPLOYEES e ON d.DEPARTMENT_ID = e.DEPARTMENT_ID
WHERE e.EMPLOYEE_ID = 105;
