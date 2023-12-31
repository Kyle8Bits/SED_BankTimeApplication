
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <utility>

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

class System{
private:
    std::vector<Member*> member_list; 
    std::vector<BookingSupporter*> booking_list;
    std::vector<string> validSupporterIDs;//This to restrict for users only book the valid supporter id
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
            cout << "****Member list****" << endl;
            loop(this->member_list.size()){
                //Go to each member to print the information
                cout << "Member " << i + 1 << ": " << endl;
                cout<< "User ID: " << member_list[i]->getMemberId()
                    << ", Username: " << member_list[i]->getUsername() 
                    << ", Password: "<< member_list[i]->getPassword()
                    << ", Credit Point: " << member_list[i]->getCreditPoint()
                    << ", Fullname: " << member_list[i]->getFullName()
                    << ", Phone Number: " << member_list[i]->getPhoneNumber()
                    << ", Address: " << member_list[i]->getAddress()
                    << ", City: " << member_list[i]->getCity()
                    << ", About Me: " << member_list[i]->getAboutMe()
                    << ", Host Rating Score: " << member_list[i]->getHostRatingScore()
                    << ", Host Count: " << member_list[i]->getHostCount()
                    << ", Block List: HAVEN't DONE YET" << endl;
                //check if the member is a Supporter or a regular member
                if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){
                    //If it is a supporter, we will print more information of supporter
                    cout << "SUPPORTER:" 
                        << ", Availability Time: " << supporter->getAvailabilityPeriod()
                        << ", Skill List: " << supporter->displaySkillList()
                        << ", Cost: " << supporter->getCost()
                        << ", average skill rating score: " << supporter->getSkillRatingScore()
                        << ", average support rating score: " << supporter->getSupportRatingScore()
                        << ", support count: " << supporter->getSupportCount() << endl;

                }
            }
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
        
            //----------------------THIS FOR GETTING AVAILABILIITY PERIOD---------------------
        string start_time_input, end_time_input;
        int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
        cout << "What is your free time (ex: 8:00 to 10:00, or 20:30 to 22:00)" << endl;
        //----------------------THIS FOR GETTING START TIME---------------------
        bool check2 = true;
        while(check2){
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

    void viewPersonalInformationMember(){
        cout << "***MY INFORMATION***" << endl;
        cout << "ID: " << logged_in_member->getMemberId() << endl;
        cout << "Username: " << logged_in_member->getUsername() << endl;
        cout << "Password: " << logged_in_member->getPassword() << endl;
        cout << "Credit Point: " << logged_in_member->getCreditPoint() << endl;
        cout << "Full Name: " << logged_in_member->getFullName() << endl;
        cout << "Phone Number: " << logged_in_member->getPhoneNumber() << endl;
        cout << "Address: " << logged_in_member->getAddress() << endl;
        cout << "City: " << logged_in_member->getCity() << endl;
        cout << "About Me: " << logged_in_member->getAboutMe() << endl;
        cout << "Host Rating Score: " << logged_in_member->getHostRatingScore() << endl;
        cout << "Host Count: " << logged_in_member->getHostCount() << endl;
        cout << "Block List:  HAVEN'T DONE YET" << endl;
    }

    void viewPersonalInformationSupporter(){
        cout << "***MY INFORMATION***" << endl;
        cout << "ID: " << logged_in_supporter->getMemberId() << endl;
        cout << "Username: " << logged_in_supporter->getUsername() << endl;
        cout << "Password: " << logged_in_supporter->getPassword() << endl;
        cout << "Credit Point: " << logged_in_supporter->getCreditPoint() << endl;
        cout << "Full Name: " << logged_in_supporter->getFullName() << endl;
        cout << "Phone Number: " << logged_in_supporter->getPhoneNumber() << endl;
        cout << "Address: " << logged_in_supporter->getAddress() << endl;
        cout << "City: " << logged_in_supporter->getCity() << endl;
        cout << "About Me: " << logged_in_supporter->getAboutMe() << endl;
        cout << "Host Rating Score: " << logged_in_supporter->getHostRatingScore() << endl;
        cout << "Host Count: " << logged_in_supporter->getHostCount() << endl;
        cout << "Block List:  HAVEN'T DONE YET" << endl;

        cout << "Time list: " << logged_in_supporter->getPairListToString();
    }

    void displayAvailableSupporter(){
        string current_user;
        cout << "****Available Supporter List****" << endl;
        cout << "================================================================\n";
        loop(this->member_list.size()){
            if(Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])){
                //Go to each member to print the information
                if(logged_in_supporter != nullptr){
                    current_user = logged_in_supporter->getMemberId();
                }
                if(supporter->getMemberId() != current_user && supporter->getStatus() == Status::ONLINE){//advoid display the current logged in supporter information
                    cout << "Supporter " << i + 1 << ": " << endl;
                    cout << "Member id: " << supporter->getMemberId() <<endl;
                    cout << "Fullname: " << supporter->getFullName() << endl;
                    cout << "City: " << supporter->getCity() << endl;
                    cout << "Skill: " << supporter->displaySkillList() << endl;
                    cout << "Cost Per Hour: " << supporter->getCost() << endl;
                    cout << "Introduction: " << supporter->getAboutMe() << endl;
                    cout << "================================================================\n";
                    validSupporterIDs.push_back(supporter->getMemberId());
                }
            }
        }
    }

    string toLower(string str){
        loop(str.length()){
            str[i] = std::tolower(str[i]);
        }
        return str;
    }

    void createBooking(){
        cout << "****WELCOME TO BOOKING DASHBOARD****"<<endl;
        displayAvailableSupporter();
        cout << "Please input the supporter's id that you want to book: ";
        string input; cin >> input;

        bool isSupporter = (logged_in_member == nullptr);
        bool isValidSupporter = false;//this to check the create bookign is successfully or not?

        loop(validSupporterIDs.size()){
            if(toLower(input) == toLower(validSupporterIDs[i])){
                if(isSupporter){
                    logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
                }
                BookingSupporter* booking = new BookingSupporter(logged_in_member->getMemberId(), member_list[i]->getMemberId());
                booking_list.push_back(booking);
                cout << "Your booking has been created" << endl;
                isValidSupporter = true;
                break;
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
                            "\nStatus: " + booking_list[i]->getStatus() << endl;

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

    void decideJob(){//For supporter to answer the request booking from host. Either accept or reject or remain pending
        int count = 1;
        std::vector<string> current_job = {};
        
        for(int i = 0; i < booking_list.size(); i++){
            if ( logged_in_supporter->getMemberId() == booking_list[i]->getSupportId()){//Check if current user is = host id 
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getHostId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                        //push the id to the vector current_job
                        current_job.push_back(booking_list[i]->getBookingId());
                        //Print basic information
                        cout <<"Booking: " + std::to_string(count) <<
                            "\nBooking ID: " + booking_list[i]->getBookingId() <<
                            "\nSupporter name: " + member_list[a]->getFullName() <<
                            "\nRating score: Will update" <<
                            "\nCity: " + member_list[a]->getCity() <<
                            "\nStatus: " + booking_list[i]->getStatus() << endl;

                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }

        string choice;
        char decide = ' ';
        bool check = true;

        cout <<"Type 'Quit' to exit\n" <<
             "Enter booking invitation code: " ;
        std::getline(cin >> std::ws, choice);

        if(choice == "Quit" || choice == "quit"){
            cout << "Returning home page" << endl;
        } else{
            loop(current_job.size()){
                if(choice == current_job[i]){
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
                }else{
                    cout << "Invalid Booking Code.\nPlease try again." << endl;
                }
            }
        }
    }

    void buyCredit(){
        cout <<"Hi";
        // int* otp = new int(rand() % (999999 - 100000 + 1) + 100000);
        bool check = true;
        string choice;
        int option;
            if ( logged_in_supporter ==nullptr){
            while (check){
                cout << "****Buying Credit Menu****" << endl;
                cout << "Current balance: " << logged_in_member->getCreditPoint() << " CP " << "\n" << endl;
                cout << "Ammount list: \n" <<
                        "1. Price: $20 \n" <<
                        "Total credit point: 20 CP \n" <<
                        "====================================\n"<<
                        "2. 50 CP\n" << 
                        "Total credit point: 50 CP + 5 CP Bonus \n" <<
                        "====================================\n"<<
                        "3. $100 \n" << 
                        "Total credit point: 100 CP + 20 CP Bonus\n" <<
                        "====================================\n" << endl;
                cout << "Choice the bundle: ";
                cin >> option;
            
                switch (option){
                    case 1:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 20);
                        cout << "You have bought 20 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint() + 20 << endl;
                        break;
                    case 2:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 55);
                        cout << "You have bought 55 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint() + 5 << endl;
                        break;
                    case 3:
                        logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 120);
                        cout << "You have bought 120 CP\n";
                        cout << "New balance: " << logged_in_member->getCreditPoint() + 120 << endl;
                        break;
                    case 4: 
                        cout <<" Returning to home page....." << endl;
                        break;
                    default:
                        cout <<"Invalid option, please select again" << endl;
                }
                cout << "Do you want to continue buying credit [Y/N]: ";
                std::getline(std::cin >> std::ws, choice);
                if (choice == "N"){
                    check = false;
                }
            }
            }
            else{
              while (check){
                cout << "****Buying Credit Menu****" << endl;
                cout << "Current credit point balance: " << logged_in_supporter->getCreditPoint() << " CP "<< "\n" << endl;
                cout << "Ammount list: \n" <<
                        "1. Price: $20 \n" <<
                        "Total credit point: 20 CP \n" <<
                        "====================================\n"<<
                        "2. 50 CP\n" << 
                        "Total credit point: 50 CP + 5 CP Bonus \n" <<
                        "====================================\n"<<
                        "3. $100 \n" << 
                        "Total credit point: 100 CP + 20 CP Bonus\n" <<
                        "====================================\n" << endl;
                cout << "Choice the bundle: ";
                cin >> option;
            
                switch (option){
                    case 1:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 20);
                        cout << "You have bought 20 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() + 20 << endl;
                        break;
                    case 2:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 55);
                        cout << "You have bought 55 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() + 5 << endl;
                        break;
                    case 3:
                        logged_in_supporter->setCreditPoint(logged_in_supporter->getCreditPoint() + 120);
                        cout << "You have bought 120 CP\n";
                        cout << "New balance: " << logged_in_supporter->getCreditPoint() + 120 << endl;
                        break;
                    case 4: 
                        cout <<" Returning to home page....." << endl;
                        break;
                    default:
                        cout <<"Invalid option, please select again" << endl;
                }
                cout << "Do you want to continue buying credit [Y/N]: ";
                std::getline(std::cin >> std::ws, choice);
                if (choice == "N"){
                    check = false;
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
                    cout << "Status: " <<  supporter->statusString(supporter->getStatus()) << endl;
                    cout << "================================================================\n";
            }
        }
    }

    void statusSetting(){
        cout <<"****Status Setting Menu****" << endl;
        cout <<"Your current status: " << logged_in_supporter->statusString(logged_in_supporter->getStatus()) << endl;

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

    string getCurrentStatus(){
        return logged_in_supporter->statusString(logged_in_supporter->getStatus());
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
