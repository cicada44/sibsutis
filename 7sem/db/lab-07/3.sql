-- 3. Сотрудники с минимум 2 позициями в прошлой карьере
SELECT employee_id, COUNT(job_id) AS job_count
FROM hr.job_history
GROUP BY employee_id
HAVING COUNT(job_id) >= 2;

