#include "Supporter.h"

const char* sp_colors::RED = "\033[1;91m";
const char* sp_colors::YELLOW = "\033[1;93m";
const char* sp_colors::WHITE_BOLD = "\033[1;97m";
const char* sp_colors::GREEN = "\033[92m";
const char* sp_colors::RESET = "\033[0m";

Supporter::Supporter(string user_name, string pass_word, string member_id, double credit_point, string full_name, string phone_number, 
    string address, string city, string about_me, double host_rating_score, 
    int host_count, int spt_not_comment, std::vector<string> block_list, std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule, Status status, 
    std::vector<string> skill_list, int cost, double skill_rating_score, double support_rating_score, int support_count, int host_not_comment, int min_host_rating)
    : Member(user_name, pass_word, member_id, credit_point, full_name, phone_number, address, city, about_me,
            host_rating_score, host_count, spt_not_comment, block_list), 
            workSchedule(workSchedule), status(status), skill_list(skill_list), cost(cost), skill_rating_score(skill_rating_score),
            support_rating_score(support_rating_score), support_count(support_count), host_not_comment(host_not_comment), min_host_rating(min_host_rating)
    {
        if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
            this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
        }
    }

//paste the Member to the Supporet (It's like copy constructor)
Supporter::Supporter(const Member& member,std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule, Status status, std::vector<string> skill_list, int cost,
            double skill_rating_score, double support_rating_score, int support_count, int min_host_rating):
            Member(member), workSchedule(workSchedule), status(status), skill_list(skill_list), cost(cost), 
            skill_rating_score(skill_rating_score), support_rating_score(support_rating_score), support_count(support_count) ,host_not_comment(host_not_comment), min_host_rating(min_host_rating)
    {
        if(member_id == "S"){//If the member id is S (Default value), we auto generate the id with the number of the number
        this->member_id = member_id + std::to_string(number_of_member);//AUTO GENERATE THE ID FOR MEMBER
    }
}

void Supporter::collectSupporterScore(int score, int skill){
    int person_comment = this->support_count - this->host_not_comment; //8 - 6 - 2
    if(score != 11 && skill != 11){
        if(support_count == 0){
            this->support_rating_score = score;
            this->skill_rating_score = skill;
            this->support_count++;
        }
        else{
            person_comment++; 
            this->support_rating_score = static_cast<double>(this->support_rating_score*(person_comment-1) + score)/person_comment;
            this->skill_rating_score = static_cast<double>(this->skill_rating_score*(person_comment-1) + skill)/person_comment;
            this->support_count++;
        }//                                                         
    }
    else{
        this->host_not_comment++;
        this->support_count++;
    }
}

