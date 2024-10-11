-- 18. Список сотрудников с минимальным стажем работы из каждого департамента
SELECT *
FROM HR.EMPLOYEES e
WHERE HIRE_DATE = (
    SELECT MIN(HIRE_DATE)
    FROM HR.EMPLOYEES
    WHERE DEPARTMENT_ID = e.DEPARTMENT_ID
)
ORDER BY DEPARTMENT_ID;
