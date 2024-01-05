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
    Time(int hour = 0, int minute = 0) : hour(hour), minute(minute) {}

    string getTime(){
        return std::to_string(this->hour) + ":" + std::to_string(this->minute);
    }

    string getHour(){
        return std::to_string(this->hour);
    }
    string getMinute(){
        return std::to_string(this->minute);
    }
};
#endif 