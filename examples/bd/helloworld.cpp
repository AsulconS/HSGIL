#include <iostream>
#include <iomanip>

#include <mysql/jdbc.h>

int main()
{
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");

    stmt = con->createStatement();
    stmt->execute("USE contacts_db");

    res = stmt->executeQuery("SELECT * FROM contact");
    std::cout << std::left << "contact_id " << std::setw(16) << "first_name" << std::setw(16) << "last_name " << std::setw(32) << "home_address" << std::setw(12) << "birthdate" << std::endl;
    while(res->next())
    {
        std::cout << std::setw(11);
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

    delete res;
    delete stmt;
    delete con;

    return EXIT_SUCCESS;
}