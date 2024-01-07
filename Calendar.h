#ifndef CALENDAR_H
#define CALENDAR_H

//#define clearScreen()
bool isLeapYear(int year);
int getDaysInMonth(int month, int year);
int calculateDayOfWeek(int day, int month, int year);
void printCalendar(int year, int month);
bool isValidDate(int day, int month, int year);

#endif 