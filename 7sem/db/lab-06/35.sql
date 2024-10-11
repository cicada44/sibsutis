-- 35. Разница между максимальной и минимальной зарплатой для каждой должности
SELECT job_id, MAX(salary) - MIN(salary) AS salary_difference
FROM hr.employees
GROUP BY job_id
ORDER BY salary_difference ASC;
