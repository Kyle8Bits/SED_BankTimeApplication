#ifndef BOOKING_SUPPORTER_H
#define BOOKING_SUPPORTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Time.cpp"
#include "Member.cpp"
#include "Supporter.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::to_string;

#define loop(n) for(int i = 0; i < n; ++i)

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
    public:
        //CONSTRUCTOR
        BookingSupporter(string host_id = "", string support_id = "", string status = "PENDING", string booking_id ="BK", string progress = "NOT STARTED", Time start_time = Time(0,0), Time end_time = Time(0,0),
                        int host_rating = 0, int skill_rating_score = 0, int supporter_rating_score = 0, string host_comment = " ", string supporter_comment = " ", double total_cost = 0) 
                        : booking_id(booking_id),host_id(host_id), support_id(support_id), status(status), progress(progress), start_time(start_time), end_time(end_time)
                        , host_rating(host_rating), skill_rating_score(skill_rating_score), supporter_rating_score(supporter_rating_score), host_comment(host_comment), supporter_comment(supporter_comment), total_cost(total_cost){
            number_of_booking++;//Increse the booking number by 1

            if(booking_id == "BK"){//If the booking id is BK (Default value), we auto generate the id with the number of the booking
                this->booking_id = booking_id + std::to_string(number_of_booking);//AUTO GENERATE THE ID FOR BOOKING
            }
        }

    bool isInBlockList(std::vector<string> block_list, string block_id){
        loop(block_list.size()){
            if(block_list[i] == block_id){
                return true;
            }
        }
        return false;
    }

    void displayAvailableSupporter(std::vector<Member*> member_list, Member* logged_in_member, Supporter* logged_in_supporter, std::vector<Supporter*>& availableSupporter) {
        bool isSupporter = (logged_in_member == nullptr);
        if (isSupporter) {
            logged_in_member = logged_in_supporter;
        }

        cout << std::left << std::setw(13) << "| Member id |" << std::setw(25) << " Fullname               |" << std::setw(15) << " City         |"
                << std::setw(16) << " Cost Per Hour |" << std::setw(40) << " Introduction                          |"  << std::setw(40) << " Skill                                 |" << endl;
        cout << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

        for (size_t i = 0; i < member_list.size(); ++i) {
            if (Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])) {
                if (supporter->getMemberId() != logged_in_member->getMemberId() && supporter->getStatus() == Status::ONLINE) {
                    if (!isInBlockList(logged_in_member->block_list, supporter->getMemberId())) {
                        cout <<"| "<< std::setw(10) << supporter->getMemberId() <<"| "<<std::setw(23) << supporter->getFullName()
                                <<"| " << std::setw(13) << supporter->getCity() <<"| "<< std::setw(14) << supporter->getCost() 
                                <<"| " << std::setw(38) << supporter->getAboutMe() << "| " <<std::setw(38) << supporter->displaySkillList() <<"|"<< endl;

                        supporter->displayWorkSchedule();

                        cout << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << endl;

                        availableSupporter.push_back(supporter);
                    }
                }
            }
        }

        if (isSupporter) {
            logged_in_member = nullptr;
        }
    }

        // Setter Functions
    void setBookingId (std::string new_booking_id){
        booking_id = new_booking_id;
    }

    void setHostId(std::string new_host_id) {
        host_id = new_host_id;
    }

    void setSupportId(std::string new_support_id) {
        support_id = new_support_id;
    }

    void setStatus(std::string new_status) {
        status = new_status;
    }
    
    void setProgress(string progress){
        this->progress = progress;
    }

    void setStartTime(Time time){
        this->start_time = time;
    }

    void setEndTime(Time time){
        this->end_time = time;
    }

    // Getter Functions
    std::string getBookingId() const { 
        return booking_id;
    }

    std::string getHostId() const {
        return host_id;
    }

    std::string getSupportId() const {
        return support_id;
    }

    std::string getStatus() const {
        return status;
    }

    string getProgress(){return this->progress;}

    friend class FileProcess; // make friend with System

    string getTimeToFile(){
        return start_time.getHour() + "-" + start_time.getMinute() + "-" + end_time.getHour() + "-" + end_time.getMinute();
    }
    
    string getTime(){
        return start_time.getTime() + " To " + end_time.getTime();
    }

    void setHostRating(int host_rating){
        this->host_rating = host_rating;
    }
    
    int getHostRating(){
        return host_rating;
    }

    void setHostComment(string comment){
        this->host_comment = comment;
    }

    string getHostComment(){
        return host_comment;
    }

    int getSkillRatingScore(){
        return skill_rating_score;
    }

    void setSkillRatingScore(int score) {
        skill_rating_score = score;
    }

    int getSupporterRatingScore(){
        return supporter_rating_score;
    }

    void setSupporterRatingScore(int score){
        supporter_rating_score = score;
    }

    string getSupporterComment(){
        return supporter_comment;
    }

    void setSupporterComment(string comment) {
        supporter_comment = comment;
    }

    double getTotalCost(){
        return this->total_cost;
    }

    void setTotalCost(double total_cost){
        this->total_cost = total_cost;
    }

    string toString(){
        return this->booking_id + "-" + this->host_id + "-" + this->support_id + "-" + this->status + "-" + this->progress + "-" + this->getTimeToFile() + "-" + to_string(this->host_rating) + "-" + to_string(this->skill_rating_score) + "-" + to_string(this->supporter_rating_score) + "-" + this->host_comment + "-" + this->supporter_comment + "-" + to_string(this->total_cost);
    }

};

int BookingSupporter::number_of_booking = 0;

#endif