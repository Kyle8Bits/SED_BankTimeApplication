//CHƯA CHẮC LÀ SẼ XÀI TỚI CÁI NÀY, ĐỂ ĐÂY DỰ PHÒNG//

#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <ctime>

class DateTime {
public:
    // Constructor
    DateTime() {
        update();
    }

    void update() {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        dayOfWeek = now->tm_wday;
    }

    void printDate() const {
        std::cout << "Current Date: " << year << '-' << month << '-' << day << std::endl;
    }

    int getToday(){
        return day;
    }

    int getThisMonth(){
        return month;
    }

    int getThisYear(){
        return year;
    }
    
    void printDayOfWeek() const {
        const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        std::cout << "Day of the Week: " << days[dayOfWeek] << std::endl;
    }

private:
    int year;
    int month;
    int day;
    int dayOfWeek;
};
#endif