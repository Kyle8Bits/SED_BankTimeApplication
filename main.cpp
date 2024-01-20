#include <iostream>
#include <vector>
#include <utility>

#include "System.h"
#include "FileProcess.h"

using std::cout;
using std::string;
using std::vector;

namespace color_main {
    const char* RED = "\033[1;91m";
    const char* GREEN = "\033[92m";
    const char* RESET = "\033[0m";  
}

#define clearScreen() cout << "\x1B[2J\x1B[H";
#define Error_Main() cout << color_main::RED << "\t\tERROR: PLease Enter Valid Input!" << color_main::RESET << std::endl;


int main(){
    clearScreen();
    cout << "EEET2482/COSC2082 ASSIGNMENT\n"
        << "'TIME BANK' APPLICATION\n"
        << "Instructor: Mr. Tran Duc Linh\n"
        << "Group: Group 7\n"
        << "S3974892, Ngo Van Tai\n"
        << "S3974876, Mai Dang Khoa\n"
        << "S3926681, Pham Ngoc Huy\n"
        << "S3978477, Nguyen Trong Khoa\n";
        
    //---------------------------------------------START PROGRAM---------------------------------------------------------------------------
    System system;
    FileProcess file_process;
    
    std::vector<Member*> member_list_from_file = file_process.loadData(system.getMemberList());//
    //The function loadData will return a vector of <Member*>. Copy it to the member_list_from_file. After that 
    //We paste the member_list_from_file to the setMemberList, to set the private attribute member_list of the class System
    system.setMemberList(member_list_from_file);

    std::vector<BookingSupporter*> booking_list_from_file = file_process.loadBookingFile(system.getBookingList());
    system.setBookingList(booking_list_from_file);

    bool request = true; // this boolean for the while loop belowcle
    bool request_guest = false;
    bool request_member = false;
    bool request_admin = false;
    bool request_supporter = false;
    bool request_setting_member = false;
    bool request_setting_supporter = false;


    
    while(request){
        string user_choice;
        cout << "\t\t____________________________________\n"
             << "\t\t|        WELCOME TO TIME BANK       |\n"
             << "\t\t|                                   |\n"
             << "\t\t|         Use the app as            |\n"
             << "\t\t|                                   |\n"
             << "\t\t|          1. Guest                 |\n"
             << "\t\t|                                   |\n"
             << "\t\t|          2. Login                 |\n"
             << "\t\t|                                   |\n"
             << "\t\t|          3. Quit                  |\n"
             << "\t\t-------------------------------------\n"
             << ">Your choice: ";
        
        getline(cin >> std::ws, user_choice);
        //Get the input of the user's ipnut
        if(user_choice == "1"){
            request_guest = true;
            while(request_guest){
                cout << "\t\t____________________________________\n"
                     << "\t\t|           WELCOME                 |\n"
                     << "\t\t|                                   |\n"
                     << "\t\t|       YOU ARE USING AS GUEST      |\n"
                     << "\t\t|                                   |\n"
                     << "\t\t|1. View supporters's information   |\n"
                     << "\t\t|                                   |\n"
                     << "\t\t|2. Register                        |\n"
                     << "\t\t|                                   |\n"
                     << "\t\t|3. Return                          |\n"
                     << "\t\t|                                   |\n"
                     << "\t\t-------------------------------------\n"
                     << ">Your choice: ";

                string guest_choice; 
                getline(cin >> std::ws, guest_choice);
                if(guest_choice == "1"){
                    clearScreen();
                    system.displaySupporter();
                } else if(guest_choice == "2"){
                    if(system.registerMember()){
                        request_guest = false;
                        cout << "Go to login page" << endl;
                    }
                } else if(guest_choice == "3"){
                    clearScreen();
                    request_guest = false;
                    cout << "Returning to the home page" << endl;
                } else{
                    clearScreen();
                    Error_Main();
                }
            }
        } else if(user_choice == "2"){
            if(system.loginMember()){
                //LOGIN AS ADMINSTRATOR
                if(system.getIsAdmin() == true){
                    request_admin = true;
                    while(request_admin){
                        cout << "\t\t____________________________________________________________\n";
                        cout << "\t\t|                   ADMIN DASHBOARD                         |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|              1. Display Member List                       |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|              2. Reset Member's Password                   |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|              3. Exit                                      |\n"
                            << "\t\t-------------------------------------------------------------\n";
                        cout << ">Your choice: ";
                        string admin_choice; 
                        getline(cin >> std::ws, admin_choice);

                        if(admin_choice == "1"){
                            clearScreen();
                            system.displayMemberList();
                        } else if(admin_choice == "2"){
                            clearScreen();
                            system.resetMemberPassword();
                        } else if(admin_choice == "3"){
                            request_admin = false;
                            cout << "Exit to main page" << endl;
                        } else{
                            cout << "Please enter the valid choice" << endl;
                        }
                    }
                    system.setIsAdmin(false);
//===========================================================MEMBER MENU HOMEPAGE========================================================
                }else if(system.getLoggedInSupporter() == nullptr){ 
                    request_member = true;
                    while(request_member){
                        cout << "\t\t____________________________________________________________\n"
                            << "\t\t|                   WELCOME BACK  + (NAME)                  |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|1. Buy credit point                                        |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|2. View supporter list                                     |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|3. Book a supporter                                        |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|4. View history booking                                    |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|5. View complted tasks by supporter                        |\n"
                            << "\t\t|> Notice: You have " << system.getNotification() << " new completed task from supporter\n"                                                    
                            << "\t\t|                                                           |\n"
                            << "\t\t|6. View my information                                     |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|7. Setting                                                 |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|8. Sign out                                                |\n"
                            << "\t\t-------------------------------------------------------------\n"
                            << ">Your choice: ";
                        string member_choice;
                        getline(cin >> std::ws, member_choice);
                        if(member_choice == "1"){
                            clearScreen();
                            system.buyCredit();
                        } else if(member_choice == "2"){
                            clearScreen();
                            system.displayAvailableSupporter();
                        } else if(member_choice == "3"){
                            clearScreen();
                            system.createBooking();
                        } else if(member_choice == "4"){
                            clearScreen();
                            system.viewHistory();
                        } else if(member_choice == "5"){
                            clearScreen();
                            system.checkCompleteTask();
                        } else if(member_choice == "6"){
                            clearScreen();
                            system.viewPersonalInformation();
                        } else if(member_choice == "7"){
                            request_setting_member = true;
                            while(request_setting_member){
                                cout << "\t\t____________________________________________________________\n"
                                    << "\t\t|                   WELCOME BACK  + (NAME)                  |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|1. Change password                                         |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|2. Change phone number                                     |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|3. Change address                                          |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|4. Change city                                             |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|5. Block a users                                           |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|6. View block list                                         |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|7. Become supporter                                        |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|8. Add information about yourself                          |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|9. Return                                                  |\n"
                                    << "\t\t-------------------------------------------------------------\n"
                                    << ">Your choice: ";
                                string member_setting_choice; 
                                getline(cin >> std::ws, member_setting_choice);
                                if(member_setting_choice == "1"){
                                    clearScreen();
                                    if(!system.getLoggedInMember()->setPasswordRequest()){
                                        cout << "Invalid Password" << endl;
                                    }
                                }else if(member_setting_choice == "2"){
                                    clearScreen();
                                    system.getLoggedInMember()->setPhoneNumberRequest();
                                }else if(member_setting_choice == "3"){
                                    clearScreen();
                                    system.getLoggedInMember()->setAddressRequest();
                                }else if(member_setting_choice == "4"){
                                    clearScreen();
                                    system.getLoggedInMember()->setCityRequest();
                                }else if(member_setting_choice == "5"){
                                    clearScreen();
                                    system.blockUser();
                                } else if(member_setting_choice == "6"){
                                    clearScreen();
                                    system.getLoggedInMember()->unblockUser();
                                }else if (member_setting_choice == "7"){
                                    clearScreen();
                                    if(system.upgradeToSupporter()){
                                        cout << "Successfully become supporter" << endl;
                                        cout << "Please login again" << endl;
                                        request_member = false;
                                        request_setting_member = false;
                                    }
                                } else if(member_setting_choice == "8"){
                                    clearScreen();
                                    system.getLoggedInMember()->addInformation();
                                } else if(member_setting_choice == "9"){
                                    clearScreen();
                                    cout << "Returning to main dashboard" << endl;
                                    system.clearAvailableSupporterList();
                                    request_setting_member = false;
                                }
                                else{
                                    clearScreen();
                                    Error_Main();
                                }
                            }
                        }else if(member_choice == "8"){
                            request_member = false;
                            system.clearAvailableSupporterList();
                            cout << "Returning to main dashboard" << endl;
                        }else {
                            clearScreen();
                            Error_Main();
                        }
                    }
//===========================================================SUPPORTER MENU HOMEPAGE========================================================
                } else{
                    request_supporter = true;
                    while(request_supporter){
                        cout << "\t\t____________________________________________________________\n"
                            << "\t\t|                   WELCOME BACK  + (NAME)                  |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|1. Buy credit point                                        |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|2. View supporter list                                     |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|3. Book a supporter                                        |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|4. View history booking                                    |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|5. View current job requests                               |\n"
                            << "\t\t|Notice: You have "<< system.getRequestNotification() << " new request\n"                                             
                            << "\t\t|                                                           |\n"
                            << "\t\t|6. Check completed task by supporter                       |\n"
                            << "\t\t|> Notice: You have " << system.getNotification() << " new completed task from supporter\n"   
                            << "\t\t|                                                           |\n"
                            << "\t\t|7. View history job                                        |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|8. View my information                                     |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|9. Change my status                                        |\n"
                            << "\t\t*** Current status: "<<system.getCurrentStatus()<<"***\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|10. Setting                                                |\n"
                            << "\t\t|                                                           |\n"
                            << "\t\t|11. Sign out                                               |\n"
                            << "\t\t-------------------------------------------------------------\n"
                            << ">Your choice: ";
                        string supporter_choice; 
                        getline(cin >> std::ws, supporter_choice);

                        if(supporter_choice == "1"){
                            clearScreen();
                            system.buyCredit();
                        } else if(supporter_choice == "2"){
                            clearScreen();
                            system.displayAvailableSupporter();
                        } else if(supporter_choice == "3"){
                            clearScreen();
                            system.createBooking();
                        } else if(supporter_choice == "4"){
                            clearScreen();
                            system.viewHistory();
                        } else if(supporter_choice == "5"){
                            clearScreen();
                            system.decideJob();
                        } else if(supporter_choice == "6"){
                            clearScreen();
                            system.checkCompleteTask();
                        } else if(supporter_choice == "7"){
                            clearScreen()
                            system.viewHistoryJob();
                        }else if(supporter_choice == "8"){
                            clearScreen();
                            system.viewPersonalInformation();
                        } else if (supporter_choice == "9"){
                            clearScreen();
                            system.statusSetting();
                        } else if(supporter_choice == "10"){
                            clearScreen();
                            request_setting_supporter = true;
                            while(request_setting_supporter){
                                cout << "\t\t____________________________________________________________\n"
                                    << "\t\t|                   WELCOME BACK  + (NAME)                  |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|1. Change password                                         |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|2. Change phone number                                     |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|3. Change address                                          |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|4. Change city                                             |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|5. Block a users                                           |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|6. View block list                                         |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|7. Modify your cost                                        |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|8. Adjust your personal information                        |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|9. Modify skills                                           |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|10. Modify free time period                                 |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|11. Set min host rating                                    |\n"
                                    << "\t\t|                                                           |\n"
                                    << "\t\t|12. Return                                                 |\n"
                                    << "\t\t-------------------------------------------------------------\n"
                                    << ">Your choice: ";
                                string suppoter_setting_choice;
                                getline(cin >> std::ws, suppoter_setting_choice);

                                if(suppoter_setting_choice == "1"){
                                    clearScreen();
                                    if(!system.getLoggedInSupporter()->setPasswordRequest()){
                                        cout << "Invalid Password" << endl;
                                    }
                                }else if(suppoter_setting_choice == "2"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->setPhoneNumberRequest();
                                }else if(suppoter_setting_choice == "3"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->setAddressRequest();
                                }else if(suppoter_setting_choice == "4"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->setCityRequest();
                                }else if(suppoter_setting_choice == "5"){
                                    clearScreen();
                                    system.blockUser();
                                } else if(suppoter_setting_choice == "6"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->unblockUser();
                                } else if(suppoter_setting_choice == "7"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->setCostRequest();
                                } else if(suppoter_setting_choice == "8"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->addInformation();
                                }else if(suppoter_setting_choice == "9"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->modifySkill();
                                } else if(suppoter_setting_choice == "10"){
                                    clearScreen();
                                    // modify time period
                                    system.getLoggedInSupporter()->setWorkSchedule();
                                } else if(suppoter_setting_choice == "11"){
                                    clearScreen();
                                    system.getLoggedInSupporter()->setMinHostRatingRequest();
                                }else if(suppoter_setting_choice == "12"){
                                    clearScreen();
                                    cout << "Returning to main dashboard" << endl;
                                    request_setting_supporter = false;
                                }
                                else{
                                    clearScreen();
                                    Error_Main();
                                }
                            }
                        } else if (supporter_choice == "11"){
                            clearScreen();
                            request_supporter = false;
                            system.clearAvailableSupporterList();
                            cout << "Return to main dashboard" << endl;
                        } else{
                            clearScreen();
                            Error_Main();
                        }
                    } 
                }
            } else{
                cout << "Incorrect username or password" << endl;
            }
        } else if(user_choice == "3"){
            clearScreen();
            cout << color_main::GREEN <<  "Thank you for using our app" << color_main::RESET << endl;
            cout << color_main::GREEN << "Exit successfully!" << color_main::RESET << endl;
            request = false;
        } else{
            clearScreen();
            Error_Main();
        }
    }

    if( !file_process.saveToFile(system.getMemberList()) ){
        // std::cerr << "Can not save to the file!" << endl;
    }

    file_process.saveBookingFile(system.getBookingList());
    
    
    return 0;
}