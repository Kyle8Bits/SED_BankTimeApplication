#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>

#include "Supporter.cpp"
#include "Member.cpp"
#include "Time.cpp"
#include "BookingSupporter.cpp"

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::stoi;
using std::getline;

#define loop(n) for(int i = 0; i < n; ++i)
#define MEMBERFILE "../SourceFile/members.dat"
#define SKILLFILE "../SourceFile/skills.dat"
#define BOOKINGFILE "../SourceFile/booking.dat"
#define TIMEFILE "../SourceFile/timepair.dat"
#define BLOCKFILE "../SourceFile/blocklist.dat"

class FileProcess{//THis class is use for loading the file and save to the file
public:
    bool saveToFile(std::vector<Member*> member_list){
        //***********************SAVE BASIC INFORMATION***********************
        std::fstream my_file;
        my_file.open(MEMBERFILE, std::ios::out);
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }

        loop(member_list.size()){
            if(i == member_list.size() - 1){//If go to the last element
                // my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" <<member_list[i]->getAddress() << "-" << member_list[i]->getCity() << "-" << member_list[i]->getAboutMe();//save to file without endl
                my_file << member_list[i]->toString();
            }else{
                my_file << member_list[i]->toString() << endl;
                // my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" << member_list[i]->getAddress() << "-" << member_list[i]->getCity() << "-" << member_list[i]->getAboutMe() << endl ;
            }
        }

        my_file.close();
        cout << "Save member SUCCESFULLY!" << endl;

