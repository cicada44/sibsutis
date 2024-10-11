-- 27. Список департаментов, которые находятся в Объединенном Королевстве
SELECT d.*
FROM HR.DEPARTMENTS d
JOIN HR.LOCATIONS l ON d.location_id = l.location_id
JOIN HR.COUNTRIES c ON l.country_id = c.country_id
WHERE c.country_name = 'United Kingdom';
