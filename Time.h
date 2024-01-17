#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <sstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace time_colors {
    extern const char* RED;
    extern const char* YELLOW;
    extern const char* GREEN;
    extern const char* RESET;
}

class Time{
    private:
        int hour;
        int minute;
    public:
    Time(int hour = 0, int minute = 0);

    string getTime();

    bool isValidTime(const string& time);

    Time getTimeFromUser();

    bool isLater(Time another_time);

    string getTimeColon();

    int getHour();

    int getMinute();

    string getHourToString();
    
    string getMinuteToString();
};

#endif