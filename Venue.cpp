#include "Venue.h"
#include <iostream>

struct Node {
    std::string date;
    Node* left;
    Node* right;
    Node(const std::string& date) : date(date), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;

Venue::Venue(int id, const std::string& name, const std::string& location, int capacity, double cost)
    : venueID(id), name(name), location(location), capacity(capacity), costPerPerson(cost), status(true) {}

bool insertDate(Node*& root, const std::string& date) {
    if (!root) {
        root = new Node(date);
        return true;
    }
    if (date < root->date) return insertDate(root->left, date);
    else if (date > root->date) return insertDate(root->right, date);
    return false; // Duplicate date
}

bool searchDate(Node* root, const std::string& date) {
    if (!root) return false;
    if (root->date == date) return true;
    if (date < root->date) return searchDate(root->left, date);
    return searchDate(root->right, date);
}

bool Venue::checkAvailability(const std::string& date, const std::string& time) {
    return !searchDate(root, date); // Check if date is free.
}

void Venue::updateVenueDetails(const std::string& details) {
    std::cout << "Venue details updated: " << details << std::endl;
}

double Venue::calculateCost(int guestCount) {
    return costPerPerson * guestCount;
}
