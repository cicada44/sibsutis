-- 24. Группировка по комиссионной надбавке и количество записей
SELECT commission_pct, COUNT(*) AS number_of_employees
FROM hr.employees
GROUP BY commission_pct
ORDER BY commission_pct DESC;
