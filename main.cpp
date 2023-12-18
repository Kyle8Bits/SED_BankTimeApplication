#include <iostream>
#include <vector>

#include "System.cpp"
#include "FileProcess.cpp"

using std::cout;
using std::string;
using std::vector;

int main(){
    cout << "EEET2482/COSC2082 ASSIGNMENT\n"
        << "'TIME BANK' APPLICATION\n"
        << "Instructor: Mr. Tran Duc Linh\n"
        << "Group: Group ...\n"
        << "S, Student Name\n"
        << "S, Student Name\n"
        << "S, Student Name\n"
        << "S, Student Name\n";
    //---------------------------------------------START PROGRAM---------------------------------------------------------------------------
    System system;
    FileProcess file_process;
    
    std::vector<Member*> member_list_from_file = file_process.loadData(system.getMemberList());//
    //The function loadData will return a vector of <Member*>. Copy it to the member_list_from_file. After that 
    //We paste the member_list_from_file to the setMemberList, to set the private attribute member_list of the class System
    system.setMemberList(member_list_from_file);
    
    bool check = true;//this boolean for the while loop below
    while(check){
        cout << "\t\t____________________________________\n"
            << "\t\t|        WELCOME TO TIME BANK       |\n"
            << "\t\t|                                   |\n"
            << "\t\t|         Use the app as            |\n"
            << "\t\t|                                   |\n"
            << "\t\t|          1. Guest                 |\n"
            << "\t\t|                                   |\n"
            << "\t\t|          2. Member                |\n"
            << "\t\t|                                   |\n"
            << "\t\t|          3. Admin                 |\n"
            << "\t\t|                                   |\n"
            << "\t\t-------------------------------------\n"
            << ">Your choice: ";

        int user_choice; cin >> user_choice; //Get the input of the user's ipnut
        switch(user_choice){
            case 1:
                cout << "Do you want to register the new account" << endl;
                cout << "[Y/N]:";
                char user_choice_char;
                cin >> user_choice_char;
                user_choice_char = std::toupper(user_choice_char);//to ensure that users type 'Y' and 'y' are the same

                switch(user_choice_char){
                    case 'Y':
                        system.registerMember();
                        break;
                    case 'N':
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                system.loginMember();
                break;
            case 3:
                //TEST, THIS ADMIN TO SHOW ALL THE MEMBERS IN THE LIST
                system.displayMemberList();
                break;
            default:
                cout << "Please enter the valid input" << endl;
                cout << "Program end!" << endl;
                check = 0;
        }
    }

    if( !file_process.saveToFile(system.getMemberList()) ){
        cout << "Can not save to the file!" << endl;
    }
    
    return 0;
}