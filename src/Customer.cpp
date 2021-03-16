/**
* File:         Customer.cpp
*
* Description:  Represents a Customer of the order system, implements Observer interface.
*
* Author:       gowth6m
*
* Date:         10/03/2021
*/

#include <iostream>
#include <iomanip>
#include <utility>
#include "Customer.hpp"

/**
 * Constructor
 *
 * @param processor: pointer to an OrderProcessor(Subject)
 * @param customerNo: Customer's unique number
 * @param customerName: Customer's name
 */
Customer::Customer(OrderProcessor &processor, int customerNo, std::string customerName) : processor(processor) {
    this->customerName = std::move(customerName);  /* name of the customer */
    this->orderQuantity = 0;                       /* initial order quantity = 0 */
    this->customerNumber = customerNo;             /* customer's unique number */
}

/**
 * Destructor
 *
 * Remove's instance of this class from the OrderProcessor's(Subject) list of observers, free memory for
 * instance of this class.
 */
Customer::~Customer() {
    processor.removeObserver(this);
}

/**
 * This function is ran when notifyObserver function is called in OrderProcessor(Concrete Subject instance).
 *
 * Depending on the states of the OrderProcessor(Subject), different functions are executed here.
 */
void Customer::update() {
    /* Current line read in OrderProcessor has type of S = Sales Order record */
    if (processor.getTypeOfRecord() == 'S') {
        if (this->customerNumber == processor.getCurrentCustomerNo()) {
            processSalesOrder();
        }
    }

    /* Current line read in OrderProcessor has type of E = End of Day record */
    if (processor.getTypeOfRecord() == 'E') {
        if (this->orderQuantity > 0 && this->customerNumber == processor.getCurrentEODCustomer()) {
            shipOrders();
        }
    }
}

/**
 * Function that runs when SaleOrder is read in the OrderProcessor.
 *
 * If order type is 'N', current read quantity in OrderProcessor is added to Customer's orderQuantity
 * and outputs a message.
 *
 * If order type is 'X', current read quantity in OrderProcessor is added to Customer's orderQuantity,
 * and its shipped.
 */
void Customer::processSalesOrder() {
        /* N = normal order */
    if (processor.getCurrentOrderType() == 'N') {
        this->orderQuantity += processor.getCurrentOrderQuantity();
        processor.setCurrentOrderTotal(this->orderQuantity);
        this->listOfOrders.emplace_back(processor.getCurrentOrderDate(),
                                        processor.getCurrentOrderType(),
                                        processor.getCurrentOrderQuantity());
        /* X = express order */
    } else if (processor.getCurrentOrderType() == 'X') {
        this->orderQuantity += processor.getCurrentOrderQuantity();
        processor.setCurrentOrderTotal(0);
        shipOrders();
        /* If read letter is not N or X, output error message */
    } else {
        std::cerr << "Error in input file line "
                  << processor.getLineNumber()
                  << ": sale order type invalid"
                  << std::endl;
        exit(-1);
    }
}

/**
 * Function to ship orders.
 *
 * Output a message, increases invoice counter and resets orderQuantity and listOfOrders for instance of this class.
 */
void Customer::shipOrders() {
    std::cout << "SC: customer " << std::setfill('0') << std::setw(4) << this->customerNumber
              << ": invoice " << processor.getInvoice() << ": date " << processor.getCurrentOrderDate()
              << ": quantity " << this->orderQuantity << std::endl;
    processor.incrementInvoice();
    /* clear the vector of orders, since they are all shipped & quantity reset to 0 */
    this->listOfOrders.clear();
    this->orderQuantity = 0;
}

/**
 * Getter for customerNumber
 *
 * @return customerNumber
 */
int Customer::getCustomerNumber() const {
    return this->customerNumber;
}

/**
 * Getter for orderQuantity
 *
 * @return orderQuantity
 */
int Customer::getOrderQuantity() const {
    return this->orderQuantity;
}