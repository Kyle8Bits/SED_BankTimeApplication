#ifndef FILE_PROCESS_H
#define FILE_PROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Member.h"
#include "Supporter.h" 
#include "Time.h" 

class FileProcess {
public:
    bool saveToFile(std::vector<Member*>& member_list);
    std::vector<Member*> loadData(std::vector<Member*>& member_list);

private:
    std::vector<std::string> readSkillSupporter(std::string id_skill);
};

#endif 
