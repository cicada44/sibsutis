-- 9. Третья по величине месячная зарплата сотрудников
SELECT DISTINCT SALARY
FROM HR.EMPLOYEES
ORDER BY SALARY DESC
LIMIT 1 OFFSET 2;
