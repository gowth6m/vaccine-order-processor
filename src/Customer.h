/*
* File:
* Description:
* Author: 		gowth6m
* Date:
*/

#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#pragma once
#include <string>
#include "Utilities.h"

using std::string;

class Customer {

private :
    string customerName;
    int customerNumber;
    int orderQuantity;

public:
    explicit Customer(const string &);

    string getCustomerName();

    int getCustomerNumber() const;

    int getOrderQuantity() const;

    void incrementQuantity(int);

    void setOrderQuantity(int);
};


#endif