#pragma once
#include <string>
using std::string;
class Customer {
private :
	string customerName;
	int customerNumber;
	int orderQuantity;

public:
	Customer(string);
	string getCustomerName();
	int getCustomerNumber();
	int getOrderQuantity();
	void incrementQuantity(int);
	void setOrderQuantity(int);

};