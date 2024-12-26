#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>

class Attendance {
private:
    int attendanceID;
    int eventID;
    std::string attendeeName;
    std::string status; // "confirmed" or "canceled"

public:
    Attendance(int id, int eventID, const std::string& attendeeName);

    void recordAttendance(const std::string& details);
    void updateAttendance(int attendanceID, const std::string& status);
};

#endif // ATTENDANCE_H
