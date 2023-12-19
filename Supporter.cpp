#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "Member.cpp"
#include "Time.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

enum class Day{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

class Supporter : public Member{
private:
    //SUPPORTER INHERITED THESE ATTRIBUTES FROM MEMBER CLASS
    // static int number_of_member;//the total number of the members in teh program
    // //ATTRIBUTE OF MEMBER
    // string member_id; 
    // int credit_point;
    // string full_name;
    // string phone_number;
    // string address;
    // string city;
    // string about_me;
    // double skill_rating_score;
    // double support_rating_score;
    // double host_rating_score;
    // int support_count;
    // int host_count;
    // std::vector<Category> category_list;//this is skill list of a member
    // std::vector<string> block_list;

    Time start_time; // (start time, end time, day)
    Time end_time;
    std::vector<string> skill_list;
    int cost;//this use for the cost of the supportter per hour
    double skill_rating_score;
    double support_rating_score;
    int support_count;

public:
    Supporter(string user_name = "", string pass_word = "", string member_id = "S", int credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, std::vector<string> block_list = {}, Time start_time = Time(0,0), Time end_time = Time(0,0), 
    std::vector<string> skill_list = {}, int cost = 0, double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0)
    : Member(user_name, pass_word, member_id, credit_point, full_name, phone_number, address, city, about_me,
            host_rating_score, host_count, block_list), 
            start_time(start_time), end_time(end_time), skill_list(skill_list), cost(cost), skill_rating_score(skill_rating_score),
            support_rating_score(support_rating_score), support_count(support_count)
    {
        if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }
    
    //paste the Member to the Supporet (It's like copy constructor)
    Supporter(const Member& member, Time start_time = Time(0,0), Time end_time = Time(0,0),std::vector<string> skill_list = {}, int cost = 0,
              double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0):
              Member(member), start_time(start_time), end_time(end_time), skill_list(skill_list), cost(cost), 
              skill_rating_score(skill_rating_score), support_rating_score(support_rating_score), support_count(support_count)
        {
            if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

    void addSkill(){
        bool check = true;
        while(check){
            string user_input;

            cout << "> Your skill: ";
            getline(cin >> std::ws, user_input);
            if(user_input.empty()){
                cout << "Please input the non-empty value" << endl;
            }else{
                skill_list.push_back(user_input);//if the skill is not empty -> push it to the list

                cout << "Do you want to continue adding" << endl;
                cout << "[Y/N]: ";
                char choice;
                cin >> choice;
                choice = toupper(choice);
                if(choice != 'Y'){
                    check = false;//If the choice of users is not 'Y', we will break the loop
                }
            }
        }

        cout << "Your skills are addedd" << endl;
    }

    int getCost(){
        return this->cost;
    }

    string getAvailabilityPeriod(){
        return "From: " + this->start_time.getTime() + " To: " + this->end_time.getTime();
    }

    string toString() override{
        return Member::toString() + "-" + this->start_time.getHour() + "-" + this->start_time.getMinute() + "-" +this->end_time.getHour() + "-" + this->end_time.getMinute() + "-" + std::to_string(this->cost) + "-" + std::to_string(this->skill_rating_score) + "-" + std::to_string(this->support_rating_score) + "-" + std::to_string(this->support_count);
    }
};