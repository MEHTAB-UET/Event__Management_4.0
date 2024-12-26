#ifndef ADMIN_H
#define ADMIN_H

#include<string>
#include <mysql.h>



class Admin {
private:
    int adminID;
    std::string name;
    std::string email;
    std::string phoneNumber;
    int passkey;
    /* std::vector<int> managedVenues;*/
     // IDs of managed venues
    MYSQL* conn; // MySQL connection object

public:
    Admin(int id, const std::string& name, const std::string& email, const std::string& phone, int key, MYSQL* connection);

    void changePassword(Admin& object);
    void addVenue();
    void editVenue();
    void removeVenue();
    void ShowAllVenues();

    //---------------------------
    void viewAllBookings();
    void generateRevenueReport();
    void viewUpcomingEvents();
    //---------------------------
    int AdminMenuu();
    void AdminSideSystem(Admin& objectOfAdmin);
    void ViewProfile();
};

#endif // ADMIN_H
