#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>

#include "Account.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

namespace mb_colors {
    const char* RED = "\033[1;91m";
    const char* YELLOW = "\033[1;93m";
    const char* WHITE_BOLD = "\033[1;97m";
    const char* GREEN = "\033[92m";
    const char* RESET = "\033[0m";
}

class Member : public Account{
protected:
    //INHERITANCE FROM ACCOUNT 
    // string user_name;
    // string pass_word;
    static int number_of_member;//the total number of the members in teh program

    //ATTRIBUTE OF MEMBER
    string member_id; 
    double credit_point;
    string full_name;
    string phone_number;
    string address;
    string city;
    string about_me;
    double host_rating_score = 0;
    int host_count = 0;
    int spt_not_comment = 0;
    std::vector<string> block_list;

public:
    //CONSTRUCTOR
    Member(string user_name = "", string pass_word = "", string member_id = "M", double credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, int supporter_not_comment = 0, std::vector<string> block_list = {})
    : Account(user_name, pass_word), 
      member_id(member_id), credit_point(credit_point), full_name(full_name), phone_number(phone_number), address(address),
      city(city), about_me(about_me), host_rating_score(host_rating_score), 
      host_count(host_count),spt_not_comment(supporter_not_comment), block_list(block_list)
    {
        number_of_member++;//Increse the student by 1

        if(member_id == "M"){//If the member id is M (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

    void collectScore(int score){
        
        int person_comment = this->host_count - this->spt_not_comment; //1 - 0 = 1
        if(score != 11){
            if(person_comment == 0){
                this->host_rating_score = score;
                this->host_count++;
            }
            else{
                person_comment++;  //= 2
                this->host_rating_score = static_cast<double>(this->host_rating_score*(person_comment-1) + score)/person_comment; 
                this->host_count++;
            }//                                              
        }
        else{
            this->spt_not_comment++;
            this->host_count++;
        }
    }



    virtual void displayPersonalInformation(){
        int padding = 20;
        cout << "***MY INFORMATION***" << endl;
        cout << std::left << mb_colors::YELLOW << std::setw(padding) << "Username: " << mb_colors::WHITE_BOLD << this->user_name << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Full Name: " << mb_colors::WHITE_BOLD << this->full_name << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Credit Point: " << mb_colors::WHITE_BOLD << this->credit_point << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Phone Number: " << mb_colors::WHITE_BOLD << this->phone_number << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Address: " << mb_colors::WHITE_BOLD << this->address << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "City: " << mb_colors::WHITE_BOLD << this->city << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Host Rating Score: " << mb_colors::WHITE_BOLD << this->host_rating_score << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Hosting Count: " << mb_colors::WHITE_BOLD << this->host_count << mb_colors::RESET << endl;
        cout << mb_colors::YELLOW << std::setw(padding) << "Block List: " << mb_colors::WHITE_BOLD << this->displayBlockList() << mb_colors::RESET << endl;
    }

    void displayUserList(){
        cout << mb_colors::YELLOW <<std::setw(180) << std::setfill('-') << "" << std::setfill(' ') << mb_colors::RESET <<std::endl;
        cout << mb_colors::YELLOW << std::left << std::setw(13) << "| Member id |" << std::setw(25) << " Fullname               |" << std::setw(15) << " Credit Point      |"
                << std::setw(15) << " Phone Number |" << std::setw(35) << " Address                          |"  << std::setw(15) << " City         |"
                << std::setw(15) << " Host Rating  |" << std::setw(16) << " Hosting Count |"  << std::setw(25) << " Block List              |"<< endl;
        cout << std::setw(180) << std::setfill('-') << "" << std::setfill(' ') << mb_colors::RESET <<std::endl;
        cout << mb_colors::WHITE_BOLD << "| " << std::setw(10) << this->member_id
                                <<"| "<<std::setw(23) << this->full_name
                                <<"| " << std::setw(18) << this->credit_point
                                <<"| " << std::setw(13) << this->phone_number
                                <<"| " << std::setw(33) << this->address
                                <<"| " << std::setw(13) << this->city
                                <<"| " << std::setw(13) << std::to_string(this->host_rating_score)
                                <<"| " << std::setw(14) << std::to_string(this->host_count)
                                <<"| " << std::setw(23) << this->displayBlockList() << " |" << endl;
        
        
        cout << mb_colors::YELLOW << std::setw(180) << std::setfill('-') << "" << std::setfill(' ') << mb_colors::RESET << std::endl;
    }


    string getMemberId(){return this->member_id;}
    void setMemberId(string member_id){this->member_id = member_id;}

    //Getter and setter

    double getCreditPoint() const {
        return credit_point;
    }

    void setCreditPoint(double value) {
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

    bool isValidPhone(const string& str) {
        
        // check if all characters in the string are digits
        for (char ch : str) {
            if (!std::isdigit(ch)) {
                cout << "You can not type character!" << endl;
                return false;
            }
        }
        // check if the string length is exactly 10
        if (str.length() != 10) {
            cout << "Your phone number must have 10 numbers" << endl;
            return false;
        }
        // if both conditions are satisfied, return true
        return true;
    }

    bool setCityRequest(){
        cout << "Please choose your current city!" << endl;
        cout << "1. Hanoi" << endl;
        cout << "2. Ho Chi Minh" << endl;
        string input; 
        getline(cin >> std::ws, input);
        if(input == "1"){
            this->city = "Hanoi";
            cout << "Your new city is record!" << endl;
            return true;
        }
        else if(input == "2"){
            this->city = "Ho Chi Minh";
            cout << "Your new city is record!" << endl;
            return true;
        }
        else{
            cout << "Invalid input!" << endl;
            return false;
        }
    }

    void setAddressRequest(){
        cout << "Please enter your new address!" << endl;
        cout << "Enter: ";
        string input;
        getline(cin >> std::ws, input);
        this->address = input;
        cout << "Your new address is record!" << endl;
    }

    bool setPhoneNumberRequest() {
        cout << "Please enter new phone number" << endl;
        cout << "Enter: ";
        string input; 
        getline(cin >> std::ws, input);
        if(isValidPhone(input)){
            this->phone_number = input;
            cout << "Your new phone number is record!" << endl;
            return true;
        }
        return false;
    }

    bool unblockUser(){
        cout << "Your current block list: " << displayBlockList() << endl;
        cout << "Do you want to unblock any user?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        string choice;
        getline(cin >> std::ws, choice);
        if(choice == "1"){
            cout << "Please enter the username you want to unblock!" << endl;
            cout << ">Your choice: ";
            string input;
            getline(cin >> std::ws, input);
            for(int i = 0; i < this->block_list.size(); ++i){
                if(this->block_list[i] == input){
                    this->block_list.erase(this->block_list.begin() + i);
                    cout << "You just unblock this users " << input << endl;
                    return true;
                }
            }
            cout << "Please enter the valid input" << endl;
            return false;
        }else if(choice == "2"){
            cout << "Return dashboard!" << endl;
            return false;
        }else{
            cout << "Please enter valid input!" << endl;
            return false;
        }
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

    bool addInformation(){ //THIS IS SET ABOUT ME
        cout << "In this section you can introduce yourself, so that the another member can know about you and your skills!" << endl;

        string input_from_user;
        getline(cin >> std::ws, input_from_user);
        
        if(!input_from_user.empty()){
            this->setAboutMe(input_from_user);
            cout << "Modify information sucessfully!" << endl;
            return true;
        }else{
            cout << "You can not leave this section empty!" << endl;
        }

        return false;
    }

    void setAboutMe(string value) {
        about_me = value;
    }

    double getAverageRatingScore() const {
        return host_rating_score;
    }

    void setAverageRatingScore(double value) {
        host_rating_score = value;
    }

    int getHostCount() const {
        return host_count;
    }

    void setHostCount(int value) {
        host_count = value;
    }

    void addCreditPoint(double credit_point){
        this->credit_point += credit_point;
    }

    void subtractCreditPoint(double credit_point){
        this->credit_point -= credit_point;
    }

    double getHostRatingScore() {
        return this->host_rating_score;
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
        return this->user_name + "-" + this->pass_word + "-" + this->member_id + "-" + this->full_name + "-" + this->phone_number + "-" + this->address + "-" + this->city +"-"+ std::to_string(this->credit_point) + "-" + std::to_string(this->host_rating_score)+ "-" + std::to_string(this->host_count)+ "-" + std::to_string(this->spt_not_comment) + "-" + this->about_me ;
    }
    
    friend class System;//Make system is friend of Member
    friend class FileProcess;
    friend class BookingSupporter;
};

int Member::number_of_member = 0;

#endif // MEMBER_H
