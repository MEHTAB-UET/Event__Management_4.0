#include "Booking.h"
#include <iostream>

// Constructor to initialize a Booking object
Booking::Booking(int id, int userID, int venueID, int eventID, double advancePayment)
    : bookingID(id), userID(userID), venueID(venueID), eventID(eventID), advancePayment(advancePayment), balance(0.0) {}

// Create a new booking with additional details
void Booking::createBooking(const std::string& details) {
    std::cout << "Booking Created: \n"
        << "Booking ID: " << bookingID << "\n"
        << "User ID: " << userID << "\n"
        << "Venue ID: " << venueID << "\n"
        << "Event ID: " << eventID << "\n"
        << "Advance Payment: " << advancePayment << "\n"
        << "Details: " << details << std::endl;
}

// Update details for a specific booking
void Booking::updateBooking(int bookingID, const std::string& updates) {
    if (this->bookingID == bookingID) {
        std::cout << "Updating Booking ID " << bookingID << " with details: " << updates << std::endl;
    }
    else {
        std::cout << "Booking ID not found for update." << std::endl;
    }
}

// Process payment for the booking and update the balance
void Booking::processPayment(double amount) {
    if (amount > balance) {
        std::cout << "Payment exceeds balance. Current balance: " << balance << std::endl;
        return;
    }
    balance -= amount;
    std::cout << "Payment of " << amount << " processed. Remaining balance: " << balance << std::endl;
}
