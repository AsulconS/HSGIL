-- Contacts with phone Format
SELECT
    c.first_name AS Nombre,
    c.last_name AS Apellidos,
    c.birthdate AS Fecha,
    GROUP_CONCAT('(', p.phone_number, ', ', p.ptype, ')' SEPARATOR ', ') AS Teléfonos
FROM
    contact c
        LEFT JOIN
    phone p USING(contact_id)
GROUP BY c.contact_id;

-- Contacts with email Format
SELECT
    c.first_name AS Nombre,
    c.last_name AS Apellidos,
    c.birthdate AS Fecha,
    GROUP_CONCAT('(', e.eaddress, ', ', e.etype, ')' SEPARATOR ', ') AS Teléfonos
FROM
    contact c
        LEFT JOIN
    email e USING(contact_id)
GROUP BY c.contact_id;

-- Example Format
SELECT 
    cp.first_name AS Nombre,
    cp.last_name AS Apellidos,
    cp.birthdate AS Fecha,
    cp.phones AS Teléfonos,
    GROUP_CONCAT('(', e.eaddress, ', ', e.etype, ')' SEPARATOR ', ') AS Correos
FROM
    (
        SELECT
            c.contact_id,
            c.first_name,
            c.last_name,
            c.birthdate,
            GROUP_CONCAT('(', p.phone_number, ', ', p.ptype, ')' SEPARATOR ', ') AS phones
        FROM
            contact c
                LEFT JOIN
            phone p USING(contact_id)
        GROUP BY c.contact_id
    ) cp
        LEFT JOIN
    email e USING(contact_id)
GROUP BY cp.contact_id;
