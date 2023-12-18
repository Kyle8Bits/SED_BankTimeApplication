#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Member.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

#define loop(n) for(int i = 0; i < n; ++i)
#define FILENAME "members.dat"

class System{
private:
    std::vector<Member*> member_list; 
    Member* logged_in_member;//This pointer of member to store the information of the member who has logged in successfully
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

        loop(member_list.size()){
            if(member_list[i]->getUsername() == user_name_input && member_list[i]->getPassword() == pass_word_input){
                cout << "Login SUCCESSFULLY!" << endl;

                logged_in_member = member_list[i];//set the loggedinmember = the member_list at index i
                return true;
            }
        }
        cout << "Your username or password is incorrect!" << endl;
        return false;
    }

    // bool saveToFile(){
    //     std::fstream my_file;
    //     my_file.open(FILENAME, std::ios::out);//use trunc to remove all the old content
    //     if (!my_file.is_open()) {
    //         cout << "Can not open the file" << endl;
    //         return false;
    //     }

    //     loop(member_list.size()){
    //         if(i == member_list.size() - 1){//If go to the last element
    //             my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" <<member_list[i]->getAddress() << "-" << member_list[i]->getCity() << "-" << member_list[i]->getAboutMe();//save to file without endl
    //         }else{
    //             my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" << member_list[i]->getAddress() << "-" << member_list[i]->getCity() << "-" << member_list[i]->getAboutMe() << endl ;
    //         }
    //     }

    //     my_file.close();
    //     cout << "Save to file SUCCESFULLY!" << endl;
    //     return true;
    // }

    // bool loadData(){
    //     std::fstream my_file;
    //     my_file.open(FILENAME, std::ios::in);

    //     if (!my_file.is_open()) {
    //         cout << "Can not open the file" << endl;
    //         return false;
    //     }
        
    //     member_list.clear(); //clear the member list before load the data
        
    //     string username_from_file, password_from_file, id_from_file, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file; // varibles to store data from file and push into the list
        
    //     while(getline(my_file, username_from_file, '-') &&  getline(my_file, password_from_file, '-') && getline(my_file, id_from_file, '-') && 
    //           getline(my_file, full_name_from_file, '-') && getline(my_file, phonenumber_from_file, '-') && getline(my_file, address_from_file, '-') && getline(my_file, city_from_file, '-') && getline(my_file, about_me_from_file)){

    //         //add it into the list
    //         Member* new_member = new Member(username_from_file, password_from_file, id_from_file, 20, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file, about_me_from_file);
    //         member_list.push_back(new_member);
    //     }
    //     my_file.close();

    //     if(!member_list.empty()){//if the list is not empty, run teh code below
    //         string max_id = member_list[0]->getMemberId();
    //         string number_part = max_id.substr(1);// take the string from the second position to end (it will skill character "M")
    //         int max_id_numeric = std::stoi(number_part);//Assume that the first member is the member which has the maximum id
            
    //         for(int i = 1; i < member_list.size(); i++){
    //             string id_string = member_list[i]->getMemberId();
    //             string number_part_id = id_string.substr(1);//take the string from the second position to end (it will skill character "M")
    //             int id_numeric = std::stoi(number_part_id);

    //             if(max_id_numeric < id_numeric){// Assign the value of id_numeric to the max_id_numeric if id_numeric is larger than max_id_numeric
    //                 max_id_numeric = id_numeric;
    //             }
    //         }

    //         //Assign teh max value to the number_of_4student in Member file
    //         Member::number_of_member = max_id_numeric;   
    //     }
        
    //     return true;
    // }

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
        cout << "****Member list****" << endl;
        loop(this->member_list.size()){
            //Go to each member to print the information
            cout << "Member " << i + 1 << ": " << endl;
            cout << "username: " << member_list[i]->getUsername() 
                 << ", password: "<< member_list[i]->getPassword()
                 << ", member id: " << member_list[i]->getMemberId()
                 << ", credit point: " << member_list[i]->getCreditPoint()
                 << ", fullname: " << member_list[i]->getFullName()
                 << ", address: " << member_list[i]->getAddress()
                 << ", city: " << member_list[i]->getCity()
                 << ", about me: " << member_list[i]->getAboutMe() << endl;
            
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


    ~System() {//Clear the member to advoid memory leak
        for (Member* member : member_list) {
            delete member;
        }
    }

    std::vector<Member*>& getMemberList(){
        return this->member_list;
    }

    void setMemberList(std::vector<Member*>& new_member_list){
        this->member_list = new_member_list;
    }

    Member* getLoggedInMember(){
        return this->logged_in_member;
    }

};

// int main(){
//     System system;
//     if(!system.loadData()){//If the loadData() function return false
//         cout << "Fail to load data" << endl;
//     }

//     int user_choice = 0;
//     bool check = true;
//     while (check){
//         cout << "1. register\n" 
//              << "2. Login\n"
//              << "3. show member\n"
//              << "4. EXIT! \n";
//         cin >> user_choice;
//         switch (user_choice){
//         case 1:
//             system.registerMember();
//             break;
//         case 2:
//             system.loginMember();
//             char user_choice;
//             cout << "Do you want to add more information about you?" << endl;
//             cout << "[Y/N]: ";
//             cin >> user_choice;

//             if(user_choice == 'Y'){
//                 system.addInformation();
//             }
//             break;
//         case 3:
//             system.displayMemberList();
//             break;
//         case 4:
//             check = false;
//             break;  
//         default:
//             check = false;
//             break;
//         }
//     }

//     if(!system.saveToFile()){
//         cout << "Can not save to file" << endl;
//     }

//     cout << "Have a nice day bro" << endl;

// }