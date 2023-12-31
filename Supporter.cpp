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
    // double credit_point;
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
    std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule;
    int cost;//this use for the cost of the supportter per hour
    double skill_rating_score=0;
    double support_rating_score= 0;
    int host_not_comment = 0;
    int support_count = 0;
    Status status = Status::OFFLINE; 
    
public:
    Supporter(string user_name = "", string pass_word = "", string member_id = "S", double credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, int spt_not_comment = 0, std::vector<string> block_list = {}, std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule = {}, Status status = Status::OFFLINE, 
    std::vector<string> skill_list = {}, int cost = 0, double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0, int host_not_comment = 0)
    : Member(user_name, pass_word, member_id, credit_point, full_name, phone_number, address, city, about_me,
            host_rating_score, host_count, spt_not_comment, block_list), 
            workSchedule(workSchedule), status(status), skill_list(skill_list), cost(cost), skill_rating_score(skill_rating_score),
            support_rating_score(support_rating_score), support_count(support_count), host_not_comment(host_not_comment)
    {
        if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }
    
    //paste the Member to the Supporet (It's like copy constructor)
    Supporter(const Member& member,std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule, Status status = Status::OFFLINE,std::vector<string> skill_list = {}, int cost = 0,
              double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0):
              Member(member), workSchedule(workSchedule), status(status), skill_list(skill_list), cost(cost), 
              skill_rating_score(skill_rating_score), support_rating_score(support_rating_score), support_count(support_count) ,host_not_comment(host_not_comment)
        {
            if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

    void collectSupporterScore(int score, int skill){
        int person_comment = this->support_count - this->host_not_comment; //8 - 6 - 2
        if(score != 11 && skill != 11){
            if(support_count == 0){
                this->support_rating_score = score;
                this->skill_rating_score = skill;
                this->support_count++;
            }
            else{
                person_comment++; 
                this->support_rating_score = static_cast<double>(this->support_rating_score*(person_comment-1) + score)/person_comment;
                this->skill_rating_score = static_cast<double>(this->skill_rating_score*(person_comment-1) + skill)/person_comment;
                this->support_count++;
            }//                                                         
        }
        else{
            this->host_not_comment++;
            this->support_count++;
        }
    }

    bool addSkill(){
        bool check = true;
        
        while(check){
            string user_input = "";
            cout << "> Your skill: ";
            getline(cin >> std::ws, user_input);
            if(user_input.empty()){
                cout << "Please input the non-empty value" << endl;
                return false;
            }else{
                skill_list.push_back(user_input);//if the skill is not empty -> push it to the list

                cout << "Do you want to continue adding" << endl;
                cout << "1. Yes, 2. No: ";
                int choice; cin >> choice;
                switch(choice){
                    case 1:
                        break;
                    case 2:
                        check = false;
                        break;
                    default:
                        check = false;
                        break;
                }
            }
        }

        cout << "Your skills are addedd" << endl;
        return true;
    }

    void displayPersonalInformation() override{
        Member::displayPersonalInformation();
        cout << "My Skill List: " << this->displaySkillList() << endl;
        cout << "My cost: " << this->cost << endl;
        cout << "My Skill Rating Score: " << this->skill_rating_score << endl;
        cout << "My Support Rating Score: " << this->support_rating_score << endl;
        cout << "My Support Count: " << this->support_count << endl;
        cout << "Not comment: " << this->host_not_comment << endl;
        cout << "My Current Status: " << statusToString(status) << endl;
        this->displayWorkSchedule();

    }

    string skillListToString(){//THIS USING FOR SAVE TO FILE
        if(skill_list.empty()){
            return "";//If the skill list have no elements, we return the blank
        }
        string skill_list_str = skill_list[0] + "-";
        for(int i = 1; i < skill_list.size(); ++i){
            skill_list_str += skill_list[i] + "-";
        }
        return skill_list_str;
    }

    // string timePairToString(){
    //     if(workSchedule.time.empty()){
    //         return "";
    //     }
    //     string time_pair_str = workSchedule.time[0].first.getTime()+"="+ (workSchedule.time[0]).second.getTime()+"-";
    //     for(int i = 1; i < workSchedule.time.size(); ++i){
    //         time_pair_str += workSchedule.time[i].first.getTime()+"="+ workSchedule.time[i].second.getTime()+"-"; 
    //     }
    //     return time_pair_str;
    // }

    string scheduleToString(){
        string result = "";
        for(int i =0 ; i < workSchedule.size(); i++){
            result += "-" + workSchedule[i].first + "-";
            for(int a  = 0 ; a < workSchedule[i].second.size(); a++){
                result += workSchedule[i].second[a].first.getTime() + "=" + workSchedule[i].second[a].second.getTime() + "-";
            }
        }
        return result;
    }

    // string weekDayToString(){
    //     if(workSchedule.weekday.empty()){
    //         return "";
    //     }
    //     string weekday_str = "Day-" + workSchedule.weekday[0]+"-";
    //     for(int i = 1; i < workSchedule.weekday.size(); ++i){
    //         weekday_str += workSchedule.weekday[i] +"-"; 
    //     }
    //     return weekday_str;
    // }

    // string displayTimePairList(){
    //     if(workSchedule.time.empty()){
    //         return "EMPTY";
    //     }
    //     string time_pair_str = "";
    //     string next_time_pair_str = "";
    //     for(int i = 0; i < workSchedule.time.size(); ++i){
    //         time_pair_str += "From: " + workSchedule.time[i].first.getTime()+" To: " + workSchedule.time[i].second.getTime(); 
    //     }
    //     return time_pair_str;
    // }

    // string displayWeekday(){
    //     if(workSchedule.weekday.empty()){
    //         return "EMPTY";
    //     }
    //     string week_day = "";
    //     for(int i = 0; i < workSchedule.weekday.size(); ++i){
    //         week_day += workSchedule.weekday[i] + (i != workSchedule.weekday.size() -1 ? "-" : ""); 
    //     }
    //     return week_day;
    // }

    void displayWorkSchedule(){
        if(workSchedule.empty()){
            cout << "EMPTY" << endl;
        }
        else{
            cout << "\t\t\t-------------------------------"<< endl;
            cout << "\t\t\t" << std::left << std::setw(30)<< "|> Work Schedule:" <<"|" << endl;

            for(int i =0 ; i < workSchedule.size(); i++){
                cout << "\t\t\t-------------------------------"<< endl;
                cout << "\t\t\t" << "| " << std::left << std::setw(28) << workSchedule[i].first << "|" << endl;
                for(int a  = 0 ; a < workSchedule[i].second.size(); a++){
                    cout << "\t\t\t" <<"| "<< std::left << std::setw(5) << workSchedule[i].second[a].first.getTime() << " to " << std::setw(19)<<workSchedule[i].second[a].second.getTime() << "|" << endl;
                }
            }
            // cout << std::setw(30) << std::setfill('-') << endl;
        }
        
    }

    string displaySkillList(){//THIS USING FOR DISPLAYING
        if(skill_list.empty()){
            return "EMPTY";//If the skill list have no elements, we return the blank
        }
        string skill_list_str;

        for(int i = 0; i < skill_list.size(); i ++){
            skill_list_str += skill_list[i] + ", ";
        }
        
        return skill_list_str;
    }

    string statusToString(Status status){
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
        return Member::toString() + "-" + std::to_string(this->cost) + "-" + std::to_string(this->skill_rating_score) + "-" + std::to_string(this->support_rating_score) + "-" + std::to_string(this->support_count) + "-" + std::to_string(this->host_not_comment) +  "-" + statusToString(getStatus());
    }

    std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > getWorkSchedule(){
        return workSchedule;
    }

    // std::vector<std::pair<Time, Time>> getPairList(){
    //     return this->time_pair_list;
    // }

    // string getPairListToString(){
    //     string result = "";
    //     for (int i = 0; i < time_pair_list.size(); i++){
    //         result += "From: " + time_pair_list[i].first.getTime() + " To: " + time_pair_list[i].second.getTime() + "\n"; 
    //     }
    //     return result;
    // }

};



#endif