#include <iostream>
#include <fstream>

using std::endl;
using std::cout;
using std::cin;
using std::string;

#define loop(n) for(int i = 0; i < n; ++i)
#define FILENAME "members.dat"


class FileProcess{//THis class is use for loading the file and save to the file
public:
    bool saveToFile(std::vector<Member*> member_list){
        std::fstream my_file;
        my_file.open(FILENAME, std::ios::out);//use trunc to remove all the old content
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
        cout << "Save to file SUCCESFULLY!" << endl;
        return true;
    }

    std::vector<Member*> loadData(std::vector<Member*>& member_list){//Pass the member_list by reference
        std::fstream my_file;
        my_file.open(FILENAME, std::ios::in);

        member_list.clear(); //clear the member list before load the data
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return member_list;
        }
        
        
        string username_from_file, password_from_file, id_from_file, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file; // varibles to store data from file and push into the list
        string start_time_hour, start_time_minute, end_time_hour, end_time_minute, cost_from_file, skill_rating_score_file, support_rating_score_file, support_count_file;
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

                new_member = new Supporter(username_from_file, password_from_file, id_from_file, 20, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file,
                                           0, 0, {}, Time(std::stoi(start_time_hour), std::stoi(start_time_minute)), Time(std::stoi(end_time_hour), std::stoi(end_time_minute)), {}, std::stoi(cost_from_file), 
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

};