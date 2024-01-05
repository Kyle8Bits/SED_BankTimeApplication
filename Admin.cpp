#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Member.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Admin {
private:
    const string adminUsername = "admin";
    const string adminPassword = "admin";

public:
    Admin(string adminUsername = "", string adminPassword = ""){}

    // Method to validate admin login
    bool adminLogin(const string& uname, const string& pwd) {
        return (uname == adminUsername && pwd == adminPassword);
    }
};


// int main() {
//     vector<Member> membersList;

//     // Sample member registration
//     Member member1("user1", "pass1");
//     membersList.push_back(member1);

//     // See full list of mmembers in another file 


//     // Admin login and password reset example
//     Admin admin(membersList);
//     admin.saveDataToFile("member.dat");

//     displayLoginScreen("Admin Login");

//     string adminUsername, adminPassword;
//     cout << "Enter admin username: ";
//     cin >> adminUsername;
//     cout << "Enter admin password: ";
//     cin >> adminPassword;

//     if (admin.adminLogin(adminUsername, adminPassword)) {
//         string memberUsername, newPwd;

//         cout << "Enter member username to reset password: ";
//         cin >> memberUsername;
//         cout << "Enter new temporary password: ";
//         cin >> newPwd;

//         admin.resetMemberPassword(adminPassword, memberUsername, newPwd);


//     // Member login 

//         displayLoginScreen("Member Login");
//         std::string memberLoginUsername, memberLoginPassword;
//         std::cout << "Enter member username to log in: ";
//         std::cin >> memberLoginUsername;
//         std::cout << "Enter password: ";
//         std::cin >> memberLoginPassword;

//         // Attempt to log in as a member
//         if (admin.memberLogin(memberLoginUsername, memberLoginPassword)) {
//             // Successfully logged in
//             // Additional member actions can be added here
//         }
//     } else {
//         std::cout << "Invalid admin credentials.\n";
//     }


//     admin.saveDataToFile("member.dat");

//     return 0;
// }
