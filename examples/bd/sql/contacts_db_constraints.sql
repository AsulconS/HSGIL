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
