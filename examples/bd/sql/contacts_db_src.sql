-- TABLES
-- --------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS contact
(
    contact_id   integer      /*PK*/,
    first_name   varchar(64)  NOT NULL,
    last_name    varchar(64)  NOT NULL,
    home_address varchar(64)  DEFAULT NULL,
    birthdate    date         DEFAULT NULL
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE IF NOT EXISTS phone
(
    phone_number integer      /*PK1*/,
    ptype        varchar(64)  DEFAULT NULL,
    contact_id   integer      /*PK2*/
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE IF NOT EXISTS email
(
    email_id   integer      /*PK*/,
    eaddress   varchar(64)  NOT NULL UNIQUE,
    etype      varchar(64)  NOT NULL,
    contact_id integer      NOT NULL
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
-- --------------------------------------------------------------------

-- CONSTRAINTS
-- --------------------------------------------------------------------
-- contact
ALTER TABLE contact ADD PRIMARY KEY(contact_id);
ALTER TABLE contact MODIFY contact_id integer NOT NULL AUTO_INCREMENT;

-- phone
ALTER TABLE phone ADD PRIMARY KEY(phone_number, contact_id);
ALTER TABLE phone MODIFY phone_number integer NOT NULL;
ALTER TABLE phone MODIFY contact_id integer NOT NULL;
ALTER TABLE phone ADD FOREIGN KEY(contact_id) REFERENCES contact(contact_id) ON DELETE CASCADE ON UPDATE CASCADE;

-- email
ALTER TABLE email ADD PRIMARY KEY(email_id);
ALTER TABLE email MODIFY email_id integer NOT NULL AUTO_INCREMENT;
ALTER TABLE email ADD FOREIGN KEY(contact_id) REFERENCES contact(contact_id) ON DELETE CASCADE ON UPDATE CASCADE;
-- --------------------------------------------------------------------

-- DATA
-- --------------------------------------------------------------------
INSERT INTO contact VALUES
(NULL, 'Antonio', 'Arjona', 'Urbanización Aviar 512-B', '1970-06-10'),
(NULL, 'Carlota', 'Cerezo', 'Calle San Lázaro 360', '1945-05-01'),
(NULL, 'Laura', 'Lopez', 'Manuel Muñoz Nájar 536-A', '1983-03-17'),
(NULL, 'Pedro', 'Perez', 'Pasaje de los Incas 768', '1975-09-30');

INSERT INTO phone VALUES
(611111111, 'Trabajo fijo', 1),
(931111111, 'Particular móvil', 1),
(913333333, 'Particular fijo', 3),
(913333333, 'Particular fijo', 4),
(644444444, 'Trabajo móvil', 4);

INSERT INTO email VALUES
(NULL, 'a@hotmail.com', 'Particular', 1),
(NULL, 'a@gmail.com', 'Trabajo', 1),
(NULL, 'c@hotmail.com', 'Particular', 2),
(NULL, 'l@gmail.com', 'Trabajo', 3);
-- --------------------------------------------------------------------
