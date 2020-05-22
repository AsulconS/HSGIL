SELECT
    cp.contact_id AS ID,
    cp.first_name AS Nombre,
    cp.last_name AS Apellidos,
    cp.home_address AS Direccion,
    cp.birthdate AS Fecha,
    cp.phones AS Telefonos,
    GROUP_CONCAT('(', e.eaddress, ', ', e.etype, ')' SEPARATOR ', ') AS Correos
FROM
    (
        SELECT
            c.contact_id,
            c.first_name,
            c.last_name,
            c.home_address,
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
