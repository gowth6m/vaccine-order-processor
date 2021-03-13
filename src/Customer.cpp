#include "Customer.h"

Customer::Customer(string customer)
{
	this->customerNumber = stoi(customer.substr(1, 4));
	this->customerName = customer.substr(5, customer.size() - 4);
	this->orderQuantity = 0;
}

string Customer::getCustomerName()
{
	return this->customerName;
}

int Customer::getCustomerNumber()
{
	return this->customerNumber;
}

int Customer::getOrderQuantity()
{
	return this->orderQuantity;
}

void Customer::incrementQuantity(int quantity)
{
	this->orderQuantity += quantity;
}

void Customer::setOrderQuantity(int quantity)
{
	this->orderQuantity = quantity;
}
