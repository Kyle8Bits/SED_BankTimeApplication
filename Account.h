#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account {
protected:
    string user_name;
    string pass_word;

public:
    Account(string user_name, string pass_word);

    string getUsername() const;
    string getPassword() const;

    void setUsername(const string& user_name);
    void setPassword(const string& pass_word);
};

#endif 
