#include "SalesOrder.h"

SalesOrder::SalesOrder(string salesOrder) {
    this->orderDate = stoi(salesOrder.substr(1, 9));
    this->orderType = salesOrder.at(9);
    this->customerNumber = stoi(salesOrder.substr(10, 4));
    this->orderQuantity = stoi(salesOrder.substr(14, 3));
}

int SalesOrder::getCustomerNumber() const {
    return this->customerNumber;
}

int SalesOrder::getOrderQuantity() const {
    return this->orderQuantity;
}

int SalesOrder::getOrderDate() const {
    return this->orderDate;
}

void SalesOrder::setOrderQuantity(int quantity) {
    this->orderQuantity = quantity;
}

char SalesOrder::getOrderType() const {
    if (this->orderType == 'N' || this->orderType == 'X') {
        return this->orderType;
    } else {
        std::cerr << "Error in input file: sale order type invalid" << std::endl;
        exit(-1);
    }
}
