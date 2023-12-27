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
    Account(string user_name = "", string pass_word = "")
            : user_name(user_name), pass_word(pass_word){}

    //GETTER & SETTER
    string getUsername(){return this->user_name;}
    string getPassword(){return this->pass_word;}

    void setUsername(string user_name){
        this->user_name = user_name;
    }

    void setPassword(string pass_word){
        this->pass_word = pass_word;
    }
};
#endif // ACCOUNT_H
