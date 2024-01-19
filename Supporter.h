#ifndef SUPPORTER_H
#define SUPPORTER_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>
#include <iomanip>

#include "Member.h"
#include "Time.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

enum class Status{
    OFFLINE,
    ONLINE
};
namespace sp_colors {
    extern const char* RED;
    extern const char* YELLOW;
    extern const char* WHITE_BOLD;
    extern const char* GREEN;
    extern const char* RESET;
}
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
    int min_host_rating;
    Status status = Status::OFFLINE; 
    
public:
    Supporter(string user_name = "", string pass_word = "", string member_id = "S", double credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, int spt_not_comment = 0, std::vector<string> block_list = {}, std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule = {}, Status status = Status::OFFLINE, 
    std::vector<string> skill_list = {}, int cost = 0, double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0, int host_not_comment = 0, int min_host_rating = 0);
    
    //paste the Member to the Supporet (It's like copy constructor)
    Supporter(const Member& member,std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule, Status status = Status::OFFLINE,std::vector<string> skill_list = {}, int cost = 0,
              double skill_rating_score = 0, double support_rating_score = 0, int support_count = 0, int min_host_rating = 0);

    void collectSupporterScore(int score, int skill);

    bool modifySkill();

    void displayPersonalInformation() override;

    string skillListToString();

    string scheduleToString();

    void displayWorkScheduleBySpecificDay(string day);

    void displayWorkSchedule();

    string displaySkillList();

    string statusToString(Status status);
    
    double getSkillRatingScore();
    double getSupportRatingScore();
    int getSupportCount();

    int getCost();

    void setCostRequest();

    int getMinHostRating();

    bool setMinHostRatingRequest();

    string getAvailabilityPeriod();

    Status getStatus() const ;

    void setStatus(Status status);

    string toString() override;

    std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > getWorkSchedule();
    
    string getDayString(int day);

    bool isAvailableInTime(Time start_time_booking, Time end_time_booking, string day);

    bool isOverlap(Time start_time, Time end_time, string day);
    
    void setWorkSchedule();

    void displayUserList();

};
#endif