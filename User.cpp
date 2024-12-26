#include "User.h"
#include <iostream>
#include <queue>
#include<mysql.h>

std::queue<int> bookingQueue; // Queue to store recent bookings.

User::User(int id, const std::string& name, const std::string& email, const std::string& passkey, const std::string& phone, MYSQL* connection)
    : userID(id), name(name), email(email), phoneNumber(phone), conn(connection) {}
//name getter of the user
std::string User::getName(User currentUser) {
    return currentUser.name;

}

User::User(MYSQL* connection)
    :userID(99), name("Tester"), email("empty@gmail.com"), phoneNumber("0305-7695043"), conn(connection) {}
//-------------------------------------------------   Sign Inn         --------------------------------------------//
void User::registerUser() {
    std::system("cls");
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                  Sign  In                                         *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*************************************************************************************" << std::endl;

    std::string name, email, password, phoneNumber;

    // Input user details
    std::cout << "Enter Name: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter Email: ";
    std::getline(std::cin, email);

    std::cout << "Enter Password: ";
    std::getline(std::cin, password);

    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phoneNumber);

    // Prepare SQL query
    std::string query = "INSERT INTO users (Name, Email, Password, PhoneNumber) VALUES ('"
        + name + "', '" + email + "', '" + password + "', '" + phoneNumber + "')";

    // Execute query
    if (mysql_query(conn, query.c_str()) == 0) {
        std::system("cls");
        std::cout << "*************************************************************************************" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*                              Registration SuccessFull !                           *" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*                                                                                   *" << std::endl;
        std::cout << "*************************************************************************************" << std::endl;
    }
    else {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
    }
}
//-------------------------------------------------   Log Inn          --------------------------------------------//
bool User::login(User& object) {
    std::system("cls");
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                  LOG IN                                           *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*************************************************************************************" << std::endl;

    std::string enteredEmail, enteredPassword;
    std::string currentName;
    std::cout << "Enter User Name:";
    std::cin >> currentName;
    object.name = currentName;

    std::cout << "Enter Email: ";
    std::cin >> enteredEmail;

    std::cout << "Enter Password: ";
    std::cin >> enteredPassword;

    // Query to validate email and password
    std::string query = "SELECT UserID, Name FROM users WHERE Email = '" + enteredEmail +
        "' AND Password = '" + enteredPassword + "'";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (row) {
            // Successful login: retrieve user data
            userID = std::stoi(row[0]);
            email = enteredEmail;
            passkey = enteredPassword;
            std::cout << "Welcome, " << row[1] << "! Login Successful!" << std::endl;
            mysql_free_result(res);

            return true;
        }
        else {
            // Invalid email or password
            std::cout << "Invalid Email or Password. Please try again." << std::endl;
        }
        mysql_free_result(res);
    }
    else {
        // Query execution error
        std::cerr << "Error: " << mysql_error(conn) << std::endl;
    }
    return false;
}
//-------------------------------------------------   Show VENUES      --------------------------------------------//
void User::showAllVenues() {
    std::system("cls");
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                              Available Venues                                     *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*************************************************************************************" << std::endl;
    MYSQL_RES* res;
    MYSQL_ROW row;

    std::string query = "select * from venues";
    if (mysql_query(conn, query.c_str()) == 0) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res)) {
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Id: " << row[0] << std::endl;
            std::cout << "Name: " << row[1] << std::endl;
            std::cout << "Location: " << row[2] << std::endl;
            std::cout << "Capacity: " << row[3] << std::endl;
            std::cout << "PerPerson: " << row[4] << std::endl;
            std::cout << "MinPerson: " << row[5] << std::endl;
            std::cout << "Available Time: " << row[6] << std::endl;
            std::cout << "----------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }



    }

}
//-------------------------------------------------   ViewBooking      --------------------------------------------//
void User::viewBookingHistory(std::string spotUser) {
    //for maintaing queue
       /* std::queue<int> tempQueue = bookingQueue;
    std::cout << "Booking History:\n";
    while (!tempQueue.empty()) {
        std::cout << "Booking ID: " << tempQueue.front() << std::endl;
        tempQueue.pop();
    }*/
    // Construct query to fetch all events booked by the user
    std::system("cls");
    std::string query = "SELECT EventID, Title, Description, Date, Time, Budget, VenueID FROM Events WHERE ClientName = '" + spotUser + "'";

    // Execute the query
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        // Check if there are any bookings
        if (mysql_num_rows(res) == 0) {
            std::cout << "No bookings found for " << spotUser << "." << std::endl;
        }
        else {
            std::cout << "Booking History for " << spotUser << ":" << std::endl;
            std::cout << "--------------------------------------" << std::endl;

            // Display each booking
            while ((row = mysql_fetch_row(res))) {
                std::cout << "Event ID: " << row[0] << std::endl;
                std::cout << "Title: " << row[1] << std::endl;
                std::cout << "Description: " << row[2] << std::endl;
                std::cout << "Date: " << row[3] << std::endl;
                std::cout << "Time: " << row[4] << std::endl;
                std::cout << "Budget: " << row[5] << std::endl;
                std::cout << "Venue ID: " << row[6] << std::endl;

                // Fetch Venue Name and Location
                std::string venueQuery = "SELECT Name, Location FROM venues WHERE VenueID = " + std::string(row[6]);
                if (mysql_query(conn, venueQuery.c_str()) == 0) {
                    MYSQL_RES* venueRes = mysql_store_result(conn);
                    MYSQL_ROW venueRow = mysql_fetch_row(venueRes);

                    if (venueRow) {
                        std::cout << "Venue Name: " << venueRow[0] << std::endl;
                        std::cout << "Location: " << venueRow[1] << std::endl;
                    }
                    else {
                        std::cout << "Venue details not found!" << std::endl;
                    }

                    // Free venue result
                    mysql_free_result(venueRes);
                }
                else {
                    std::cerr << "Error fetching venue details: " << mysql_error(conn) << std::endl;
                }

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
//-------------------------------------------------   Booking Venue    --------------------------------------------//
void User::bookVenue(std::string spotUser) {
    showAllVenues(); // Display all available venues

    // Collect user inputs
    int venueID, numPersons;
    std::string eventName, description, date, time;


    std::cout << "Enter the ID of the venue in which you want to arrange your event: ";
    std::cin >> venueID;
    std::cin.ignore();
    

    std::cout << "Enter the Name of your Event: ";
    std::getline(std::cin, eventName);

    std::cout << "Enter a Description for your Event: ";
    std::getline(std::cin, description);

    std::cout << "Enter the Date (YYYY-MM-DD) on which you want to arrange your event: ";
    std::cin >> date;

    std::cout << "Enter the Time (HH:MM:SS) for your event: ";
    std::cin >> time;

    std::cout << "Enter the Number of Persons attending the event: ";
    std::cin >> numPersons;

    // Fetch PricePerPerson from the selected venue
    std::string priceQuery = "SELECT PricePerPerson FROM Venues WHERE VenueID = " + std::to_string(venueID);
    if (mysql_query(conn, priceQuery.c_str()) != 0) {
        std::cerr << "Error fetching venue details: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (!row) {
        std::cerr << "Invalid Venue ID or venue does not exist." << std::endl;
        mysql_free_result(res);
        return;
    }

    double pricePerPerson = std::stod(row[0]); // Convert to double
    double totalBudget = pricePerPerson * numPersons;
    mysql_free_result(res);

    // Insert the event into the Events table
    std::string insertQuery = "INSERT INTO events (Title, Description, ClientName, Date, Time, Budget, VenueID) VALUES ('" +
        eventName + "', '" + description + "', '" + spotUser + "' , '" + date + "', '" + time + "', " +
        std::to_string(totalBudget) + ", " + std::to_string(venueID) + ")";

    if (mysql_query(conn, insertQuery.c_str()) == 0) {
        std::cout << "Event booked successfully!" << std::endl;
        std::cout << "Total Budget: " << totalBudget << std::endl;
        //Removing From Venues Table
        //deleteVenue(venueID);
  
    }
    else {
        std::cerr << "Error booking event: " << mysql_error(conn) << std::endl;
    }
}
//-------------------------------------------------   DEL Venue    --------------------------------------------//
void User::deleteVenue(int VenueID) {
    // Create the delete query for the venue
    std::string deleteVenueQuery = "DELETE FROM Venues WHERE VenueID = " + std::to_string(VenueID);

    // Execute the delete query
    if (mysql_query(conn, deleteVenueQuery.c_str()) == 0) {
        // Query successful, venue deleted
        std::cout << "Venue with ID " << VenueID << " has been successfully removed from available venues." << std::endl;
    }
    else {
        // Handle query error
        std::cerr << "Error removing venue: " << mysql_error(conn) << std::endl;
    }
}

//-------------------------------------------------   Cancel Booking   --------------------------------------------//
void User::cancelBooking(MYSQL* conn) {

    std::cout << "Your Current Bookings:" << std::endl;
    std::string query = "SELECT EventID, Title, Date FROM events";
    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;

        if (mysql_num_rows(res) == 0) {
            std::cout << "No bookings available to cancel." << std::endl;
            mysql_free_result(res);
            return;
        }

        while ((row = mysql_fetch_row(res))) {
            std::cout << "Event ID: " << row[0] << ", Title: " << row[1] << ", Date: " << row[2] << std::endl;
        }

        mysql_free_result(res);

        // Prompt user for the event ID to cancel
        int eventID;
        std::cout << "Enter the ID of the event you want to cancel: ";
        std::cin >> eventID;

        // Delete query
        std::string deleteQuery = "DELETE FROM events WHERE EventID = " + std::to_string(eventID);

        // Execute the delete query
      
        if (mysql_query(conn, deleteQuery.c_str()) == 0) {
            if (mysql_affected_rows(conn) > 0) {
                std::cout << "Event with ID " << eventID << " has been successfully canceled." << std::endl;
            }
            else {
                std::cout << "No event found with ID " << eventID << "." << std::endl;
            }
        }
        else {
            std::cerr << "Error canceling event: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cerr << "Error fetching events: " << mysql_error(conn) << std::endl;
    }
}

//-------------------------------------------------   User Menu        --------------------------------------------//
int User::userMenuu() {
    int choice;
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                         WELCOME    TO  USER   PANNEL                              *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*                                                                                   *" << std::endl;
    std::cout << "*************************************************************************************" << std::endl;
    std::cout << "1. Show Venues" << std::endl;
    std::cout << "2. Book a Venue for Event  " << std::endl;
    std::cout << "3. View My Bookings" << std::endl;
    std::cout << "4. Cancel a Booking" << std::endl;
    std::cout << "99. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    return choice;
}
//-------------------------------------------------   User Side System --------------------------------------------//
void User::UserSideSystem(std::string spotUSER) {
    int userChoice = 10;

    while (userChoice != 99) {

        userChoice = userMenuu();
        if (userChoice == 1) {
            showAllVenues();
        }
        else if (userChoice == 2) {
            bookVenue(spotUSER);
        }
        else if (userChoice == 3) {
            viewBookingHistory(spotUSER);
        }
        else if (userChoice == 4)
        {
            cancelBooking(conn);
        }
    }
}
