#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Member.cpp"
#include "BookingSupporter.cpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;

#define loop(n) for(int i = 0; i < n; ++i)
#define MEMBERFILE "members.dat"
#define BOOKINGFILE "booking.dat"


class System{
private:
    std::vector<Member*> member_list;
    std::vector<BookingSupporter*> booking_list;
    Member* loged_in_member;

public:
    Member* getLoggedInMember() const {
    return loged_in_member;
    }

    //CONSTRUCTOR
    System(std::vector<Member*> member_list = {}) : member_list(member_list){}

    //The function below to get the position of the member in the list via the username
    int getPositionOfMemberByUsername(string user_name_account){
        loop(this->member_list.size()){//Go to each member to find the user_name 
            if(member_list[i]->getUsername() == user_name_account){
                return i;//If we can find it, return the position of it
            }
        }
        return -1;
    }

    bool checkEmtpy(const string& str){
        if(str.empty()){
            cout << "Please enter non-empty value!" << endl;
            return false;
        }

        return true;
    }

    bool registerMember(){
        string user_name_input; 
        string pass_word_input; //these 2 attributes to take the value from input
        cout << "****Your registration adds great value to our community. Thank you!****" << endl;
        cout << "Please enter username & password: " << endl;
        cout << ">Username: " ;
        getline(cin >> std::ws, user_name_input); //std::ws to ignore the reduntant space

        if(!checkEmtpy(user_name_input)){//Call the check empty function
            return false;
        }
        //Check the username is existed or not?
        int position = getPositionOfMemberByUsername(user_name_input); //call the function getPosition... to find the position of the usrname
        //if the function return -1 --> that user name is not existed. By constrast, position>0 --> that username is existed

        if(position >= 0){
            cout << "This username is taken. Can you please use the another name?" << endl;
            return false;
        } 
        
        //ask for password
        cout << "Password: ";
        getline(cin >> std::ws, pass_word_input);

        if(!checkEmtpy(pass_word_input)){//Call the check empty function
            return false;
        }

        string full_name_input, phone_number_input, address_input, city_input;//declare 3 variables to get basic information of users
        cout << "****Please enter few basic information to complete the registration****" << endl;
        cout << ">Your full name: ";
        getline(cin >> std::ws, full_name_input);

        do{//Do until users type valid phone number 
            cout << "Your phone number: ";
            std::getline(cin >> std::ws, phone_number_input);
        }while(!isValidPhone(phone_number_input));
        
        cout << "Your address: ";
        getline(cin >> std::ws, address_input);

        int user_choice = 0;
        cout <<"****Our application only exists at Ho Chi Minh and Hanoi****" << endl;
        cout << "1. Hanoi" << endl
             << "2. Ho Chi Minh" << endl
             << ">Your choice: ";
        cin >> user_choice;
        switch(user_choice){
            case 1://Hanoi
                city_input = "Hanoi";
                break;
            case 2://Ho Chi MInh
                city_input = "Ho Chi Minh";
                break;
            default: //invlaid input
                cout << "Please enter valid input!" << endl;
                return false;
                break;
        }

        cout << "Succesfully collecting your info" << std::endl;
        //Create a member and push it in the lsit
        Member* new_member = new Member(user_name_input, pass_word_input);
        //SET SOME BASIC INFORMATION
        new_member->setFullName(full_name_input);
        new_member->setPhoneNumber(phone_number_input);
        new_member->setAddress(address_input);
        new_member->setCity(city_input);

        //push it in the list
        member_list.push_back( new_member );
        //SUCCESSFUL REGISTER
        cout << "Register member succesffully!" << endl;
        
        return true;
    }

    bool loginMember(){
        string user_name_input;
        string pass_word_input;//these 2 variables to store the input of the users

        cout << "****Login form****" << endl;
        cout << ">Username: ";
        getline(cin >> std::ws, user_name_input);
        cout << ">Password: ";
        getline(cin >> std::ws, pass_word_input);

        loop(member_list.size()){
            if(member_list[i]->getUsername() == user_name_input && member_list[i]->getPassword() == pass_word_input){
                cout << "Login SUCCESSFULLY!" << endl;
                loged_in_member = member_list[i];
                return true;
            }
        }
        cout << "Your username or password is incorrect!" << endl;
        return false;
    }

