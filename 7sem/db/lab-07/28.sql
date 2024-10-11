-- 28. Сотрудники, принятые в 2004 году, сгруппированные по месяцам
SELECT DATE_FORMAT(hire_date, '%M') AS hire_month, COUNT(employee_id) AS number_of_hires
FROM hr.employees
WHERE YEAR(hire_date) = 2004
GROUP BY MONTH(hire_date), hire_month
