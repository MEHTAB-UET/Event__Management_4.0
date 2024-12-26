#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

class Payment {
private:
    int paymentID;
    int bookingID;
    double amountPaid;
    double balanceDue;
    std::string status; // "pending" or "complete"

public:
    Payment(int id, int bookingID, double amountPaid);

    void recordPayment(const std::string& details);
    void updatePaymentStatus(int paymentID, const std::string& status);
    void generateInvoice(int bookingID);
};

#endif // PAYMENT_H
