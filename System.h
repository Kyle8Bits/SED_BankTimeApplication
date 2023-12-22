#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Member.h"
#include "Supporter.h"
#include "Time.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

#define loop(n) for(int i = 0; i < n; ++i)
#define FILENAME "members.dat"

class System{
private:
    std::vector<Member*> member_list; 
    Member* logged_in_member;
    Supporter* logged_in_supporter;

public:
    System(std::vector<Member*> member_list);

    int getPositionOfMemberByUsername(string user_name_account);
    bool checkNonEmpty(const string& str);
    bool registerMember();
    bool loginMember();
    bool isValidPhone(const string& str);
    void displayMemberList();
    bool addInformation();
    bool upgradeToSupporter();
    std::vector<Member*>& getMemberList();
    void setMemberList(std::vector<Member*>& new_member_list);
    Member* getLoggedInMember();
    Supporter* getLoggedInSupporter();
    ~System();
};

#endif // SYSTEM_H
