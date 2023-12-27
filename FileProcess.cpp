#include <iostream>
#include <fstream>
#include <vector>

#include "Supporter.cpp"
#include "Member.cpp"
#include "Time.cpp"
#include "BookingSupporter.cpp"

using std::endl;
using std::cout;
using std::cin;
using std::string;

#define loop(n) for(int i = 0; i < n; ++i)
#define MEMBERFILE "SourceFile/members.dat"
#define SKILLFILE "SourceFile/skills.dat"
#define BOOKINGFILE "SourceFile/booking.dat"


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

        cout << "Save to file SUCCESFULLY!" << endl;
        return true;
    }

    std::vector<Member*> loadData(std::vector<Member*>& member_list){//Pass the member_list by reference
        std::fstream my_file;
        my_file.open(MEMBERFILE, std::ios::in);
        member_list.clear(); //clear the member list before load the data
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return member_list;
        }
        
        string username_from_file, password_from_file, id_from_file, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file; // varibles to store data from file and push into the list
        string start_time_hour, start_time_minute, end_time_hour, end_time_minute, cost_from_file, skill_rating_score_file, support_rating_score_file, support_count_file;
        std::vector<string> skill_list = {};
        while(getline(my_file, username_from_file, '-') &&  getline(my_file, password_from_file, '-') && getline(my_file, id_from_file, '-') && 
              getline(my_file, full_name_from_file, '-') && getline(my_file, phonenumber_from_file, '-') && getline(my_file, address_from_file, '-') && getline(my_file, city_from_file, '-')){

            char checkType = id_from_file[0];//this to check the id is M or S
            
            Member* new_member = nullptr;//declare the new member & ready to push to the list
            if(checkType == 'M'){
                getline(my_file, about_me_from_file);// This to read about me from teh file, I can not but it in the while loop because it does neccessary for users
                new_member = new Member(username_from_file, password_from_file, id_from_file, 20, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file);
            } else if (checkType == 'S'){
                getline(my_file, about_me_from_file, '-');
                getline(my_file, start_time_hour, '-');
                getline(my_file, start_time_minute, '-');
                getline(my_file, end_time_hour, '-');
                getline(my_file, end_time_minute, '-');
                getline(my_file, cost_from_file, '-');
                getline(my_file, skill_rating_score_file, '-');
                getline(my_file, support_rating_score_file, '-');
                getline(my_file, support_count_file);
                
                skill_list = readSkillSupporter(id_from_file);

                new_member = new Supporter(username_from_file, password_from_file, id_from_file, 20, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file,
                                           0, 0, {}, Time(std::stoi(start_time_hour), std::stoi(start_time_minute)), Time(std::stoi(end_time_hour), std::stoi(end_time_minute)), skill_list, std::stoi(cost_from_file), 
                                           std::stod(skill_rating_score_file), std::stod(support_rating_score_file), std::stoi(support_count_file));
                
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

    bool saveBookingFile(std::vector<BookingSupporter*>& booking_list){
        std::fstream my_file;
        my_file.open(BOOKINGFILE, std::ios::out);
        if(!my_file.is_open()){
            cout << "Can not open the booking file"<< endl;
            return false;
        }

        loop(booking_list.size()){
            if(i == booking_list.size() - 1){//If go to the last element
                my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus();//save to file without endl
            }else{
                my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus() << endl;
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

        string bookingid_from_file, hostid_from_file, supportid_from_file, status_from_file;

        while (getline(my_file, bookingid_from_file, '-') && getline(my_file, hostid_from_file, '-') && getline(my_file, supportid_from_file, '-') && getline(my_file,status_from_file)){
            BookingSupporter *booking  = new BookingSupporter(hostid_from_file, supportid_from_file, status_from_file, bookingid_from_file);
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
