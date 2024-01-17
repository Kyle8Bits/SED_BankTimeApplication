#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

class Calendar{
    public:
    bool isLeapYear(int year);

    int getDaysInMonth(int month, int year);

    int calculateDayOfWeek(int day, int month, int year);

    int extractTheDayweek(int day, int month, int year);

    void printCalendar(int year, int month);

    bool isValidDate(int day, int month, int year) ;
};
#endif