#include <iostream>
#include <ctime>

class DateTime {
public:
    // Constructor
    DateTime() {
        update();  // Initialize the object with the current date and time
    }

    // Function to update the date and time
    void update() {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
        dayOfWeek = now->tm_wday;
    }

    // Function to print the current date
    void printDate() const {
        std::cout << "Current Date: " << year << '-' << month << '-' << day << std::endl;
    }

    // Function to print the day of the week
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
