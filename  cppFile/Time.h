#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <sstream> 

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace time_colors{
    const char* RED = "\033[1;91m";
    const char* RESET = "\033[0m";  
}

class Time{
private:
    int hour;
    int minute;
public:
    Time(int hour = 0, int minute = 0){}

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

#endif // TIME_H