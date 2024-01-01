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
    static int number_of_booking; //the number of the booking
    public:
        //CONSTRUCTOR
        BookingSupporter(string host_id = "", string support_id = "", string status = "PENDING", string booking_id ="BK", string progress = "NOT STARTED") 
                        : booking_id(booking_id),host_id(host_id), support_id(support_id), status(status), progress(progress){
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

};

int BookingSupporter::number_of_booking = 0;

#endif