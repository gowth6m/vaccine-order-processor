//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#include "Order.hpp"

Order::Order(int date, char type, int quantity) {
    this->date = date;
    this->type = type;
    this->quantity = quantity;
}

int Order::getDate() {
    return 0;
}

int Order::getQuantity() {
    return 0;
}

char Order::getType() {
    return 0;
}
