#include <iostream>
#include <vector>

#include "System.cpp"
#include "FileProcess.cpp"

using std::cout;
using std::string;
using std::vector;

#define clearScreen() cout << "\x1B[2J\x1B[H";


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

    std::vector<BookingSupporter*> booking_list_from_file = file_process.loadBookingFile(system.getBookingList());
    system.setBookingList(booking_list_from_file);

    bool request = true; // this boolean for the while loop below
    bool request_guest = true;
    bool request_member = false;
    bool request_admin = false;
    bool request_supporter = false;

    
    while(request){
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

        char user_choice = ' ';  
        cin >> user_choice;
        //Get the input of the user's ipnut
            switch(user_choice){
            case '1'://==================GUEST MENU=================
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

                    char guest_choice; cin >> guest_choice;
                    switch(guest_choice){
                        case '1':
                            system.displaySupporter();
                            break;
                        case '2':
                            system.registerMember();
                            request_guest = false;
                            cout << "Go to login page" << endl;
                            break;
                        case '3':
                            request_guest = false;
                            cout << "Returning to the home page" << endl;
                            clearScreen();
                            break;
                        default:
                            cout << "Invalid input, please choose again!" << endl;
                            clearScreen();
                    }
                }
                break;
            case '2':
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
                            char admin_choice = ' '; cin >> admin_choice;
                            switch(admin_choice){
                                case '1':
                                    clearScreen();
                                    system.displayMemberList();
                                    break;
                                case '2':
                                    clearScreen();
                                    system.resetMemberPassword();
                                    break;
                                case '3':
                                    request_admin = false;
                                    cout << "Exit to main page" << endl;
                                    break;
                                default:
                                    cout << "Please enter the valid choice" << endl;
                                    break;
                            }  
                        }
                        system.setIsAdmin(false);
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
                                << "\t\t|5. Become supporter                                        |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|6. Manage account                                          |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|7. View my information                                     |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|8. Sign out                                                |\n"
                                << "\t\t-------------------------------------------------------------\n"
                                << ">Your choice: ";
                            char member_choice; cin >> member_choice;
                            switch (member_choice){
                                case '1':
                                    clearScreen();
                                    system.buyCredit();
                                    break;
                                case '2':
                                    //VIEW SUPPORTER LIST
                                    clearScreen();
                                    system.displayAvailableSupporter();
                                    break;
                                case '3':
                                    //Book a supporter
                                    clearScreen();
                                    system.createBooking();
                                    break;
                                case '4':
                                    clearScreen();
                                    system.viewHistory();
                                    break;
                                case '5':
                                    clearScreen();
                                    system.upgradeToSupporter();
                                    break;
                                case '6':
                                    clearScreen();
                                    //SHOW BASIC INFORMATION
                                    break;
                                case '7':
                                    clearScreen();
                                    system.viewPersonalInformationMember();
                                    break;
                                case '8':
                                    request_member = false;
                                    cout << "Returning to main dashboard" << endl;
                                default:
                                    break;
                            }
                        }
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
                                << "\t\t|                                                           |\n"
                                << "\t\t|6. Manage account                                          |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|7. View my information                                     |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|8. Sign out                                                |\n"
                                << "\t\t-------------------------------------------------------------\n"
                                << ">Your choice: ";
                                char supporter_choice; cin >> supporter_choice;

                                switch(supporter_choice){
                                    case '1':
                                        clearScreen();
                                        system.buyCredit();
                                        break;
                                    case '2':
                                        clearScreen();
                                        system.displayAvailableSupporter();
                                        break;
                                    case '3':
                                        clearScreen();
                                        system.createBooking();
                                        break;
                                    case '4':
                                        clearScreen();
                                        system.viewHistory();
                                        break;
                                    case '5':
                                        clearScreen();
                                        system.decideJob();
                                        break;
                                    case '6':
                                        break;
                                    default:
                                        request_supporter = false;
                                        cout << "Return to main dashboard" << endl;
                                        break;
                                }
                        } 
                    }
                } 
                else{
                    cout << "Incorrect username or password" << endl;
                }
                break;
            case '3':
                cout << "Thank you for using our app" << endl;
                cout << "Exit successfully!" << endl;
                request = false;
                clearScreen();
                break;
            default:
                clearScreen();
                cout << "****Please enter the valid input****" << endl;
                break;
            }
    }

    if( !file_process.saveToFile(system.getMemberList()) ){
        cout << "Can not save to the file!" << endl;
    }

    file_process.saveBookingFile(system.getBookingList());
    // if( !file_process.saveBookingFile(system.getBookingList()) ){
    //     cout << "Can not save booking list " << endl;
    // }
    
    return 0;
}


