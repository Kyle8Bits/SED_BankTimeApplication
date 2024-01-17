#include "RealTime.h"

// Constructor
RealTime::RealTime() {
    update();
}

void RealTime::update() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
    dayOfWeek = now->tm_wday;
}

void RealTime::printDate() const {
    std::cout << "Current Date: " << year << '-' << month << '-' << day << std::endl;
}

int RealTime::getToday(){
    return day;
}

int RealTime::getThisMonth(){
    return month;
}

int RealTime::getThisYear(){
    return year;
}

void RealTime::printDayOfWeek() const {
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::cout << "Day of the Week: " << days[dayOfWeek] << std::endl;
}