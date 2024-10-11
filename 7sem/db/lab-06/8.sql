-- 8. Неповторяющиеся значения зарплат, отсортированные по убыванию
SELECT DISTINCT salary
FROM hr.employees
ORDER BY salary DESC;
