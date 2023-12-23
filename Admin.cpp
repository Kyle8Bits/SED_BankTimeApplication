#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Member {
private:
    string username;
    string password;
    bool loggedIn;

public:
    Member(const string& uname, const string& pwd) : username(uname), password(pwd), loggedIn(false) {
        // Initialize other member details
    }

    // Getter for username
    string getUsername() const {
        return username;
    }


     // Getter for password
    string getPassword() const {
        return password;
    }


    // Method to reset the password
    void resetPassword(const string& newPwd) {
        // Add validation if needed
        password = newPwd;
        loggedIn = false;
        cout << "Temporary password set successfully. Please log in with the new password.\n";
    }

    // Method to log in with the password
    bool login(const string& enteredPassword) {
        if (enteredPassword == password) {
            loggedIn = true;
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Invalid password. Login failed.\n";
            return false;
        }
    }

    // Method to check if the member is logged in
    bool isLoggedIn() const {
        return loggedIn;
    }
};

class Admin {
private:
    const string adminUsername = "admin";
    const string adminPassword = "admin";
    vector<Member>& members;

public:
    Admin(vector<Member>& membersList) : members(membersList) {}

    // Method to validate admin login
    bool adminLogin(const string& uname, const string& pwd) {
        return (uname == adminUsername && pwd == adminPassword);
    }

    // Method to reset password for a member
    void resetMemberPassword(const string& adminPwd, const string& memberUsername, const string& newPwd) {
        if (!adminLogin(adminUsername, adminPwd)) {
            cout << "Invalid admin credentials. Cannot reset password.\n";
            return;
        }

        for (Member& member : members) {
            if (member.getUsername() == memberUsername) {
                member.resetPassword(newPwd);
                return;
            }
        }

        cout << "Member not found.\n";
    }

     // Method to log in as a member
    bool memberLogin(const std::string& uname, const std::string& pwd) {
        for (Member& member : members) {
            if (member.getUsername() == uname) {
                return member.login(pwd);
            }
        }

        std::cout << "Member not found.\n";
        return false;
    }

      // Save member data to a file
    void saveDataToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Member& member : members) {
                file << member.getUsername() << " " << member.getPassword() << "\n";
            }
            file.close();
            cout << "Data saved to file: " << filename << endl;
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    // Load member data from a file
    void loadDataFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            members.clear(); // Clear existing members
            string uname, pwd;
            while (file >> uname >> pwd) {
                members.emplace_back(uname, pwd);
            }
            file.close();
            cout << "Data loaded from file: " << filename << endl;
        } else {
            cout << "Unable to open file: " << filename << endl;
        }
    }
};



// Function to display a simple login screen
void displayLoginScreen(const string& title) {
    std::cout << "-----------------------------\n";
    std::cout << "    " << title << " - Time Bank\n";
    std::cout << "-----------------------------\n";
}


int main() {
    vector<Member> membersList;

    // Sample member registration
    Member member1("user1", "pass1");
    membersList.push_back(member1);

    // See full list of mmembers in another file 


    // Admin login and password reset example
    Admin admin(membersList);
    admin.saveDataToFile("member.dat");

    displayLoginScreen("Admin Login");

    string adminUsername, adminPassword;
    cout << "Enter admin username: ";
    cin >> adminUsername;
    cout << "Enter admin password: ";
    cin >> adminPassword;

    if (admin.adminLogin(adminUsername, adminPassword)) {
        string memberUsername, newPwd;

        cout << "Enter member username to reset password: ";
        cin >> memberUsername;
        cout << "Enter new temporary password: ";
        cin >> newPwd;

        admin.resetMemberPassword(adminPassword, memberUsername, newPwd);


    // Member login 

        displayLoginScreen("Member Login");
        std::string memberLoginUsername, memberLoginPassword;
        std::cout << "Enter member username to log in: ";
        std::cin >> memberLoginUsername;
        std::cout << "Enter password: ";
        std::cin >> memberLoginPassword;

        // Attempt to log in as a member
        if (admin.memberLogin(memberLoginUsername, memberLoginPassword)) {
            // Successfully logged in
            // Additional member actions can be added here
        }
    } else {
        std::cout << "Invalid admin credentials.\n";
    }


    admin.saveDataToFile("member.dat");

    return 0;
}
