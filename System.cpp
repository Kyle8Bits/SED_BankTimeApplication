#include "System.h"

const char* colors::RED = "\033[1;91m";
const char* colors::YELLOW = "\033[1;93m";
const char* colors::GREEN = "\033[92m";
const char* colors::RESET = "\033[0m"; 

//CONSTRUCTOR
System::System(std::vector<Member*> member_list) : member_list(member_list){}

//The function below to get the position of the member in the list via the username
int System::getPositionOfMemberByUsername(string user_name_account){
    loop(this->member_list.size()){//Go to each member to find the user_name 
        if(member_list[i]->getUsername() == user_name_account){
            return i;//If we can find it, return the position of it
        }
    }
    return -1;
}

bool System::checkNonEmpty(const string& str){
    if(str.empty()){
        cout << "Please enter non-empty value!" << endl;
        return false;
    }

    return true;
}

bool System::registerMember(){
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

    string city_choice;
    cout <<"****Our application only exists at Ho Chi Minh and Hanoi****" << endl;
    while(city_choice != "1" && city_choice != "2"){
        cout << "1. Hanoi" << endl
                << "2. Ho Chi Minh" << endl
                << ">Your choice: ";
        getline(cin >> std::ws, city_choice);
    }

    if(city_choice == "1"){
        city_input = "Hanoi";
    }else if (city_choice == "2"){
        city_input = "Ho Chi Minh";
    } else{
        cout << colors::RED << "Invalid input" << colors::RESET << endl;
    }

    cout << colors::GREEN << "Succesfully collecting your info" << colors::RESET << std::endl;
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

bool System::loginMember(){
    string user_name_input;
    string pass_word_input;//these 2 variables to store the input of the users
    
    cout << "****Login form****" << endl;
    cout << ">Username: ";
    getline(cin >> std::ws, user_name_input);
    cout << ">Password: ";
    getline(cin >> std::ws, pass_word_input);

    if(user_name_input == "admin" && pass_word_input == "rmit1234"){
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
bool System::isValidPhone(const string& str) {
    
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

void System::displayMemberList(){
    if(is_admin){
        for (int i = 0; i < member_list.size(); i++){
            Supporter* supporter = dynamic_cast<Supporter*>(member_list[i]);
            if (supporter == nullptr){ 
                member_list[i]->displayUserList();
            }
            else {
                supporter->displayUserList(); 
            }
        }
    }else{
        cout << "You do not have permisson to do that" << endl;
    }
}

bool System::checkDuplicateDay(std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > list, string choose){
    bool check = true;
    loop(list.size()){ 
        if (list[i].first == choose){
            check = false;
        }
    }
    return check;
}

string System::getDayString(int day) {
    switch (day) {
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 7: return "Sunday";
    }
    return "";
}

bool System::isValidCost(const string& cost_str){
    for (char ch : cost_str) {
        if (!std::isdigit(ch)) {
            cout << colors::RED << "Please enter only digit!" << colors::RESET << endl;
            return false;
        }
    }
    return true;
}

bool System::upgradeToSupporter(){
    if(dynamic_cast<Supporter*>(logged_in_member)){//CHECK THE MEMBER IS ALREADY SUPPORTER OR NOT?
        cout << "You are aldready supporter!" << endl;
        return false;
    }
    //----------------------THIS FOR GETTING SKILL LIST---------------------

    
    cout << "Thank you for becomming the supporter. Your choice helps our community alot!" << endl;
    cout << "First, you need to add some skills that you have. These skills can change in your account's setting!" << endl;
    std::vector<string> skill_list_input;
    std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule;

    bool skill_check = true;
    while(skill_check){
        
        string choice;
        string skill_input;//declare variable store the input of the users
        cout << ">Your skill: ";
        getline(cin >> std::ws, skill_input);
        skill_list_input.push_back(skill_input);
        cout << colors:: GREEN << "Your new skill " << skill_input << " is added sucessfully!" << colors::RESET<< endl;
        
        bool confirm_check = true;
        while(confirm_check){
            cout << "Do you want to continue!\n";
            cout << "1. Yes" << endl
                << "2. No" << endl;
            cout << ">Your choice: ";
            getline(cin >> std::ws, choice);

            if(choice == "1"){
                cout << colors:: GREEN << "Continue Adding!" << colors::RESET<< endl;
                confirm_check = false;
            } else if(choice == "2"){
                cout << colors:: GREEN << "Stop Adding!" << colors::RESET<< endl;
                skill_check = false;
                confirm_check = false;
            }else{
                cout << colors::RED << "Please enter the valid input!" <<  colors::RESET << endl;
            }
        }
    }        
        //----------------------THIS FOR GETTING AVAILABILIITY PERIOD---------------------
    cout << "***********Now you will make a period schedule, you can change it later***********" << endl;
    cout << "In the first time, you can only one time period. You can add it more in your account setting!" << endl;
    
    bool schedule_check = true;
    while(schedule_check){
    //----------------------THIS FOR GETTING THE WEEKLY WORKDAY----------------

        while(schedule_check){
            bool time_check = true;
            string user_day_choice; 

            cout<<"Please enter which days of the week you work.\n";
            cout << "1. Monday \n"
                << "2. Tuesday \n"
                << "3. Wednesday \n"
                << "4. Thursday \n"
                << "5. Friday \n"
                << "6. Saturday \n"
                << "7. Sunday \n";
            cout <<"=============================================================" << endl;
            cout << ">Your choice: " << endl;
            bool check_option = true;
            getline(cin >> std::ws, user_day_choice);
            if(user_day_choice == "1" || user_day_choice == "2" || user_day_choice == "3" || user_day_choice == "4" || user_day_choice == "5" || user_day_choice == "6" || user_day_choice == "7"){
                
                user_day_choice = getDayString(std::stoi(user_day_choice));//convert from number to the string
                while(time_check){
                    cout << "Please enter the start time (HH:MM)" << endl;
                    Time start_time = start_time.getTimeFromUser();
                    cout << "Please enter the end time (HH:MM)" << endl;
                    Time end_time = end_time.getTimeFromUser();

                    if(!start_time.isLater(end_time)){
                        //If the start time is ealier than the end time --> valid input
                        //add the time and the day to the workSchedule
                        workSchedule.push_back(std::make_pair(user_day_choice, std::vector<std::pair<Time, Time>>{std::make_pair(start_time, end_time)}));
                        time_check = false;
                        schedule_check = false;
                    }else{
                        //The end time is ealier than the start time --> invalid input
                        cout << colors::RED << "Your end time must come after the start time" << colors::RESET << endl;
                        continue;
                    }

                }
            }else{
                cout << colors::RED << "Please enter the valid input!" << colors::RESET << endl;
            }
            
        }
    }

    //----------------------THIS FOR GETTING COST PER HOUR---------------------
    string cost_input_str; 
    cout << "What is the hourly credit point you would like to charge: ";
    getline(cin >> std::ws, cost_input_str);
    while(!isValidCost(cost_input_str)){//ask users to input the valid cost until the isValidCost return true
        cout << colors::RED << "Please enter the valid cost!" << colors::RESET << endl;
        cout << "What is the hourly rate you would like to charge: ";
        getline(cin >> std::ws, cost_input_str);
    }
    
    int cost_input = std::stoi(cost_input_str);//convert the string to int

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
    
    Supporter* new_supporter = new Supporter(*logged_in_member, workSchedule, Status::OFFLINE, skill_list_input, cost_input);

    //remove this member to the list, because they already become the supporter
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

void System::resetMemberPassword() {
    if(is_admin){
        string id_input, password_input;
        cout << "Please enter the User's Id that you want to reset password" << endl;
        getline(cin >> std::ws, id_input);
        id_input[0] = toupper(id_input[0]);

        for (Member* member : member_list) {
            if (member->getMemberId() == id_input) {
                cout << "You are editing " << member->getFullName() << "'s password" << endl;
                cout << "Enter the new password: ";
                getline(cin >> std::ws, password_input);

                member->setPassword(password_input);
                cout << colors::GREEN << "Reset password sucessfully!" << colors::RESET << endl;
                return;
            }
        }
        cout << colors::RED << "Member not found.\n" << colors::RESET;
    } else{
        cout << "Only admin can do that" << endl;
    }
}

void System::viewPersonalInformation(){
    if(logged_in_member != nullptr){
        logged_in_member->displayPersonalInformation();
        cout << endl;
    } else{
        logged_in_supporter->displayPersonalInformation();
    }
}

bool System::checkValidTime(string time) {
    
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

bool System::isAvailableDay(Supporter* id, int dayOfWeek){
    string day = getDayString(dayOfWeek);

    loop(id->getWorkSchedule().size()){
        if(id->getWorkSchedule()[i].first == day){
            return true;
        }
    }
    return false;
}


void System::displayAvailableSupporter(){
    booking.displayAvailableSupporter(member_list, logged_in_member,  logged_in_supporter, availableSupporter, booking_list);
}

double System::findCreditPointFromTime(Time start_time, Time end_time, int cost_per_hour){
    int start_minute_total = start_time.getHour() * 60 + start_time.getMinute();//find the total minues of start time
    int end_minutes_total = end_time.getHour() * 60 + end_time.getMinute();//find the total minutes of end time

    int total_minutes = end_minutes_total - start_minute_total;//find the total minutes of the period

    double cost_per_minute = (double) cost_per_hour / 60.0;//find the cost per minute
    
    double total_cost = cost_per_minute * total_minutes;//find the total cost of the period

    return total_cost;
}

bool System::isValidInterger(const string& str){
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            cout << colors::RED << "Please enter only digit!" << colors::RESET << endl;
            return false;
        }
    }
    return true;
}

void System::createBooking(){
    cout << "****WELCOME TO BOOKING DASHBOARD****"<<endl;
    Supporter* choose_supporter;//supporter that users choose
    displayAvailableSupporter();
    cout << "Please input the supporter's id that you want to book: ";
    string input; 
    getline(cin >> std::ws, input);
    input[0] = toupper(input[0]);

//=========================CHECK IS THAT SUPPORTER IS EXSIT=======================
    
    bool isSupporter = (logged_in_member == nullptr);
    bool isValidSupporter = false;//this to check the create bookign is successfully or not?
    if(isSupporter){
        logged_in_member = logged_in_supporter;//use this to prevent segment fault when the current users is supporter
    }
    loop(availableSupporter.size()){
        if(input == availableSupporter[i]->getMemberId()){// if the id of input is matched with the supporter's id
            // if(!booking.isInBlockList(logged_in_member->getBlockList(), availableSupporter[i]->getMemberId()) && booking.isInTheCity(logged_in_member, input, availableSupporter)){
            if(logged_in_member->getHostRatingScore() < availableSupporter[i]->getMinHostRating()){
                cout << colors::RED << "You can not book this supporter because your host rating score is lower than the supporter's min host rating score" << colors::RESET << endl;
                return;
            }
            else if (booking.isInBlockList(logged_in_member->getBlockList(), availableSupporter[i]->getMemberId())){
                BlockError();
                return;
            }
            else if (!booking.isInTheCity(logged_in_member, input, availableSupporter)){
                CityError();
                return;
            } else{
                choose_supporter = availableSupporter[i];
                isValidSupporter = true;
                break;
            }
        }
    }
    if(!isValidSupporter){
        IdNotInListError();
        return;
    }

    //===========================User choose the day to book here===============================================
    Calendar calendar;
    RealTime today;
    int day_save_to_file, month_save_to_file, year_save_to_file;
    bool decide_month_check = true;
    while(decide_month_check){
        // clearScreen();
        calendar.printCalendar(today.getThisYear(), today.getThisMonth());
        
        cout <<"1. Book withtin this month" << endl;
        cout <<"2. Book for with another calendar" << endl;
        cout <<"3. Cancle" << endl;
        
        string choice;
        cout << "> Your choice: "; 
        getline(std::cin >> std::ws, choice);

        string day_str;
        string day_str_another_month;//this use for the case 2
        if (choice == "1"){
            //User book in the current month
            bool day_check =true;
            while(day_check){
                bool dayofweek = true;
                while(dayofweek){
                    cout << "> Choose the day in above month: "; 
                    getline(cin >> std::ws, day_str);
                    if(!isValidInterger(day_str)){
                    }
                    else if(std::stoi(day_str) < 1 || std::stoi(day_str) > calendar.getDaysInMonth(today.getThisMonth(), today.getThisYear())){
                        calendar.printCalendar(today.getThisYear(), today.getThisMonth());
                        cout << colors::RED << "The selected day does not exist in this month. Please select again" << colors::RESET << endl;
                    }
                    else if (std::stoi(day_str) < today.getToday()){
                        calendar.printCalendar(today.getThisYear(), today.getThisMonth());
                        cout << colors::RED << "The selected must be today or the following days. Please select again" << colors::RESET <<  endl;
                    }
                    else {
                        if(isAvailableDay(choose_supporter, calendar.extractTheDayweek(std::stoi(day_str) ,today.getThisMonth(), today.getThisYear()) -1 )){
                            day_save_to_file = std::stoi(day_str);
                            year_save_to_file = today.getThisYear();
                            month_save_to_file = today.getThisMonth();
                            day_check = false;
                            dayofweek = false;
                        }
                        else{
                            cout << colors::RED << "This supporter do not work on " << getDayString( calendar.extractTheDayweek( std::stoi(day_str),today.getThisMonth(), today.getThisYear()) - 1 )<< colors::RESET << endl;
                        }
                    }
                }
            }

        decide_month_check = false;
        }else if( choice == "2"){
            bool month_year_check = true;
            string year_str, month_str;
    //==========================CHECK MONTH AND YEAR==============================
            while(month_year_check){
                //user want to book in the another month
                cout << "Please enter the year you want to make the booking: "; 
                getline(cin >> std::ws, year_str);
                cout << "Please enter the month you want to make the booking: ";
                getline(cin >> std::ws, month_str);
                if( !isValidInterger(month_str) || !isValidInterger(year_str)){
                }
                else if(year_str.length() > 4 || month_str.length() > 2 ){
                    cout << colors::RED << "Please enter the valid input!" << colors::RESET << endl;
                }
                else if(std::stoi(month_str) < 1 || std::stoi(month_str) > 12){
                    cout << colors::RED << "Plese enter the valid month! Only 12 months in a year" << colors::RESET << endl;
                }
                else if(std::stoi(year_str) < today.getThisYear() || std::stoi(month_str) < today.getThisMonth()){
                    cout << colors::RED << "You can not book in the past!" << colors::RESET << endl;
                }
                else{
                    month_year_check = false;
                }
            }
        //======================CHECK THE DAY==================================
            bool day_check =true;
            while(day_check){
                bool dayofweek = true;
                while(dayofweek){
                    cout << "> Choose the day in above month: "; 
                    getline(cin >> std::ws, day_str);
                    if(!isValidInterger(day_str)){
                    }
                    else if(std::stoi(day_str) < 1 || std::stoi(day_str) > calendar.getDaysInMonth(std::stoi(month_str), std::stoi(year_str))){
                        calendar.printCalendar(std::stoi(year_str), std::stoi(month_str));
                        cout << colors::RED << "The selected day does not exist in this month. Please select again" << colors::RESET << endl;
                    }
                    else if (std::stoi(day_str) < today.getToday()){
                        calendar.printCalendar(std::stoi(year_str), std::stoi(month_str));
                        cout << colors::RED << "The selected must be today or the following days. Please select again" << colors::RESET <<  endl;
                    }
                    else {
                        if(isAvailableDay(choose_supporter, calendar.extractTheDayweek(std::stoi(day_str) ,std::stoi(month_str), std::stoi(year_str)) -1 )){
                            day_save_to_file = std::stoi(day_str);
                            year_save_to_file = std::stoi(month_str);
                            month_save_to_file = std::stoi(year_str);
                            day_check = false;
                            dayofweek = false;
                        }
                        else{
                            cout << colors::RED << "This supporter do not work on " << getDayString( calendar.extractTheDayweek( std::stoi(day_str),std::stoi(month_str), std::stoi(year_str)) - 1 )<< colors::RESET << endl;
                        }
                    }
                }
            }

            decide_month_check = false;
        }
        else if (choice == "3"){
            cout << "Returning to dashboard" << endl;
            return;
        }else{
            cout << colors::RED <<"Invalid select please choose again" << colors::RESET << endl;
        }
    }
    
    //*****THIS PART FOR GETTING TIME ********
    string day_str = getDayString(calendar.extractTheDayweek(day_save_to_file,month_save_to_file,year_save_to_file)); 
    Time start_time, end_time;
    bool time_check = true;  
    //=====================CHECK THE TIME==============================================
    while(time_check){
        choose_supporter->displayWorkSchedule();
        cout << "Choose the time you want to book. Noitce that: the time you choose must match with the free time of the supporter!" << endl;
        // int start_time_hour, start_time_minute, end_time_hour, end_time_minute;
        // string start_time_input, end_time_input;
        cout << "Please enter the start time [HH:MM]\n";
        start_time = start_time.getTimeFromUser();
        cout << "Please enter the end time [HH:MM]\n";
        end_time = end_time.getTimeFromUser();
        
        if(start_time.isLater(end_time)){
            LogicTimeError();
        }
        else if(!choose_supporter->isAvailableInTime(start_time, end_time, day_str)){
            BookingTimeError();
        }
        else{
            time_check = false;
        }
    }

    //===========This part return thr price and wait for confirm================================
    int total_cost = findCreditPointFromTime(start_time, end_time, choose_supporter->getCost());
                    
    bool check_cost = true;
    while(check_cost){
        cout << "The total cost of this booking is: " << total_cost << endl;
        cout << "Do you want to continue?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        string choice;
        getline(cin >> std::ws, choice);
        if(choice == "1"){
            if(logged_in_member->getCreditPoint() < total_cost){//check the credit point of the users and the cost per hour of the supporter
                InsufficientPointError();
                return;
            }
            //PUSH NEW BOOKING TO THE BOOKING LIST
            BookingSupporter* booking = new BookingSupporter(logged_in_member->getMemberId(), choose_supporter->getMemberId());
            //SET THE START AND END TIME OF THE NEW BOOKINg
            booking->setStartTime(start_time);
            booking->setEndTime(end_time);
            booking->setTotalCost(total_cost);
            booking->setDate(day_save_to_file, month_save_to_file, year_save_to_file);
            booking_list.push_back(booking);
            // cout << "Your booking has been created" << endl;
            SucessBooking();//Print sucessfull message
            isValidSupporter = true;
            this->availableSupporter.clear();
            //clear after create booking to prevent push duplicated Supporter
            //get out of function and return to the main dashboard
            check_cost = false;
            time_check = false;
        } else if(choice == "2"){
            cout << colors::YELLOW << "You have canceled the booking" << colors::YELLOW << endl;
            isValidSupporter = true;
            return;
        } else{
            cout << colors::RED << "Please enter the valid input!" << colors::RESET << endl;
        }

    }
    

    if(isSupporter){
        //retur nthe logged_inmember become nullptr
        logged_in_member = nullptr;
    }
}

void System::viewHistory(){//For host to view which supporter they have booked 
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

void System::setStatusById(string id, string choice){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            booking_list[i]->setStatus(choice);
            break;
        }
    }
}

string System::getStatusById(string id){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            return booking_list[i]->getStatus();
        }
    }
    return "";
}

void System::setProgressById(string id, string choice){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            booking_list[i]->setProgress(choice);
            break;
        }
    }
}

