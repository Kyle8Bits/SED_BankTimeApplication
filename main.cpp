#include <iostream>
#include <vector>
using std::cout;
using std::cin;
using std::string;
using std::vector;

int main(){
    
    bool request = true;

    while(request){

        cout << "EEET2482/COSC2082 ASSIGNMENT\n"
            << "'TIME BANK' APPLICATION\n"
            << "Instructor: Mr. Tran Duc Linh\n"
            << "Group: Group ...\n"
            << "S3974876, Mai Dang Khoa\n"
            << "S3974892, Ngo Van Tai\n"
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
            << "\t\t|          4. Quit                  |\n"
            << "\t\t-------------------------------------\n"
            << ">Your choice: ";

        int user_choice; //Get the input of the user's ipnut
        cin >> user_choice;
        switch(user_choice){
            
            //=================================================================================================================
            //GUEST MENU
            case 1:
            {
                bool request_guest = true;
                while (request_guest){
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

                    int guest_choice;
                    cin >> guest_choice;
                        switch(guest_choice){
                            case 1:
                            //add show info function
                            cout << "(Show info SP)" << std::endl;
                            break;

                            case 2:
                            //add regis function
                            cout <<"(Register here)" << std::endl;
                            break;

                            case 3:
                            request_guest = false;
                            cout << "Returning to the home page" << std::endl;

                            default:
                            std::cerr << "Invalide choose please choose again"<< std::endl;
                        }
                }
            break;
            }
            //=================================================================================================================
            //NOTE: input the sign in function before this menu is displayed
            //MEMBER MENU
            case 2:
            {
                bool request_member = true;
                while (request_member){
                    cout << "\t\t____________________________________________________________\n"
                        << "\t\t|                   WELCOME BACK  + (NAME)                  |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|Your ID is: + (ID)                                         |\n"
                        << "\t\t|Your skill's rating score is: + (skillscore)               |\n"
                        << "\t\t|Your hostpitality's rating score is: + (host_score)        |\n"
                        << "\t\t|Your status is: + (current status)                         |\n"
                        << "\t\t|Your credit point: + (current point)                       |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|1. Buy credit point                                        |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|2. View supporter list                                     |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|3. View history booking                                    |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|4. Manage account                                          |\n"
                        << "\t\t|                                                           |\n"
                        << "\t\t|5. Sign out                                                |\n"
                        << "\t\t--------------------------------------------------------------\n"
                        << ">Your choice: ";

                    int member_choice;
                    cin >> member_choice;
                    switch (member_choice){
                        case 1:
                        //add buy credit function
                            cout << "(Buy credit point here)" << std::endl;
                            break;

                        case 2:
                        //add support function + booking in the function
                            cout << "(Show support list here)" << std::endl;
                            break;

                        case 3:
                        //add show history booking function here
                            cout << "(History booking here)"<< std::endl;
                            break;
                        case 4: 
                        //add manage account fucntion here
                            cout <<"(manage account here)"<< std::endl;
                            break;
                        case 5:
                            request_member = false;
                            cout << "Returning to member dashboard" << std::endl;
                            break;
                        
                        default:
                            std::cerr << "Invalide choose please choose again"<< std::endl;

                    }
                }
            break;
            }

            case 3:
            {
                bool request_admin = true;
                while (request_admin){
                    cout<< "\t\t____________________________________\n"
                        << "\t\t|           ADMIN DASHBOARD         |\n"
                        << "\t\t|                                   |\n"
                        << "\t\t|1. Manage account list             |\n"
                        << "\t\t|                                   |\n"
                        << "\t\t|2. View member list                |\n"
                        << "\t\t|                                   |\n"
                        << "\t\t|3. View profit                     |\n"
                        << "\t\t|                                   |\n"
                        << "\t\t|4. Sign out                        |\n"
                        << "\t\t-------------------------------------\n"
                        << ">Your choice: ";
                        int admin_choice;
                        cin >> admin_choice;
                    switch (admin_choice){
                    case 1:
                        //add manage account function from admin here
                        cout <<"(Manage accout from admin)"<< std::endl;
                        break;

                    case 2:
                        //add view member list here
                        cout << "(Display member list)"<< std::endl;
                        break;

                    case 3:
                        //add show profit function here
                        cout << "(Show profit here)"<< std::endl;
                        break;

                    case 4:
                        cout << "Returning to home page" << std::endl;
                        request_admin = false;
                    default:
                        std::cerr << "Invalide choose please choose again"<< std::endl;
                        cout << "Invalid choose. "<< std::endl;
                        break;
                    }    
                }
                break;
            }
            case 4:
            request = false;
            break;

            default:
            std::cerr << "Invalide choose please choose again"<< std::endl;
        }


        cout <<"Have a nice day!!!";
    }
    return 0;
}
