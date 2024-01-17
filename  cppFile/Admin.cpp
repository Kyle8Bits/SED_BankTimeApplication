#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Member.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Admin {
private:
    const string adminUsername = "admin";
    const string adminPassword = "admin";

public:
    Admin(string adminUsername = "", string adminPassword = ""){}

    // Method to validate admin login
    bool adminLogin(const string& uname, const string& pwd) {
        return (uname == adminUsername && pwd == adminPassword);
    }
};