        //***********************SAVE SKILL LIST INFORMATION FOR SUPPORTER***********************
        my_file.open(SKILLFILE, std::ios::out);
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }

        if(!member_list.empty()){//If the member is empty, we do not write to the file
            loop(member_list.size()){
                //check the memberlist at index i is the supporter or not
                if (Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])) {
                    my_file << supporter->getMemberId() << "-" << supporter->skillListToString() << endl;
                    //Print the skill list with format ID1-SKILL1-SKILL2 
                    //                                 ID2-SKILL1-SKILL2
                }
            }
        }
        my_file.close();
        cout << "Save supporter SUCCESFULLY!" << endl;

        //***********************SAVE TIME PAIR LIST INFORMATION FOR SUPPORTER***********************
        my_file.open(TIMEFILE, std::ios::out);
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }

        if(!member_list.empty()){//If the member is empty, we do not write to the file
            loop(member_list.size()){
                //check the memberlist at index i is the supporter or not
                if (Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])) {
                    my_file << supporter->getMemberId() << supporter->scheduleToString() << endl;
                    //Print the skill list with format ID1-STIME#ETIME1-STIME#ETIME2
                    //                                 ID2-STIME#ETIME1-STIME#ETIME2
                }
            }
        }
        my_file.close();
        cout << "Save to file SUCCESFULLY!" << endl;


        //***********************SAVE BLOCK LIST FOR MEMBER & SUPPORTER***********************
        my_file.open(BLOCKFILE, std::ios::out);
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }

        if(!member_list.empty()){
            loop(member_list.size()){
                my_file << member_list[i]->getMemberId() << "-" << member_list[i]->blockListToString() << endl;
            }
        }

        my_file.close();
        return true;
    }

    Status statusEnum(string status){
        if (status == "OFFLINE"){
            return Status::OFFLINE;
        }
        else if (status == "ONLINE") {
            return Status::ONLINE;
        }
        else {
            cout <<"Cannot found the status";
            return Status::OFFLINE;  
        }
    }

    std::vector<Member*> loadData(std::vector<Member*>& member_list){//Pass the member_list by reference
        std::fstream my_file;
        my_file.open(MEMBERFILE, std::ios::in);
        member_list.clear(); //clear the member list before load the data
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return member_list;
        }
        
        string username_from_file, password_from_file, id_from_file, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file,crepoint_from_file, about_me_from_file; // varibles to store data from file and push into the list
        string start_time_hour, start_time_minute, end_time_hour, end_time_minute, cost_from_file, skill_rating_score_file, support_rating_score_file, support_count_file, host_not_comment_file,status_from_file, host_rating_score_file, host_count_file, supporter_not_comment_file, min_host_rating_file;
        std::vector<string> skill_list = {};
        std::vector<string> block_list = {};
        std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > workSchedule = {};
        
        while(getline(my_file, username_from_file, '-') &&  getline(my_file, password_from_file, '-') && getline(my_file, id_from_file, '-') && 
              getline(my_file, full_name_from_file, '-') && getline(my_file, phonenumber_from_file, '-') && getline(my_file, address_from_file, '-') && getline(my_file, city_from_file, '-') && getline(my_file, crepoint_from_file, '-') && getline(my_file, host_rating_score_file,'-') && getline(my_file,host_count_file,'-')&& getline(my_file,supporter_not_comment_file,'-')){

            char checkType = id_from_file[0];//this to check the id is M or S
            Member* new_member = nullptr;//declare the new member & ready to push to the list
            if(checkType == 'M'){
                block_list = readBlockList(id_from_file);

                getline(my_file, about_me_from_file);// This to read about me from teh file, I can not but it in the while loop because it does neccessary for users
                new_member = new Member(username_from_file, password_from_file, id_from_file, std::stod(crepoint_from_file), full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file, std::stod(host_rating_score_file), std::stoi(host_count_file),std::stoi(supporter_not_comment_file), block_list);
            } else if (checkType == 'S'){
                getline(my_file, about_me_from_file, '-'); //Be the one
                getline(my_file, cost_from_file, '-'); // 16
                getline(my_file, skill_rating_score_file, '-'); //9
                getline(my_file, support_rating_score_file, '-');//9
                getline(my_file, support_count_file,'-');//2
                getline(my_file, host_not_comment_file,'-');//0
                getline(my_file, status_from_file, '-');//online
                getline(my_file, min_host_rating_file);

                skill_list = readSkillSupporter(id_from_file);
                workSchedule = readWorkDay(id_from_file);
                block_list = readBlockList(id_from_file);

                // cout << id_from_file << endl;

                new_member = new Supporter(username_from_file, password_from_file, id_from_file, std::stod(crepoint_from_file), full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file,
                                           std::stod(host_rating_score_file),std::stoi(host_count_file),std::stoi(supporter_not_comment_file), block_list, workSchedule, statusEnum(status_from_file), skill_list, std::stoi(cost_from_file), 
                                           std::stod(skill_rating_score_file), std::stod(support_rating_score_file), std::stoi(support_count_file), std::stoi(host_not_comment_file), std::stoi(min_host_rating_file));
            }
            if(new_member){
                member_list.push_back(new_member);
            }
        }
        my_file.close();
        
        if(!member_list.empty()){//if the list is not empty, run teh code below
            string max_id = member_list[0]->getMemberId();
            string number_part = max_id.substr(1);// take the string from the second position to end (it will skill character "M")
            int max_id_numeric = std::stoi(number_part);//Assume that the first member is the member which has the maximum id
            
            for(int i = 1; i < member_list.size(); i++){
                string id_string = member_list[i]->getMemberId();
                string number_part_id = id_string.substr(1);//take the string from the second position to end (it will skill character "M")
                int id_numeric = std::stoi(number_part_id);

                if(max_id_numeric < id_numeric){// Assign the value of id_numeric to the max_id_numeric if id_numeric is larger than max_id_numeric
                    max_id_numeric = id_numeric;
                }
            }

            //Assign the max value to the number_of_4student in Member file
            Member::number_of_member = max_id_numeric;//This to ensure that the automatically generate the id correct!
            //we will set the number of student = the maximum id in the list, because if the admin remove the id, the number_of_member will not correct anymore,
        }
        
        return member_list;
    }

    std::vector<string> readSkillSupporter(string id_skill){
        std::vector<string> skill_list;
        std::fstream my_file;
        my_file.open(SKILLFILE, std::ios::in);
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return skill_list;
        }
        string skill, id;
        while(getline(my_file, id, '-')){
            if(id == id_skill){
                while(getline(my_file, skill, '-') && skill[0] != '\n'){
                    //This skill[0] != '\n to stop the function when the skill at index 0 is newline
                    skill_list.push_back(skill);
                }
                break;
            }
            //if the id is not match, skip the rest of the file
            getline(my_file,skill);
        }
        my_file.close();

        return skill_list;
    }

    std::vector<string> readBlockList(string id){
        std::vector<string> block_list;
        std::fstream my_file;
        my_file.open(BLOCKFILE, std::ios::in);

        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return block_list;
        }

        string block_id, id_from_file;
        while(getline(my_file, id_from_file, '-')){
            if(id_from_file == id){
                while(getline(my_file, block_id, '-') && block_id[0] != '\n'){
                    //This skill[0] != '\n to stop the function when the skill at index 0 is newline
                    block_list.push_back(block_id);
                }
                break;
            }
            //if the id is not match, skip the rest of the file
            getline(my_file,block_id);
        }
        my_file.close();

        return block_list;
    }

    std::vector<std::pair<std::string, std::vector<std::pair<Time, Time>>>> readWorkDay(const std::string& id_time) {
        std::vector<std::pair<std::string, std::vector<std::pair<Time, Time>>>> workSchedule;
        std::fstream my_file;
        my_file.open(TIMEFILE, std::ios::in); // Replace with your actual filename
        if (!my_file.is_open()) {
            std::cout << "Can not open the file" << std::endl;
            return workSchedule;
        }

        std::string time_pair, id, day_week;

        while (getline(my_file, id, '-')) {
            if (id == id_time) {
                while (getline(my_file, day_week, '-') && time_pair[0] != '\n') {
                    std::vector<std::pair<Time, Time>> time_pair_list;

                    while (getline(my_file, time_pair, '-') && time_pair[0] != '\0' && time_pair[0] != '\n') {
                        std::stringstream iss(time_pair);
                        int start_hour, start_min, end_hour, end_min;

                        char separator = ':';
                        iss >> start_hour >> separator >> start_min >> separator >> end_hour >> separator >> end_min;

                        time_pair_list.push_back(std::make_pair(Time(start_hour, start_min), Time(end_hour, end_min)));
                    }

                    workSchedule.push_back(std::make_pair(day_week, time_pair_list));
                }
                break;
            }

            // If the id is not a match, skip the rest of the line
            getline(my_file, day_week);
        }

        my_file.close();
        return workSchedule;
    }

    bool saveBookingFile(std::vector<BookingSupporter*>& booking_list){
        std::fstream my_file;
        my_file.open(BOOKINGFILE, std::ios::out);
        if(!my_file.is_open()){
            cout << "Can not open the booking file"<< endl;
            return false;
        }

        loop(booking_list.size()){
            if(i == booking_list.size() - 1){//If go to the last element
                my_file << booking_list[i]->toString();
                // my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus() << "-" << booking_list[i]->getProgress() << "-" << booking_list[i]->getTimeToFile();//save to file without endl
            }else{
                my_file << booking_list[i]->toString() << endl;
                // my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus() << "-" << booking_list[i]->getProgress() << "-" << booking_list[i]->getTimeToFile() << "-" << booking_list[i]. << endl;
            }
        }
        my_file.close();
        cout << "SAVE BOOKING SUCCESSFULLY" << endl;
        return true;
    }

    std::vector<BookingSupporter*> loadBookingFile(std::vector<BookingSupporter*>& booking_list){
        std::fstream my_file;
        my_file.open(BOOKINGFILE, std::ios::in);

        if (!my_file.is_open()){
            std::cerr << "Cannot read the booking file" << endl;
            return booking_list;
        }

        booking_list.clear(); //clear the list before reload data

        string bookingid_from_file, hostid_from_file, supportid_from_file, status_from_file, progress_from_file;
        string start_hour_file, start_minute_file, end_hour_file, end_minute_file;
        string host_rating_file, skill_rating_file, supporter_rating_file, host_comment_file, supporter_comment_file, total_cost_file;
        string day_from_file, month_from_file, year_from_file;

        while (getline(my_file, bookingid_from_file, '-') && getline(my_file, hostid_from_file, '-') && getline(my_file, supportid_from_file, '-') && getline(my_file, status_from_file, '-') && getline(my_file, progress_from_file, '-')
               && getline(my_file, start_hour_file, '-') && getline(my_file, start_minute_file, '-') && getline(my_file, end_hour_file, '-') && getline(my_file, end_minute_file, '-')
               && getline(my_file, host_rating_file, '-') && getline(my_file, skill_rating_file, '-') && getline(my_file, supporter_rating_file, '-') && getline(my_file, host_comment_file, '-') && getline(my_file, supporter_comment_file, '-') && getline(my_file, total_cost_file,'-') && getline(my_file, day_from_file,'-') && getline(my_file, month_from_file,'-') && getline(my_file, year_from_file)){
            
            Time start_time(std::stoi(start_hour_file), std::stoi(start_minute_file));
            Time end_time(std::stoi(end_hour_file), std::stoi(end_minute_file));
            BookingSupporter *booking  = new BookingSupporter(hostid_from_file, supportid_from_file, status_from_file, bookingid_from_file, progress_from_file, start_time, end_time, stoi(host_rating_file), stoi(skill_rating_file), stoi(supporter_rating_file), host_comment_file, supporter_comment_file, std::stod(total_cost_file), std::stoi(day_from_file), std::stoi(month_from_file), std::stoi(year_from_file));
            booking_list.push_back(booking);
        }
        my_file.close();

        if (!booking_list.empty()) {
            string max_id = booking_list[0]->getBookingId();
            string number_part = max_id.substr(2);  // Skip the first two characters (prefix "BK")
            int max_id_numeric;
            max_id_numeric = std::stoi(number_part);

        for (int i = 1; i < booking_list.size(); i++) {
            string id_string = booking_list[i]->getBookingId();
            string part_id = id_string.substr(2);  // Skip the first two characters (prefix "BK")
            int id_numeric;
            id_numeric =  std::stoi(part_id);

            if (max_id_numeric < id_numeric) {
                max_id_numeric = id_numeric;
            }
        }
            //Assign new start value for booking in BookingSupporter class
            BookingSupporter::number_of_booking = max_id_numeric;
        }
        return booking_list;
    }
}; 

#endif