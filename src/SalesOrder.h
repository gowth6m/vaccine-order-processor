/*
* File:			customerQueue.h
* Description:
* Author: 		gowth6m
* Date:
*/

#ifndef __SALEORDER_H
#define __SALEORDER_H
#pragma once
#include <string>
#include <iostream>

using std::string;

class SalesOrder {
private:
    int orderDate;
    char orderType;
    int customerNumber;
    int orderQuantity;
public:
    explicit SalesOrder(string);

    int getCustomerNumber() const;

    int getOrderQuantity() const;

    int getOrderDate() const;

    void setOrderQuantity(int);

    char getOrderType() const;
};

#endif