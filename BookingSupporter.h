#ifndef BOOKING_SUPPORTER_H
#define BOOKING_SUPPORTER_H

#include <iostream>
#include <vector>
#include <fstream>

#include "Time.h"
#include "Member.h"
#include "Supporter.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::to_string;

#define loop(n) for(int i = 0; i < n; ++i)\

namespace bk_colors {
    extern const char* YELLOW;
    extern const char* WHITE_BOLD;
    extern const char* RESET;
}

class BookingSupporter{
    private:
    string booking_id,host_id, support_id, status, progress;//PROGRESS use for appter accepting the invitation
    Time start_time; 
    Time end_time;
    int host_rating;//THIS IS FOR HOST
    int skill_rating_score;//THIS IS FOR SUPPORTER - skill
    int supporter_rating_score;//THIS IS FOR SUPPORTER - character
    string host_comment; //supporter to host
    string supporter_comment; // host to supporter
    double total_cost;
    static int number_of_booking; //the number of the booking
    int day, month, year;
    public:
        //CONSTRUCTOR
    BookingSupporter(string host_id = "", string support_id = "", string status = "PENDING", string booking_id ="BK", string progress = "NOT STARTED", Time start_time = Time(0,0), Time end_time = Time(0,0),
                    int host_rating = 0, int skill_rating_score = 0, int supporter_rating_score = 0, string host_comment = " ", string supporter_comment = " ", double total_cost = 0, int day =0, int month = 0, int year = 0);
                    
    bool isInBlockList(std::vector<string> block_list, string block_id);

    bool isInTheCity(Member* booker, string id_supporter_selected, std::vector<Supporter*>& availableSupporter);

    void displayComment(Supporter* selected_supporter, std::vector<BookingSupporter*> booking_list, std::vector<Member*> member_list);

    void displayAvailableSupporter(std::vector<Member*> member_list, Member* logged_in_member, Supporter* logged_in_supporter, std::vector<Supporter*>& availableSupporter, std::vector<BookingSupporter*> booking_list, bool filterCity);

    void displayAvailableSupporterForGuest(std::vector<Member*> member_list, Member* logged_in_member, Supporter* logged_in_supporter, std::vector<Supporter*>& availableSupporter, std::vector<BookingSupporter*> booking_list);

        // Setter Functions
    void setBookingId (std::string new_booking_id);

    void setHostId(std::string new_host_id) ;

    void setSupportId(std::string new_support_id) ;

    void setStatus(std::string new_status);
    
    void setProgress(string progress);

    void setStartTime(Time time);

    void setEndTime(Time time);

    // Getter Functions
    std::string getBookingId();

    std::string getHostId();

    std::string getSupportId();

    std::string getStatus();

    string getProgress();

    friend class FileProcess; // make friend with System

    string getTimeToFile();
    
    string getStartTimeToString();

    string getEndTimeToString();

    Time getStartTime();

    Time getEndTime();

    string getTime();

    void setHostRating(int host_rating);
    
    int getHostRating();

    void setHostComment(string comment);

    string getHostComment();

    int getSkillRatingScore();

    void setSkillRatingScore(int score);

    int getSupporterRatingScore();

    void setSupporterRatingScore(int score);

    string getSupporterComment();

    void setSupporterComment(string comment);

    double getTotalCost();

    void setTotalCost(double total_cost);

    string toString();

    void setDate(int day, int month, int year);

    string getDate();
};


#endif