-- 13. Сотрудники из департаментов 20, 60 и 90
SELECT employee_id, first_name, last_name, department_id
FROM hr.employees
WHERE department_id IN (20, 60, 90);
