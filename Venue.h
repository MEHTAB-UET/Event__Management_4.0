#ifndef VENUE_H
#define VENUE_H

#include <string>

class Venue {
private:
    int venueID;
    std::string name;
    std::string location;
    int capacity;
    double costPerPerson;
    int minGuests;
    std::string timings;
    bool status; // true = active, false = inactive

public:
    Venue(int id, const std::string& name, const std::string& location, int capacity, double cost);

    bool checkAvailability(const std::string& date, const std::string& time);
    void updateVenueDetails(const std::string& details);
    double calculateCost(int guestCount);
};

#endif // VENUE_H
