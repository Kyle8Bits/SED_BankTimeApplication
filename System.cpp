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

using std::cout;
using std::cin;
using std::string;
using std::endl;

#define loop(n) for(int i = 0; i < n; ++i)
#define FILENAME "members.dat"
#define clearScreen() std::cout << "\x1B[2K\x1B[1G"
class System{
private:
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

    bool addInformation(){ //THIS IS SET ABOUT ME
        cout << "In this section you can introduce yourself, so that the another member can know about you and your skills!" << endl;

        string input_from_user;
        getline(cin >> std::ws, input_from_user);
        
        if(checkNonEmpty(input_from_user)){
            logged_in_member->setAboutMe(input_from_user);
            cout << "Modify information sucessfully!" << endl;
            return true;
        }

        return false;
    }
    //----------------------THIS IS TO PRINT CALENDER---------------------
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

    void printCalendar(int year, int month) {
        clearScreen();
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
            std::cout << std::setw(5) << day;

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
        std::vector<std::pair<Time,Time>> time_pair_list;
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
        //----------------------THIS IS TO CHOOSE A CALENDAR---------------------
        int year = 2024; // Starting year
        int month = 1;   // Starting month
        int choice = 0;
        while (choice != 4) {
            printCalendar(year, month);
            std::cout << "Choose an option:" << std::endl;
            std::cout << "1. Previous Month" << std::endl;
            std::cout << "2. Next Month" << std::endl;
            std::cout << "3. Customize (Select Month/Day)" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter choice: ";
            std::cin >> choice;
            switch (choice) {
                case 1:
                    if (month == 1) {
                        month = 12;
                        --year;
                    } else {
                        --month;
                    }
                    break;
                case 2:
                    if (month == 12) {
                        month = 1;
                        ++year;
                    } else {
                        ++month;
                    }
                    break;
                case 3:
                    std::cout << "Enter year: ";
                    std::cin >> year;

                    std::cout << "Enter month (1-12): ";
                    std::cin >> month;

                    if (year < 0 || month < 1 || month > 12) {
                        std::cout << "Invalid year or month entered." << std::endl;
                        break;
                    }
                    break;
                case 4:
                    std::cout << "Exiting..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please select again." << std::endl;
                    break;
            }
        }
            //----------------------THIS FOR GETTING AVAILABILIITY PERIOD---------------------
        string start_time_input, end_time_input;
        int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
        int day;
        cout << "What is your free time (ex: 8:00 to 10:00, or 20:30 to 22:00)" << endl;
        //----------------------THIS FOR GETTING START TIME---------------------
        bool check2 = true;
        while(check2){
            std::cout << "Enter free day for the month (1-" << getDaysInMonth(month, year) << "): ";
            std::cin >> day;
            if (!isValidDate(day, month, year)) {
                std::cout << "Invalid day entered. Please enter a valid day within the month." << std::endl;
                continue;
            }
            cout << "Start time: ";
            getline(cin >> std::ws, start_time_input);
            //hh:mm
            //h:m
            //2:20, 2:3
            //24hAMPM
            //start time: 20:00
            // end time: 18:00
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
            
            time_pair_list.push_back(std::make_pair(Time(start_time_hour, start_time_minute), Time(end_time_hour, end_time_minute)));
            
            cout << "Do you want to continue: [Y/N]: ";
                char choice; cin >> choice;
                if(choice != 'Y' && choice != 'y'){
                    check2 = false;
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

        
        //----------------------ADD ALL IT IN SUPPORTER---------------------
        //first change the id of logged_in_member from M to S
        string supporter_id = logged_in_member->getMemberId(); supporter_id[0] ='S';//Change the first cahracter of id from M to S
        //set the id of logged_in_member
        logged_in_member->setMemberId(supporter_id);
        //set the basic introduction of logged_in_member
        logged_in_member->setAboutMe(about_me_input);
        //create new pointer supporter
        
        Supporter* new_supporter = new Supporter(*logged_in_member,time_pair_list, skill_list_input, cost_input);

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
            logged_in_supporter->displayBlockList();
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

    bool isInBlockList(std::vector<string> block_list, string block_id){
        loop(block_list.size()){
            if(block_list[i] == block_id){
                return true;
            }
        }
        return false;
    }

    void displayAvailableSupporter(){
        bool isSupporter = (logged_in_member == nullptr);
        if(isSupporter){
            logged_in_member = logged_in_supporter;
        }
        
        cout << "****Available Supporter List****" << endl;
        cout << "================================================================\n";
        loop(this->member_list.size()){
            if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){
                //Go to each member to print the information
                if(supporter->getMemberId() != logged_in_member->getMemberId() && supporter->getStatus() == Status::ONLINE){//advoid display the current logged in supporter information
                    if(!isInBlockList(logged_in_member->block_list, supporter->getMemberId() )){
                        //IF the current supporter is not in the block list, we wil print the information of supporter
                        cout << "Supporter " << i + 1 << ": " << endl;
                        cout << "Member id: " << supporter->getMemberId() <<endl;
                        cout << "Fullname: " << supporter->getFullName() << endl;
                        cout << "City: " << supporter->getCity() << endl;
                        cout << "Skill: " << supporter->displaySkillList() << endl;
                        cout << "Available Periods: " << supporter->displaySkillList();
                        cout << "Cost Per Hour: " << supporter->getCost() << endl;
                        cout << "Introduction: " << supporter->getAboutMe() << endl;
                        cout << "================================================================\n";
                        availableSupporter.push_back(supporter);
                    }
                    //still push that supporter, even if it in the block list of the current users
                }
            }
        }
        if(isSupporter){
            logged_in_member = nullptr;
        }
    }

    string toLower(string str){
        loop(str.length()){
            str[i] = std::tolower(str[i]);
        }
        return str;
    }

    bool checkValidTime(string time){
        for(int i = 0; i < time.length(); ++i){
            if(!isdigit(time[i]) && time[i] != ':'){
                return false;
            }
        }
        return true;
    }

    bool checkValidTime(int start_hour, int start_minute, int end_hour, int end_minute){
        if(start_hour < 0 || start_hour > 23 || start_minute < 0 || start_minute > 59 || 
           end_hour < 0 || end_hour > 23 || end_minute < 0 || end_minute > 59){
            cout << "Please enter the the true range~!" << endl;
            return false;
        }

        if(end_hour < start_hour || (end_hour == start_hour && end_minute <= start_minute)){
            cout << "Your end time must larger than your start time!" << endl;
            return false;
        }
        
        return true;
    }
    

    void createBooking(){
        cout << "****WELCOME TO BOOKING DASHBOARD****"<<endl;
        displayAvailableSupporter();
        cout << "Please input the supporter's id that you want to book: ";
        string input; cin >> input;

        bool isSupporter = (logged_in_member == nullptr);
        bool isValidSupporter = false;//this to check the create bookign is successfully or not?

        loop(availableSupporter.size()){
            if(toLower(input) == toLower(availableSupporter[i]->getMemberId())){
                if(isSupporter){
                    logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
                }
                if(logged_in_member->getCreditPoint() >= availableSupporter[i]->getCost()){//check the credit point of the users and the cost per hour of the supporter
                    if(!isInBlockList(logged_in_member->getBlockList(), availableSupporter[i]->getMemberId())){
                        int year = 2024; // Starting year
                        int month = 1;   // Starting month
                        int choice = 0;
                        while (choice != 4) {
                            printCalendar(year, month);
                            std::cout << "Choose an option:" << std::endl;
                            std::cout << "1. Previous Month" << std::endl;
                            std::cout << "2. Next Month" << std::endl;
                            std::cout << "3. Customize (Select Month/Day)" << std::endl;
                            std::cout << "4. Exit" << std::endl;
                            std::cout << "Enter choice: ";
                            std::cin >> choice;
                            switch (choice) {
                                case 1:
                                    if (month == 1) {
                                        month = 12;
                                        --year;
                                    } else {
                                        --month;
                                    }
                                    break;
                                case 2:
                                    if (month == 12) {
                                        month = 1;
                                        ++year;
                                    } else {
                                        ++month;
                                    }
                                    break;
                                case 3:
                                    std::cout << "Enter year: ";
                                    std::cin >> year;

                                    std::cout << "Enter month (1-12): ";
                                    std::cin >> month;

                                    if (year < 0 || month < 1 || month > 12) {
                                        std::cout << "Invalid year or month entered." << std::endl;
                                        break;
                                    }
                                    break;
                                case 4:
                                    std::cout << "Exiting..." << std::endl;
                                    break;
                                default:
                                    std::cout << "Invalid choice. Please select again." << std::endl;
                                    break;
                            }
                        }
                        int day;
                        std::cout << "Enter free day for the month (1-" << getDaysInMonth(month, year) << "): ";
                        std::cin >> day;
                        if (!isValidDate(day, month, year)) {
                            std::cout << "Invalid day entered. Please enter a valid day within the month." << std::endl;
                            continue;
                        }
                        cout << "Choose the time you want to book. Noitce that: the time you choose must match with the free time of the supporter!" << endl;
                        int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
                        string start_time_input, end_time_input;
                        cout << "Start Time: ";
                        getline(cin >> std::ws, start_time_input);
                        cout << "End Time: ";
                        getline(cin >> std::ws, end_time_input);

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

                            if(checkValidTime(start_time_hour, start_time_minute, end_time_hour, end_time_minute)){
                                //PUSH NEW BOOKING TO THE BOOKING LIST
                                BookingSupporter* booking = new BookingSupporter(logged_in_member->getMemberId(), availableSupporter[i]->getMemberId());
                                //SET THE START AND END TIME OF THE NEW BOOKINg
                                booking->setStartTime(Time(start_time_hour, start_time_minute));
                                booking->setEndTime(Time(end_time_hour, end_time_minute));
                                booking_list.push_back(booking);
                                cout << "Your booking has been created" << endl;
                                isValidSupporter = true;
                                break; 
                            }else{
                                //if the condition is wrong, we return the function
                                return;
                            }
                        }else{
                            cout << "Please enter the valid input!" << endl;
                            return;
                        }            
                    }else{
                        cout <<"You can not book a supporter in your block list" << endl;
                        return;
                    }
                }else{
                    cout << "Insufficient credit points to book this supporter" << endl;
                    isValidSupporter = true;
                    break;
                }
            }
        }
        if(isSupporter){
            logged_in_member = nullptr;
        }
        if(!isValidSupporter){
            cout << "Please enter the valid supporter's id" << endl;
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
                            "\nRating score: Will update" <<
                            "\nCity: " << member_list[a]->getCity() <<
                            "\nStatus: " << booking_list[i]->getStatus() <<
                            "\nTime: " << booking_list[i]->getTime() << endl;
                            
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
                            cout << "Do you complete the job?" << endl;
                            cout << "1. Yes\n" 
                                 << "2. No" << endl;
                            cout << ">Your choice: "; cin >> decide;
                            switch(decide){
                                case '1':
                                    //&***************UNCOMMENT IT WHEN DONE***************
                                    setProgressById(current_job[i], "COMPLETED");
                                    cout << "Congratulation! You just finished the job." << endl;
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
                                                    cout << "Leave comment about your host: " << endl;
                                                    cout << ">Comment: "; 
                                                    string user_comment; 
                                                    getline(cin >> std::ws, user_comment);
                                                    setHostCommentById(current_job[i], user_comment);
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
        // int* otp = new int(rand() % (999999 - 100000 + 1) + 100000);
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
                switch(option){
                    case 'Y':
                        logged_in_supporter->setStatus(Status::ONLINE);
                        check = false;
                        break;
                    case 'N':
                        cout << "Your status remaining OFFLINE" << endl;
                        check = false;
                        break;
                    default:
                        cout << "Invalid input. Please input again" << endl;
                }
            }
        }
        else if (logged_in_supporter->getStatus() == Status::ONLINE){
            while (check){
                cout << "Do you want to change your status to OFFLINE [Y/N]";
                cin >> option;
                switch(option){
                    case 'Y':
                        logged_in_supporter->setStatus(Status::OFFLINE);
                        check = false;
                        break;
                    case 'N':
                        cout << "Your status remaining ONLINE" << endl;
                        check = false;
                        break;
                    default:
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
        std::vector<string> complete_list_id;
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
                            "\nSupporter comment: " <<booking_list[i]->getHostComment() <<
                            "\nSupporter rated you: " <<booking_list[i]->getHostRating() << endl;

                            complete_list_id.push_back(booking_list[i]->getBookingId());
                            
                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        bool valid_choice = false;

        cout << "==============================================\n" << endl;

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
                    cout <<"Do you want to give a feedback to this supporter?"<< endl;
                    cout << "1. Yes"<<
                            "\n2. No" << endl;
                    cin >> option;

                    switch(option){
                        case 1:
                            while(rate_check){
                                cout << "What would you rate this supporter's skill [0/10]: ";
                                cin >> rating;
                                cout << "How would you like this supporter [0/10]: ";
                                cin >> skill;
                                if (rating <= 10 && rating >= 0 && skill <= 10 && skill >= 0){
                                    rate_check = false;
                                }
                                else{
                                    cout << "Invalid. The rating must less than 10" << endl;
                                }
                            }
                            cout << "Give some comment (Put blank if you do not want to comment): ";
                            getline(cin >> std::ws, comment);

                            setSupportRatingById(skill, rating, comment, complete_list_id[i]);

                            cout << "Thank you for giving feedback" << endl;
                            check = false;
                            break;
                        case 2:
                            setSupportRatingById(11, 11, " ", complete_list_id[i]);
                            // booking_list[i]->setSupporterRatingScore(11);
                            // booking_list[i]->setSkillRatingScore(11);
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
        int count = 0;
        for(int i =0; i < booking_list.size(); i++){
            if (booking_list[i]->getProgress() == "COMPLETED" && booking_list[i]->getHostComment() == " "){
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
            logged_in_supporter->setBlockList(logged_in_member->block_list);
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

    ~System() {//Clear the member to advoid memory leak
        for (Member* member : member_list) {
            delete member;
        }
        for(BookingSupporter* booking_supporter : booking_list){
            delete booking_supporter;
        }
    }
};
