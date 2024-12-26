#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
private:
    int bookingID;
    int userID;
    int venueID;
    int eventID;
    double advancePayment;
    double balance;

public:
    Booking(int id, int userID, int venueID, int eventID, double advancePayment);

    void createBooking(const std::string& details);
    void updateBooking(int bookingID, const std::string& updates);
    void processPayment(double amount);
};

#endif // BOOKING_H
