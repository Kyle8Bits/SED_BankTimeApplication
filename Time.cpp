#ifndef TIME
#define TIME
#include <iostream>
#include <string> 
#include <iomanip>
using std::string;

class Time{
private:
    int hour;
    int minute;
public:
    friend std::istream& operator>>(std::istream& is, Time& time);
    Time(int hour = 0, int minute = 0) : hour(hour), minute(minute) {}

    string getTime(){
        std::stringstream ss;
        ss << std::to_string(this->hour) << ":" <<
               std::setw(2) << std::setfill('0') << std::to_string(this->minute);
        
        return ss.str();
    }

    bool isLater(Time another_time){
        //This function will return true if this time is later than another_time
        if(this->hour > another_time.hour){
            //if this hour is greater than another_time hour, return true
            return true;
        }else if(this->hour == another_time.hour){
            if(this->minute > another_time.minute){
                //if is the same hour, but this minute is larger --> true
                return true;
            }
        }
        return false;
    }

    string getTimeColon(){

        string digitalTime = "";

        if(this->hour <= 9){
            digitalTime += "0" + std::to_string(this->hour) + ":" + std::to_string(this->minute);
        }
        else{
            digitalTime += std::to_string(this->hour) + ":" + std::to_string(this->minute);
        }

        return digitalTime;
    }

    string getHour(){
        return std::to_string(this->hour);
    }
    string getMinute(){
        return std::to_string(this->minute);
    }
};
#endif 