-- 27. Должности и количество сотрудников с комиссионной надбавкой
SELECT job_id, COUNT(*) AS employees_with_commission
FROM hr.employees
WHERE commission_pct IS NOT NULL
GROUP BY job_id;
