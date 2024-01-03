#ifndef BOOKING_SUPPORTER_H
#define BOOKING_SUPPORTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Time.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::to_string;

class BookingSupporter{
    private:
    string booking_id,host_id, support_id, status, progress;//PROGRESS use for appter accepting the invitation
    Time start_time; 
    Time end_time;
    int host_rating;//THIS IS FOR HOST
    int skill_rating_score;//THIS IS FOR SUPPORTER - skill
    int supporter_rating_score;//THIS IS FOR SUPPORTER - character
    string host_comment;
    string supporter_comment; // supporter to host
    static int number_of_booking; //the number of the booking
    public:
        //CONSTRUCTOR
        BookingSupporter(string host_id = "", string support_id = "", string status = "PENDING", string booking_id ="BK", string progress = "NOT STARTED", Time start_time = Time(0,0), Time end_time = Time(0,0),
                        int host_rating = 11, int skill_rating_score = 11, int supporter_rating_score = 11, string host_comment = " ", string supporter_comment = " ") 
                        : booking_id(booking_id),host_id(host_id), support_id(support_id), status(status), progress(progress), start_time(start_time), end_time(end_time)
                        , host_rating(host_rating), skill_rating_score(skill_rating_score), supporter_rating_score(supporter_rating_score), host_comment(host_comment), supporter_comment(supporter_comment){
            number_of_booking++;//Increse the booking number by 1

            if(booking_id == "BK"){//If the booking id is BK (Default value), we auto generate the id with the number of the booking
                this->booking_id = booking_id + std::to_string(number_of_booking);//AUTO GENERATE THE ID FOR BOOKING
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

    string toString(){
        return this->booking_id + "-" + this->host_id + "-" + this->support_id + "-" + this->status + "-" + this->progress + "-" + this->getTimeToFile() + "-" + to_string(this->host_rating) + "-" + to_string(this->skill_rating_score) + "-" + to_string(this->supporter_rating_score) + "-" + this->host_comment + "-" + this->supporter_comment;
    }

};

int BookingSupporter::number_of_booking = 0;

#endif