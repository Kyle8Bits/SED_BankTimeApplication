#include "Time.h"

const char* time_colors::RED = "\033[1;91m";
const char* time_colors::YELLOW = "\033[1;93m";
const char* time_colors::GREEN = "\033[92m";
const char* time_colors::RESET = "\033[0m";

Time::Time(int hour, int minute) : hour(hour), minute(minute) {}

string Time::getTime(){
    std::stringstream ss;
    ss << std::to_string(this->hour) << ":" <<
            std::setw(2) << std::setfill('0') << std::to_string(this->minute);
    
    return ss.str();
}

bool Time::isValidTime(const string& time){//use paste by reference to advoid create the copy of parameter (const to not chagne the time that we paste in)
    if(time.length() != 5 || time[2] != ':' || !isdigit(time[0]) || !isdigit(time[1]) || !isdigit(time[3]) || !isdigit(time[4])){
        //if the length of the string is not 5 --> error
        //if the 0,1,3,4 character is not digit --> error
        //FORMAT HH:MM
        return false;
    } 

    //Check the valid time 
    int hour = std::stoi(time.substr(0,2));//get the 2 first character of the string --> convert to int
    int minute = std::stoi(time.substr(3,2));//get the 2 last character of the string --> convert to int
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59){
        //if hour is not in range(0-24) --> false
        //if minutes is not in rnage(0-60) --> false
        return false;
    }

    return true;
}

Time Time::getTimeFromUser(){
    cout << ">Your choice: ";
    string time;
    getline(cin >> std::ws, time);
    while(!isValidTime(time)){
        cout << time_colors::RED << "Please enter valid time!" << time_colors::RESET << endl;
        cout << ">Your choice: ";
        getline(cin >> std::ws, time);
    }
    int hour = std::stoi(time.substr(0,2));//get the 2 first character of the string --> convert to int
    int minute = std::stoi(time.substr(3,2));//get the 2 last character of the string --> convert to int
    Time time_obj(hour, minute);
    return time_obj;
}

bool Time::isLater(Time another_time){
    //This function will return true if this time is later than another_time
    if(this->hour > another_time.hour){
        //if this hour is greater than another_time hour, return true
        return true;
    }else if(this->hour == another_time.hour){
        if(this->minute >= another_time.minute){
            //if is the same hour, but this minute is larger --> true
            return true;
        }
    }
    return false;
}

string Time::getTimeColon(){

    string digitalTime = "";

    if(this->hour <= 9){
        digitalTime += "0" + std::to_string(this->hour) + ":" + std::to_string(this->minute);
    }
    else{
        digitalTime += std::to_string(this->hour) + ":" + std::to_string(this->minute);
    }

    return digitalTime;
}

int Time::getHour(){
    return this->hour;
}

int Time::getMinute(){
    return this->minute;
}

string Time::getHourToString(){
    return std::to_string(this->hour);
}
string Time::getMinuteToString(){
    return std::to_string(this->minute);
}