    bool saveToFile(){
        std::fstream my_file;
        my_file.open(MEMBERFILE, std::ios::out);//use trunc to remove all the old content
        if (!my_file.is_open()) {
            cout << "Can not open the member file" << endl;
            return false;
        }

        loop(member_list.size()){
            if(i == member_list.size() - 1){//If go to the last element
                my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" <<member_list[i]->getAddress() << "-" << member_list[i]->getCity();//save to file without endl
            }else{
                my_file << member_list[i]->getUsername() << "-" << member_list[i]->getPassword() << "-" << member_list[i]->getMemberId() << "-" << member_list[i]->getFullName() << "-" << member_list[i]->getPhoneNumber() << "-" << member_list[i]->getAddress() << "-" << member_list[i]->getCity() << endl;
            }
        }

        my_file.close();
        cout << "SAVE MEMBER SUCCESS" << endl;
        return true;
    }

    //This boolean to read all data 
    bool readDataFromFileCheck(std::fstream& my_file, string& username, string& password, string& id, string& full_name, string& phone_number, string& address, string& city){
        //Read data from file
        if(! (getline(my_file, username, '-') &&  getline(my_file, password, '-') && getline(my_file, id, '-') && 
              getline(my_file, full_name, '-') && getline(my_file, phone_number, '-') && getline(my_file, address, '-') && getline(my_file, city, '-'))){
            //IF faile to read data from file
            return false;
        }

        return true;
    }

    bool loadData(){
        std::fstream my_file;
        my_file.open(MEMBERFILE, std::ios::in);

        if (!my_file.is_open()) {
            cout << "Can not open the file" << endl;
            return false;
        }
        
        member_list.clear(); //clear the member list before load the data
        
        string username_from_file, password_from_file, id_from_file, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file; // varibles to store data from file and push into the list
        
        while(getline(my_file, username_from_file, '-') &&  getline(my_file, password_from_file, '-') && getline(my_file, id_from_file, '-') && 
              getline(my_file, full_name_from_file, '-') && getline(my_file, phonenumber_from_file, '-') && getline(my_file, address_from_file, '-') && getline(my_file, city_from_file)){

            //add it into the list
            Member* new_member = new Member(username_from_file, password_from_file, id_from_file, 20, full_name_from_file, phonenumber_from_file, address_from_file, city_from_file);
            member_list.push_back(new_member);
        }
        my_file.close();

        if(!member_list.empty()){//if the list is not empty, run teh code below
            string max_id = member_list[0]->getMemberId();
            string number_part = max_id.substr(1);// take the string from the second position to end (it will skill character "M")
            int max_id_numeric = std::stoi(number_part);//Assume that the first member is the member which has the maximum id
            
            for(int i = 1; i < member_list.size(); i++){
                string id_string = member_list[i]->getMemberId();
                string number_part_id = id_string.substr(1);//take the string from the second position to end (it will skill character "M")
                int id_numeric = std::stoi(number_part_id);

                if(max_id_numeric < id_numeric){// Assign the value of id_numeric to the max_id_numeric if id_numeric is larger than max_id_numeric
                    max_id_numeric = id_numeric;
                }
            }

            //Assign teh max value to the number_of_student in Member file
            Member::number_of_member = max_id_numeric;   
        }
        
        return true;
    }

    //method to check phone number
    bool isValidPhone(const string& str) {
        
        // check if all characters in the string are digits
        for (char ch : str) {
            if (!std::isdigit(ch)) {
                cout << "You can not type character!" << endl;
                return false;
            }
        }
        // check if the string length is exactly 10
        if (str.length() != 10) {
            cout << "Your phone number must have 10 numbers" << endl;
            return false;
        }
        
        
        // if both conditions are satisfied, return true
        return true;
    }

