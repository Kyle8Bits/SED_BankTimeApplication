#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>

#include "Account.cpp"
#include "Category.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

class Member : public Account{
protected:
    //INHERITANCE FROM ACCOUNT 
    // string user_name;
    // string pass_word;
    static int number_of_member;//the total number of the members in teh program

    //ATTRIBUTE OF MEMBER
    string member_id; 
    int credit_point;
    string full_name;
    string phone_number;
    string address;
    string city;
    string about_me;
    double host_rating_score;
    int host_count;
    std::vector<string> block_list;

public:
    //CONSTRUCTOR
    Member(string user_name = "", string pass_word = "", string member_id = "M", int credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, std::vector<string> block_list = {})
    : Account(user_name, pass_word), 
      member_id(member_id), credit_point(credit_point), full_name(full_name), phone_number(phone_number), address(address),
      city(city), about_me(about_me), host_rating_score(host_rating_score), 
      host_count(host_count), block_list(block_list)
    {
        number_of_member++;//Increse the student by 1

        if(member_id == "M"){//If the member id is M (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

    virtual void displayPersonalInformation(){
        cout << "***MY INFORMATION***" << endl;
        cout << "ID: " << this->member_id << endl;
        cout << "Username: " << this->user_name << endl;
        cout << "Password: " << this->pass_word << endl;
        cout << "Credit Point: " << this->credit_point << endl;
        cout << "Full Name: " << this->full_name << endl;
        cout << "Phone Number: " << this->phone_number << endl;
        cout << "Address: " << this->address << endl;
        cout << "City: " << this->city << endl;
        cout << "About Me: " << this->about_me << endl;
        cout << "Host Rating Score: " << this->host_rating_score << endl;
        cout << "Host Count: " << this->host_count << endl;
        cout << "Block List: " << this->displayBlockList() << endl;
    }

    string getMemberId(){return this->member_id;}
    void setMemberId(string member_id){this->member_id = member_id;}

    //Getter and setter

    int getCreditPoint() const {
        return credit_point;
    }

    void setCreditPoint(int value) {
        credit_point = value;
    }

    string getFullName() const {
        return full_name;
    }

    void setFullName(string value) {
        full_name = value;
    }

    string getPhoneNumber() const {
        return phone_number;
    }

    void setPhoneNumber(string value) {
        phone_number = value;
    }

    string getAddress() const {
        return address;
    }

    void setAddress(string value) {
        address = value;
    }

    string getCity() const {
        return city;
    }

    void setCity(string value) {
        city = value;
    }

    string getAboutMe() const {
        return about_me;
    }

    void setAboutMe(string value) {
        about_me = value;
    }

    double getHostRatingScore() const {
        return host_rating_score;
    }

    void setHostRatingScore(double value) {
        host_rating_score = value;
    }

    int getHostCount() const {
        return host_count;
    }

    void setHostCount(int value) {
        host_count = value;
    }

    string displayBlockList(){//THIS USE FOR PRINTING OUT
        if(block_list.empty()){
            return "EMPTY";
        }
        string block_string;
        for(int i = 0; i < block_list.size(); ++i){
            block_string += block_list[i] + ", ";
        } 

        return block_string;
    }

    string blockListToString(){
        if(block_list.empty()){
            return "";
        }
        string block_string = block_list[0] + "-";
        for(int i = 1; i < block_list.size(); ++i){
            block_string += block_list[i] + "-";
        } 

        return block_string;
    }

    const std::vector<string>& getBlockList() const {
        return block_list;
    }

    void setBlockList(const std::vector<string>& value) {
        block_list = value;
    }

    virtual ~Member() = default;

    virtual string toString(){
        return this->user_name + "-" + this->pass_word + "-" + this->member_id + "-" + this->full_name + "-" + this->phone_number + "-" + this->address + "-" + this->city +"-"+ std::to_string(this->credit_point) + "-" + this->about_me;
    }
    
    friend class System;//Make system is friend of Member
    friend class FileProcess;
};

int Member::number_of_member = 0;

#endif // MEMBER_H
