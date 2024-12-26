#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    int eventID;
    std::string title;
    std::string description;
    std::string clientName;
    std::string date;
    std::string time;
    double budget;
    int venueID;

public:
    Event(int id, const std::string& title, const std::string& clientName, const std::string& date, const std::string& time);

    void scheduleEvent(const std::string& details);
    void updateEventDetails(int eventID, const std::string& updates);
    void cancelEvent(int eventID);
};

#endif // EVENT_H