    void displayMemberList(){
        cout << "****Member list****" << endl;
        loop(this->member_list.size()){
            //Go to each member to print the information
            cout << "Member " << i + 1 << ": " << endl;
            cout << "username: " << member_list[i]->getUsername() 
                 << ", password: "<< member_list[i]->getPassword()
                 << ", member id: " << member_list[i]->getMemberId()
                 << ", credit point: " << member_list[i]->getCreditPoint()
                 << ", fullname: " << member_list[i]->getFullName()
                 << ", address: " << member_list[i]->getAddress()
                 << ", city: " << member_list[i]->getCity() << endl;
            
        }
    }

    void displayAvailableList(){
        cout << "****Available list****" << endl;
        cout << "================================================================\n";
        loop(this->member_list.size()){
            //Go to each member to print the information
            cout << "Member " << i + 1 << ": " << endl;
            cout << "Member id: " << member_list[i]->getMemberId() <<endl;
            cout << "Fullname: " << member_list[i]->getFullName() << endl;
            cout << "City: " << member_list[i]->getCity() << endl;
            cout << "================================================================\n";
        }
    }

    bool saveBookingFile(){
        std::fstream my_file;
        my_file.open(BOOKINGFILE, std::ios::out);
        if(!my_file.is_open()){
            cout << "Can not open the booking file"<< endl;
            return false;
        }

        loop(booking_list.size()){
            if(i == booking_list.size() - 1){//If go to the last element
                my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus();//save to file without endl
            }else{
                my_file << booking_list[i]->getBookingId() << "-" << booking_list[i]->getHostId() << "-" << booking_list[i]->getSupportId() << "-" <<  booking_list[i]->getStatus() << endl;
            }
        }
        my_file.close();
        cout << "SAVE BOOKING SUCCESS" << endl;
        return true;
    }

    bool loadBookingFile(){
        std::fstream my_file;
        my_file.open(BOOKINGFILE, std::ios::in);

        if (!my_file.is_open()){
            std::cerr << "Cannot read the booking file" << endl;
            return false;
        }

        booking_list.clear(); //clear the list before reload data

        string bookingid_from_file, hostid_from_file, supportid_from_file, status_from_file;

        while (getline(my_file, bookingid_from_file, '-') && getline(my_file, hostid_from_file, '-') && getline(my_file, supportid_from_file, '-') && getline(my_file,status_from_file)){
            BookingSupporter *booking  = new BookingSupporter(hostid_from_file, supportid_from_file, status_from_file, bookingid_from_file);
            booking_list.push_back(booking);
        }
        my_file.close();

        if (!booking_list.empty()) {
            string max_id = booking_list[0]->getBookingId();
            string number_part = max_id.substr(2);  // Skip the first two characters (prefix "BK")
            int max_id_numeric;
            max_id_numeric = std::stoi(number_part);
           

        for (int i = 1; i < booking_list.size(); i++) {
            string id_string = booking_list[i]->getBookingId();
            string part_id = id_string.substr(2);  // Skip the first two characters (prefix "BK")
            int id_numeric;
            id_numeric =  std::stoi(part_id);

            if (max_id_numeric < id_numeric) {
                max_id_numeric = id_numeric;
            }
        }
        
            //Assign new start value for booking in BookingSupporter class
            BookingSupporter::number_of_booking = max_id_numeric;
        }
        return true;
    }

    bool isAvailable(string id, string input){
        for (int i = 0; i < input.size(); i++) {
            if (std::tolower(id[i]) != std::tolower(input[i])) {
                cout << "Cannot file the support" << endl;
                return false;
                break;
            }       
        }
        return true;
    }

   void createBooking(){
        cout << "****WELCOME TO BOOKING DASHBOARD****"<<endl;
        displayAvailableList();
        cout << "Please input the id of the supporter you want to book: ";
        string choose;
        cin >> choose;

        loop(member_list.size()){
            if (isAvailable(member_list[i]->getMemberId(),choose)){
                BookingSupporter* booking = new BookingSupporter(loged_in_member->getMemberId(), member_list[i]->getMemberId());
                booking_list.push_back(booking);
                cout << "Your booking has been created!" << endl;
                break;
            }

        }
   }

