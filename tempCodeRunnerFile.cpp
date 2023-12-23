

class Member {
private:
    std::string username;
    std::string password;
    bool loggedIn;

public:
    Member(const std::string& uname, const std::string& pwd) : username(uname), password(pwd), loggedIn(false) {
        // Initialize other member details
    }
