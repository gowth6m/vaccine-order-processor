//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#include <iostream>
#include <iomanip>
#include "Customer.hpp"

/** Constructor */
Customer::Customer(OrderProcessor &processor, int customerNo, std::string customerName) : processor(processor) {
    this->customerName = customerName;
    this->orderQuantity = 0;
    this->customerNumber = customerNo;
}

/** Destructor */
Customer::~Customer() {
    processor.removeObserver(this);
}

/** Runs when notifyObserver is called */
void Customer::update() {
    if (processor.getTypeOfRecord() == 'S') {
        if (this->customerNumber == processor.getCurrentCustomerNo()) {
            processSalesOrder(processor.getCurrentLine());
        }
    } else if (processor.getTypeOfRecord() == 'E') {
        if (this->orderQuantity > 0) {
            shipOrders();
        }
    }
}

void Customer::processSalesOrder(std::string saleOrderRecord) {

    if (processor.getCurrentOrderType() == 'N') {
        this->orderQuantity += processor.getCurrentOrderQuantity();
        processor.setCurrentOrderTotal(this->orderQuantity);
        this->listOfOrders.push_back(Order(processor.getCurrentOrderDate(),
                                           processor.getCurrentOrderType(),
                                           processor.getCurrentOrderQuantity()));

    } else if (processor.getCurrentOrderType() == 'X') {
        this->orderQuantity += processor.getCurrentOrderQuantity();
        processor.setCurrentOrderTotal(0);
        shipOrders();

    } else {
        std::cerr << "Error in input file line "
                  << processor.getLineNumber()
                  << ": sale order type invalid"
                  << std::endl;
        exit(-1);
    }
}

void Customer::shipOrders() {
    /* clear the vector of orders, since they are all shipped */
    std::cout << "SC: customer " << std::setfill('0') << std::setw(4) << this->customerNumber
              << ": invoice " << processor.getInvoice() << ": date " << processor.getCurrentOrderDate()
              << ": quantity " << this->orderQuantity << std::endl;
    this->listOfOrders.clear();
    this->orderQuantity = 0;
}

int Customer::getCustomerNumber() {
    return this->customerNumber;
}

int Customer::getOrderQuantity() {
    return this->orderQuantity;
}