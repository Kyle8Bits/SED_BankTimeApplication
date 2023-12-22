#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <vector>
using namespace std;
class Category {
private:
    std::string category_name;
    std::vector<std::string> skill_list;

public:
    Category(string category_name, vector<string> skill_list);

    string getCategoryName() const;
    void setCategoryName(const string& name);

    bool addSkill(const string& skill);
    void removeSkill(const string& skill);
};

#endif
