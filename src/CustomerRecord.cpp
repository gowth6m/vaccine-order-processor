#include <iostream>
#include "CustomerRecord.h"


/**
 * Constructor
 *
 * A parameterized constructor for the customer. A line read from file and passed to the constructor that is parsed
 * and stored in each variable of customer.
 *
 * @param customer: a customer record line from input file
 * */
CustomerRecord::CustomerRecord(const string &line, int lineNumber) {
    this->errorInLine = false;
    this->lineNumber = lineNumber;
    this->customerName = line.substr(5, line.size() - 4);
    this->orderQuantity = 0;
    this->customerNumber = processCustomerNumber(line);
}

/**
 * Destructor
 */
CustomerRecord::~CustomerRecord() = default;

/**
 * Function that checks if customer number in the line from input file is valid.
 *
 * @param line: line of record from input file
 * @return the customer number
 */
int CustomerRecord::processCustomerNumber(const string &line) {
    try {
        int customerNo = std::stoi(line.substr(1, 4));
        if(customerNo == 0) {
            std::cerr << "Error in input file line " << this->lineNumber << ", customer record: invalid conversion of customer number of 0000"
                      << std::endl;
            this->errorInLine = true;
            exit(-1);
        }
        return customerNo;
    }
    catch(std::invalid_argument &e){
        // if no conversion could be performed
        std::cerr << "Error in input file line " << this->lineNumber << ", customer record: invalid conversion of customer number to "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
    catch(std::out_of_range &e){
        std::cerr << "Error in input file line " << this->lineNumber << ", customer record: customer number out of range during conversion "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
}

/**
 * Function to add more to existing quantity
 *
 * @param quantity: the amount you want the quantity to increase
 */
void CustomerRecord::incrementQuantity(int quantity) {
    this->orderQuantity += quantity;
}

/**
 * Setter for orderQuantity
 *
 * @param quantity: initial order quantity that you would like to set for a customer
 */
void CustomerRecord::setOrderQuantity(int quantity) {
    this->orderQuantity = quantity;
}

/**
 * Getter for errorInLine
 *
 * @return true if there is an error in read line
 */
bool CustomerRecord::isErrorInLine() const {
    return this->errorInLine;
}

/**
 * Getter for customerName
 *
 * @return name of the customer
 */
string CustomerRecord::getCustomerName() {
    return this->customerName;
}

/**
 * Getter for customerName
 *
 * @return customer number
 */
int CustomerRecord::getCustomerNumber() const {
    return this->customerNumber;
}

/**
 * Getter for orderQuality
 *
 * @return order quantity
 */
int CustomerRecord::getOrderQuantity() const {
    return this->orderQuantity;
}