void System::addHostScoreByID(string id, int rating){
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

void System::addSupporterScoreByID(string id, int rating, int skill_rating){
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

void System::setHostCommentById(string id, string comment){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            booking_list[i]->setHostComment(comment);
            break;
        }
    }
}

string System::getProgressById(string id){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            return booking_list[i]->getProgress();
        }
    }
    return "";
}

void System::setHostRatingById(string id, int rating){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            booking_list[i]->setHostRating(rating);
            break;
        }
    }
}

double System::getMoneyById(string id){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            return booking_list[i]->getTotalCost();
        }
    }
    return 0;
}

std::vector<string> System::showAvalableBooking(){
    cout << "****THE LIST OF REQUEST BOOKING****\n";
    int count = 1;
    cout << "\n";
    std::vector<string> current_job = {};
    cout << colors::YELLOW << std::setw(146) << std::setfill('-') << colors::RESET << endl;
    cout << bk_colors::YELLOW << std::left << std::setw(7) << "| Num |" << std::setw(13) << " Booking ID |" << std::setw(20) << " Host Name         |"
            << std::setw(15) << " City         |" << std::setw(15) << " Host Rating  |"  << std::setw(12) << " Status    |" << std::setw(17) << " Progress       |"
            << std::setw(20) << " Time              |" << std::setw(15) << " Book date    |" << std::setw(8) << " Cost  |" <<endl;

    cout << colors::YELLOW << std::setw(146) << std::setfill('-') << colors::RESET << std::setfill(' ')<< endl;
    for(int i = 0; i < booking_list.size(); i++){
        if ( logged_in_supporter->getMemberId() == booking_list[i]->getSupportId() && booking_list[i]->getProgress() != "COMPLETED" && booking_list[i]->getStatus() != "REJECTED"){//Check if current user is = host id 
            for (int a = 0; a < member_list.size(); a++){
                if (booking_list[i]->getHostId() == member_list[a]->getMemberId()){//get the matchecd supporter id in booking list and in memberlist
                    //push the id to the vector current_job
                    current_job.push_back(booking_list[i]->getBookingId());
                    //Print basic information
                    cout <<"| "<< std::setw(4) <<std::to_string(count) << "| " 
                        << std::setw(11)<< booking_list[i]->getBookingId() << "| "
                        << std::setw(18)<< member_list[a]->getFullName() << "| " 
                        << std::setw(13)<< member_list[a]->getCity() << "| "
                        << std::setw(13) << std::fixed << std::setprecision(2) << member_list[a]->getAverageRatingScore() << "| ";

                        if(booking_list[i]->getStatus() == "ACCEPTED"){
                        cout << colors::GREEN << std::setw(10) << booking_list[i]->getStatus() << colors::RESET << "| ";
                        cout << colors::GREEN << std::setw(15) << booking_list[i]->getProgress() << colors::RESET << "| ";
                        }
                        else{
                        cout << colors::YELLOW << std::setw(10) << booking_list[i]->getStatus() << colors::RESET << "| ";
                        cout << colors::YELLOW << std::setw(15)<< "WAIT" << colors::RESET << "| ";
                        }
                    cout << std::setw(18)<< booking_list[i]->getTime() << "| "
                        << std::setw(13) << booking_list[i]->getDate() << "| "
                        << std::setw(6) << booking_list[i]->getTotalCost() <<"|" << endl;

                    cout << colors::YELLOW << std::setw(146) << std::setfill('-') << colors::RESET << std::setfill(' ') << endl;
                }
            }
            count++;
        }
    }

    return current_job;
}


