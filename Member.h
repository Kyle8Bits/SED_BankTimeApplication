#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>
#include <iomanip>

#include "Account.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

namespace mb_colors {
    extern const char* RED;
    extern const char* YELLOW;
    extern const char* WHITE_BOLD;
    extern const char* GREEN;
    extern const char* RESET;
}

class Member : public Account{
protected:
    //INHERITANCE FROM ACCOUNT 
    // string user_name;
    // string pass_word;
    static int number_of_member;//the total number of the members in teh program

    //ATTRIBUTE OF MEMBER
    string member_id; 
    double credit_point;
    string full_name;
    string phone_number;
    string address;
    string city;
    string about_me;
    double host_rating_score = 0;
    int host_count = 0;
    int spt_not_comment = 0;
    std::vector<string> block_list;

public:
    //CONSTRUCTOR
    Member(string user_name = "", string pass_word = "", string member_id = "M", double credit_point = 20, string full_name = "", string phone_number = "", 
    string address = "", string city = "", string about_me = "",double host_rating_score = 0, 
    int host_count = 0, int supporter_not_comment = 0, std::vector<string> block_list = {});

    void collectScore(int score);

    virtual void displayPersonalInformation();

    void displayUserList();

    string getMemberId();
    void setMemberId(string member_id);

    //Getter and setter

    double getCreditPoint() const ;

    void setCreditPoint(double value);

    string getFullName() const ;

    void setFullName(string value);

    string getPhoneNumber() const;

    void setPhoneNumber(string value);

    bool isValidPhone(const string& str) ;

    bool setCityRequest();

    void setAddressRequest();

    bool setPhoneNumberRequest();

    bool unblockUser();

    string getAddress() const;

    void setAddress(string value);

    string getCity() const ;

    void setCity(string value);

    string getAboutMe() const ;

    bool addInformation();

    void setAboutMe(string value) ;

    double getAverageRatingScore() const ;

    void setAverageRatingScore(double value) ;

    int getHostCount() const ;

    void setHostCount(int value) ;

    void addCreditPoint(double credit_point);

    void subtractCreditPoint(double credit_point);

    double getHostRatingScore() ;

    string displayBlockList();

    string blockListToString();

    const std::vector<string>& getBlockList() const;

    void setBlockList(const std::vector<string>& value);

    virtual ~Member() = default;

    virtual string toString();
    
    friend class System;//Make system is friend of Member
    friend class FileProcess;
    friend class BookingSupporter;
};


#endif // MEMBER_H
