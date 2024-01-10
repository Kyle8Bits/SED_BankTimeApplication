#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iomanip>

#include "Member.cpp"
#include "Supporter.cpp"
#include "Time.cpp"
#include "BookingSupporter.cpp"
#include "Calendar.cpp"
#include "RealTime.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::find;

#define loop(n) for(int i = 0; i < n; ++i)
// #define FILENAME "members.dat"
#define clearScreen() cout << "\x1B[2J\x1B[H";

namespace colors{
    const char* RED = "\033[1;91m";
    const char* GREEN = "\033[92m";
    const char* RESET = "\033[0m";  
}

#define NotExistSupporterError() cout << colors::RED << "\t\tERROR: This supporter do not exsit in the list" << colors::RESET << std::endl;
#define BookingTimeError() cout << colors::RED << "\t\tERROR: This supporter work schedule do not match your booking time" << colors::RESET << std::endl;
#define LogicTimeError() cout << colors::RED << "\t\tERROR: The start time must come before the endtime" << colors::RESET << std::endl;
#define TimeFormatError() cout << colors::RED << "\t\tERROR: The time must be in form HH:MM" << colors::RESET << std::endl;
#define BlockError() cout << colors::RED << "\t\tERROR: You can not book a supporter in your block list" << colors::RESET << std::endl;
#define InsufficientPointError() cout << colors::RED << "\t\tERROR: Insufficient credit points to book this supporter" << colors::RESET << std::endl;
#define SucessBooking() cout << colors::GREEN << "\t\tYour booking has been created" << colors::RESET << endl;



class System{
private:
    BookingSupporter booking;
    std::vector<Member*> member_list; 
    std::vector<BookingSupporter*> booking_list;
    std::vector<Supporter*> availableSupporter;//This to restrict for users only book the valid supporter id
    Member* logged_in_member;//This pointer of member to store the information of the member who has logged in successfully
    Supporter* logged_in_supporter;//This pointer of member to store the information of the member who has logged in successfully
    bool is_admin = false;

public:
    //CONSTRUCTOR
    System(std::vector<Member*> member_list = {}) : member_list(member_list){}

    //The function below to get the position of the member in the list via the username
    int getPositionOfMemberByUsername(string user_name_account){
        loop(this->member_list.size()){//Go to each member to find the user_name 
            if(member_list[i]->getUsername() == user_name_account){
                return i;//If we can find it, return the position of it
            }
        }
        return -1;
    }

    bool checkNonEmpty(const string& str){
        if(str.empty()){
            cout << "Please enter non-empty value!" << endl;
            return false;
        }

        return true;
    }

    bool registerMember(){
        string user_name_input; 
        string pass_word_input; //these 2 attributes to take the value from input
        cout << "****Your registration adds great value to our community. Thank you!****" << endl;
        cout << "Please enter username & password: " << endl;
        cout << ">Username: " ;
        getline(cin >> std::ws, user_name_input); //std::ws to ignore the reduntant space

        if(!checkNonEmpty(user_name_input)){//Call the check empty function
            return false;
        }
        //Check the username is existed or not?
        int position = getPositionOfMemberByUsername(user_name_input); //call the function getPosition... to find the position of the usrname
        //if the function return -1 --> that user name is not existed. By constrast, position>0 --> that username is existed

        if(position >= 0){
            cout << "This username is taken. Can you please use the another name?" << endl;
            return false;
        } 
        
        //ask for password
        cout << "Password: ";
        getline(cin >> std::ws, pass_word_input);

        if(!checkNonEmpty(pass_word_input)){//Call the check empty function
            return false;
        }

        string full_name_input, phone_number_input, address_input, city_input;//declare 3 variables to get basic information of users
        cout << "****Please enter few basic information to complete the registration****" << endl;
        cout << ">Your full name: ";
        getline(cin >> std::ws, full_name_input);

        do{//Do until users type valid phone number 
            cout << "Your phone number: ";
            std::getline(cin >> std::ws, phone_number_input);
        }while(!isValidPhone(phone_number_input));
        
        cout << "Your address: ";
        getline(cin >> std::ws, address_input);

        int user_choice = 0;
        cout <<"****Our application only exists at Ho Chi Minh and Hanoi****" << endl;
        cout << "1. Hanoi" << endl
             << "2. Ho Chi Minh" << endl
             << ">Your choice: ";
        cin >> user_choice;
        switch(user_choice){
            case 1://Hanoi
                city_input = "Hanoi";
                break;
            case 2://Ho Chi MInh
                city_input = "Ho Chi Minh";
                break;
            default: //invlaid input
                cout << "Please enter valid input!" << endl;
                return false;
                break;
        }

        cout << "Succesfully collecting your info" << std::endl;
        //Create a member and push it in the lsit
        Member* new_member = new Member(user_name_input, pass_word_input);
        //SET SOME BASIC INFORMATION
        new_member->setFullName(full_name_input);
        new_member->setPhoneNumber(phone_number_input);
        new_member->setAddress(address_input);
        new_member->setCity(city_input);

        //push it in the list
        member_list.push_back( new_member );
        //SUCCESSFUL REGISTER
        cout << "Register member succesffully!" << endl;
        
        return true;
    }

