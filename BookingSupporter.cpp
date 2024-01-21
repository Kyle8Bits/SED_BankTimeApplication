#include "BookingSupporter.h"

const char* bk_colors::YELLOW = "\033[1;93m";
const char* bk_colors::WHITE_BOLD = "\033[1;97m";
const char* bk_colors::RESET = "\033[0m";

int BookingSupporter::number_of_booking = 0;

//CONSTRUCTOR
BookingSupporter::BookingSupporter(string host_id, string support_id, string status, string booking_id, string progress, Time start_time, Time end_time,
            int host_rating, int skill_rating_score, int supporter_rating_score, string host_comment, string supporter_comment, double total_cost, int day, int month, int year) 
            : booking_id(booking_id),host_id(host_id), support_id(support_id), status(status), progress(progress), start_time(start_time), end_time(end_time)
            , host_rating(host_rating), skill_rating_score(skill_rating_score), supporter_rating_score(supporter_rating_score), host_comment(host_comment), 
            supporter_comment(supporter_comment), total_cost(total_cost), day(day), month(month), year(year){
    
    number_of_booking++;//Increse the booking number by 1
    if(booking_id == "BK"){//If the booking id is BK (Default value), we auto generate the id with the number of the booking
    this->booking_id = booking_id + std::to_string(number_of_booking);//AUTO GENERATE THE ID FOR BOOKING
}
}

bool BookingSupporter::isInBlockList(std::vector<string> block_list, string block_id){
    loop(block_list.size()){
        if(block_list[i] == block_id){
            return true;
        }
    }
    return false;
}

bool BookingSupporter::isInTheCity(Member* booker, string id_supporter_selected, std::vector<Supporter*>& availableSupporter){
    bool check = false;

    for (int i = 0; i < availableSupporter.size(); i++){
        if(id_supporter_selected == availableSupporter[i]->member_id){
            if (availableSupporter[i]->getCity() == booker->getCity()){
                check = true;
            }
        }
    }
    
    return check;
}

void BookingSupporter::displayComment(Supporter* selected_supporter, std::vector<BookingSupporter*> booking_list, std::vector<Member*> member_list){
    int count = 0;
    std::vector<std::pair<string, string>> comment;
    cout << "Nearest comment: " << endl;
    for (int i = booking_list.size() -1 ; i >= 0; i--){
            if(booking_list[i]->getSupportId() == selected_supporter->getMemberId() && booking_list[i]->getProgress() == "COMPLETED" && booking_list[i]->getSupporterComment() != "x" && booking_list[i]->getSupporterComment() != " " && count < 4){
                comment.push_back(std::make_pair(booking_list[i]->getHostId(),booking_list[i]->getSupporterComment()));
                count++;
            }
    }
    
    if(!comment.empty()){
        for (int x = 0; x < member_list.size(); x++){
            for (int a = 0; a < comment.size(); a++){
                if(member_list[x]->getMemberId() == comment[a].first){
                    cout << "From: " << member_list[x]->getFullName();
                    cout << " - \"" << comment[a].second << "\"" << endl;
                }
            }
        }
    }
    else{
        cout << "This supporter have not have a comment" << endl;
    }
}

void BookingSupporter::displayAvailableSupporter(std::vector<Member*> member_list, Member* logged_in_member, Supporter* logged_in_supporter, std::vector<Supporter*>& availableSupporter, std::vector<BookingSupporter*> booking_list) {
    bool isSupporter = (logged_in_member == nullptr);
    if (isSupporter) {
        logged_in_member = logged_in_supporter;
    }
    cout << std::setw(191) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET <<std::endl;
    cout << bk_colors::YELLOW << std::left << std::setw(13) << "| Member id |" << std::setw(25) << " Fullname               |" << std::setw(15) << " City         |"
            << std::setw(16) << " Cost Per Hour |" << std::setw(40) << " Introduction                          |"  << std::setw(40) << " Skill                                 |"
            << std::setw(15) << " Skill Rating |" << std::setw(9) << " Rating |"  << std::setw(18) << " Min Host Rating |"<<endl;

    cout << std::setw(191) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET <<std::endl;

    for (size_t i = 0; i < member_list.size(); ++i) {
        if (Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])) {
            if (supporter->getMemberId() != logged_in_member->getMemberId() && supporter->getStatus() == Status::ONLINE) {
                if (!isInBlockList(logged_in_member->block_list, supporter->getMemberId()) && !isInBlockList(supporter->block_list, logged_in_member->getMemberId())) {
                    //if the the supporter appears in the block list of the member, we will not display the supporter and vice versa
                    cout <<bk_colors::WHITE_BOLD<<"| "<< std::setw(10) << supporter->getMemberId() <<"| "<<std::setw(23) << supporter->getFullName()
                            <<"| " << std::setw(13) << supporter->getCity() <<"| "<< std::setw(14) << supporter->getCost() 
                            <<"| " << std::setw(38) << supporter->getAboutMe() << "| " <<std::setw(38) << supporter->displaySkillList() 
                            <<"| " <<std::setw(13) << supporter->getSkillRatingScore() << "| " <<std::setw(7) << supporter->getSupportRatingScore() 
                            <<"| " <<std::setw(15) << supporter->getMinHostRating() <<" |"<<bk_colors::RESET<<endl;
                    cout << bk_colors::YELLOW << std::setw(191) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET << std::endl;
                    supporter->displayWorkSchedule();

                    cout << bk_colors::YELLOW << std::setw(191) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET << endl;
                    displayComment(supporter, booking_list, member_list);
                    cout << bk_colors::YELLOW << std::setw(191) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET << endl;

                    availableSupporter.push_back(supporter);
                }
            }
        }
    }

    if (isSupporter) {
        logged_in_member = nullptr;
    }
}

