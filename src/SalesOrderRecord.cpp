#include "SalesOrderRecord.h"

SalesOrderRecord::SalesOrderRecord(string line, int lineNumber) {
    this->lineNumber = lineNumber;
    this->errorInLine = false;

    checkForValidLength(line);  /* checks for valid length */
    this->orderDate = processOrderDate(line);
    this->orderType = line.at(9);
    this->customerNumber = processCustomerNumber(line);
    this->orderQuantity = stoi(line.substr(14, 3));
}

void SalesOrderRecord::checkForValidLength(const string& line){
    if (line.length() != 18) {
        std::cerr << "Error in input file line " << this->lineNumber
                  << ", invalid length of sales order record line" << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
}

int SalesOrderRecord::processOrderDate(const string &line){
    try {
        int customerNo = stoi(line.substr(1, 9));
        if(customerNo == 0) {
            std::cerr << "Error in input file line " << this->lineNumber
                      << ", sales order record: invalid date of 0" << std::endl;
            this->errorInLine = true;
            exit(-1);
        }
        return customerNo;
    }
    catch(std::invalid_argument &e){
        std::cerr << "Error in input file line " << this->lineNumber << ", sales order record: invalid conversion of "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
    catch(std::out_of_range &e){
        std::cerr << "Error in input file line " << this->lineNumber << ", sales order record: out of range. "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
}

char SalesOrderRecord::processOrderType(const string &line){
    return 'a';
}

int SalesOrderRecord::processCustomerNumber(const string &line) {
    try {
        int customerNo = std::stoi(line.substr(10, 4));
        if(customerNo == 0) {
            std::cerr << "Error in input file line " << this->lineNumber
                      << ", sales order record: invalid conversion of customer number of 0000" << std::endl;
            this->errorInLine = true;
            exit(-1);
        }
        return customerNo;
    }
    catch(std::invalid_argument &e){
        std::cerr << "Error in input file line " << this->lineNumber << ", sales order record: invalid conversion of "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
    catch(std::out_of_range &e){
        std::cerr << "Error in input file line " << this->lineNumber << ", sales order record: out of range. "
                  << &e << std::endl;
        this->errorInLine = true;
        exit(-1);
    }
}

int SalesOrderRecord::processOrderQuantity(const string &line){
    return 0;
}

int SalesOrderRecord::getCustomerNumber() const {
    return this->customerNumber;
}

int SalesOrderRecord::getOrderQuantity() const {
    return this->orderQuantity;
}

int SalesOrderRecord::getOrderDate() const {
    return this->orderDate;
}

void SalesOrderRecord::setOrderQuantity(int quantity) {
    this->orderQuantity = quantity;
}

char SalesOrderRecord::getOrderType() const {
    if (this->orderType == 'N' || this->orderType == 'X') {
        return this->orderType;
    } else {
        std::cerr << "Error in input file: sale order type invalid" << std::endl;
        exit(-1);
    }
}
