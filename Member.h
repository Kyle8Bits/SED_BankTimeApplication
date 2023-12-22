#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>
#include "Account.h"
using std::string;
using std::vector;

class Member : public Account {
private:
    static int number_of_member;
    string member_id;
    int credit_point;
    string full_name;
    string phone_number;
    string address;
    string city;
    string about_me;
    double host_rating_score;
    int host_count;
    vector<string> block_list;

public:
    Member(string user_name , string pass_word , string member_id , int credit_point , string full_name , string phone_number ,
           string address, string city, string about_me, double host_rating_score,
           int host_count, vector<string> block_list);

    string getMemberId() const;
    void setMemberId(const string& member_id);

    int getCreditPoint() const;
    void setCreditPoint(int value);

    string getFullName() const;
    void setFullName(const string& value);

    string getPhoneNumber() const;
    void setPhoneNumber(const string& value);

    string getAddress() const;
    void setAddress(const string& value);

    string getCity() const;
    void setCity(const string& value);

    string getAboutMe() const;
    void setAboutMe(const string& value);

    double getHostRatingScore() const;
    void setHostRatingScore(double value);

    int getHostCount() const;
    void setHostCount(int value);

    const vector<string>& getBlockList() const;
    void setBlockList(const vector<string>& value);

    virtual ~Member() = default;
    virtual string toString();

    friend class System; 
    friend class FileProcess;
};

int Member::number_of_member;

#endif 
