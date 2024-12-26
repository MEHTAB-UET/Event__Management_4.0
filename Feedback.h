#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

class Feedback {
private:
    int feedbackID;
    int userID;
    int eventID;
    std::string comments;
    int rating;

public:
    Feedback(int id, int userID, int eventID, const std::string& comments, int rating);

    void addFeedback(const std::string& details);
    void viewFeedback(int venueID);
    void generateFeedbackReport();
};

#endif // FEEDBACK_H