bool Supporter::modifySkill(){
    bool check_adding;
    bool check_adding_2;
    bool check_remove;
    bool check_remove_2;
    string input;
    do{
        cout << "This is your current skill: " << displaySkillList() << endl;
        cout << "What do you want to do!" << endl;
        cout << "1. Add more skill" << endl;
        cout << "2. Remove skills" << endl;
        cout << "3. Return menu" << endl;
        cout << ">Your choice:";
        input = "";
        getline(cin >> std::ws, input);

        if(input == "1"){
            do{
                bool valid = true;
                check_adding = true;
                check_adding_2 = true;

                cout << "This is your current skill: ";
                cout << displaySkillList() << endl;

                cout << "****ADD NEW SKILL****" << endl;
                string skill_input;
                cout << "> Your skill: ";
                getline(cin >> std::ws, skill_input);
                if(skill_input.empty()){
                    cout << "Please input the non-empty value" << endl;
                    return false;
                }

                for(int i = 0; i < skill_list.size(); ++i){
                    if(skill_input == skill_list[i]){
                        cout << sp_colors::RED << "This skill is already exist!" << sp_colors::RESET << endl;
                        valid = false;
                    }
                }
                if(valid){
                    skill_list.push_back(skill_input);//if the skill is not empty -> push it to the list
                    cout << sp_colors::GREEN << "Your skill is added succesfully!" << sp_colors::RESET << endl;
                    while(check_adding_2){
                        cout << "Do you want to continue adding" << endl;
                        cout << "1. Yes " << endl;
                        cout << "2. No " << endl;
                        cout << "> Your choice: ";
                        getline(cin >> std::ws, skill_input);
                        if(skill_input == "1"){
                            cout << sp_colors::YELLOW << "Your new skill: " << skillListToString() << sp_colors::RESET << endl;
                            check_adding_2 = false;
                            continue;
                        } else if(skill_input == "2"){
                            cout << sp_colors::YELLOW << "Your new skill: " << skillListToString() << sp_colors::RESET << endl;
                            check_adding = false;
                            check_adding_2 = false;
                        } else{
                            cout << sp_colors::RED << "Please enter valid input" << sp_colors::RESET << endl;
                        }
                    }
                }
            } while(check_adding);
        } else if(input == "2"){
            do{
                check_remove_2 = true;
                check_remove = true;
                cout << "This is your current skill: " << displaySkillList() << endl;
                cout << "Please enter the name of skill you want to remove!" << endl;
                cout << ">Your choice: ";
                string remove_option;
                getline(cin >> std::ws, remove_option);
                bool valid_choice = false;

                for(int i = 0; i < this->skill_list.size(); ++i){
                    if(remove_option == skill_list[i]){
                        skill_list.erase(skill_list.begin() + i);
                        valid_choice = true;
                        cout << sp_colors::GREEN << "Your skill is removed succesfully!" << sp_colors::RESET << endl;
                        while(check_remove_2){
                            cout << "Do you want to remove more skill?" << endl;
                            cout << "1. Yes" << endl;
                            cout << "2. No" << endl;
                            cout << ">Your choice: ";
                            getline(cin >> std::ws, remove_option);
                            if(remove_option == "1"){
                                check_remove_2 = false;
                            } else if(remove_option == "2"){
                                check_remove_2 = false;
                                check_remove = false;
                            } else{
                                cout << sp_colors::RED << "Please enter valid input" << sp_colors::RESET << endl;
                            }
                        }
                    } 
                }

                if(!valid_choice){
                    cout << sp_colors::RED << "Please enter valid input" << sp_colors::RESET << endl;
                }
            }while(check_remove);
        } else if(input == "3"){
            return true;
        } else{
            cout << sp_colors::RED << "Please enter valid input" << sp_colors::RESET << endl;
        }
    }while(true);

    return false;
}

void Supporter::displayPersonalInformation(){
    int padding = 30;
    Member::displayPersonalInformation();
        cout << "\n" <<endl;
    cout << "****SUPPORTER PORTFOLIO****" << endl;
    cout << std::left << sp_colors::YELLOW << std::setw(padding) << "My Skill List: " << sp_colors::WHITE_BOLD << this->displaySkillList() << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My cost: " << sp_colors::WHITE_BOLD << this->cost << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My Skill Rating Score: " << sp_colors::WHITE_BOLD << this->skill_rating_score << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My Support Rating Score: " << sp_colors::WHITE_BOLD << this->support_rating_score << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My Job Count: " << sp_colors::WHITE_BOLD << this->support_count << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My Current Status: " << sp_colors::WHITE_BOLD << statusToString(status) << sp_colors::RESET << endl;
    cout << sp_colors::YELLOW << std::setw(padding) << "My Minimum Host Rating: " << sp_colors::WHITE_BOLD << ((this->min_host_rating == 0) ? "None" : std::to_string(this->min_host_rating)) << sp_colors::RESET << endl;
    this->displayWorkSchedule();
}

string Supporter::skillListToString(){//THIS USING FOR SAVE TO FILE
    if(skill_list.empty()){
        return "";//If the skill list have no elements, we return the blank
    }
    string skill_list_str = skill_list[0] + "-";
    for(int i = 1; i < skill_list.size(); ++i){
        skill_list_str += skill_list[i] + "-";
    }
    return skill_list_str;
}


