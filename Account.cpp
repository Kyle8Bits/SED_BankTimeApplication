#include "Account.h"

//CONSTRUCTOR
Account::Account(string user_name, string pass_word)
        : user_name(user_name), pass_word(pass_word){}

//GETTER & SETTER
string Account::getUsername(){return this->user_name;}
string Account::getPassword(){return this->pass_word;}

void Account::setUsername(string user_name){
    this->user_name = user_name;
}

void Account::setPassword(string pass_word){
    this->pass_word = pass_word;
}

bool Account::setPasswordRequest(){
    cout << "Please enter your old password!" << endl;
    cout << "Password: ";
    string input;
    getline(cin >> std::ws, input);
    if(input == this->pass_word){
        cout << "Please enter new password: ";
        getline(cin >> std::ws, input);
        this->pass_word = input;
        cout << "Your new password is record!" << endl;
        return true;
    }

    return false;
}