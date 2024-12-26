#include "Attendance.h"
#include <iostream>
#include <string>

// Constructor to initialize attendance details
Attendance::Attendance(int id, int eventID, const std::string& attendeeName)
    : attendanceID(id), eventID(eventID), attendeeName(attendeeName), status("confirmed") {}

// Method to record attendance
void Attendance::recordAttendance(const std::string& details) {
    // In a real implementation, this would save attendance details to a database
    status = "confirmed"; // Assuming the attendee is confirmed
    std::cout << "Attendance recorded for " << attendeeName << " at event " << eventID << ". Status: " << status << std::endl;
}

// Method to update attendance status (confirmed/canceled)
void Attendance::updateAttendance(int attendanceID, const std::string& status) {
    // In a real system, this would update the attendance status in the database
    this->status = status;
    std::cout << "Attendance status for " << attendeeName << " at event " << eventID << " updated to: " << status << std::endl;
}