void BookingSupporter::displayAvailableSupporterForGuest(std::vector<Member*> member_list, Member* logged_in_member, Supporter* logged_in_supporter, std::vector<Supporter*>& availableSupporter, std::vector<BookingSupporter*> booking_list) {
    cout << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET <<std::endl;
    cout << bk_colors::YELLOW << std::left << std::setw(13) << "| Member id |" << std::setw(25) << " Fullname               |" << std::setw(15) << " City         |"
            << std::setw(16) << " Cost Per Hour |" << std::setw(40) << " Introduction                          |"  << std::setw(40) << " Skill                                 |" <<endl;

    cout << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET <<std::endl;

    for (size_t i = 0; i < member_list.size(); ++i) {
        if (Supporter* supporter = dynamic_cast<Supporter*>(member_list[i])) {
            cout <<bk_colors::WHITE_BOLD<<"| "<< std::setw(10) << supporter->getMemberId() <<"| "<<std::setw(23) << supporter->getFullName()
                    <<"| " << std::setw(13) << supporter->getCity() <<"| "<< std::setw(14) << supporter->getCost() 
                    <<"| " << std::setw(38) << supporter->getAboutMe() << "| " <<std::setw(38) << supporter->displaySkillList() 
                    <<"| " <<std::setw(13) <<bk_colors::RESET<<endl;
            cout << bk_colors::YELLOW << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET << std::endl;
            supporter->displayWorkSchedule();

            cout << bk_colors::YELLOW << std::setw(149) << std::setfill('-') << "" << std::setfill(' ') << bk_colors::RESET << endl;
        }
    }
}

    // Setter Functions
void BookingSupporter::setBookingId (std::string new_booking_id){
    booking_id = new_booking_id;
}

void BookingSupporter::setHostId(std::string new_host_id) {
    host_id = new_host_id;
}

void BookingSupporter::setSupportId(std::string new_support_id) {
    support_id = new_support_id;
}

void BookingSupporter::setStatus(std::string new_status) {
    status = new_status;
}

void BookingSupporter::BookingSupporter::setProgress(string progress){
    this->progress = progress;
}

void BookingSupporter::setStartTime(Time time){
    this->start_time = time;
}

void BookingSupporter::setEndTime(Time time){
    this->end_time = time;
}

// Getter Functions
string BookingSupporter::getBookingId(){ 
    return booking_id;
}

string BookingSupporter::getHostId(){
    return host_id;
}

std::string BookingSupporter::getSupportId(){
    return support_id;
}

std::string BookingSupporter::getStatus(){
    return this->status;
}

string BookingSupporter::getProgress(){return this->progress;}

string BookingSupporter::getTimeToFile(){
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << start_time.getHourToString() << "-"
        << std::setw(2) << std::setfill('0') << start_time.getMinuteToString() << "-"
        << std::setw(2) << std::setfill('0') << end_time.getHourToString() << "-"
        << std::setw(2) << std::setfill('0') << end_time.getMinuteToString() << std::setfill(' ');
        return ss.str();
}

string BookingSupporter::getStartTimeToString(){
    return start_time.getTimeColon();
}

string BookingSupporter::getEndTimeToString(){
    return end_time.getTimeColon();
}

Time BookingSupporter::getStartTime(){
    return this->start_time;
}

Time BookingSupporter::getEndTime(){
    return this->end_time;
}

string BookingSupporter::getTime(){
    return start_time.getTime() + " To " + end_time.getTime();
}

void BookingSupporter::setHostRating(int host_rating){
    this->host_rating = host_rating;
}

int BookingSupporter::getHostRating(){
    return host_rating;
}

void BookingSupporter::setHostComment(string comment){
    this->host_comment = comment;
}

string BookingSupporter::getHostComment(){
    return host_comment;
}

int BookingSupporter::getSkillRatingScore(){
    return skill_rating_score;
}

void BookingSupporter::setSkillRatingScore(int score) {
    skill_rating_score = score;
}

int BookingSupporter::getSupporterRatingScore(){
    return supporter_rating_score;
}

void BookingSupporter::setSupporterRatingScore(int score){
    supporter_rating_score = score;
}

string BookingSupporter::getSupporterComment(){
    return supporter_comment;
}

void BookingSupporter::setSupporterComment(string comment) {
    supporter_comment = comment;
}

double BookingSupporter::getTotalCost(){
    return this->total_cost;
}

void BookingSupporter::setTotalCost(double total_cost){
    this->total_cost = total_cost;
}

string BookingSupporter::toString(){
    return this->booking_id + "-" + this->host_id + "-" + this->support_id + "-" + this->status + "-" + this->progress + "-" + this->getTimeToFile() + "-" + to_string(this->host_rating) + "-" + to_string(this->skill_rating_score) + "-" + to_string(this->supporter_rating_score) + "-" + this->host_comment + "-" + this->supporter_comment + "-" + to_string(this->total_cost) + "-" + to_string(this->day) + "-" + to_string(this->month) + "-" + to_string(this->year);
}

void BookingSupporter::setDate(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

string BookingSupporter::getDate(){
    return std::to_string(this->day) + "/" + std::to_string(this->month) + "/" +  std::to_string(this->year);
}
