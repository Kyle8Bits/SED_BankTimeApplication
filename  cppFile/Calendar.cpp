#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
// #include <Calendar.h>
//#define clearScreen() std::cout << "\x1B[2K\x1B[1G"

class Calendar{
    // private:
    // bool isLeapYear(int year);
    // int getDaysInMonth(int month, int year);
    // int calculateDayOfWeek(int day, int month, int year);
    // void printCalendar(int year, int month);
    // bool isValidDate(int day, int month, int year);

    public:

    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int getDaysInMonth(int month, int year) {
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return daysInMonth[month - 1];
    }

    int calculateDayOfWeek(int day, int month, int year) {
        if (month < 3) {
            month += 12;
            year -= 1;
        }

        int century = year / 100;
        year %= 100;

        int dayOfWeek = (day + ((13 * (month + 1)) / 5) + year + (year / 4) + (century / 4) - (2 * century)) % 7;
        dayOfWeek = (dayOfWeek + 5) % 7;
        if (dayOfWeek < 0) {
            dayOfWeek += 7;
        }

        return dayOfWeek;
    }

    int extractTheDayweek(int day, int month, int year){
        if (month < 3) {
            month += 12;
            year -= 1;
        }

        int century = year / 100;
        year %= 100;

        int dayOfWeek = (day + ((13 * (month + 1)) / 5) + year + (year / 4) + (century / 4) - (2 * century)) % 7;
        dayOfWeek = (dayOfWeek + 5) % 7;
        if (dayOfWeek < 0) {
            dayOfWeek += 7;
        }

        return dayOfWeek + 2;
    }

    void printCalendar(int year, int month) {
        //clearScreen();
        std::cout << "Calendar for " << month << "/" << year << ":\n";
        std::cout << "  Mon  Tue  Wed  Thu  Fri  Sat  Sun" << std::endl;
        int daysInMonth = getDaysInMonth(month, year);
        int startDay = calculateDayOfWeek(1, month, year); // Calculate the starting day of the month

        int day = 1;

        // Print leading spaces until the starting day of the week
        for (int i = 0; i < startDay; ++i) {
            std::cout << std::setw(5) << " ";
        }

        // Print the days of the month
        while (day <= daysInMonth) {
            std::cout << std::right << std::setw(5) << day;

            if ((day + startDay) % 7 == 0 || day == daysInMonth) {
                std::cout << std::endl;
            }
            day++;
        }
    }

    bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > getDaysInMonth(month, year)) {
        return false;
    }
    return true;
    }
};
#endif