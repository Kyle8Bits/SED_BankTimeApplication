#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class Account{
protected:
    string user_name;
    string pass_word;
public:
    //CONSTRUCTOR
    Account(string user_name = "", string pass_word = "");

    //GETTER & SETTER
    string getUsername();
    string getPassword();

    void setUsername(string user_name);

    void setPassword(string pass_word);

    bool setPasswordRequest();
};
#endif // ACCOUNT_H
