#ifndef BOOKING_SUPPORTER_H
#define BOOKING_SUPPORTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class BookingSupporter{
    private:
    string booking_id,host_id, support_id, status, progress;//PROGRESS use for appter accepting the invitation
    Time start_time; 
    Time end_time;
    static int number_of_booking; //the number of the booking
    string host_comment; //from host to supporter
    string supporter_comment; //from supporter to host
    float host_rating_score;
    float supporter_rating_score;
    public:
        //CONSTRUCTOR
        BookingSupporter(string host_id = "", string support_id = "", string status = "PENDING", string booking_id ="BK", string progress = "NOT STARTED", Time start_time = Time(0,0), Time end_time = Time(0,0), string host_comment = "NON", string supporter_comment = "NON", float host_rating_score = 0.0, float supporter_rating_score = 0.0) 
                        : booking_id(booking_id),host_id(host_id), support_id(support_id), status(status), progress(progress), start_time(start_time), end_time(end_time), host_comment(host_comment), supporter_comment(supporter_comment), host_rating_score(host_rating_score), supporter_rating_score(supporter_rating_score) {
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

    std::string getHostComment() const {
        return host_comment;
    }

    std::string getSupporterComment() const {
        return supporter_comment;
    }

    float getHostRatingScore() const {
        return host_rating_score;
    }

    float getSupporterRatingScore() const {
        return supporter_rating_score;
    }

    // Setter methods
    void setHostComment(const std::string& comment) {
        host_comment = comment;
    }

    void setSupporterComment(const std::string& comment) {
        supporter_comment = comment;
    }

    void setHostRatingScore(float score) {
        host_rating_score = score;
    }

    void setSupporterRatingScore(float score) {
        supporter_rating_score = score;
    }
};

int BookingSupporter::number_of_booking = 0;

#endif