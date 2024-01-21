#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iomanip>

#include "Member.h"
#include "Supporter.h"
#include "Time.h"
#include "BookingSupporter.h"
#include "Calendar.h"
#include "RealTime.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::find;

#define loop(n) for(int i = 0; i < n; ++i)
// #define FILENAME "members.dat"
#define clearScreen() cout << "\x1B[2J\x1B[H";

namespace colors{
    extern const char* RED;
    extern const char* YELLOW;
    extern const char* GREEN;
    extern const char* RESET;  
}

#define NotExistSupporterError() cout << colors::RED << "\t\tERROR: This supporter do not exsit in the list" << colors::RESET << std::endl;
#define BookingTimeError() cout << colors::RED << "\t\tERROR: This supporter work schedule do not match your booking time" << colors::RESET << std::endl;
#define LogicTimeError() cout << colors::RED << "\t\tERROR: The start time should be earlier than the end time." << colors::RESET << std::endl;
#define TimeFormatError() cout << colors::RED << "\t\tERROR: The time must be in form HH:MM" << colors::RESET << std::endl;
#define BlockError() cout << colors::RED << "\t\tERROR: You can not book a supporter in your block list" << colors::RESET << std::endl;
#define InsufficientPointError() cout << colors::RED << "\t\tERROR: Insufficient credit points to book this supporter" << colors::RESET << std::endl;
#define SucessBooking() cout << colors::GREEN << "\t\tYour booking has been created" << colors::RESET << endl;
#define IdNotInListError() cout << colors::RED << "\t\tPlease enter the valid supporter's id" << colors::RESET << endl;
#define CityError() cout << colors::RED << "You cannot book the supporter with different city" << colors::RESET << endl;


class System{
private:
    BookingSupporter booking;
    std::vector<Member*> member_list; 
    std::vector<BookingSupporter*> booking_list;
    std::vector<Supporter*> availableSupporter;//This to restrict for users only book the valid supporter id
    Member* logged_in_member;//This pointer of member to store the information of the member who has logged in successfully
    Supporter* logged_in_supporter;//This pointer of member to store the information of the member who has logged in successfully
    bool is_admin = false;

public:
    //CONSTRUCTOR
    System(std::vector<Member*> member_list = {});

    //The function below to get the position of the member in the list via the username
    int getPositionOfMemberByUsername(string user_name_account);

    bool checkNonEmpty(const string& str);

    bool registerMember();

    bool loginMember();
   
    //method to check phone number
    bool isValidPhone(const string& str);

    bool isValidInterger(const string& str);

    bool upgradeToSupporter();

    int getRequestNotification();

    int getNotification();

    void clearAvailableSupporterList();
    
    bool checkDuplicateDay(std::vector< std::pair< string, std:: vector< std::pair< Time, Time> > > > list, string choose);

    std::string getDayString(int day) ;

    void resetMemberPassword();

    bool isValidCost(string str);

    double findCreditPointFromTime(Time start_time, Time end_time, int cost_per_hour);

    void viewPersonalInformation();

    bool checkValidTime(string time);

    bool isAvailableDay(Supporter* id, int dayOfWeek);

    void displayAvailableSupporter(bool filterCity);

    void createBooking();

    void viewHistory();

    void setStatusById(string id, string choice);

    string getStatusById(string id);

    void setProgressById(string id, string choice);

    void addHostScoreByID(string id, int rating);

    void addSupporterScoreByID(string id, int rating, int skill_rating);

    void setHostCommentById(string id, string comment);

    string getProgressById(string id);

    void setHostRatingById(string id, int rating);

    double getMoneyById(string id);

    std::vector<string> showAvalableBooking();


    void decideJob();

    std::vector<BookingSupporter*> isOverLap(string bk_id);

    void buyCredit();

    void displaySupporter();

    void statusSetting();

    void viewHistoryJob();

    void setSupportRatingById(int skill_score, int support_score, string comment, string id);

    void checkCompleteTask();

    string getCurrentStatus();

    bool blockUser();

    string getFullNameFromId(string id);

    void showBlockList();

    std::vector<Member*>& getMemberList();

    std::vector<BookingSupporter*>& getBookingList();

    void setMemberList(std::vector<Member*>& new_member_list);

    void setBookingList(std::vector<BookingSupporter*>& new_booking_list);

    void displayMemberList();

    Member* getLoggedInMember();

    Supporter* getLoggedInSupporter();

    bool getIsAdmin();

    void setIsAdmin(bool is_admin);

    BookingSupporter getBooking();

    ~System();
};
#endif