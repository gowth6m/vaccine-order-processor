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
	SalesOrder(string);
	int getCustomerNumber();
	int getOrderQuantity();
	int getOrderDate();
	void setOrderQuantity(int);
	char getOrderType();
};