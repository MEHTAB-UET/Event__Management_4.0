#include "Payment.h"
#include <iostream>

// Constructor to initialize a Payment object
Payment::Payment(int id, int bookingID, double amountPaid)
    : paymentID(id), bookingID(bookingID), amountPaid(amountPaid), balanceDue(0.0), status("pending") {}

// Record a new payment with additional details
void Payment::recordPayment(const std::string& details) {
    std::cout << "Payment Recorded: \n"
        << "Payment ID: " << paymentID << "\n"
        << "Booking ID: " << bookingID << "\n"
        << "Amount Paid: " << amountPaid << "\n"
        << "Details: " << details << std::endl;

    // Check if payment is complete
    if (balanceDue == 0) {
        status = "complete";
        std::cout << "Payment status updated to: " << status << std::endl;
    }
}

// Update payment status (e.g., "pending" or "complete")
void Payment::updatePaymentStatus(int paymentID, const std::string& status) {
    if (this->paymentID == paymentID) {
        this->status = status;
        std::cout << "Payment ID " << paymentID << " status updated to: " << status << std::endl;
    }
    else {
        std::cout << "Payment ID not found for update." << std::endl;
    }
}

// Generate an invoice for the given booking ID
void Payment::generateInvoice(int bookingID) {
    if (this->bookingID == bookingID) {
        std::cout << "Invoice for Booking ID: " << bookingID << "\n"
            << "Payment ID: " << paymentID << "\n"
            << "Amount Paid: " << amountPaid << "\n"
            << "Balance Due: " << balanceDue << "\n"
            << "Status: " << status << std::endl;
    }
    else {
        std::cout << "Booking ID not found for invoice generation." << std::endl;
    }
}
