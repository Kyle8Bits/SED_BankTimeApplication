#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;

class Category {
private:
    string category_name;
    std::vector<string> skill_list;
public:
    Category(string category_name = "", std::vector<string> skill_list = {})
             : category_name(category_name), skill_list(skill_list) {}
    
    string getCategoryName(){return category_name;}
    
    void setCategoryName(string& name){this->category_name = name;}
    
    bool addSkill(const string& skill){
        for(int i = 0; i < skill_list.size(); ++i){
            if(skill_list[i] == skill){//check for duplication
                cout << "This skill is already existed!" << endl;
                return false;
            }
        }

        skill_list.push_back(skill);
        return true;
    }

    void removeSkill(const string& skill){
        for(int i = 0; i < skill_list.size(); ++i){
            if(skill_list[i] == skill){//Find the skill
                skill_list.erase(skill_list.begin() + i);
                cout << "Delete successfully!" << endl;
            }
        }
    }
    
};