-- 14. Сотрудники-клерки с зарплатой в диапазоне [2500, 3000]
SELECT employee_id, first_name, last_name, salary, job_id
FROM hr.employees
WHERE job_id LIKE '%CLERK%'
AND salary BETWEEN 2500 AND 3000;