    void displayBookingList(Member* member){//For supporter to view the request booking from host
        string spID = member->getMemberId();
        int count = 1;
        cout << spID << "\n\n";

        cout <<"****THE AVAILABLE SUPPORTER LIST****\n";
        for(int i = 0; i < booking_list.size(); i++){
            if ( spID == booking_list[i]->getSupportId()){
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getHostId() == member_list[a]->getMemberId()){
                        cout <<"Booking " + std::to_string(count) <<
                            "\nBooking ID: " + booking_list[i]->getBookingId() <<
                            "\nHost name: " + member_list[a]->getFullName() <<
                            "\nRating score: Will update" <<
                            "\nCity: " + member_list[a]->getCity() <<
                            "\nStatus: " + booking_list[i]->getStatus() << endl;

                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }
    }

    void decideBooking(){ //For supporter to answer the request booking from host. Either accept or reject or remain pending
        string choice;
        int decide;
        bool check = true;
       
        cout <<"Type 'Quit' to exit\n" <<
            "Enter booking invitation code: " ;
        std::getline(cin >> std::ws, choice);

        if(choice == "Quit"){
           cout << "Returning to homepage\n" << endl;
        }
        else {
        loop(booking_list.size()){
            if(choice == booking_list[i]->getBookingId()){
                cout <<"1. ACCEPTED\n"<<
                        "2. REJECTED\n" <<
                        "3. RETURN\n"<< endl;
                cout <<"Enter your choice: ";
                cin >> decide;
                        switch (decide){
                        case 1:
                        booking_list[i]->setStatus("ACCEPTED");
                        saveBookingFile();
                            break;
                        case 2:
                        booking_list[i]->setStatus("REJECTED");
                        saveBookingFile();
                            break;
                        case 3:
                        displayBookingList(loged_in_member);
                        decideBooking();
                        }
            }
                else{
                    cout << "Invalid Booking Code.\nPlease try again." << endl;
                    decideBooking();
                }
            }
        }
    }

    void displayInviteList(Member* member){//For host to view which supporter they have booked 
        string hostID = member->getMemberId();
        int count = 1;
        cout << hostID << "\n\n";
        cout << "****THE LIST OF SUPPOTER YOU HAVE BOOKED****\n";
        for(int i = 0; i < booking_list.size(); i++){
            if ( hostID == booking_list[i]->getHostId()){
                for (int a = 0; a < member_list.size(); a++){
                    if (booking_list[i]->getSupportId() == member_list[a]->getMemberId()){
                        cout <<"Booking " + std::to_string(count) <<
                            "\nBooking ID: " + booking_list[i]->getBookingId() <<
                            "\nSupporter name: " + member_list[a]->getFullName() <<
                            "\nRating score: Will update" <<
                            "\nCity: " + member_list[a]->getCity() <<
                            "\nStatus: " + booking_list[i]->getStatus() << endl;

                        cout << "==============================================\n" << endl;
                    }
                }
                count++;
            }
        }
    }

    ~System() {//Clear the member to advoid memory leak
        for (Member* member : member_list) {
            delete member;
        }
        for (BookingSupporter* booking : booking_list){
            delete booking;
        }
    }
};

int main(){
    System system;
    if(!system.loadData() || !system.loadBookingFile()){//If the loadData() function return false
        cout << "Fail to load data" << endl;
    }

    int user_choice = 0;
    bool check = true;
    while (check){
        cout << "1. register\n" 
             << "2. Login\n"
             << "3. show member\n"
             << "4. book a supporter\n"
             << "5. View booking\n"
             << "6. View who your are booking\n"
             << "7. EXIT! \n";
        cin >> user_choice;
        switch (user_choice){
        case 1:
            system.registerMember();
            break;
        case 2:
            system.loginMember();
            break;
        case 3:
            system.displayMemberList();
            break;
        case 4:
            system.createBooking();
            break;
        case 5:
            system.displayBookingList(system.getLoggedInMember());
            system.decideBooking();
            break;
        case 6:
            system.displayInviteList(system.getLoggedInMember());
            break;
        case 7:
            check = false;
            break;  
        default:
            check = false;
            break;
        }
    }

    if(system.saveToFile() && system.saveBookingFile()) {
        cout << "Have a nice day bro" << endl;
    }
    else{
        cout << "Can not save to file" << endl;
    }
}