
#ifndef __SALEORDER_H
#define __SALEORDER_H
#pragma once

#include <string>
#include <iostream>

using std::string;

class SalesOrderRecord {
private:
    bool errorInLine;
    int lineNumber;
    int orderDate;
    char orderType;
    int customerNumber;
    int orderQuantity;

    void checkForValidLength(const string&);

    int processOrderDate(const string &);

    char processOrderType(const string &);

    /**
     * Function that checks if customer number in the line from input file is valid.
     *
     * @param line: line of record from input file
     * @return the customer number
     */
    int processCustomerNumber(const string &);

    int processOrderQuantity(const string &);

public:
    explicit SalesOrderRecord(string, int);

    int getCustomerNumber() const;

    int getOrderQuantity() const;

    int getOrderDate() const;

    void setOrderQuantity(int);

    char getOrderType() const;
};

#endif