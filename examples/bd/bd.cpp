#include <HSGIL/hsgil.hpp>

#include <mysql/jdbc.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

void showExampleTable(sql::Connection* con)
{
    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM contact");

    std::cout << std::left
        << std::setw(4) << "ID "
        << std::setw(16) << "First Name"
        << std::setw(16) << "Last Name"
        << std::setw(32) << "Address"
        << std::setw(12) << "Birthdate"
        << std::endl;
    while(res->next())
    {
        std::cout << std::setw(4);
        std::cout << res->getInt("contact_id");
        std::cout << std::setw(16);
        std::cout << res->getString("first_name");
        std::cout << std::setw(16);
        std::cout << res->getString("last_name");
        std::cout << std::setw(32);
        std::cout << res->getString("home_address");
        std::cout << std::setw(12);
        std::cout << res->getString("birthdate");
        std::cout << std::endl;
    }
    std::cout << std::endl;

    delete res;
    delete stmt;
}

void showFullQueryTable(sql::Connection* con, const char* queryPath = "sql/contacts_db_full_query.sql")
{
    std::ifstream f;
    f.open(queryPath);

    std::string query {};
    std::string chunk {};

    while(f >> chunk)
    {
        query += chunk + ' ';
    }

    f.close();

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::ResultSet* res = stmt->executeQuery(query);

    std::cout << std::left
        << std::setw(4)  << "ID"
        << std::setw(16) << "Name"
        << std::setw(16) << "Last Name"
        << std::setw(32) << "Address"
        << std::setw(12) << "Birthdate"
        << std::setw(64) << "Phones"
        << std::setw(64) << "Emails"
        << std::endl;
    while(res->next())
    {
        std::cout << std::setw(4);
        std::cout << res->getString("ID");
        std::cout << std::setw(16);
        std::cout << res->getString("Nombre");
        std::cout << std::setw(16);
        std::cout << res->getString("Apellidos");
        std::cout << std::setw(32);
        std::cout << res->getString("Direccion");
        std::cout << std::setw(12);
        std::cout << res->getString("Fecha");
        std::cout << std::setw(64);
        std::cout << res->getString("Telefonos");
        std::cout << std::setw(64);
        std::cout << res->getString("Correos");
        std::cout << std::endl;
    }
    std::cout << std::endl;

    delete res;
    delete stmt;
}

void showEmails(sql::Connection* con)
{
    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::ResultSet* res = stmt->executeQuery("SELECT email_id, eaddress, etype, contact_id, CONCAT(c.first_name, ' ', c.last_name) AS name FROM email INNER JOIN contact c USING(contact_id)");

    std::cout << std::left
        << std::setw(4) << "ID "
        << std::setw(32) << "Address"
        << std::setw(16) << "Type"
        << std::setw(12) << "Owner's ID"
        << std::setw(32) << "Owner's Full Name"
        << std::endl;
    while(res->next())
    {
        std::cout << std::setw(4);
        std::cout << res->getInt("email_id");
        std::cout << std::setw(32);
        std::cout << res->getString("eaddress");
        std::cout << std::setw(16);
        std::cout << res->getString("etype");
        std::cout << std::setw(12);
        std::cout << res->getInt("contact_id");
        std::cout << std::setw(32);
        std::cout << res->getString("name");
        std::cout << std::endl;
    }
    std::cout << std::endl;

    delete res;
    delete stmt;
}