void System::decideJob(){//For supporter to answer the request booking from host. Either accept or reject or remain pending
    bool invitation_code_loop_check = true;
    std::vector<string> current_job;
    while(invitation_code_loop_check){
        current_job.clear();
        std::vector<string> current_job = showAvalableBooking();
        if(current_job.empty()){
            //if the curernt_job doesn't have that booking, we get out this loop
            cout << "You do not have booking yet" << endl;
            invitation_code_loop_check = false;
            return;
        }
        
                
        string choice;
        bool validChoice = false;

        cout << "Enter booking invitation code: ";
        cout << "Type 'q' to exit\n";
        std::getline(cin >> std::ws, choice);

        if(choice == "q"){
            invitation_code_loop_check = false;
            cout << "Returning home page" << endl;
            break;
        } else{
            choice[0] = toupper(choice[0]);//make the first character of users'input beomce upper
            //it helps users can enter lower character but still match the id
            choice[1] = toupper(choice[1]);

            loop(current_job.size()){ 
                if(choice  == current_job[i]){
                    validChoice = true;
                    if(getProgressById(current_job[i]) == "IN PROGRESS"){
                        string decide_in_progress;
                        bool in_progress_loop_check = true;

                        while(in_progress_loop_check){
                            cout << "Have you completed the job?" << endl;
                            cout << "1. Yes\n" 
                                    << "2. No" << endl;
                            cout << ">Your choice: "; getline(cin >> std::ws, decide_in_progress);
                            if(decide_in_progress =="1"){
                                //&***************UNCOMMENT IT WHEN DONE***************
                                setProgressById(current_job[i], "COMPLETED");
                                cout << colors::GREEN << "Congratulation! You just finished the job." << colors::RESET << endl;
                                cout << colors::GREEN << "You just receive: " << getMoneyById(current_job[i]) << colors::RESET << " CP" << endl;
                                logged_in_supporter->addCreditPoint(getMoneyById(current_job[i]));//add the new money to the supporter's account
                                cout << colors::YELLOW << "Your new balance: " << logged_in_supporter->getCreditPoint() << colors::RESET << endl;

                                string completed_decide;
                                bool completed_loop_check = true;
                                while(completed_loop_check){
                                    cout << "Do you want to leave feedback and rate your host\n";
                                    cout << "1. Yes\n" << "2. No\n" << ">Your choice:";
                                    getline(cin >> std::ws, completed_decide);

                                    if(completed_decide == "1"){
                                        bool check = true;
                                        while(check){
                                            cout << "Please rate your host (scale: 0 - 10)" << endl;
                                            cout << ">Rating: ";
                                            string input;  
                                            getline(cin >> std::ws, input);

                                            std::stringstream iss(input);
                                            int rating;

                                            if(iss >> rating){
                                                    //IF the conversion is successful
                                                if(rating >= 0 && rating <= 10){
                                                    if(rating < 5){
                                                        cout << "Sorry about your bad experiance" << endl;
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
                                                    //remove the booking from the current_job

                                                    completed_loop_check = false;
                                                    in_progress_loop_check = false;
                                                    check = false;
                                                } else{
                                                    cout << "****Please enter the valid rating****" << endl;
                                                } 
                                            }else{
                                                cout << "Please enter the valid rating!" << endl;
                                            }
                                        }
                                    } else if (completed_decide == "2"){
                                        cout << "****Do not leave comment****" << endl;
                                        setHostRatingById(current_job[i], 11);
                                        setHostCommentById(current_job[i], "x");
                                        addHostScoreByID(current_job[i], 11);
                                        cout << "Return main page!" << endl;
                                        //remove the booking from the current_job=
                                        completed_loop_check = false;
                                        in_progress_loop_check = false;

                                    } else{
                                        cout << colors::RED << "Please enter the valid choice!" << colors::RESET << endl;
                                    }

                                }

                            }else if(decide_in_progress == "2"){
                                    in_progress_loop_check = false;
                                    cout << "Return the main page" << endl;
                            }else{
                                cout << colors::RED << "Please enter the valid choice!" << colors::RESET << endl;
                            }
                        }
                    }

                    else if(getStatusById(current_job[i]) == "ACCEPTED"){
                        cout << "***Do you want to start the job***\n" << endl;
                        cout << "1. Take the job\n" 
                            << "2. Return\n"
                            << ">Your choice: ";
                        string accepted_decide;

                        while(accepted_decide != "1" && accepted_decide != "2"){    
                            //loop this until the users choose 1 or 2
                            getline(cin >> std::ws, accepted_decide);

                            if (accepted_decide == "1"){
                                cout << colors::GREEN << "You accept to take the job\n" << colors::RESET << endl;
                                setProgressById(current_job[i], "IN PROGRESS"); 
                            }
                            else if (accepted_decide == "2"){
                                cout << "Return to previous page\n";
                            }
                            else{
                                cout << colors::RED << "Invalid choice!" << colors::RESET << endl;
                            }
                        }

                    }else{
                        //if the status is PENDING
                        std::vector <BookingSupporter* > overLap_list = isOverLap(choice);
                        cout << "1. ACCEPTED\n"<<
                                "2. REJECTED\n" <<
                                "3. RETURN\n"<< endl;

                        string accept_choice;
                        cout << ">Your choice: "; 
                        while(accept_choice != "1" && accept_choice != "2" && accept_choice != "3"){
                            //run the loop until the users chooose 1 ,2 or 3
                            getline(cin >> std::ws, accept_choice);
                            if(accept_choice == "1"){
                                if(overLap_list.empty()){
                                    setStatusById(current_job[i], "ACCEPTED");
                                    cout<< colors::GREEN << "You have accepted this booking." << colors::RESET << endl;
                                }else{
                                    int count_overlap = 1;
                                    cout << colors::YELLOW << "ACCEPTED booking " << choice << " will automatically REJECTED the overlapping booking below:" << colors::RESET << endl;
                                    cout << "\n";
                                    cout << std::setw(149) << colors::YELLOW << std::setfill('-') << colors::RESET <<  endl;
                                    cout << bk_colors::YELLOW << std::left << std::setw(7) << "| Num |" << std::setw(13) << " Booking ID |" << std::setw(20) << " Host Name         |"
                                                    << std::setw(15) << " City         |" << std::setw(15) << " Host Rating  |"  << std::setw(12) << " Status    |" << std::setw(17) << " Progress       |"
                                                    << std::setw(20) << " Time              |" << std::setw(15) << " Book date    |" << std::setw(8) << " Cost  |" <<endl;
                                    cout << std::setw(149) << colors::YELLOW << std::setfill('-') << colors::RESET <<  endl;

                                    loop (overLap_list.size()){
                                        cout << overLap_list[i]->getBookingId() << " : " << overLap_list[i]->getTime() << endl;
                                        for (int a = 0; a < member_list.size(); a++){
                                            if(overLap_list[i]->getHostId() == member_list[a]->getMemberId()){
                                                colors::RESET;

                                                cout << std::setfill(' ') <<"| "<< std::setw(4) <<std::to_string(count_overlap) << "| " 
                                                    << std::setw(11)<< overLap_list[i]->getBookingId() << "| "
                                                    << std::setw(18)<< member_list[a]->getFullName() << "| " 
                                                    << std::setw(13)<< member_list[a]->getCity() << "| "
                                                    << std::setw(13) << std::fixed << std::setprecision(2) 
                                                    << member_list[a]->getAverageRatingScore() << "| "
                                                    << std::setw(10) << overLap_list[i]->getStatus() << "| "
                                                    << std::setw(15) << overLap_list[i]->getProgress() << "| "
                                                    << std::setw(18)<< overLap_list[i]->getTime() << "| "
                                                    << std::setw(13) << overLap_list[i]->getDate() << "| "
                                                    << std::setw(6) <<overLap_list[i]->getTotalCost() <<"|" << endl;

                                                    count_overlap++;
                                                    cout << std::setfill('-') << std::setw(149) << colors::YELLOW  << colors::RESET  <<  endl;

                                            }  
                                        }
                                    }

                                    string choice_for_overlap;
                                    cout << "Do you want to continue ?" << endl;
                                    cout << "1. ACCEPTED THIS AND REJECTED OTHER \n"
                                            << "2. CANCEL BOOKING" << endl;
                                    while(choice_for_overlap != "1" && choice_for_overlap != "2"){
                                        getline(cin >> std::ws, choice_for_overlap);

                                        if (choice_for_overlap == "2"){
                                            cout << colors::YELLOW << "You have canceled the booking" << colors::RESET<< endl;
                                            return;
                                        } else if (choice_for_overlap == "1"){
                                            cout << "All the overlap booking have been rejected" << endl;
                                            loop (overLap_list.size()){
                                                overLap_list[i]->setStatus("REJECTED");
                                            }
                                            
                                            setStatusById(current_job[i], "ACCEPTED");
                                            cout << colors::GREEN << "You have accepted the " << current_job[i] << " booking." << colors::RESET << endl;
                                        } else{
                                            cout << colors::RED << "Please enter the valid choice!" << colors::RESET << endl;
                                        }

                                    }
                                }

                            }else if(accept_choice == "2"){
                                setStatusById(current_job[i], "REJECTED");
                            }else{
                                cout << colors::RED << "Please enter the valid choice!" << colors::RESET << endl;
                            }
                        }
                    }
                    break;
                }
            }
            if(!validChoice){
                cout << "Please enter the valid choice!" << endl;
            }
        }
    }

    
}

std::vector<BookingSupporter*> System::isOverLap(string bk_id){
    std::vector<BookingSupporter*> relateBooking = {};
    std::vector<BookingSupporter*> denide_booking_list ={};
    BookingSupporter* booking_accept;

    bk_id[0] = toupper(bk_id[0]);
    bk_id[1] = toupper(bk_id[1]);

    loop(booking_list.size()){
        if(booking_list[i]->getSupportId() == logged_in_supporter->getMemberId() && booking_list[i]->getBookingId() != bk_id){
            relateBooking.push_back(booking_list[i]);
        }
        if(booking_list[i]->getBookingId() == bk_id){
            booking_accept = booking_list[i];
        }
    }

    cout <<"Choose: " << bk_id << "-" <<booking_accept->getTime() << "\n" << endl;

    loop(relateBooking.size()){
        if(booking_accept->getDate() == relateBooking[i]->getDate()){
            Time booking_accept_start_time = booking_accept->getStartTime();
            Time booking_accept_end_time = booking_accept->getEndTime();
            if(relateBooking[i]->getProgress() != "COMPLETED"){
                if(!booking_accept_start_time.isLater(relateBooking[i]->getEndTime()) && booking_accept_end_time.isLater(relateBooking[i]->getStartTime()) && relateBooking[i]->getStatus() != "REJECTED"){
                // if(compareTimes(booking_accept->getStartTime(), relateBooking[i]->getEndTime()) && compareTimes(relateBooking[i]->getStartTime(), booking_accept->getEndTime()) && relateBooking[i]->getStatus() != "REJECTED" ){
                    denide_booking_list.push_back(relateBooking[i]);
                    cout << "Status " << relateBooking[i]->getStatus() << endl;
                }
            }
        }
    }

    return denide_booking_list;
}

void System::buyCredit(){
    bool isSupporter = (logged_in_member == nullptr);

    if(isSupporter){
        logged_in_member = logged_in_supporter; //use member point to the suppoter
    }

    string option;
    bool check = true;
    while(check){
        cout << "****Buying Credit Menu****" << endl;
        cout << "Current balance: " << logged_in_member->getCreditPoint() << " CP " << endl << endl;
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
                << "4. Returning Menu" << endl;
        cout << "Choice the bundle: ";
        getline(cin >> std::ws, option);

        if(option == "1"){
            logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 20);
            cout << colors::GREEN << "You have bought 20 CP\n" << colors::RESET;
            cout << colors::GREEN << "New balance: " << logged_in_member->getCreditPoint() << colors::RESET << endl ;
            check = false;
        }
        else if(option == "2"){
            logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 55);
            cout << colors::GREEN << "You have bought 55 CP\n" << colors::RESET;
            cout << colors::GREEN << "New balance: " << logged_in_member->getCreditPoint() << colors::RESET << endl;
            check = false;
        }
        else if(option == "3"){
            logged_in_member->setCreditPoint(logged_in_member->getCreditPoint() + 120);
            cout << colors::GREEN << "You have bought 120 CP\n" << colors::RESET;
            cout << colors::GREEN << "New balance: " << logged_in_member->getCreditPoint() << colors::RESET << endl;
            check = false;
        } else if(option == "4"){
            check = false;
            cout << "Returning main page" << endl;
        }
        else{
            cout << colors::RED << "Invalid option, please select again" << endl << colors::RESET;
        }
    }
    if(isSupporter){
        logged_in_member = nullptr;
    }
    
}

