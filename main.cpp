#include <iostream>
using std::cout;
using std::string;
using std::vector;

class User{
private:
    string username;
    string password;
    string phone_number;
    string email;
    string home_address;
    std::vector<string> skill_list;

public:
    User(string usernameVal = "", string passwordVal = "", string phone_numberVal = "", string emailVal = "",
         string home_addressVal = "", std::vector<string> skill_listVal = {})
    : username(usernameVal), password(passwordVal), phone_number(phone_numberVal), 
      email(emailVal), home_address(home_addressVal), skill_list(skill_listVal.begin(), skill_listVal.end()){
        // for(int i = 0; i < skill_listVal.size(); ++i){
        //     skill_list.push_back(skill_listVal[i]);
        // }
    }
};
int main(){
    cout << "EEET2482/COSC2082 ASSIGNMENT\n"
         << "'TIME BANK' APPLICATION\n"
         << "Instructor: Mr. Tran Duc Linh\n"
         << "Group: Group ...\n"
         << "S, Student Name\n"
         << "S, Student Name\n"
         << "S, Student Name\n"
         << "S, Student Name\n";

    cout << "\t\t____________________________________\n"
         << "\t\t|        WELCOME TO TIME BANK       |\n"
         << "\t\t|                                   |\n"
         << "\t\t|         User the app as           |\n"
         << "\t\t|                                   |\n"
         << "\t\t|          1. Guest                 |\n"
         << "\t\t|                                   |\n"
         << "\t\t|          2. Member                |\n"
         << "\t\t|                                   |\n"
         << "\t\t|          3. Admin                 |\n"
         << "\t\t|                                   |\n"
         << "\t\t-------------------------------------\n"
         << ">Your choice: ";

    int user_choice; //Get the input of the user's ipnut
    switch(user_choice){
        case 1:
            break;
    }
    
    return 0;
}