void insertContact(sql::Connection* con, const char* first_name, const char* last_name, const char* home_address, const char* birthdate)
{
    if((strcmp(first_name, "") == 0) || (strcmp(last_name, "") == 0) || (strcmp(home_address, "") == 0) || (strcmp(birthdate, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("INSERT INTO contact VALUES (NULL, ?, ?, ?, ?)");

    prep_stmt->setString(1, first_name);
    prep_stmt->setString(2, last_name);
    prep_stmt->setString(3, home_address);
    prep_stmt->setString(4, birthdate);
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void insertPhone(sql::Connection* con, const char* phone_number, const char* phone_type, const char* contact_id)
{
    if((strcmp(phone_number, "") == 0) || (strcmp(phone_type, "") == 0) || (strcmp(contact_id, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("INSERT INTO phone VALUES (?, ?, ?)");

    prep_stmt->setInt(1, std::stoi(phone_number));
    prep_stmt->setString(2, phone_type);
    prep_stmt->setInt(3, std::stoi(contact_id));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void insertEmail(sql::Connection* con, const char* email, const char* email_type, const char* contact_id)
{
    if((strcmp(email, "") == 0) || (strcmp(email_type, "") == 0) || (strcmp(contact_id, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("INSERT INTO email VALUES (NULL, ?, ?, ?)");

    prep_stmt->setString(1, email);
    prep_stmt->setString(2, email_type);
    prep_stmt->setInt(3, std::stoi(contact_id));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void updateContact(sql::Connection* con, const char* contact_id, const char* first_name, const char* last_name, const char* home_address, const char* birthdate)
{
    if((strcmp(contact_id, "") == 0) || (strcmp(first_name, "") == 0) || (strcmp(last_name, "") == 0) || (strcmp(home_address, "") == 0) || (strcmp(birthdate, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("UPDATE contact SET first_name = ?, last_name = ?, home_address = ?, birthdate = ? WHERE contact_id = ?");

    prep_stmt->setString(1, first_name);
    prep_stmt->setString(2, last_name);
    prep_stmt->setString(3, home_address);
    prep_stmt->setString(4, birthdate);
    prep_stmt->setInt(5, std::stoi(contact_id));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void updatePhone(sql::Connection* con, const char* phone_number, const char* new_phone_number, const char* phone_type)
{
    if((strcmp(phone_number, "") == 0) || (strcmp(new_phone_number, "") == 0) || (strcmp(phone_type, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("UPDATE phone SET phone_number = ?, ptype = ? WHERE phone_number = ?");

    prep_stmt->setInt(1, std::stoi(new_phone_number));
    prep_stmt->setString(2, phone_type);
    prep_stmt->setInt(3, std::stoi(phone_number));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void updateEmail(sql::Connection* con, const char* email_id, const char* email, const char* email_type)
{
    if((strcmp(email_id, "") == 0) || (strcmp(email, "") == 0) || (strcmp(email_type, "") == 0))
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("UPDATE email SET eaddress = ?, etype = ? WHERE email_id = ?");

    prep_stmt->setString(1, email);
    prep_stmt->setString(2, email_type);
    prep_stmt->setInt(3, std::stoi(email_id));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

void removeContact(sql::Connection* con, const char* contact_id)
{
    if(strcmp(contact_id, "") == 0)
    {
        return;
    }

    sql::Statement* stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    sql::PreparedStatement* prep_stmt = con->prepareStatement("DELETE FROM contact WHERE contact_id = ?");

    prep_stmt->setInt(1, std::stoi(contact_id));
    prep_stmt->execute();

    delete prep_stmt;
    delete stmt;
}

int main(int argc, char** argv)
{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");

    gil::FormWindow window(1280, 720, "Handy Contact Manager");
    if(!window.isReady())
    {
        delete con;
        return EXIT_FAILURE;
    }

    gil::InputButton button01;
    gil::InputButton button02;
    gil::InputButton button03;
    gil::InputButton button04;
    gil::InputButton button05;
    gil::InputButton button06;
    gil::InputButton button07;
    gil::InputButton button08;
    gil::InputButton button09;
    gil::InputButton button10;

    gil::EventHandler eventHandler;
    eventHandler.addKeyControl(gil::BUTTON_001, button01, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_002, button02, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_003, button03, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_004, button04, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_005, button05, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_006, button06, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_007, button07, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_008, button08, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_009, button09, 1.0f);
    eventHandler.addKeyControl(gil::BUTTON_010, button10, 1.0f);

    window.setEventHandler(eventHandler);

    gil::Tag buttonTag01  = window.addButton( 20, 640, 120, 20, 1, "Show Contacts");
    gil::Tag buttonTag02  = window.addButton(150, 640, 140, 20, 2, "Show Full Contacts");
    gil::Tag buttonTag03  = window.addButton(300, 640, 140, 20, 3, "Show Emails");

    // Create Contact Form
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag01   = window.addLabel(10, 10, 610, 20, "Create Contact Form");

    gil::Tag labelTag02   = window.addLabel(10,  40, 100, 20, "Name");
    gil::Tag labelTag03   = window.addLabel(10,  70, 100, 20, "Last Name");
    gil::Tag labelTag04   = window.addLabel(10, 100, 100, 20, "Address");
    gil::Tag labelTag05   = window.addLabel(10, 130, 100, 20, "Birthdate");

    gil::Tag nameTag01      = window.addTextBox(120,  40, 500, 20);
    gil::Tag lastNameTag01  = window.addTextBox(120,  70, 500, 20);
    gil::Tag addressTag01   = window.addTextBox(120, 100, 500, 20);
    gil::Tag birthdateTag01 = window.addTextBox(120, 130, 500, 20);

    gil::Tag buttonTag04  = window.addButton(120, 160, 120, 20, 4, "Create Contact");

    // -----------------------------------------------------------------------------------
    
    // Add Phone Form (Check your ID at the table shown with Show Contacts and get the ID)
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag06   = window.addLabel(10, 190, 610, 20, "Add Phone Form");
    gil::Tag labelTag07   = window.addLabel(10, 210, 610, 20, "(Check your ID at the table shown with Show Contacts and get it)");

    gil::Tag labelTag08   = window.addLabel(10, 240, 100, 20, "ID");
    gil::Tag labelTag09   = window.addLabel(10, 270, 100, 20, "Phone");
    gil::Tag labelTag10   = window.addLabel(10, 300, 100, 20, "Phone Type");

    gil::Tag idTag01      = window.addTextBox(120, 240, 500, 20);
    gil::Tag phoneTag01     = window.addTextBox(120, 270, 500, 20);
    gil::Tag phoneTypeTag01 = window.addTextBox(120, 300, 500, 20);

    gil::Tag buttonTag05  = window.addButton(120, 330, 120, 20, 5, "Add Phone");

    // -----------------------------------------------------------------------------------

    // Add Email Form (Check your ID at the table shown with Show Contacts and get the ID)
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag11   = window.addLabel(10, 360, 610, 20, "Add Email Form");
    gil::Tag labelTag12   = window.addLabel(10, 380, 610, 20, "(Check your ID at the table shown with Show Contacts and get it)");

    gil::Tag labelTag13   = window.addLabel(10, 410, 100, 20, "ID");
    gil::Tag labelTag14   = window.addLabel(10, 440, 100, 20, "Email");
    gil::Tag labelTag15   = window.addLabel(10, 470, 100, 20, "Email Type");

    gil::Tag idTag02      = window.addTextBox(120, 410, 500, 20);
    gil::Tag emailTag01     = window.addTextBox(120, 440, 500, 20);
    gil::Tag emailTypeTag01 = window.addTextBox(120, 470, 500, 20);

    gil::Tag buttonTag06  = window.addButton(120, 500, 120, 20, 6, "Add Email");

    // -----------------------------------------------------------------------------------

    // Update Contact Form
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag16   = window.addLabel(630, 10, 610, 20, "Update Contact Form");
    gil::Tag labelTag17   = window.addLabel(630, 30, 610, 20, "(Check your ID at the table shown with Show Contacts and get it)");

    gil::Tag labelTag18   = window.addLabel(630,  60, 100, 20, "ID");
    gil::Tag labelTag19   = window.addLabel(630,  90, 100, 20, "New Name");
    gil::Tag labelTag20   = window.addLabel(630, 120, 100, 20, "New L. Name");
    gil::Tag labelTag21   = window.addLabel(630, 150, 100, 20, "New Address");
    gil::Tag labelTag22   = window.addLabel(630, 180, 100, 20, "New Birthdate");

    gil::Tag idTag03        = window.addTextBox(740,  60, 500, 20);
    gil::Tag nameTag02      = window.addTextBox(740,  90, 500, 20);
    gil::Tag lastNameTag02  = window.addTextBox(740, 120, 500, 20);
    gil::Tag addressTag02   = window.addTextBox(740, 150, 500, 20);
    gil::Tag birthdateTag02 = window.addTextBox(740, 180, 500, 20);

    gil::Tag buttonTag07  = window.addButton(740, 210, 120, 20, 7, "Update Contact");

    // -----------------------------------------------------------------------------------

    // Remove Contact Form (Check your ID at the table shown with Show Contacts and get the ID)
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag23   = window.addLabel(630, 240, 610, 20, "Remove Contact Form");
    gil::Tag labelTag24   = window.addLabel(630, 260, 610, 20, "(Check your ID at the table shown with Show Contacts and get it)");

    gil::Tag labelTag25   = window.addLabel(630, 290, 100, 20, "ID");

    gil::Tag idTag04      = window.addTextBox(740, 290, 500, 20);

    gil::Tag buttonTag08  = window.addButton(740, 320, 120, 20, 8, "Remove Contact");

    // -----------------------------------------------------------------------------------

    // Update Phone Form (Check your ID at the table shown with Show Contacts and get the ID)
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag26   = window.addLabel(630, 350, 610, 20, "Update Phone Form");
    gil::Tag labelTag27   = window.addLabel(630, 370, 610, 20, "(Use your last phone to change it)");

    gil::Tag labelTag28   = window.addLabel(630, 400, 100, 20, "Phone");
    gil::Tag labelTag29   = window.addLabel(630, 430, 100, 20, "New Phone");
    gil::Tag labelTag30   = window.addLabel(630, 460, 100, 20, "New P. Type");

    gil::Tag phoneTag02     = window.addTextBox(740, 400, 500, 20);
    gil::Tag phoneTag03     = window.addTextBox(740, 430, 500, 20);
    gil::Tag phoneTypeTag03 = window.addTextBox(740, 460, 500, 20);

    gil::Tag buttonTag09  = window.addButton(740, 490, 120, 20, 9, "Update Phone");

    // -----------------------------------------------------------------------------------

    // Update Email Form (Check your ID at the table shown with Show Contacts and get the ID)
    // -----------------------------------------------------------------------------------

    gil::Tag labelTag31   = window.addLabel(630, 520, 610, 20, "Update Email Form");
    gil::Tag labelTag32   = window.addLabel(630, 540, 610, 20, "(Check your email ID at the table shown with Show Emails and get it)");

    gil::Tag labelTag33   = window.addLabel(630, 570, 100, 20, "ID");
    gil::Tag labelTag34   = window.addLabel(630, 600, 100, 20, "New Email");
    gil::Tag labelTag35   = window.addLabel(630, 630, 100, 20, "New E. Type");

    gil::Tag emailTag02     = window.addTextBox(740, 570, 500, 20);
    gil::Tag emailTag03     = window.addTextBox(740, 600, 500, 20);
    gil::Tag emailTypeTag03 = window.addTextBox(740, 630, 500, 20);

    gil::Tag buttonTag10  = window.addButton(740, 660, 120, 20, 10, "Update Email");

    // -----------------------------------------------------------------------------------

    while(window.isActive())
    {
        window.pollEvents();

        if(button01.isTriggered())
        {
            showExampleTable(con);
        }
        if(button02.isTriggered())
        {
            if(argc > 1)
            {
                showFullQueryTable(con, argv[1]);
            }
            else
            {
                showFullQueryTable(con);
            }
        }
        if(button03.isTriggered())
        {
            showEmails(con);
        }
        if(button04.isTriggered())
        {
            insertContact(con,  window.getTextBoxText(nameTag01).c_str(),
                                window.getTextBoxText(lastNameTag01).c_str(),
                                window.getTextBoxText(addressTag01).c_str(),
                                window.getTextBoxText(birthdateTag01).c_str());

            window.setTextBoxText(nameTag01, "");
            window.setTextBoxText(lastNameTag01, "");
            window.setTextBoxText(addressTag01, "");
            window.setTextBoxText(birthdateTag01, "");
        }
        if(button05.isTriggered())
        {
            insertPhone(con,    window.getTextBoxText(phoneTag01).c_str(),
                                window.getTextBoxText(phoneTypeTag01).c_str(),
                                window.getTextBoxText(idTag01).c_str());

            window.setTextBoxText(idTag01, "");
            window.setTextBoxText(phoneTag01, "");
            window.setTextBoxText(phoneTypeTag01, "");
        }
        if(button06.isTriggered())
        {
            insertEmail(con,    window.getTextBoxText(emailTag01).c_str(),
                                window.getTextBoxText(emailTypeTag01).c_str(),
                                window.getTextBoxText(idTag02).c_str());

            window.setTextBoxText(idTag02, "");
            window.setTextBoxText(emailTag01, "");
            window.setTextBoxText(emailTypeTag01, "");
        }
        if(button07.isTriggered())
        {
            updateContact(con,  window.getTextBoxText(idTag03).c_str(),
                                window.getTextBoxText(nameTag02).c_str(),
                                window.getTextBoxText(lastNameTag02).c_str(),
                                window.getTextBoxText(addressTag02).c_str(),
                                window.getTextBoxText(birthdateTag02).c_str());

            window.setTextBoxText(idTag03, "");
            window.setTextBoxText(nameTag02, "");
            window.setTextBoxText(lastNameTag02, "");
            window.setTextBoxText(addressTag02, "");
            window.setTextBoxText(birthdateTag02, "");
        }
        if(button08.isTriggered())
        {
            removeContact(con, window.getTextBoxText(idTag04).c_str());
            window.setTextBoxText(idTag04, "");
        }
        if(button09.isTriggered())
        {
            updatePhone(con,    window.getTextBoxText(phoneTag02).c_str(),
                                window.getTextBoxText(phoneTag03).c_str(),
                                window.getTextBoxText(phoneTypeTag03).c_str());

            window.setTextBoxText(phoneTag02, "");
            window.setTextBoxText(phoneTag03, "");
            window.setTextBoxText(phoneTypeTag03, "");
        }
        if(button10.isTriggered())
        {
            updateEmail(con,    window.getTextBoxText(emailTag02).c_str(),
                                window.getTextBoxText(emailTag03).c_str(),
                                window.getTextBoxText(emailTypeTag03).c_str());

            window.setTextBoxText(emailTag02, "");
            window.setTextBoxText(emailTag03, "");
            window.setTextBoxText(emailTypeTag03, "");
        }
    }

    delete con;
    return EXIT_SUCCESS;
}
