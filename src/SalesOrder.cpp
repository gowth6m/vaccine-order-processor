#include "SalesOrder.h"

SalesOrder::SalesOrder(string salesOrder)
{
	this->orderDate = stoi(salesOrder.substr(1, 9));
	this->orderType = salesOrder.at(9);
	this->customerNumber = stoi(salesOrder.substr(10, 4));
	this->orderQuantity = stoi(salesOrder.substr(14, 3));
}

//check if number or string
bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) == false) return false;
	}
	return true;
}

int SalesOrder::getCustomerNumber()
{
	return this->customerNumber;
}

int SalesOrder::getOrderQuantity()
{
	return this->orderQuantity;
}

int SalesOrder::getOrderDate()
{
	return this->orderDate;
}

void SalesOrder::setOrderQuantity(int quantity)
{
	this->orderQuantity = quantity;
}

char SalesOrder::getOrderType()
{
	if(this->orderType == 'N' || this->orderType == 'X')
	{
		return this->orderType;
	}
	else
	{
		std::cerr << "Error in input file: sale order order type invalid";
		exit(-1);
	}
}
