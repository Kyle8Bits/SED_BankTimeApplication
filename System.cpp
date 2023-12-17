#include <iostream>
#include <vector>
#include <fstream>

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

    bool registerMember(){
        string user_name_input; 
        string pass_word_input; //these 2 attributes to take the value from input
        cout << "****Your registration adds great value to our community. Thank you!****" << endl;
        cout << "Please enter these basic information below: " << endl;
        cout << ">Username: " ;
        getline(cin >> std::ws, user_name_input); //std::ws to ignore the reduntant space
        if(user_name_input.empty()){//Check wether the users not type anything?
            cout << "Please enter non-empty value" << endl;
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

        if(pass_word_input.empty()){
            cout << "Please enter non-empty value" << endl;
            return false;
        }
        //Create a member and push it in the lsit
        Member* new_member = new Member(user_name_input, pass_word_input);
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
                return true;
            }
        }
        cout << "Your username or password is incorrect!" << endl;
        return false;
    }

    void displayMemberList(){
        cout << "****Member list****" << endl;
        loop(this->member_list.size()){
            //Go to each member to print the information
            cout << member_list[i]->getUsername() << ":" << member_list[i]->getPassword() << endl;
        }
    }

    bool saveToFile(){
        std::fstream my_file;
        my_file.open(FILENAME, std::ios::out);//use trunc to remove all the old content
        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }

        loop(member_list.size()){
            if(i == member_list.size() - 1){//If go to the last element
                my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword();//save to file without endl
            }else{
                my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << endl;
            }
        }

        my_file.close();
        cout << "Save to file SUCCESFULLY!";
        return true;
    }

    bool loadData(){
        std::fstream my_file;
        my_file.open(FILENAME, std::ios::in);

        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }
        
        member_list.clear(); //clear the member list before load the data
        
        string username_from_file, password_from_file; // 2 varibles to store the username and password to pass into the list
        while (getline(my_file, username_from_file, '-') && getline(my_file, password_from_file)) {
            // Read data from the file
            if (username_from_file.empty() || password_from_file.empty()) {
                break; // If the username or password cannot get the value anymore, break the loop
            }

            // Include it all in the list
            Member* new_member = new Member(username_from_file, password_from_file);
            member_list.push_back(new_member);
        }

        my_file.close();
        return true;
    }

    bool addPersonalData(){
        
    }

    ~System() {//Clear the member to advoid memory leak
        for (Member* member : member_list) {
            delete member;
        }
    }
};

int main(){
    System system;
    if(!system.loadData()){//If the loadData() function return false
        cout << "Fail to load data" << endl;
    }

    int user_choice = 0;
    bool check = true;
    while (check){
        cout << "1. register\n" 
             << "2. Login\n"
             << "3. show member\n"
             << "4. EXIT! \n";
        cin >> user_choice;
        switch (user_choice){
        case 1:
            system.registerMember();
            break;
        case 2:
            system.loginMember();
            break;
        case 3:
            system.displayMemberList();
            break;
        case 4:
            check = false;
            break;  
        default:
            check = false;
            break;
        }
    }

    if(!system.saveToFile()){
        cout << "Can not save to file" << endl;
    }

    cout << "Have a nice day bro" << endl;

}