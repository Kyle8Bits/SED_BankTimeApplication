#include <iostream>
#include <vector>

#include "Account.cpp"
#include "Skill.cpp"
using std::cout;
using std::cin;
using std::string;
using std::endl;

class Member : public Account{
private:
    //INHERITANCE FROM ACCOUNT 
    // string user_name;
    // string pass_word;

    //ATTRIBUTE OF MEMBER
    string member_id; 
    static int number_of_student;//the number of the student 
    int credit_point;
    string full_name;
    string phone_number;
    string address;
    string city;
    // vector<Skill> skill_list;
    string about_me;
    double skill_rating_score;
    double support_rating_score;
    double host_rating_score;
    int support_count;
    int host_count;
    std::vector<string> block_list;

public:
    //CONSTRUCTOR
    Member(string user_name = "", string pass_word = "", string member_id = "M", int credit_point = 0, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "", double skill_rating_score = 0, double support_rating_score = 0, 
    double host_rating_score = 0, int support_count = 0, int host_count = 0, std::vector<string> block_list = {})
    : Account(user_name, pass_word), 
      credit_point(credit_point), full_name(full_name), phone_number(phone_number), address(address),
      city(city), about_me(about_me), skill_rating_score(skill_rating_score), support_rating_score(support_rating_score),
      host_rating_score(host_rating_score), support_count(support_count), host_count(host_count), block_list(block_list)
    {
        number_of_student++;//Increse the student by 1
        this->member_id = member_id + std::to_string(number_of_student);//AUTO GENERATE THE ID FOR MEMBER
    }

    string getMemberId(){return this->member_id;}
};

int Member::number_of_student = 0;
