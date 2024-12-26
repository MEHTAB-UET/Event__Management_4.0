#include "Admin.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <mysql.h> // MySQL API header

std::map<int, std::vector<int>> venueGraph; // Adjacency list for venues.

//---------------------------------------------------------       Constructor                ------------------------------------------------------------------//
Admin::Admin(int id, const std::string& name, const std::string& email, const std::string& phone, int key, MYSQL* connection)
{
    this->adminID = id;
    this->name = name;
    this->email = email;
    this->phoneNumber = phone;
    this->passkey = key;
    this->conn = connection;
    if (conn) {
        std::cout << "Admin connected to database." << std::endl;
    }
    else {
        std::cerr << "Failed to connect Admin to database." << std::endl;
    }
}
//---------------------------------------------------------      Change Password             ------------------------------------------------------------------//
void Admin::changePassword(Admin& objectOfAdmin) {
    int newPasskey, cnfrmPasskey;
    bool isPasswordSet = false;
    std::cout << "YOUR CURRENT PASSWORD IS :" << objectOfAdmin.passkey << std::endl;
    while (isPasswordSet == false) {
        std::cout << "Enter New Passkey:" << std::endl;
        std::cin >> newPasskey;
        std::cout << "Confirm Password" << std::endl;
        std::cin >> cnfrmPasskey;
        if (newPasskey != cnfrmPasskey)
        {
            std::system("cls");
            std::cout << "Password Not match" << std::endl;
        }
        else
        {
            objectOfAdmin.passkey = newPasskey;
            std::cout << "Password Reset Successfully" << std::endl;
            isPasswordSet = true;
        }

    }
}
//---------------------------------------------------------  Entering a  new venue           ------------------------------------------------------------------//
void Admin::addVenue() {
    std::cout << "Adding venue function called" << std::endl;
    std::string NameOfVenue, Location, AvailableTime;
    int capacity, perPerson, minimumPerson;

    // Clear the input buffer
    std::cin.ignore(1000, '\n');


    // input of venue name
    std::cout << "Enter Name of New Venue :" << std::endl;
    std::getline(std::cin, NameOfVenue);

    // input of location
    std::cout << "Enter Location: " << std::endl;
    std::getline(std::cin, Location);

    // input of capacity
    std::cout << "Capacity of Persons: " << std::endl;
    std::cin >> capacity;
    std::cin.ignore(); // Clear leftover newline character

    // input of perPerson
    std::cout << "Enter Price Per Person" << std::endl;
    std::cin >> perPerson;
    std::cin.ignore(); // Clear leftover newline character

    // input of Minimum Person
    std::cout << "Minimum Person: " << std::endl;
    std::cin >> minimumPerson;
    std::cin.ignore(); // Clear leftover newline character

    // input of available-time
    std::cout << "Available Time: ";
    std::getline(std::cin, AvailableTime);




    //------------   Query to add new Venue--------------------//
    std::string query = "INSERT INTO Venues (Name, Location, Capacity, PricePerPerson, MinPersons, AvailableTime) VALUES ('"
        + NameOfVenue + "', '" + Location + "', " + std::to_string(capacity) + ", " + std::to_string(perPerson) + ", " + std::to_string(minimumPerson) + ", '" +
        AvailableTime + "')";


    // Execute query
    if (mysql_query(conn, query.c_str()) == 0) {
        std::cout << "Venue added successfully." << std::endl;
    }
    else {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        //std::cout << "Error a araha ha" << std::endl;
    }
}
//---------------------------------------------------------         Showing All Venues       ------------------------------------------------------------------//
void Admin::ShowAllVenues() {
    MYSQL_RES* res;
    MYSQL_ROW row;

    std::string query = "select * from venues";
    if (mysql_query(conn, query.c_str()) == 0) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Id              : " << row[0] << std::endl;
            std::cout << "Name            : " << row[1] << std::endl;
            std::cout << "Location        : " << row[2] << std::endl;
            std::cout << "Capacity        : " << row[3] << std::endl;
            std::cout << "PerPerson       : " << row[4] << std::endl;
            std::cout << "MinPerson       : " << row[5] << std::endl;
            std::cout << "Available Time  : " << row[6] << std::endl;
            std::cout << "----------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }



    }

}
//---------------------------------------------------------         Edit Venue               ------------------------------------------------------------------//
void Admin::editVenue() {
    ShowAllVenues();
    int venueID, editChoice;
    std::cout << "Enter the ID of the venue you want to edit: ";
    std::cin >> venueID;
    std::cin.ignore();  // Clear the input buffer

    // Show the menu to the user
    std::cout << "What would you like to edit?" << std::endl;
    std::cout << "1. Edit Name" << std::endl;
    std::cout << "2. Edit Location" << std::endl;
    std::cout << "3. Edit Price per Person" << std::endl;
    std::cout << "4. Edit Available Time" << std::endl;
    std::cout << "Enter your choice (1-4): ";
    std::cin >> editChoice;
    std::cin.ignore();  // Clear the input buffer

    if (editChoice == 1) {
        // Edit Name
        std::string newName;
        std::cout << "Enter new Name: ";
        std::getline(std::cin, newName);

        std::string query = "UPDATE Venues SET Name = '" + newName + "' WHERE VenueID = " + std::to_string(venueID);
        if (mysql_query(conn, query.c_str()) == 0) {
            std::cout << "Venue name updated successfully." << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
    }
    else if (editChoice == 2) {
        // Edit Location
        std::string newLocation;
        std::cout << "Enter new Location: ";
        std::getline(std::cin, newLocation);

        std::string query = "UPDATE Venues SET Location = '" + newLocation + "' WHERE VenueID = " + std::to_string(venueID);
        if (mysql_query(conn, query.c_str()) == 0) {
            std::cout << "Venue location updated successfully." << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
    }
    else if (editChoice == 3) {
        // Edit Price Per Person
        double newPrice;
        std::cout << "Enter new Price Per Person: ";
        std::cin >> newPrice;

        std::string query = "UPDATE Venues SET PricePerPerson = " + std::to_string(newPrice) + " WHERE VenueID = " + std::to_string(venueID);
        if (mysql_query(conn, query.c_str()) == 0) {
            std::cout << "Venue price updated successfully." << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
    }
    else if (editChoice == 4) {
        // Edit Available Time
        std::string newAvailableTime;
        std::cout << "Enter new Available Time: ";
        std::getline(std::cin, newAvailableTime);

        std::string query = "UPDATE Venues SET AvailableTime = '" + newAvailableTime + "' WHERE VenueID = " + std::to_string(venueID);
        if (mysql_query(conn, query.c_str()) == 0) {
            std::cout << "Venue available time updated successfully." << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
}
//---------------------------------------------------------        RemoveVenue               ------------------------------------------------------------------//
void Admin::removeVenue() {
    int venueID;
    std::cout << "Enter the ID of the venue you want to delete: ";
    std::cin >> venueID;

    // Confirmation message
    char confirmation;
    std::cout << "Are you sure you want to delete the venue with ID " << venueID << "? (y/n): ";
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        std::string query = "DELETE FROM Venues WHERE VenueID = " + std::to_string(venueID);
        if (mysql_query(conn, query.c_str()) == 0) {
            std::cout << "Venue deleted successfully." << std::endl;
        }
        else {
            std::cout << "Error: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cout << "Venue deletion cancelled." << std::endl;
    }
}
//---------------------------------------------------------         View All Bookings        ------------------------------------------------------------------//
void Admin::viewAllBookings() {
    std::system("cls");
    std::string query = "SELECT * FROM events";


    // Execute the query
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        // Check if there are any bookings
        if (mysql_num_rows(res) == 0) {
            std::cout << "No bookings found for " << this->name << "." << std::endl;
        }
        else {
            std::cout << "--------------------------------------" << std::endl;

            // Display each booking
            while ((row = mysql_fetch_row(res))) {
                std::cout << "Event ID         : " << row[0] << std::endl;
                std::cout << "Title            : " << row[1] << std::endl;
                std::cout << "Description      : " << row[2] << std::endl;
                std::cout << "Date             : " << row[3] << std::endl;
                std::cout << "Time             : " << row[4] << std::endl;
                std::cout << "Budget           : " << row[5] << std::endl;
                std::cout << "Venue ID         : " << row[6] << std::endl;
                std::cout << "--------------------------------------" << std::endl;
            }
        }

        // Free result set
        mysql_free_result(res);
    }
    else {
        // Handle query error
        std::cerr << "Error fetching booking history: " << mysql_error(conn) << std::endl;
    }
}
//---------------------------------------------------------         Revenuew Report          ------------------------------------------------------------------//
void Admin::generateRevenueReport() {
    std::cout << "Revenue report generated." << std::endl;
}
//---------------------------------------------------------         View Upcomming Events    ------------------------------------------------------------------//
void Admin::viewUpcomingEvents() {
    viewAllBookings();
}
//--------------------------------------------------------          Profile view             ------------------------------------------------------------------//
void Admin::ViewProfile() {
    std::cout << "ID        :" << adminID << std::endl;
    std::cout << "Name      :" << name << std::endl;
    std::cout << "Email     :" << phoneNumber << std::endl;
    std::cout << "Passkey   :" << passkey << std::endl;
}
//---------------------------------------------------------------     Admin Menu   -----------------------------------------------------------------------------//
int Admin::AdminMenuu() {
    int ansByAdmin;
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                         WELCOME   TO   ADMIN  PANNEL                              *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "1-Change Passowrd" << std::endl;
    std::cout << "2-Add a new Venue" << std::endl;
    std::cout << "3-Show All Venues" << std::endl;
    std::cout << "4-Edit Venue" << std::endl;
    std::cout << "5-Remove Venue" << std::endl;
    std::cout << "6-View All Bookings" << std::endl;
    std::cout << "7-Generate Revenue Report" << std::endl;
    std::cout << "8-View Profile" << std::endl;
    std::cout << "9-View Request (pending) and Give Approval " << std::endl;
    std::cin >> ansByAdmin;
    std::system("cls");
    return ansByAdmin;
}
//---------------------------------------------------------------     Admin Side System       -----------------------------------------------------------------//

void Admin::AdminSideSystem(Admin& rootUser) {

    int exit = 1;
    int AdminChoice = 2;
    while (exit != 99)
    {
        int isValid;
        std::cout << "Enter your Passkey : ";
        std::cin >> isValid;
        std::system("cls");
        if (isValid == rootUser.passkey) {
            do
            {
                AdminChoice = AdminMenuu();
                if (AdminChoice == 1) {
                    //Change password
                    std::system("cls");
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                 CHANGE PASSWORD                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.changePassword(rootUser);
                }
                else if (AdminChoice == 2) {
                    std::system("cls");
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                Add a New Venue                                    *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.addVenue();
                }
                else if (AdminChoice == 3) {
                    std::system("cls");
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                Show All Venues                                    *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.ShowAllVenues();


                }
                else if (AdminChoice == 4) {
                    std::system("cls");
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                  Edit Venue                                       *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.editVenue();
                }
                else if (AdminChoice == 5) {
                    std::system("cls");

                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                  Remove Venue                                     *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.ShowAllVenues();
                    rootUser.removeVenue();
                }
                else if (AdminChoice == 6) {
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                 View All Bookings                                 *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.viewAllBookings();
                }
                else if (AdminChoice == 7) {
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                Generate Revenue Report                            *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                }
                else if (AdminChoice == 8) {
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                      View Profile                                 *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;
                    rootUser.ViewProfile();
                }
                else if (AdminChoice == 9) {
                    std::cout << "*************************************************************************************" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                      View Request                                 *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*                                                                                   *" << std::endl;
                    std::cout << "*************************************************************************************" << std::endl;

                }
            } while (AdminChoice != 99);

        }
        else
        {
            std::cout << "Incorrect Passkey............" << std::endl;
            exit = 99;
        }
    };
}