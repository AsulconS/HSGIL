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
