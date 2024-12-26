#include "System.h"
#include <iostream>
#include <vector>

// Add a user to the system
void System::addUser(const User& user) {
    users.push_back(user);
    std::cout << "User added successfully!" << std::endl;
}

// Add an admin to the system
void System::addAdmin(const Admin& admin) {
    admins.push_back(admin);
    std::cout << "Admin added successfully!" << std::endl;
}

// View system summary (overview of users, admins, venues, and events)
void System::viewSystemSummary() {
    std::cout << "System Summary: " << std::endl;
    std::cout << "Total Users: " << users.size() << std::endl;
    std::cout << "Total Admins: " << admins.size() << std::endl;
    std::cout << "Total Venues: " << venues.size() << std::endl;
    std::cout << "Total Events: " << events.size() << std::endl;
}
