#ifndef TIME
#define TIME
#include <iostream>
#include <string> 
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
    
    friend std::istream& operator>>(std::istream& is, Time& time) {
    int hour, minute;
    char colon;

    // Read hour
    is >> hour;

    // Check for colon separator
    if (is >> colon && colon == ':') {
        // Read minute
        is >> minute;

        // Set the Time object
        time = Time(hour, minute);
    } else {
        // Set failbit if the format is incorrect
        is.setstate(std::ios::failbit);
    }

    return is;
}
};
#endif 