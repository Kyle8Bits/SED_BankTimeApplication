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
                                << "\t\t|6. Become supporter                                        |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|7. Manage account                                          |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|8. View my information                                     |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|9. Block a user                                            |\n"
                                << "\t\t|                                                           |\n"
                                << "\t\t|10. Sign out                                               |\n"
                                << "\t\t-------------------------------------------------------------\n"
                                << ">Your choice: ";
                            string member_choice; cin >> member_choice;
                            if(member_choice == "1"){