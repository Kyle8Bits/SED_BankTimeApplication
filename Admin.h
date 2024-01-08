#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <Member.h>
class Admin {
private:
    const std::string adminUsername;
    const std::string adminPassword;

public:
    Admin(std::string adminUsername, std::string adminPassword);

    // Method to validate admin login
    bool adminLogin(const std::string& uname, const std::string& pwd);
};

#endif // ADMIN_H
