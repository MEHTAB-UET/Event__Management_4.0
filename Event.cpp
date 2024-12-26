#include "Event.h"
#include <iostream>

// Constructor to initialize an Event object
Event::Event(int id, const std::string& title, const std::string& clientName, const std::string& date, const std::string& time)
    : eventID(id), title(title), clientName(clientName), date(date), time(time), budget(0.0), venueID(0) {}

// Schedule an event with additional details
void Event::scheduleEvent(const std::string& details) {
    std::cout << "Event Scheduled: \n"
        << "Title: " << title << "\n"
        << "Client Name: " << clientName << "\n"
        << "Date: " << date << "\n"
        << "Time: " << time << "\n"
        << "Details: " << details << std::endl;
}

// Update details for a specific event
void Event::updateEventDetails(int eventID, const std::string& updates) {
    if (this->eventID == eventID) {
        std::cout << "Updating Event ID " << eventID << " with details: " << updates << std::endl;
    }
    else {
        std::cout << "Event ID not found for update." << std::endl;
    }
}

// Cancel a specific event
void Event::cancelEvent(int eventID) {
    if (this->eventID == eventID) {
        std::cout << "Event ID " << eventID << " titled '" << title << "' has been canceled." << std::endl;
    }
    else {
        std::cout << "Event ID not found for cancellation." << std::endl;
    }
}
