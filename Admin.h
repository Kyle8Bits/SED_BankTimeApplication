// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
using std::string;

class Admin {
private:
    const std::string adminUsername = "admin";
    const std::string adminPassword = "rmit1234";

public:
    Admin(std::string adminUsername = "", std::string adminPassword = "");
};

#endif // ADMIN_H