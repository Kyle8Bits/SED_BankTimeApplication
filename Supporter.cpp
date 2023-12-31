#ifndef SUPPORTER_H
#define SUPPORTER_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>

#include "Member.cpp"
#include "Time.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;


// enum class Day{
//     Monday,
//     Tuesday,
//     Wednesday,
//     Thursday,
//     Friday,
//     Saturday,
//     Sunday
// };

enum class Status{
    OFFLINE,
    ONLINE
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
    std::vector<std::pair<Time, Time>> time_pair_list;
    int cost;//this use for the cost of the supportter per hour
    double skill_rating_score;
    double support_rating_score;
    int support_count;
    Status status; 

public:
    Supporter(string user_name = "", string pass_word = "", string member_id = "S", int credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, std::vector<string> block_list = {}, std::vector<std::pair<Time, Time>> time_pair_list = {}, 
    std::vector<string> skill_list = {}, int cost = 0, double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0, Status status = Status::OFFLINE)
    : Member(user_name, pass_word, member_id, credit_point, full_name, phone_number, address, city, about_me,
            host_rating_score, host_count, block_list), 
            time_pair_list(time_pair_list), skill_list(skill_list), cost(cost), skill_rating_score(skill_rating_score),
            support_rating_score(support_rating_score), support_count(support_count), status(status)
    {
        if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }
    
    //paste the Member to the Supporet (It's like copy constructor)
    Supporter(const Member& member,std::vector<std::pair<Time, Time>> time_pair_list = {},std::vector<string> skill_list = {}, int cost = 0,
              double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0):
              Member(member), time_pair_list(time_pair_list), skill_list(skill_list), cost(cost), 
              skill_rating_score(skill_rating_score), support_rating_score(support_rating_score), support_count(support_count), status(status)
        {
            if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

    // bool addSkill(){
    //     bool check = true;
        
    //     while(check){
    //         string user_input = "";
    //         cout << "> Your skill: ";
    //         getline(cin >> std::ws, user_input);
    //         if(user_input.empty()){
    //             cout << "Please input the non-empty value" << endl;
    //             return false;
    //         }else{
    //             skill_list.push_back(user_input);//if the skill is not empty -> push it to the list

    //             cout << "Do you want to continue adding" << endl;
    //             cout << "1. Yes, 2. No: ";
    //             int choice; cin >> choice;
    //             switch(choice){
    //                 case 1:
    //                     break;
    //                 case 2:
    //                     check = false;
    //                     break;
    //                 default:
    //                     check = false;
    //                     break;
    //             }
    //         }
    //     }

    //     cout << "Your skills are addedd" << endl;
    //     return true;
    // }

    string skillListToString(){
        if(skill_list.empty()){
            return "";//If the skill list have no elements, we return the blank
        }
        string skill_list_str = skill_list[0] + "-";
        for(int i = 1; i < skill_list.size(); ++i){
            skill_list_str += skill_list[i] + "-";
        }
        return skill_list_str;
    }

    string timePairToString(){
        if(time_pair_list.empty()){
            return "Empty";
        }
        string time_pair_str = time_pair_list[0].first.getTime()+"="+ time_pair_list[0].second.getTime()+"-";
        for(int i = 1; i < time_pair_list.size(); ++i){
            time_pair_str += time_pair_list[i].first.getTime()+"="+ time_pair_list[i].second.getTime()+"-"; 
        }
        return time_pair_str;
    }

    string displaySkillList(){
        if(skill_list.empty()){
            return "";//If the skill list have no elements, we return the blank
        }
        string skill_list_str = skill_list[0] + "+";

        for(int i = 1; i < skill_list.size(); i ++){
            skill_list_str += skill_list[i] + "+";
        }
        
        return skill_list_str;
    }

    string statusString(Status status){
        switch (status) {
            case Status::OFFLINE:
                return "OFFLINE";
            case Status::ONLINE:
                return "ONLINE";
            default:
                return "UNKNOWN";
        }
    }
    
    double getSkillRatingScore(){return this->skill_rating_score;}
    double getSupportRatingScore(){return this->support_rating_score;}
    int getSupportCount(){return support_count;}

    int getCost(){
        return this->cost;
    }

    string getAvailabilityPeriod(){
        return "From: " + this->start_time.getTime() + " To: " + this->end_time.getTime();
    }

    Status getStatus() const {
        return status;
    }

    void setStatus(Status status){
        this->status = status;
    }

    string toString() override{
        return Member::toString() + "-" + std::to_string(this->cost) + "-" + std::to_string(this->skill_rating_score) + "-" + std::to_string(this->support_rating_score) + "-" + std::to_string(this->support_count) + "-" + statusString(getStatus());
    }

    std::vector<std::pair<Time, Time>> getPairList(){
        return this->time_pair_list;
    }

    string getPairListToString(){
        string result = "";
        for (int i = 0; i < time_pair_list.size(); i++){
            result += std::to_string(i + 1) + " " +
                  time_pair_list[i].first.getTime() +
                  "->" +
                  time_pair_list[i].second.getTime() +
                  "\n";
        }
        return result;
    }

};



#endif