string Supporter::scheduleToString(){
    string result = "";
    for(int i =0 ; i < workSchedule.size(); i++){
        result += "-" + workSchedule[i].first + "-";
        for(int a  = 0 ; a < workSchedule[i].second.size(); a++){
            result += workSchedule[i].second[a].first.getTime() + "=" + workSchedule[i].second[a].second.getTime() + "-";
        }
    }
    return result;
}

void Supporter::displayWorkSchedule(){
    if(workSchedule.empty()){
        cout << "EMPTY" << endl;
    }
    else{
        cout << sp_colors::WHITE_BOLD << std::left << std::setw(30)<< "|> Work Schedule:" <<"|" << endl;

        for(int i =0 ; i < workSchedule.size(); i++){
            cout << sp_colors::YELLOW<< "-------------------------------"<< sp_colors::RESET << endl;
            cout << "| " << std::left << std::setw(28) << workSchedule[i].first << "|" << endl;
            for(int a  = 0 ; a < workSchedule[i].second.size(); a++){
                cout << "| "<< std::left << std::setw(5) << workSchedule[i].second[a].first.getTime() << " to " << std::setw(19)<<workSchedule[i].second[a].second.getTime() << "|" << endl;
            }
        }
        sp_colors::RESET;
        // cout << std::setw(30) << std::setfill('-') << endl;
    }
    
}

string Supporter::displaySkillList(){//THIS USING FOR DISPLAYING
    if(skill_list.empty()){
        return "EMPTY";//If the skill list have no elements, we return the blank
    }
    string skill_list_str;

    for(int i = 0; i < skill_list.size(); i ++){
        skill_list_str += skill_list[i] + ", ";
    }
    
    return skill_list_str;
}

string Supporter::statusToString(Status status){
    switch (status) {
        case Status::OFFLINE:
            return "OFFLINE";
        case Status::ONLINE:
            return "ONLINE";
        default:
            return "UNKNOWN";
    }
}

double Supporter::getSkillRatingScore(){return this->skill_rating_score;}
double Supporter::getSupportRatingScore(){return this->support_rating_score;}
int Supporter::getSupportCount(){return support_count;}

int Supporter::getCost(){
    return this->cost;
}

void Supporter::setCostRequest(){
    cout << "Please enter new cost!" << endl;
    cout << ">Input: ";
    string input;
    getline(cin >> std::ws, input);
    for(int i = 0; i < input.length(); i++){
        if(!isdigit(input[i])){
            cout << "Please enter valid number!" << endl;
            return;
        }
    }

    this->cost = std::stoi(input);
    return;
}

int Supporter::getMinHostRating(){
    return this->min_host_rating;
}

bool Supporter::setMinHostRatingRequest(){
    cout << "Please enter your minimum rating! This will help you avoid the bad host!" << endl;
    cout << ">Your choice: ";
    string input;
    getline(cin >> std::ws, input);
    for(int i = 0; i < input.length(); i++){
        if(!isdigit(input[i])){
            cout << "Please enter valid number!" << endl;
            return false;
        }
    }

    this->min_host_rating = std::stoi(input);
    cout << "Your minimum rating is set!" << endl;
    return true;
}

string Supporter::getAvailabilityPeriod(){
    return "From: " + this->start_time.getTime() + " To: " + this->end_time.getTime();
}

Status Supporter::getStatus() const {
    return status;
}

void Supporter::setStatus(Status status){
    this->status = status;
}

string Supporter::toString(){
    return Member::toString() + "-" + std::to_string(this->cost) + "-" + std::to_string(this->skill_rating_score) + "-" + std::to_string(this->support_rating_score) + "-" + std::to_string(this->support_count) + "-" + std::to_string(this->host_not_comment) +  "-" + statusToString(getStatus()) + "-" + std::to_string(this->min_host_rating);
}

std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > Supporter::getWorkSchedule(){
    return workSchedule;
}

