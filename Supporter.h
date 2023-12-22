#ifndef SUPPORTER_H
#define SUPPORTER_H

#include <iostream>
#include <string>
#include <vector>
#include "Member.h"
#include "Time.h"

class Supporter : public Member {
private:
    Time start_time;
    Time end_time;
    std::vector<std::string> skill_list;
    int cost;
    double skill_rating_score;
    double support_rating_score;
    int support_count;

public:
    Supporter(std::string user_name , std::string pass_word , std::string member_id , int credit_point , std::string full_name , std::string phone_number ,
              std::string address , std::string city , std::string about_me , double host_rating_score ,
              int host_count , std::vector<std::string> block_list , Time start_time , Time end_time ,
              std::vector<std::string> skill_list , int cost , double skill_rating_score , double support_rating_score , int support_count );

    Supporter(const Member& member, Time start_time, Time end_time,  std::vector<std::string> skill_list , int cost ,
              double skill_rating_score , double support_rating_score , int support_count );

    bool addSkill();
    int getCost() const;
    std::string getAvailabilityPeriod() const;
    std::string toString() override;
    std::string skillListToString() const;
    std::string showSkillList() const;
    double getSkillRatingScore() const;
    double getSupportRatingScore() const;
    int getSupportCount() const;
};

#endif 