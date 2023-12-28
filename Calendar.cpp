#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

// Function to check if the year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a specific month of a year
int getDaysInMonth(int month, int year) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysInMonth[month - 1];
}

// Function to check if a date is valid
bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > getDaysInMonth(month, year)) {
        return false;
    }
    return true;
}

struct FreeDay {
    int day;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
};

void printCalendar(int year, int month) {
    std::cout << "Calendar for " << month << "/" << year << ":\n\n";
    std::cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << std::endl;

    // Implement logic to print the calendar here...
    // This code will print a basic calendar layout, you might need to modify it further based on your needs
    int daysInMonth = getDaysInMonth(month, year);
    int startDay = 1; // Assuming the month starts on Sunday (0), modify this based on the actual starting day of the month

    for (int day = 1; day <= daysInMonth + startDay; ++day) {
        if (day <= startDay) {
            std::cout << "     ";
        } else {
            std::cout << std::setw(5) << day - startDay;
        }

        if (day % 7 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void printFreeDays(const std::vector<FreeDay>& freeDays) {
    std::cout << "\nList of Free Days with Times:\n" << std::endl;
    for (const auto& freeDay : freeDays) {
        std::cout << "Day: " << freeDay.day << " | Time: " << std::setw(2) << std::setfill('0') << freeDay.startHour << ":" << std::setw(2) << freeDay.startMinute
                  << " to " << std::setw(2) << freeDay.endHour << ":" << std::setw(2) << freeDay.endMinute << std::endl;
    }
}

int main() {
    int year, month;

    std::cout << "Enter year: ";
    std::cin >> year;

    std::cout << "Enter month (1-12): ";
    std::cin >> month;

    if (year < 0 || month < 1 || month > 12) {
        std::cout << "Invalid year or month entered." << std::endl;
        return 1;
    }

    printCalendar(year, month);

    std::vector<FreeDay> freeDays;

    int day;
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        std::cout << "Enter free day for the month (1-" << getDaysInMonth(month, year) << "): ";
        std::cin >> day;

        if (!isValidDate(day, month, year)) {
            std::cout << "Invalid day entered. Please enter a valid day within the month." << std::endl;
            continue;
        }

        std::string startTime, endTime;
        std::cout << "Enter starting time (format: 'start hour: start min'): ";
        std::cin >> startTime;
        int startHour, startMinute;
        char separator;
        std::istringstream(startTime) >> startHour >> separator >> startMinute;

        if (separator != ':' || startHour < 0 || startHour > 23 || startMinute < 0 || startMinute > 59) {
            std::cout << "Invalid starting time format or values. Please enter a valid time." << std::endl;
            continue;
        }

        std::cout << "Enter ending time (format: 'end hour: end min'): ";
        std::cin >> endTime;
        int endHour, endMinute;
        std::istringstream(endTime) >> endHour >> separator >> endMinute;

        if (separator != ':' || endHour < 0 || endHour > 23 || endMinute < 0 || endMinute > 59 || endHour < startHour || (endHour == startHour && endMinute <= startMinute)) {
            std::cout << "Invalid ending time format or values. Please enter a valid time greater than the starting time." << std::endl;
            continue;
        }

        FreeDay newFreeDay = {day, startHour, startMinute, endHour, endMinute};
        freeDays.push_back(newFreeDay);

        std::cout << "Do you want to enter another free day? (y/n): ";
        std::cin >> choice;
    }

    printFreeDays(freeDays);

    return 0;
}