void System::displaySupporter(){
    booking.displayAvailableSupporterForGuest(member_list, logged_in_member,  logged_in_supporter, availableSupporter, booking_list);
}

void System::statusSetting(){
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

void System::viewHistoryJob(){

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
                        "\nHost rated you: will update" << 
                        "\nStatus: " << booking_list[i]->getStatus() <<
                        "\nProgress: " << booking_list[i]->getProgress() << endl;
                        
                        
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

void System::setSupportRatingById(int skill_score, int support_score, string comment, string id){
    loop(booking_list.size()){
        if(booking_list[i]->getBookingId() == id){
            booking_list[i]->setSkillRatingScore(skill_score);
            booking_list[i]->setSupporterRatingScore(support_score);
            booking_list[i]->setSupporterComment(comment);
            break;
        }
    }
}

void System::checkCompleteTask(){//EDIT IT
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

    string choice;
    cout <<"Please enter a booking id: ";
    getline(cin >> std::ws, choice);
    bool rate_check = true;
    choice[0] = std::toupper(choice[0]);
    choice[1] = std::toupper(choice[1]);

    loop (complete_list_id.size()){
        if(complete_list_id[i] == choice){
            bool check = true;
            string comment = " ";
            string rating_str;
            string skill_str;
            valid_choice = true;
            int skill, rating;

            while(check){
                cout << colors::GREEN << "Congratulation! Your booking has been finished" << colors::RESET <<endl;
                cout << colors::YELLOW << "The cost for this booking is: " << getMoneyById(complete_list_id[i]) << colors::RESET << endl;
                logged_in_member->subtractCreditPoint(getMoneyById(complete_list_id[i]));
                cout << "Your new balance: " << logged_in_member->getCreditPoint() << endl;
                cout <<"Do you want to give a feedback to this supporter?"<< endl;
                cout << "1. Yes\n"
                        << "2. No" << endl;
                string option;

                while(option != "1" && option != "2"){
                    //run the loop until the users enter 1 or 2
                    getline(cin >> std::ws, option);
                    if(option == "1"){
                        while(rate_check){
                            cout << "Please rate your supporter's skill(scale: 0 - 10): ";
                            cout << ">Rating: ";
                            getline(std::cin >> std::ws, skill_str);
                            cout << "How would you like this supporter (scale 0 - 10): ";
                            cout << ">Rating: ";
                            getline(std::cin >> std::ws, rating_str);

                            if(isValidInterger(skill_str) && isValidInterger(rating_str)){
                                //CONVERT THEY BACK TO THE INTEGER
                                skill = std::stoi(skill_str);
                                rating = std::stoi(rating_str);

                                if (rating <= 10 && rating >= 0 && skill <= 10 && skill >= 0){
                                    rate_check = false;
                                }
                            }else{
                                cout << colors::RED << "Please enter the valid rating!" << colors::RESET << endl;
                            }
                        }
                        cout << "Give some comment (Put 'x' if you do not want to comment): ";
                        getline(cin >> std::ws, comment);

                        setSupportRatingById(skill, rating, comment, complete_list_id[i]);

                        addSupporterScoreByID(complete_list_id[i],rating, skill);

                        cout << "Thank you for giving feedback" << endl;
                        check = false;
                        break;
                    } else if(option == "2"){
                        setSupportRatingById(11, 11, "x", complete_list_id[i]);
                        addSupporterScoreByID(complete_list_id[i],11,11);

                        check = false;
                        break;
                    } else{
                        cout << colors::RED << "Please enter the valid choice!" << colors::RESET << endl;
                    }
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

string System::getCurrentStatus(){
    return logged_in_supporter->statusToString(logged_in_supporter->getStatus());
}

int System::getNotification(){ 
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

int System::getRequestNotification(){
    int count = 0;
    loop (booking_list.size()){
        if (logged_in_supporter->getMemberId() == booking_list[i]->getSupportId() && booking_list[i]->getStatus() == "PENDING"){
            count++;
        }
    }
    return count;
}

bool System::blockUser(){
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

string System::getFullNameFromId(string id){
    loop(member_list.size()){
        if(id == member_list[i]->getMemberId()){
            return member_list[i]->getFullName();
        }
    }
    return "Can not find!";
}

void System::showBlockList(){
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

std::vector<Member*>& System::getMemberList(){
    return this->member_list;
}

std::vector<BookingSupporter*>& System::getBookingList(){
    return this->booking_list;
}

void System::setMemberList(std::vector<Member*>& new_member_list){
    this->member_list = new_member_list;
}

void System::setBookingList(std::vector<BookingSupporter*>& new_booking_list){
    this->booking_list = new_booking_list;
}

Member* System::getLoggedInMember(){
    return this->logged_in_member;
}

Supporter* System::getLoggedInSupporter(){
    return this->logged_in_supporter;
}

bool System::getIsAdmin(){
    return this->is_admin;
}

void System::setIsAdmin(bool is_admin){
    this->is_admin = is_admin;
}

BookingSupporter System::getBooking(){
    return this->booking;
}

System::~System() {//Clear the member to advoid memory leak
    for (Member* member : member_list) {
        delete member;
    }
    for(BookingSupporter* booking_supporter : booking_list){
        delete booking_supporter;
    }
}