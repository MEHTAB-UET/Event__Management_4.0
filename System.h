#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "User.h"
#include "Admin.h"
#include "Venue.h"
#include "Event.h"

class System {
private:
    std::vector<User> users;
    std::vector<Admin> admins;
    std::vector<Venue> venues;
    std::vector<Event> events;

public:
    void addUser(const User& user);
    void addAdmin(const Admin& admin);
    void viewSystemSummary();
};

#endif // SYSTEM_H