string Supporter::getDayString(int day) {
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

bool Supporter::isAvailableInTime(Time start_time_booking, Time end_time_booking, string day){
    std::vector<std::pair<Time,Time>> selected_day;
    selected_day.clear();
    for(int i = 0; i < workSchedule.size(); ++i){
        if(day == workSchedule[i].first){
            selected_day = workSchedule [i].second;
        }
    }

    if(selected_day.empty()){
        cout << "empty" << endl;
    }
    else{
        for (int a = 0; a < selected_day.size(); a++){
            if(selected_day[a].second.isLater(end_time_booking) && start_time_booking.isLater(selected_day[a].first)){
                return true;
            }
        }
    }

    return false;
}

bool Supporter::isOverlap(Time start_time, Time end_time, string day){
    for(int i = 0; i < workSchedule.size(); ++i){
        if(day == workSchedule[i].first){
                //if the input day is the same with the day in the work schedule
                //we will go to each time of the period in the work schedule to check
            for(int a = 0; a < workSchedule[i].second.size(); ++a){
                if(end_time.isLater(workSchedule[i].second[a].first) && !start_time.isLater(workSchedule[i].second[a].second)){
                    //the 2 time overlap when
                    // End Time of Interval 1>Start Time of Interval 2 and
                    // Start Time of Interval 1<End Time of Interval 2
                    return true;
                }
            }
        }
    }
    return false;
}

void Supporter::setWorkSchedule() {
    cout << "This is your current schedule!" << endl;
    displayWorkSchedule();
    cout << sp_colors::YELLOW << "-------------------------------" << sp_colors::RESET << endl << endl;

    bool check_page = true;

    while(check_page){
        bool add_check = true;
        bool remove_check = true;
        bool isValidRemove = false;
        bool isValidRemoveTime = false;
        cout << "What do you want to modify in your schedule!" << endl;
        cout << "1. Add new free time period" << endl;
        cout << "2. Remove free time period" << endl;
        cout << "3. Quit" << endl;
        cout << ">Your choice: ";
        string user_choice;

        getline(cin >> std::ws, user_choice);
        if(user_choice == "1"){//THis is for add new free time
            while(add_check){
                cout << "This is your current work day!" << endl;
                //PRINT THE WORKING DAY (MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY)
                for(int i = 0; i < workSchedule.size(); ++i){
                    cout << i + 1 << ": " << workSchedule[i].first << endl;
                }
                cout << workSchedule.size() + 1 << ": Add another day" << endl;
                cout << workSchedule.size() + 2 << ": Return" << endl;
                cout << sp_colors::YELLOW << "-------------------------------" << sp_colors::RESET << endl << endl;

                cout << ">Your choice: ";
                string user_add_day_choice;
                getline(cin >> std::ws, user_add_day_choice);
                if(user_add_day_choice == std::to_string(workSchedule.size() + 2)){
                    //USER WANT TO RETURN
                    add_check = false;
                    break;
                } 
                
                if(user_add_day_choice == std::to_string(workSchedule.size() + 1)){
                    //USER WANT TO ADD MORE DAY                
                    bool check_add_day = true;
                    bool check_time_add = true;
                    while(check_add_day){
                        
                        cout << "Please enter which days of the week you work.\n";
                        cout << "1. Monday \n"
                            << "2. Tuesday \n"
                            << "3. Wednesday \n"
                            << "4. Thursday \n"
                            << "5. Friday \n"
                            << "6. Saturday \n"
                            << "7. Sunday \n"
                            << "8. Return \n";
                        cout <<"=============================================================" << endl;
                        cout << ">Your Choice: " << endl;
                        string user_add_day;
                        getline(cin >> std::ws, user_add_day);
                        if(user_add_day == "8"){
                            //USER WANT TO RETURN to the previous page
                            check_add_day = false;
                        }else if(user_add_day == "1" || user_add_day == "2" || user_add_day == "3" || user_add_day == "4" || user_add_day == "5" || user_add_day == "6" || user_add_day == "7"){
                            //We need to check is the day already exist in the work schedule
                            user_add_day = getDayString(std::stoi(user_add_day));
                            bool day_exist = false;
                            for(int i = 0; i < workSchedule.size(); ++i){
                                if(user_add_day == workSchedule[i].first){
                                    cout << sp_colors::RED << "This day is already exist in your work schedule!" << sp_colors::RESET << endl;
                                    cout << sp_colors::RED << "Please choose that day to add your new time" << sp_colors::RESET << endl;
                                    check_add_day = false;
                                    day_exist = true;
                                }
                            }
                            if(!day_exist){
                                //WE get the time from users
                                while(check_time_add){
                                    cout << "Please enter the start time (HH:MM)" << endl;
                                    Time start_time = start_time.getTimeFromUser();
                                    cout << "Please enter the end time (HH:MM)" << endl;
                                    Time end_time = end_time.getTimeFromUser();
                                    
                                    if(!start_time.isLater(end_time)){
                                        //PUSH THE TIME TO THE WORK SCHEDULE WITH THE NEW DAY
                                        workSchedule.push_back(std::make_pair(user_add_day, std::vector< std::pair< Time, Time> >{std::make_pair(start_time, end_time)}));
                                        cout << sp_colors::GREEN << "Your time period is added!" << sp_colors::RESET << endl;
                                        cout << sp_colors::GREEN << user_add_day << ": FROM " << start_time.getTime() << " TO: " << end_time.getTime() << sp_colors::RESET << endl;

                                        check_time_add = false;//get out the get time loop
                                        check_add_day = false;
                                        add_check = false;//return add/remove page 
                                        break;

                                    }else{
                                        //THE END TIME IS EALIER THAN THE STAART TIME --> INVALID
                                        cout << sp_colors::RED << "Your end time must come after than the start time" << sp_colors::RESET << endl;
                                        continue;
                                    }
                                }

                            }
                        } else{
                            cout << sp_colors::RED << "Invalid Choice!" << sp_colors::RESET << endl;
                            continue;
                        }
                    }


                    // add_check = false; //return add/remove page
                } else{
                    //USER WANT TO ADD THE TIME TO THE EXISTING DAY
                    bool is_valid_add_time = false;

                    for(int i = 0; i < workSchedule.size(); ++i){
                        if(user_add_day_choice == std::to_string(i + 1)){
                            bool check_time = true;
                            while(check_time){
                                cout << "Please enter the start time (HH:MM)" << endl;
                                Time start_time = start_time.getTimeFromUser();
                                cout << "Please enter the end time (HH:MM)" << endl;
                                Time end_time = end_time.getTimeFromUser();
                                
                                if(!start_time.isLater(end_time)){
                                    //the isLater function will return the true if the start time is later than end time
                                    //if the start time is ealier than end time --> go to this statement --> valid
                                    //WE NEED TO CHECK IF THE TIME IS OVERLAP WITH THE EXISTING TIME
                                    if(isOverlap(start_time, end_time, workSchedule[i].first)){
                                        //if this isOverLap return true// prompts users to enter again
                                        cout << sp_colors::RED << "Your time period is overlap with the existing time period!" << sp_colors::RESET << endl;
                                        continue;
                                    }

                                    workSchedule[i].second.push_back(std::make_pair(start_time, end_time));
                                    cout << sp_colors::GREEN << "Your time period is added!" << sp_colors::RESET << endl;
                                    cout << sp_colors::GREEN << "FROM " << start_time.getTime() << " TO: " << end_time.getTime() << sp_colors::RESET << endl;
                                    add_check = false;//return add/remove page  
                                    is_valid_add_time = true;     
                                    break;
                                }else{
                                    //THE END TIME IS EALIER THAN THE STAART TIME --> INVALID
                                    cout << sp_colors::RED << "Your end time must be greater than the start time" << sp_colors::RESET << endl;
                                    continue;
                                }
                            }        
                        }
                    }
                    if(!is_valid_add_time){
                        cout << sp_colors::RED << "Invalid Choice!" << sp_colors::RESET << endl;
                    }
                }
            }
        }else if(user_choice == "2"){
            //******USER WANT TO REMOVE TIME******
            while(remove_check){
                cout << "Please choose your day that you want to remove" << endl;
                for(int i = 0; i < workSchedule.size(); ++i){
                    cout <<  i + 1 << ": " << workSchedule[i].first << endl;
                    if(i == workSchedule.size() - 1){
                        cout << i + 2 << ": Return" << endl;
                    }
                }

                cout << ">Your choice: ";
                string user_remove_day;
                getline(cin >> std::ws, user_remove_day);
                if(user_remove_day == std::to_string(workSchedule.size() + 1)){//get out the loop
                    remove_check = false;
                    break;
                }
                for(int i = 0; i < workSchedule.size(); ++i){
                    if(user_remove_day == std::to_string(i + 1)){
                        string remove_time;
                        cout << "Please choose the time period that you want to modify" << endl;

                        for(int a = 0; a < workSchedule[i].second.size(); ++a){
                            cout << a + 1 << ": " << workSchedule[i].second[a].first.getTime() << " to " << workSchedule[i].second[a].second.getTime() << endl;
                        }

                        cout << ">Your choice: ";
                        getline(cin >> std::ws, remove_time);
                        for(int a = 0; a < workSchedule[i].second.size(); ++a){
                            if(remove_time == std::to_string(a + 1)){
                                workSchedule[i].second.erase(workSchedule[i].second.begin() + a);
                                cout << sp_colors::GREEN << "Your time period is removed!" << sp_colors::RESET << endl;
                                isValidRemoveTime = true;
                                break;
                            } 
                        }
                        if(!isValidRemove){
                            cout << sp_colors::RED << "Invalid Choice!" << sp_colors::RESET << endl;
                        }
                        //get out this page. Force users to enter again
                        isValidRemove = true;
                        remove_check = false;
                    }
                }
            }
            //if the time in the day is empty, we remove the day too
            for(int i = 0; i < workSchedule.size(); ++i){
                if(workSchedule[i].second.empty()){
                    workSchedule.erase(workSchedule.begin() + i);
                }
            }
            
        }else if(user_choice == "3"){
            check_page = false;
        }else{
            cout << sp_colors::RED << "Invalid Choice!" << sp_colors::RESET << endl;
        }
    }      
}

void Supporter::displayUserList(){
    cout << sp_colors::YELLOW << std::setw(266) << std::setfill('-') << "" << std::setfill(' ') << sp_colors::RESET <<std::endl;
    cout << sp_colors::YELLOW << std::left << std::setw(13) << "| Member id |" << std::setw(25) << " Fullname               |" << std::setw(15) << " Credit Point      |"
            << std::setw(15) << " Phone Number |" << std::setw(35) << " Address                          |"  << std::setw(15) << " City         |"
            << std::setw(15) << " Host Rating  |" << std::setw(16) << " Hosting Count |"  << std::setw(25) << " Block List              |" 
            << std::setw(20) << " Supporting Count   |" <<std::setw(10) << " Rating  |" 
            << std::setw(15) << " Rating Skill |" << std::setw(40) << " Introduction                          |" << endl;
    cout << std::setw(266) << std::setfill('-') << "" << std::setfill(' ') << sp_colors::RESET <<std::endl;
    cout << sp_colors::WHITE_BOLD << "| " << std::setw(10) << this->member_id
                            <<"| "<<std::setw(23) << this->full_name
                            <<"| " << std::setw(18) << this->credit_point
                            <<"| " << std::setw(13) << this->phone_number
                            <<"| " << std::setw(33) << this->address
                            <<"| " << std::setw(13) << this->city
                            <<"| " << std::setw(13) << std::to_string(this->host_rating_score)
                            <<"| " << std::setw(14) << std::to_string(this->host_count)
                            <<"| " << std::setw(24) << this->displayBlockList()
                            <<"| " << std::setw(19) << this->support_count
                            <<"| " << std::setw(8) << this->support_rating_score
                            <<"| " << std::setw(13) << this->skill_rating_score  
                            <<"| " << std::setw(38) << this->about_me << "|"<< endl;
            cout << sp_colors::YELLOW << std::setw(266) << std::setfill('-') << "" << std::setfill(' ') << sp_colors::RESET << std::endl;
            this->displayWorkSchedule();

}