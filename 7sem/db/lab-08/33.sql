-- 33. Список сотрудников, у которых отсутствуют данные о карьерном росте
SELECT e.*
FROM HR.EMPLOYEES e
LEFT JOIN HR.JOB_HISTORY j ON e.EMPLOYEE_ID = j.EMPLOYEE_ID
WHERE j.EMPLOYEE_ID IS NULL AND e.DEPARTMENT_ID IN (20, 40, 70, 110);
