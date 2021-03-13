/*
* File:			customerQueue.h
* Description:
* Author: 		gowth6m
* Date:
*/

#include "Customer.h"

Customer::Customer(const string& customer) {
    this->customerName = Utilities::extractNameFromLine(customer);
    this->customerNumber = stoi(customer.substr(1, 4));
    this->customerName = customer.substr(5, customer.size() - 4);
    this->orderQuantity = 0;
}

/* PUBLIC */
string Customer::getCustomerName() {
    return this->customerName;
}

int Customer::getCustomerNumber() const {
    return this->customerNumber;
}

int Customer::getOrderQuantity() const {
    return this->orderQuantity;
}

void Customer::incrementQuantity(int quantity) {
    this->orderQuantity += quantity;
}

void Customer::setOrderQuantity(int quantity) {
    this->orderQuantity = quantity;
}


