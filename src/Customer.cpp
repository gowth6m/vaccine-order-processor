//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#include <iostream>
#include <iomanip>
#include "Customer.hpp"

/** Constructor */
Customer::Customer(OrderProcessor &processor, std::string line) : processor(processor) {
    this->errorInLine = false;
    this->customerName = line.substr(5, line.size() - 4);
    this->orderQuantity = 0;
    this->customerNumber = processCustomerNumber(line, 1, 4);
}

/** Destructor */
Customer::~Customer() {
    processor.removeObserver(this);
}

/** Runs when notifyObserver is called */
void Customer::update() {
    if (processor.getTypeOfRecord() == 'S') {
        if (this->customerNumber == processCustomerNumber(processor.getCurrentLine(), 10, 4)) {
            addSalesOrder(processor.getCurrentLine());
        }
    } else if (processor.getTypeOfRecord() == 'E') {
        if (this->orderQuantity != 0) {

        }
    } else if (processor.getTypeOfRecord() == 'E') {
        std::cout << "End of day order" << std::endl;
    }
}


int Customer::processCustomerNumber(const std::string &line, int startPos, int endPos) {
    try {
        int customerNo = std::stoi(line.substr(startPos, endPos));
        if(customerNo == 0) {
            std::cerr << "Error in input file line " << processor.getLineNumber() << ": invalid conversion of customer number of 0000"
                      << std::endl;
            this->errorInLine = true;
            exit(-1);
        }
        return customerNo;
    }
    catch(std::invalid_argument &e){
        // if no conversion could be performed
        std::cerr << "Error in input file line " << this->lineNumber << ": invalid conversion of customer number to "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
    catch(std::out_of_range &e){
        std::cerr << "Error in input file line " << this->lineNumber << ": customer record: customer number out of range during conversion "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
}

int Customer::getCustomerNumber() {
    return this->customerNumber;
}

void Customer::addSalesOrder(std::string saleOrderRecord) {
    int date = processCustomerNumber(saleOrderRecord, 1, 9);
    char type = saleOrderRecord.at(9);
    int quantity = processCustomerNumber(saleOrderRecord, 14, 3);
    this->orderQuantity += quantity;
    this->listOfOrders.push_back(Order(date, type, quantity));

    if (type == 'N') {
        std::cout << "OP: customer " << std::setfill('0') << std::setw(4) << this->customerNumber
                  << ": normal order: quantity " << quantity << std::endl;
    } else if (type == 'X') {
        std::cout << "OP: customer " << std::setfill('0') << std::setw(4) << this->customerNumber
                  << ": EXPRESS order: quantity " << quantity << std::endl;
        this->orderQuantity = 0;
    } else {
        std::cerr << "Error in input file line " << processor.getLineNumber()
                  << ": sale order type invalid"
                  << std::endl;
        exit(-1);
    }
}
