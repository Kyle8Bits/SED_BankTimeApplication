#ifndef REAL_TIME_H
#define REAL_TIME_H

#include <iostream>
#include <ctime>

class RealTime {
public:
    // Constructor
    RealTime();

    void update();

    void printDate() const;

    int getToday();

    int getThisMonth();

    int getThisYear();
    
    void printDayOfWeek() const;

private:
    int year;
    int month;
    int day;
    int dayOfWeek;
};
#endif