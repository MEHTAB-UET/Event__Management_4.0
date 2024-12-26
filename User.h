#ifndef USER_H
#define USER_H

#include <string>
#include<mysql.h>


class User {
private:
    int userID;

    std::string email;
    std::string passkey;
    std::string phoneNumber;
    MYSQL* conn;

public:
    User(MYSQL* connection);
    std::string name;
    User(int id, const std::string& name, const std::string& email, const std::string& passkey, const std::string& phone, MYSQL* connection);
    std::string getName(User obj);
    void registerUser();
    bool login(User& object);
    void showAllVenues();
    void viewBookingHistory(std::string spotUser);
    void deleteVenue(int venID);
    //void searchVenue(const std::string& criteria);
    void bookVenue(std::string user);
    void cancelBooking(MYSQL* conn);
    //void cancelBooking();
    int userMenuu();
    void UserSideSystem(std::string currentUser);
};

#endif // USER_H
