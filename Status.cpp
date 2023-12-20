#include <iostream>
#include <string>
#include <map> // Add this line to include the map header

using std::string;

enum class Status {
    PENDING,
    ACCEPTED,
    REJECTED
};

string statusToString(Status status) {
    static std::map<Status, string> statusMap = {
        {Status::PENDING, "Pending"},
        {Status::ACCEPTED, "Accepted"},
        {Status::REJECTED, "Rejected"},
    };

    auto it = statusMap.find(status);
    if (it != statusMap.end()) {
        return it->second;
    } else {
        return "Unknown"; // Handle unknown enum values
    }
}
