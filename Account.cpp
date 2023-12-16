#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class Account{
protected:
    string user_name;
    string email;
    string pass_word;
public:
    //CONSTRUCTOR
    Account(string user_name = "", string email = "", string pass_word = "")
            : user_name(user_name), email(email), pass_word(pass_word){}

    //GETTER & SETTER
    string getUsername(){return this->user_name;}
    string getPassword(){return this->pass_word;}
    string getEmail(){return this->email;}

    void setUsername(string user_name){
        this->user_name = user_name;
    }

    void setPassword(string pass_word){
        this->pass_word = pass_word;
    }

    void setEmail(string email){
        this->email = email;
    }
};

class Member : public Account{
private:
    //INHERITANCE FROM ACCOUNT 
    // string user_name;
    // string email;
    // string pass_word;


};