    bool loginMember(){
        string user_name_input;
        string pass_word_input;//these 2 variables to store the input of the users
       
        cout << "****Login form****" << endl;
        cout << ">Username: ";
        getline(cin >> std::ws, user_name_input);
        cout << ">Password: ";
        getline(cin >> std::ws, pass_word_input);

        if(user_name_input == "admin" && pass_word_input == "admin"){
            is_admin = true;
            return true;
        }

        loop(member_list.size()){
            if(member_list[i]->getUsername() == user_name_input && member_list[i]->getPassword() == pass_word_input){
                cout << "Login SUCCESSFULLY!" << endl;

                if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){//check the memberlist at index i is supporter* type or not
                    //if yes, modify the logged_in_supporter
                    logged_in_supporter = supporter;
                    logged_in_member = nullptr;
                } else{
                    //if no set vice versa
                    logged_in_supporter = nullptr;
                    logged_in_member = member_list[i];
                }
                return true;
            }
        }
        return false;
    }
   
    //method to check phone number
    bool isValidPhone(const string& str) {
        
        // check if all characters in the string are digits
        for (char ch : str) {
            if (!std::isdigit(ch)) {
                cout << "You can not type character!" << endl;
                return false;
            }
        }
        // check if the string length is exactly 10
        if (str.length() != 10) {
            cout << "Your phone number must have 10 numbers" << endl;
            return false;
        }
        
        
        // if both conditions are satisfied, return true
        return true;
    }

    void displayMemberList(){
        if(is_admin){
            for(Member* member : member_list){
                member->displayPersonalInformation();
            }
            // cout << "****Member list****" << endl;
            // loop(this->member_list.size()){
            //     //Go to each member to print the information
            //     cout << "Member " << i + 1 << ": " << endl;
            //     cout<< "User ID: " << member_list[i]->getMemberId()
            //         << ", Username: " << member_list[i]->getUsername() 
            //         << ", Password: "<< member_list[i]->getPassword()
            //         << ", Credit Point: " << member_list[i]->getCreditPoint()
            //         << ", Fullname: " << member_list[i]->getFullName()
            //         << ", Phone Number: " << member_list[i]->getPhoneNumber()
            //         << ", Address: " << member_list[i]->getAddress()
            //         << ", City: " << member_list[i]->getCity()
            //         << ", About Me: " << member_list[i]->getAboutMe()
            //         << ", Host Rating Score: " << member_list[i]->getHostRatingScore()
            //         << ", Host Count: " << member_list[i]->getHostCount()
            //         << ", Block List: HAVEN't DONE YET" << endl;
            //     //check if the member is a Supporter or a regular member
            //     if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){
            //         //If it is a supporter, we will print more information of supporter
            //         cout << "SUPPORTER:" 
            //             << ", Availability Time: " << supporter->getAvailabilityPeriod()
            //             << ", Skill List: " << supporter->displaySkillList()
            //             << ", Cost: " << supporter->getCost()
            //             << ", average skill rating score: " << supporter->getSkillRatingScore()
            //             << ", average support rating score: " << supporter->getSupportRatingScore()
            //             << ", support count: " << supporter->getSupportCount() << endl;

            //     }
            // }
        }else{
            cout << "You do not have permisson to do that" << endl;
        }
    }
    
    bool checkDuplicateDay(std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > list, string choose){
        bool check = true;
        loop(list.size()){ 
            if (list[i].first == choose){
                check == false;
            }
        }
        return check;
    }

    std::string getDayString(int day) {
        switch (day) {
            case 1: return "Monday";
            case 2: return "Tuesday";
            case 3: return "Wednesday";
            case 4: return "Thursday";
            case 5: return "Friday";
            case 6: return "Saturday";
            case 7: return "Sunday";
            default: return "Invalid Day";
        }
    }

    bool upgradeToSupporter(){
        if(dynamic_cast<Supporter*>(logged_in_member)){//CHECK THE MEMBER IS ALREADY SUPPORTER OR NOT?
            cout << "You are aldready supporter!" << endl;
            return false;
        }
        //----------------------THIS FOR GETTING SKILL LIST---------------------

        string skill_input;//declare variable store the input of the users
        cout << "Thank you for becomming the supporter. Your choice helps our community alot!" << endl;
        cout << "First, you need to add some skills that you have" << endl;
        bool check = true;
        std::vector<string> skill_list_input;
        std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule;
        std::vector<std::pair<Time,Time>> time_pair_list;
        string weekday;
        while(check){
            cout << ">Your skill:";
            getline(cin >> std::ws, skill_input);
            skill_list_input.push_back(skill_input);
            cout << "Do you want to continue: [Y/N]";
            char choice; cin >> choice;
            if(choice != 'Y' && choice != 'y'){
                check = false;
            }
        }
        cout << "Your skills are added successfully" << endl;
        
            //----------------------THIS FOR GETTING AVAILABILIITY PERIOD---------------------
        cout << "Now you will make a period schedule, you can change it later" << endl;
        
        bool schedule_check = true;
        while(schedule_check){
        //----------------------THIS FOR GETTING THE WEEKLY WORKDAY----------------
            int day_choice;

            while(schedule_check){
                cout<<"Please enter which days of the week you work.\n";
                cout << "1. Monday \n"
                    << "2. Tuesday \n"
                    << "3. Wednesday \n"
                    << "4. Thursday \n"
                    << "5. Friday \n"
                    << "6. Saturday \n"
                    << "7. Sunday \n";
                cout <<"=============================================================" << endl;
                cout << "Already in the list: ";
                loop(workSchedule.size()){
                    cout << workSchedule[i].first << "-";
                }

                cout << "\n";
                bool check_option = true;

                while(check_option){ 
                cout << "Your option(eg. 1 for Monday,7 for Sunday): "; cin >> day_choice;
                    
                    if(!checkDuplicateDay(workSchedule, getDayString(day_choice))){
                        cout << "You already select this day, please choose another day" << endl;
                    }
                    else{

                        bool option_time = true;
                        while(option_time){
                            string start_time_input, end_time_input;
                            int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
                            cout << "What is your free time (ex: 8:00 to 10:00, or 20:30 to 22:00)" << endl;
                            //----------------------THIS FOR GETTING START TIME---------------------
                            bool check_time_valid = true;

                            while(check_time_valid){
                                cout << "Start time: ";
                                getline(cin >> std::ws, start_time_input);
                                std::stringstream ss1;
                                ss1 << start_time_input;//Get the startime to the ss1

                                ss1 >> start_time_hour;
                                ss1.ignore();//ignore the colon
                                ss1 >> start_time_minute;
                                
                                //----------------------THIS FOR GETTING END TIME---------------------
                                
                                cout << "End time: ";
                                getline(cin >> std::ws, end_time_input);
                                
                                std::stringstream ss2;
                                ss2 << end_time_input;//Get the startime to the ss2
                                ss2 >> end_time_hour;
                                ss2.ignore();
                                ss2 >> end_time_minute;

                                if (!checkValidTime(start_time_input) && !checkValidTime(end_time_input)){
                                    cout << "Invalid format! Please enter in the form HH:MM." << endl;
                                }
                                else if(!compareTimes(start_time_input, end_time_input)){
                                    cout << "Invalid! The start time must come before the end time";
                                }
                                else{
                                    time_pair_list.push_back(std::make_pair(Time(start_time_hour, start_time_minute), Time(end_time_hour, end_time_minute)));
                                    check_time_valid = false;
                                }   
                            }

                            char option;
                            cout <<"Do you want to to add more period time for " << getDayString(day_choice) <<" [Y/N]: ";
                            cin >> option;
                            if (option == 'N' || option == 'n'){
                                option_time = false;
                            }
                        }
                        weekday = getDayString(day_choice);
                        check_option = false; 
                    }

                    workSchedule.push_back(std::make_pair(weekday,time_pair_list));

                }

                char option_day;
                    cout << "Do you want to add more period[Y/N]: "; 
                    cin >> option_day;
                    if(option_day != 'Y' && option_day != 'y'){
                        schedule_check = false;
                    }
                }
            }

        //----------------------THIS FOR GETTING COST PER HOUR---------------------
        int cost_input; 
        cout << "What is the hourly rate you would like to charge: ";
        cin >> cost_input;
        //----------------------ADD BASIC INTRODUCTION---------------------
        string about_me_input;
        cout << "Please introduce some basic things about yourself (Academic Level, Hobby, ...)" << endl;
        getline(cin >> std::ws, about_me_input);

        //---------------------FIX ID IN BOOKING LIST-----------------
        loop(booking_list.size()){
            if(logged_in_member->getMemberId() == booking_list[i]->getHostId()){
                string new_id =  booking_list[i]->getHostId();
                new_id[0] = 'S';
                booking_list[i]->setHostId(new_id);
            }
        }

        //----------------------ADD ALL IT IN SUPPORTER---------------------
        //first change the id of logged_in_member from M to S
        string supporter_id = logged_in_member->getMemberId(); supporter_id[0] ='S';//Change the first cahracter of id from M to S
        //set the id of logged_in_member
        logged_in_member->setMemberId(supporter_id);
        //set the basic introduction of logged_in_member
        logged_in_member->setAboutMe(about_me_input);
        //create new pointer supporter
        
        Supporter* new_supporter = new Supporter(*logged_in_member,workSchedule, Status::OFFLINE, skill_list_input, cost_input);
        // loop(workSchedule.weekday.size()){
        //     cout << workSchedule.weekday[i] << " ";
        // }

        loop(member_list.size()){
            if(member_list[i] == logged_in_member){
                member_list.erase(member_list.begin() + i); 
                logged_in_member = nullptr;
                break;
            }
        }
        
        logged_in_supporter = new_supporter;//make the logged_in_supporter = new_supporter
        //Add the new_supporter to the list
        member_list.push_back(new_supporter);
        
        return true;
    }

    void resetMemberPassword() {
        if(is_admin){
            string username_input, password_input;
            cout << "Please enter the User's username that you want to reset password" << endl;
            getline(cin >> std::ws, username_input);

            for (Member* member : member_list) {
                if (member->getUsername() == username_input) {
                    
                    cout << "Enter the new password: ";
                    getline(cin >> std::ws, password_input);

                    member->setPassword(password_input);
                    cout << "Reset password sucessfully!" << endl;
                    return;
                }
            }
            cout << "Member not found.\n";
        } else{
            cout << "Only admin can do that" << endl;
        }
    }

    void viewPersonalInformation(){
        if(logged_in_member != nullptr){
            logged_in_member->displayPersonalInformation();
            cout << endl;
        } else{
            logged_in_supporter->displayPersonalInformation();
        }

        // cout << "***MY INFORMATION***" << endl;
        // cout << "ID: " << logged_in_member->getMemberId() << endl;
        // cout << "Username: " << logged_in_member->getUsername() << endl;
        // cout << "Password: " << logged_in_member->getPassword() << endl;
        // cout << "Credit Point: " << logged_in_member->getCreditPoint() << endl;
        // cout << "Full Name: " << logged_in_member->getFullName() << endl;
        // cout << "Phone Number: " << logged_in_member->getPhoneNumber() << endl;
        // cout << "Address: " << logged_in_member->getAddress() << endl;
        // cout << "City: " << logged_in_member->getCity() << endl;
        // cout << "About Me: " << logged_in_member->getAboutMe() << endl;
        // cout << "Host Rating Score: " << logged_in_member->getHostRatingScore() << endl;
        // cout << "Host Count: " << logged_in_member->getHostCount() << endl;
        // cout << "Block List: " << logged_in_member->blockListToString()<< endl;
    }

    // void viewPersonalInformationSupporter(){
    //     cout << "***MY INFORMATION***" << endl;
    //     cout << "ID: " << logged_in_supporter->getMemberId() << endl;
    //     cout << "Username: " << logged_in_supporter->getUsername() << endl;
    //     cout << "Password: " << logged_in_supporter->getPassword() << endl;
    //     cout << "Credit Point: " << logged_in_supporter->getCreditPoint() << endl;
    //     cout << "Full Name: " << logged_in_supporter->getFullName() << endl;
    //     cout << "Phone Number: " << logged_in_supporter->getPhoneNumber() << endl;
    //     cout << "Address: " << logged_in_supporter->getAddress() << endl;
    //     cout << "City: " << logged_in_supporter->getCity() << endl;
    //     cout << "About Me: " << logged_in_supporter->getAboutMe() << endl;
    //     cout << "Host Rating Score: " << logged_in_supporter->getHostRatingScore() << endl;
    //     cout << "Host Count: " << logged_in_supporter->getHostCount() << endl;
    //     cout << "Block List:  HAVEN'T DONE YET" << endl;

    //     // cout << "Time list: " << logged_in_supporter->getPairListToString();
    // }


    string toLower(string str){
        loop(str.length()){
            str[i] = std::tolower(str[i]);
        }
        return str;
    }

    bool checkValidTime(string time) {
        
        if (time.length() != 5) {
            return false;
        }

        
        for (int i = 0; i < time.length(); ++i) {
            if ((i < 2 && !isdigit(time[i])) || (i == 2 && time[i] != ':') || (i > 2 && !isdigit(time[i]))) {
                return false;
            }
        }

        
        int hours = stoi(time.substr(0, 2));
        int minutes = stoi(time.substr(3, 2));

        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
            return false;
        }

        return true;
    }

    bool compareTimes( string time1, string time2) {
        std::istringstream stream1(time1);
        std::istringstream stream2(time2);

        int hours1, minutes1, hours2, minutes2;

        char colon; // To consume the ':' character

        // Parse the first time
        stream1 >> hours1 >> colon >> minutes1;

        // Parse the second time
        stream2 >> hours2 >> colon >> minutes2;

        // Compare hours
        if (hours1 < hours2) {
            return true;
        } else if (hours1 > hours2) {
            return false;
        }

        // Hours are equal, compare minutes
        return (minutes1 <= minutes2);
    }

    bool isTimeIntervalContained(string start1, string end1, string start2, string end2) {
        // Check if start1 is equal to or after start2
        bool startCondition = compareTimes(start1, start2) || start1 == start2;

        // Check if end1 is equal to or before end2
        bool endCondition = compareTimes(end2, end1) || end1 == end2;

        // If both conditions are met, the first interval is contained within the second interval
        return startCondition && endCondition;
    }

    bool isSupporterAvilableInBookingTime(string id, int dayOfweek ,string start_time_booking, string end_time_booking){
        bool check = false;
        std::vector<std::pair<Time, Time>> selected_timepair;
        Supporter* booked_supporter;
        loop(member_list.size()){
            if (member_list[i]->getMemberId() == id){
                booked_supporter == member_list[i];
                break;
            }
        }

        string day = getDayString(dayOfweek);

        loop(booked_supporter->getWorkSchedule().size()){
            if( day == booked_supporter->getWorkSchedule()[i].first){
                booked_supporter->getWorkSchedule()[i].second = selected_timepair;
                break;
            }
        }

        loop(selected_timepair.size()){
            if(!selected_timepair.empty()){
                if(isTimeIntervalContained(start_time_booking, end_time_booking, selected_timepair[i].first.getTime(), selected_timepair[i].second.getTime())){
                    check = true;
                    break;
                }
            }
        }

        return check;
    }


    void displayAvailableSupporter(){
        booking.displayAvailableSupporter(member_list, logged_in_member,  logged_in_supporter, availableSupporter);
    }

    double findCreditPointFromTime(int start_hour, int start_minute, int end_hour, int end_minute, int cost_per_hour){
        int start_minute_total = start_hour * 60 + start_minute;//find the total minues of start time
        int end_minutes_total = end_hour * 60 + end_minute;//find the total minutes of end time

        int total_minutes = end_minutes_total - start_minute_total;//find the total minutes of the period

        double cost_per_minute = (double) cost_per_hour / 60.0;//find the cost per minute
        
        double total_cost = cost_per_minute * total_minutes;//find the total cost of the period

        return total_cost;
    }

    void createBooking(){
        cout << "****WELCOME TO BOOKING DASHBOARD****"<<endl;
        displayAvailableSupporter();
        cout << "Please input the supporter's id that you want to book: ";
        string input; cin >> input;


//=========================CHECK IS THAT SUPPORTER IS EXSIT=======================
        
        bool isSupporter = (logged_in_member == nullptr);
        bool isValidSupporter = false;//this to check the create bookign is successfully or not?

        loop(availableSupporter.size()){
            if(toLower(input) == toLower(availableSupporter[i]->getMemberId())){
                if(isSupporter){
                    logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
                }

//==================================SELECT TIME==========================================================================
                if(!booking.isInBlockList(logged_in_member->getBlockList(), availableSupporter[i]->getMemberId())){
//===========================User choose the day to book here===============================================
                    Calendar calendar;
                    RealTime today;
                    bool decide_month_check = true;
                    while(decide_month_check){
                        // clearScreen();
                        calendar.printCalendar(today.getThisYear(), today.getThisMonth());
                        
                        cout <<"1. Book withtin this month" << endl;
                        cout <<"2. Book for with another calendar" << endl;
                        cout <<"3. Cancle" << endl;
                        
                        int choice;
                        cout << "> Your choice: "; cin >> choice;

                        int day;
                        if (choice == 1){
                            bool day_check =true;
                            while(day_check){
                                cout << "> Choice the day in above month: "; cin >> day;

                                if (day >= 1 && day <= calendar.getDaysInMonth(today.getThisMonth(), today.getThisYear())){
                                    if ( day >= today.getToday()){
                                        day_check = false;
                                    }
                                    else{
                                        calendar.printCalendar(today.getThisYear(), today.getThisMonth());
                                        cout << colors::RED << "The selected must be today or the following days. Please select again" << colors::RESET <<  endl;
                                    }
                                }
                                else{

                                    calendar.printCalendar(today.getThisYear(), today.getThisMonth());
                                    cout << colors::RED << "The selected day does not exist in this month. Please select again" << colors::RESET << endl;
                                }
                            }
                            decide_month_check = false;
                        }
                        else if( choice == 2){
                            clearScreen();
                            bool year_month_check = true;
                            while(year_month_check){
                                int year, month;
                                cout << "Please enter the year you want to make the booking: "; cin >> year;
                                cout << "Please enter the month you want to make the booking: "; cin >> month;

                                if (year >= today.getThisYear() && (month >= today.getThisMonth() &&  month <= 12)){
                                    clearScreen();
                                    calendar.printCalendar(year,month);

                                    bool day_check =true;
                                    while(day_check){
                                        cout << "> Choice the day in above month: "; cin >> day;

                                        if (day >= 1 && day <= calendar.getDaysInMonth(today.getThisYear(), today.getThisMonth())){
                                            if ( day >= today.getToday()){
                                                day_check = false;
                                            }
                                            else{
                                                cout << colors::RED << "The selected must be today or the following days. Please select again" << colors::RESET << endl;
                                            }
                                        }
                                        else{
                                            cout << colors::RED << "The selected day does not exist in this month. Please select again" << colors::RESET << endl;
                                        }
                                    }

                                    year_month_check =false;
                                }
                                else{
                                    cout << colors::RED <<"The selected month and year is invalid. Please select again" << colors::RESET <<  endl;
                                }
                            }
                            decide_month_check = false;
                        }
                        else if (choice == 3){
                            cout << "Returning to dashboard" << endl;
                            return;
                        }

                        else{
                            cout << colors::RED <<"Invalid select please choose again" << colors::RESET << endl;
                        }
                    }

                    cout << "Choose the time you want to book. Noitce that: the time you choose must match with the free time of the supporter!" << endl;
                    int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
                    string start_time_input, end_time_input;
                    cout << "Start Time: ";
                    getline(cin >> std::ws, start_time_input);
                    cout << "End Time: ";
                    getline(cin >> std::ws, end_time_input);


//==================================SELECT TIME==========================================================================
                    if(checkValidTime(start_time_input) && checkValidTime(end_time_input)){
                        //use one string to 2 integer
                        std::stringstream ss_start_time;
                        ss_start_time << start_time_input;

                        ss_start_time >> start_time_hour;
                        ss_start_time.ignore();
                        ss_start_time >> start_time_minute;

                        std::stringstream ss_end_time;
                        ss_end_time << end_time_input;

                        ss_end_time >> end_time_hour;
                        ss_end_time.ignore();
                        ss_end_time >> end_time_minute;

                        if(compareTimes(start_time_input, end_time_input)){
                            
                            //=============Check is the time is in range with the schedule===============
                            // if(isSupporterAvilableInBookingTime(selected_supporter->getMemberId(), )

                            //****CHECK CREDIT POINT****

                            int total_cost = findCreditPointFromTime(start_time_hour, start_time_minute, end_time_hour, end_time_minute, availableSupporter[i]->getCost());
                            cout << "The total cost of this booking is: " << total_cost << endl;
                            cout << "Do you want to continue? [Y/N]: ";
                            string choice; cin >> choice;
                            if(choice == "Y" || choice == "y"){
                                if(logged_in_member->getCreditPoint() < total_cost){//check the credit point of the users and the cost per hour of the supporter
                                    InsufficientPointError();
                                    return;
                                }
                                //PUSH NEW BOOKING TO THE BOOKING LIST
                                BookingSupporter* booking = new BookingSupporter(logged_in_member->getMemberId(), availableSupporter[i]->getMemberId());
                                //SET THE START AND END TIME OF THE NEW BOOKINg
                                booking->setStartTime(Time(start_time_hour, start_time_minute));
                                booking->setEndTime(Time(end_time_hour, end_time_minute));
                                booking->setTotalCost(total_cost);
                                booking_list.push_back(booking);
                                // cout << "Your booking has been created" << endl;
                                SucessBooking();//Print sucessfull message
                                isValidSupporter = true;
                                this->availableSupporter.clear();
                                //clear after create booking to prevent push duplicated Supporter
                                break; 
                            } else{
                                cout << "You have canceled the booking" << endl;
                                isValidSupporter = true;
                                break;
                            }


                        }else{
                            LogicTimeError();
                            return;
                        }
                    }else{
                        TimeFormatError();
                        return;
                    }            
                    }else{
                        // cout <<"You can not book a supporter in your block list" << endl;
                        BlockError();
                        return;
                    }

            }
        }
        if(isSupporter){
            logged_in_member = nullptr;
        }
        if(!isValidSupporter){
            cout << colors::RED << "Please enter the valid supporter's id" << colors::RESET << endl;
        }
    }

    void viewHistory(){//For host to view which supporter they have booked 
        bool isSupporter = (logged_in_member == nullptr);
        
        if(isSupporter){
            logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
        }

        cout << "****THE LIST OF SUPPOTER YOU HAVE BOOKED****\n";
        int count = 1;
        for(int i = 0; i < booking_list.size(); i++){
            if ( logged_in_member->getMemberId() == booking_list[i]->getHostId()){//Check if current user is = host id 
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getSupportId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                        cout <<"Booking " + std::to_string(count) <<
                            "\nBooking ID: " + booking_list[i]->getBookingId() <<
                            "\nSupporter name: " + member_list[a]->getFullName() <<
                            "\nRating score: Will update" <<
                            "\nCity: " + member_list[a]->getCity() <<
                            "\nStatus: " + booking_list[i]->getStatus() <<
                            "\nProgress: " + booking_list[i]->getProgress() <<
                            "\nTime: " + booking_list[i]->getTime() << endl;
                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        if(isSupporter){
            logged_in_member = nullptr;
        }
    }

    void setStatusById(string id, string choice){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                booking_list[i]->setStatus(choice);
                break;
            }
        }
    }

    string getStatusById(string id){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                return booking_list[i]->getStatus();
            }
        }
        return "";
    }

    void setProgressById(string id, string choice){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                booking_list[i]->setProgress(choice);
                break;
            }
        }
    }

    void addHostScoreByID(string id, int rating){
        string currentUser;
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                currentUser = booking_list[i]->getHostId();
                break;
            }
        }

        loop(member_list.size()){
            if(currentUser == member_list[i]->getMemberId()){
                member_list[i]->collectScore(rating);
                break;
            }
        }
    }

    void addSupporterScoreByID(string id, int rating, int skill_rating){
        string currentUser;
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                currentUser = booking_list[i]->getSupportId();
                break;
            }
        }

        loop(member_list.size()){
            if(currentUser == member_list[i]->getMemberId()){
                Supporter* supporter = dynamic_cast<Supporter*>(member_list[i]);
                supporter->collectSupporterScore(rating, skill_rating);
                break;
            }
        }
    }

    void setHostCommentById(string id, string comment){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                booking_list[i]->setHostComment(comment);
                break;
            }
        }
    }

    string getProgressById(string id){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                return booking_list[i]->getProgress();
            }
        }
        return "";
    }

    void setHostRatingById(string id, int rating){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                booking_list[i]->setHostRating(rating);
                break;
            }
        }
    }

    double getMoneyById(string id){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                return booking_list[i]->getTotalCost();
            }
        }
        return 0;
    }

    void decideJob(){//For supporter to answer the request booking from host. Either accept or reject or remain pending
        cout << "****THE LIST OF REQUEST BOOKING****\n";
        int count = 1;
        std::vector<string> current_job = {};
        
        for(int i = 0; i < booking_list.size(); i++){
            if ( logged_in_supporter->getMemberId() == booking_list[i]->getSupportId() && booking_list[i]->getProgress() != "COMPLETED"){//Check if current user is = host id 
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getHostId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                        //push the id to the vector current_job
                        current_job.push_back(booking_list[i]->getBookingId());
                        //Print basic information
                        cout <<"Booking: " << std::to_string(count) <<
                            "\nBooking ID: " << booking_list[i]->getBookingId() <<
                            "\nHost name: " << member_list[a]->getFullName() <<
                            "\nCity: " << member_list[a]->getCity() <<
                            "\nStatus: " << booking_list[i]->getStatus() <<
                            "\nTime: " << booking_list[i]->getTime() << 
                            "\nCost: " << booking_list[i]->getTotalCost() <<
                            "\nHost Rating: " << std::fixed << std::setprecision(2) << member_list[a]->getAverageRatingScore() << endl;

                        if(booking_list[i]->getStatus() == "ACCEPTED"){
                            cout << "Progress: " << booking_list[i]->getProgress() << endl;
                        }
                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        //If current job is empty. Notify that and return the function
        if(current_job.empty()){
            cout << "You do not have booking yet" << endl;
        }else{
            string choice;
            char decide = ' ';
            bool validChoice = false;

            cout <<"Type 'Quit' to exit\n" <<
                "Enter booking invitation code: " ;
            std::getline(cin >> std::ws, choice);

            if(choice == "Quit" || choice == "quit"){
                cout << "Returning home page" << endl;
            } else{
                loop(current_job.size()){
                    if(choice == current_job[i]){
                        validChoice = true;
                        if(getProgressById(current_job[i]) == "IN PROGRESS"){
                            cout << "Have you completed the job?" << endl;
                            cout << "1. Yes\n" 
                                 << "2. No" << endl;
                            cout << ">Your choice: "; cin >> decide;
                            switch(decide){
                                case '1':
                                    //&***************UNCOMMENT IT WHEN DONE***************
                                    setProgressById(current_job[i], "COMPLETED");
                                    cout << "Congratulation! You just finished the job." << endl;
                                    cout << "You just receive: " << getMoneyById(current_job[i]) << " CP" << endl;
                                    logged_in_supporter->addCreditPoint(getMoneyById(current_job[i]));//add the new money to the supporter's account
                                    cout << "Your new balance: " << logged_in_supporter->getCreditPoint() << endl;

                                    cout << "Do you want to leave feedback and rate your host\n";
                                    cout << "1. Yes\n" << "2. No\n" << ">Your choice:";
                                    cin >> decide;
                                    if(decide == '1'){
                                        bool check = true;
                                        while(check){
                                            cout << "Please rate your host (scale: 0 - 10)" << endl;
                                            cout << ">Rating: ";
                                            string input;  
                                            cin >> input;

                                            std::stringstream iss(input);
                                            int rating;
                                            if(iss >> rating){
                                                //IF the conversion is successful
                                                if(rating >= 0 && rating <= 10){
                                                    if(rating < 5){
                                                        cout << "Sorry about your bad experiance" << endl;
                                                        cout << "Do you want to block this host (IMPROVE SOON)" << endl;
                                                    }
                                                    //modify rating
                                                    setHostRatingById(current_job[i], rating);
                                                    cout << "Leave comment about your host(Put 'x' if you dont want to comment): " << endl;
                                                    cout << ">Comment: "; 
                                                    string user_comment; 
                                                    getline(cin >> std::ws, user_comment);
                                                    setHostCommentById(current_job[i], user_comment);

                                                    addHostScoreByID(current_job[i], rating);

                                                    cout << "Thank you for your feedback\n";
                                                    check = false;
                                                } else{
                                                    cout << "****Please enter the valid rating****" << endl;
                                                } 
                                            }else{
                                                cout << "Please enter the valid rating!" << endl;
                                            }
                                        }

                                    } else{
                                        setHostRatingById(current_job[i], 11);
                                        setHostCommentById(current_job[i], "x");
                                        addHostScoreByID(current_job[i], 11);
                                        cout << "Return main page!" << endl;
                                        break;
                                    }

                                    break;
                                case '2':
                                    cout << "Return the main page" << endl;
                                    break;
                                default:
                                    cout << "Return the main page" << endl;
                                    break;
                            }


                        }   
                        else if(getStatusById(current_job[i]) == "ACCEPTED"){
                            cout << "***Do you want to start the job***\n" << endl;
                            cout << "1. Take the job\n" 
                                 << "2. Return\n"
                                 << ">Your choice: ";
                            cin >> decide;
                            switch (decide){
                            case '1':
                                cout << "YOU ACCEPT TAKE THE JOB\n";
                                setProgressById(current_job[i], "IN PROGRESS");
                                break;
                            case '2':
                                cout << "RETURN\n";
                                break;
                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                            }
                            
                        }else{
                            cout << "1. ACCEPTED\n"<<
                                    "2. REJECTED\n" <<
                                    "3. RETURN\n"<< endl;
                            cout << ">Your choice: "; cin >> decide;
                            switch(decide){
                                case '1':
                                    setStatusById(current_job[i], "ACCEPTED");
                                    break;
                                case '2':
                                    setStatusById(current_job[i], "REJECTED");
                                    break;
                                case '3':
                                    break;
                                    break;
                            }
                        }
                    }
                }
                if(!validChoice){
                    cout << "Please enter the valid choice!" << endl;
                }
            }
        }
    }

    void buyCredit(){
    bool check = true;
    string choice;
    int option;
        string verify;

        if (logged_in_supporter == nullptr)
        {
            while (check)
            {
                cout << "****Buying Credit Menu****" << endl;
                cout << "Current balance: " << logged_in_member->getCreditPoint() << " CP "
                     << "\n"
                     << endl;
                cout << "Ammount list: \n"
                     << "1. Price: $20 \n"
                     << "Total credit point: 20 CP \n"
                     << "====================================\n"
                     << "2. Price: $50 \n"
                     << "Total credit point: 50 CP + 5 CP Bonus \n"
                     << "====================================\n"
                     << "3. Price: $100 \n"
                     << "Total credit point: 100 CP + 20 CP Bonus\n"
                     << "====================================\n"
                     << endl;
                cout << "Choice the bundle: ";
                cin >> option;
                //==verify part===
                cout << "Please enter your password to verify: ";
                getline(cin >> std::ws, verify);
                if (verify == logged_in_member->getPassword())
                {
                    switch (option)
                    {
                    case 1:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 20);
                        cout << "You have bought 20 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint() << endl;
                        break;
                    case 2:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 55);
                        cout << "You have bought 55 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint() << endl;
                        break;
                    case 3:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 120);
                        cout << "You have bought 120 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint()<< endl;
                        break;
                    case 4:
                        cout << " Returning to home page....." << endl;
                        break;
                    default:
                        cout << "Invalid option, please select again" << endl;
                    }
                    cout << "Do you want to continue buying credit [Y/N]: ";
                    std::getline(std::cin >> std::ws, choice);
                    if (choice == "N" || choice == "N")
                    {
                        check = false;
                    }
                    cout << "Successfully buy credit" << endl;
                }
                else
                {
                    cout << "Verify fail.Please try again" << endl;
                }
            }
        }
        else
        {
            while (check)
            {
                cout << "****Buying Credit Menu****" << endl;
                cout << "Current credit point balance: " << logged_in_supporter->getCreditPoint() << " CP "
                     << "\n"
                     << endl;
                cout << "Ammount list: \n"
                     << "1. Price: $20 \n"
                     << "Total credit point: 20 CP \n"
                     << "====================================\n"
                     << "2. Price: $50\n"
                     << "Total credit point: 50 CP + 5 CP Bonus \n"
                     << "====================================\n"
                     << "3. Price: $100 \n"
                     << "Total credit point: 100 CP + 20 CP Bonus\n"
                     << "====================================\n"
                     << endl;
                cout << "Choice the bundle: ";
                cin >> option;
                //==verify part===
                cout << "Please enter your password to verify: ";
                getline(cin >> std::ws, verify);
                if (verify == logged_in_supporter->getPassword())
                {
                    switch (option)
                    {
                    case 1:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 20);
                        cout << "You have bought 20 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() << endl;
                        break;
                    case 2:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 55);
                        cout << "You have bought 55 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() << endl;
                        break;
                    case 3:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 120);
                        cout << "You have bought 120 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() << endl;
                        break;
                    case 4:
                        cout << " Returning to home page....." << endl;
                        break;
                    default:
                        cout << "Invalid option, please select again" << endl;
                    }
                    cout << "Do you want to continue buying credit [Y/N]: ";
                    std::getline(std::cin >> std::ws, choice);
                    if (choice == "N")
                    {
                        check = false;
                    }
                    cout << "Successfully buy credit" << endl;
                }
                else
                {
                    cout << "Verify fail.Please try again" << endl;
                }
            }
        }
    }

    void displaySupporter(){
        cout << "****Supporter List****" << endl;
        cout << "================================================================\n";
        loop(this->member_list.size()){
            if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){
                    cout << "Supporter " << i + 1 << ": " << endl;
                    cout << "Member id: " << supporter->getMemberId() <<endl;
                    cout << "Fullname: " << supporter->getFullName() << endl;
                    cout << "City: " << supporter->getCity() << endl;
                    cout << "Skill: " << supporter->displaySkillList() << endl;
                    cout << "Cost Per Hour: " << supporter->getCost() << endl;
                    cout << "Introduction: " << supporter->getAboutMe() << endl;
                    cout << "Status: " <<  supporter->statusToString(supporter->getStatus()) << endl;
                    cout << "================================================================\n";
            }
        }
    }

    void statusSetting(){
        cout <<"****Status Setting Menu****" << endl;
        cout <<"Your current status: " << logged_in_supporter->statusToString(logged_in_supporter->getStatus()) << endl;

        bool check = true;
        char option;

        if (logged_in_supporter->getStatus() == Status::OFFLINE){
            while (check){
                cout << "Do you want to change your status to ONLINE [Y/N]";
                cin >> option;

                if(option == 'Y' || option == 'y'){
                    logged_in_supporter->setStatus(Status::ONLINE);
                    cout << "Your status switch to ONLINE, people can book you now" << endl;
                    check = false;
                }
                else if(option == 'N' || option == 'n'){
                     cout << "Your status remaining OFFLINE" << endl;
                        check = false;
                }
                else{
                    cout << "Invalid input. Please input again" << endl;
                }
            }
        }
        else if (logged_in_supporter->getStatus() == Status::ONLINE){
            while (check){
                cout << "Do you want to change your status to OFFLINE [Y/N]";
                cin >> option;
               if(option == 'Y' || option == 'y'){
                    logged_in_supporter->setStatus(Status::OFFLINE);
                    cout << "Your status switch to OFFLINE, people can book you now" << endl;
                    check = false;
                }
                else if(option == 'N' || option == 'n'){
                     cout << "Your status remaining ONLINE" << endl;
                        check = false;
                }
                else{
                    cout << "Invalid input. Please input again" << endl;
                }
            }
        }         
    }

    void viewHistoryJob(){

        cout << "****THE LIST OF HISTORY JOB****\n";
        int count = 1;
        std::vector<string> current_job = {};
        
        for(int i = 0; i < booking_list.size(); i++){
            if ( logged_in_supporter->getMemberId() == booking_list[i]->getSupportId()){//Check if current user is = host id 
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getHostId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                        //push the id to the vector current_job
                        current_job.push_back(booking_list[i]->getBookingId());
                        //Print basic information
                        cout <<"Booking: " << std::to_string(count) <<
                            "\nBooking ID: " << booking_list[i]->getBookingId() <<
                            "\nHost name: " << member_list[a]->getFullName() <<
                            "\nRating score: Will update" <<
                            "\nCity: " << member_list[a]->getCity() <<
                            "\nTime: " << booking_list[i]->getTime() << 
                            "\nHost comment: will update" <<
                            "\nHost rated you: will update" << endl;
                            
                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        //If current job is empty. Notify that and return the function
        if(current_job.empty()){
            cout << "You do not have any history booking yet" << endl;
        }
    }

    void setSupportRatingById(int skill_score, int support_score, string comment, string id){
        loop(booking_list.size()){
            if(booking_list[i]->getBookingId() == id){
                booking_list[i]->setSkillRatingScore(skill_score);
                booking_list[i]->setSupporterRatingScore(support_score);
                booking_list[i]->setSupporterComment(comment);
                break;
            }
        }
    }

    void checkCompleteTask(){
        std::vector<string> complete_list_id;//store booking id
        bool isSupporter = (logged_in_member == nullptr);

        if(isSupporter){
            logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
        }

        cout <<"****YOUR BOOKING HAVE BEEN FINISHED****"<<endl;
        int count = 1;
        std::vector<string> current_job = {};
        
        for(int i = 0; i < booking_list.size(); i++){
            if (logged_in_member->getMemberId() == booking_list[i]->getHostId() && booking_list[i]->getProgress() == "COMPLETED" && booking_list[i]->getSkillRatingScore() != 11 && booking_list[i]->getSupporterComment() == " " ){//Check if current user is = host id 
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getSupportId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                        cout <<"Booking: " << std::to_string(count) <<
                            "\nBooking ID: " << booking_list[i]->getBookingId() <<
                            "\nSupporter name: " << member_list[a]->getFullName() <<
                            "\nCity: " << member_list[a]->getCity() <<
                            "\nTime: " << booking_list[i]->getTime() << 
                            "\nTotal Cost: " << booking_list[i]->getTotalCost() <<
                            "\nSupporter comment: " <<booking_list[i]->getHostComment() << endl;
                            if(booking_list[i]->getHostRating() != 11){//if the host rating is 11 --> supporter do not want to rate
                                cout << "\nSupporter rated you: " <<booking_list[i]->getHostRating() << endl;
                            }

                            complete_list_id.push_back(booking_list[i]->getBookingId());
                            
                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        if(complete_list_id.empty()){
            cout << "You do not have any booking that need to be rated" << endl;
            return;
        }

        bool valid_choice = false;

        string choice = "";
        cout <<"Please enter a booking id: ";
        getline(cin >> std::ws, choice);
        bool rate_check = true;

        loop (complete_list_id.size()){
            if(complete_list_id[i] == choice){
                bool check = true;
                int option;
                string comment = " ";
                int rating;
                int skill;
                valid_choice = true;

                while(check){
                    cout << "Congratulation! Your booking has been finished" <<endl;
                    cout << "The cost for this booking is: " << getMoneyById(complete_list_id[i]) << endl;
                    logged_in_member->subtractCreditPoint(getMoneyById(complete_list_id[i]));
                    cout << "Your new balance: " << logged_in_member->getCreditPoint() << endl;
                    cout <<"Do you want to give a feedback to this supporter?"<< endl;
                    cout << "1. Yes"<<
                            "\n2. No" << endl;
                    cin >> option;

                    switch(option){
                        case 1:
                            while(rate_check){
                                cout << "Please rate your supporter's skill(scale: 0 - 10): ";
                                cout << ">Rating: ";
                                cin >> skill;
                                cout << "How would you like this supporter (scale 0 - 10): ";
                                cout << ">Rating: ";
                                cin >> rating;
                                if (rating <= 10 && rating >= 0 && skill <= 10 && skill >= 0){
                                    rate_check = false;
                                }
                                else{
                                    cout << "Please enter the valid rating!" << endl;
                                }
                            }
                            cout << "Give some comment (Put 'x' if you do not want to comment): ";
                            getline(cin >> std::ws, comment);

                            setSupportRatingById(skill, rating, comment, complete_list_id[i]);

                            addSupporterScoreByID(complete_list_id[i],rating, skill);

                            cout << "Thank you for giving feedback" << endl;
                            check = false;
                            break;
                        case 2:
                            setSupportRatingById(11, 11, "x", complete_list_id[i]);
                            addSupporterScoreByID(complete_list_id[i],11,11);

                            check = false;
                            break;
                        default: 
                            cout << "Please enter again!";
                            break;
                    }
                }
            }
        }
        if(!valid_choice){
            cout <<"Please enter valid id"<<endl;
        }

        if(isSupporter){
            
            logged_in_member = nullptr;
        }
    }

    string getCurrentStatus(){
        return logged_in_supporter->statusToString(logged_in_supporter->getStatus());
    }

    int getNotification(){ 
        bool isSupporter = (logged_in_member == nullptr);

        if(isSupporter){
            logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
        }
        
        int count = 0;

        for(int i =0; i < booking_list.size(); i++){
            if (logged_in_member->getMemberId() == booking_list[i]->getHostId() && booking_list[i]->getProgress() == "COMPLETED" && booking_list[i]->getSupporterComment() == " "){
                count++;
            }
        }

        if(isSupporter){
            logged_in_member = nullptr;
        }
        
        return count;
    }

    int getRequestNotification(){
        int count = 0;
        loop (booking_list.size()){
            if (logged_in_supporter->getMemberId() == booking_list[i]->getSupportId() && booking_list[i]->getStatus() == "PENDING"){
                count++;
            }
        }
        return count;
    }

    bool blockUser(){
        cout << "Enter the id of the user that you want to block:";
        string input;
        getline(cin >> std::ws, input);
       

        bool isSupporter = (logged_in_member == nullptr);
        if(isSupporter){
            logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
        }
        
        bool valid_choice = false;
        char choice; 
        bool check = true;
        if(input == logged_in_member->getMemberId()){
            cout << "You can not block yourself!" << endl;
            return false;
        }
        loop(member_list.size()){
            if(input == member_list[i]->getMemberId()){
                valid_choice = true;
                while(check){
                    cout << "Do you want to block this person:" << endl;
                    cout << "Id: " << member_list[i]->getMemberId();
                    cout << " Name: " << member_list[i]->getFullName() << endl;
                    cout << "1. Yes\n" 
                        << "2. Return\n";
                    cout << ">Your choice: ";
                    cin >> choice;
                    if(choice == '1'){
                        logged_in_member->block_list.push_back(member_list[i]->getMemberId());
                        cout << "Block this person successfully!" << endl;
                        check = false;
                    }else if(choice == '2'){
                        cout << "Return to main dashboard!" << endl;
                        check = false;
                    }else{
                        cout << "Please enter valid choice!" << endl;
                    }
                }
            }
        }

        if(isSupporter){
            // logged_in_supporter->setBlockList(logged_in_member->block_list);
            logged_in_member = nullptr;
        }

        if(!valid_choice){
            cout << "Please enter valid input!" << endl;
        }

        return true;
    }

    string getFullNameFromId(string id){
        loop(member_list.size()){
            if(id == member_list[i]->getMemberId()){
                return member_list[i]->getFullName();
            }
        }
        return "Can not find!";
    }

    void showBlockList(){
        //**************IT HASN'T DO WITH SUPPORTER*************

        if(logged_in_member->block_list.size() == 0){
            cout << "EMPTY Block list" << endl;
            return;
        }

        for(int i = 0; i << logged_in_member->block_list.size(); ++i){
            cout << "Your block list: " << endl;
            cout << i + 1 << ": " << getFullNameFromId(logged_in_member->block_list[i]) << endl;
        }
    }

    std::vector<Member*>& getMemberList(){
        return this->member_list;
    }

    std::vector<BookingSupporter*>& getBookingList(){
        return this->booking_list;
    }

   void setMemberList(std::vector<Member*>& new_member_list){
        this->member_list = new_member_list;
    }

    void setBookingList(std::vector<BookingSupporter*>& new_booking_list){
        this->booking_list = new_booking_list;
    }

    Member* getLoggedInMember(){
        return this->logged_in_member;
    }

    Supporter* getLoggedInSupporter(){
        return this->logged_in_supporter;
    }

    bool getIsAdmin(){
        return this->is_admin;
    }

    void setIsAdmin(bool is_admin){
        this->is_admin = is_admin;
    }

    BookingSupporter getBooking(){
        return this->booking;
    }

    ~System() {//Clear the member to advoid memory leak
        for (Member* member : member_list) {
            delete member;
        }
        for(BookingSupporter* booking_supporter : booking_list){
            delete booking_supporter;
        }
    }
};
#endif