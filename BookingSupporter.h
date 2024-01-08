#ifndef BOOKING_SUPPORTER_H
#define BOOKING_SUPPORTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Time.h" 

using std::string;

class BookingSupporter {
private:
    string booking_id;
    string host_id;
    string support_id;
    string status;
    string progress;
    Time start_time;
    Time end_time;
    int host_rating;
    int skill_rating_score;
    int supporter_rating_score;
    string host_comment;
    string supporter_comment;
    static int number_of_booking;

public:
    BookingSupporter(string host_id, string support_id, string status, string booking_id,
                     string progress, Time start_time, Time end_time,
                     int host_rating, int skill_rating_score, int supporter_rating_score,
                     string host_comment, string supporter_comment);

    void setBookingId(std::string new_booking_id);
    void setHostId(std::string new_host_id);
    void setSupportId(std::string new_support_id);
    void setStatus(std::string new_status);
    void setProgress(string progress);
    void setStartTime(Time time);
    void setEndTime(Time time);

    std::string getBookingId() const;
    std::string getHostId() const;
    std::string getSupportId() const;
    std::string getStatus() const;
    string getProgress();
    string getTimeToFile();
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
    string toString();

    friend class FileProcess;
};

#endif
