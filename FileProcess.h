#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <utility>

#include "Supporter.h"
#include "Member.h"
#include "Time.h"
#include "BookingSupporter.h"

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::stoi;
using std::getline;

#define loop(n) for(int i = 0; i < n; ++i)
#define MEMBERFILE "SourceFile/members.dat"
#define SKILLFILE "SourceFile/skills.dat"
#define BOOKINGFILE "SourceFile/booking.dat"
#define TIMEFILE "SourceFile/timepair.dat"
#define BLOCKFILE "SourceFile/blocklist.dat"

class FileProcess{//THis class is use for loading the file and save to the file
public:
    bool saveToFile(std::vector<Member*> member_list);

    Status statusEnum(string status);

    std::vector<Member*> loadData(std::vector<Member*>& member_list);

    std::vector<string> readSkillSupporter(string id_skill);

    std::vector<string> readBlockList(string id);

    std::vector<std::pair<std::string, std::vector<std::pair<Time, Time>>>> readWorkDay(const std::string& id_time);

    bool saveBookingFile(std::vector<BookingSupporter*>& booking_list);

    std::vector<BookingSupporter*> loadBookingFile(std::vector<BookingSupporter*>& booking_list);
}; 

#endif