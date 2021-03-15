//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#ifndef VACCINEORDERSYSTEM_ORDER_HPP
#define VACCINEORDERSYSTEM_ORDER_HPP


#include <string>

class Order {

private:
    int date;
    int quantity;
    char type;

public:
    Order(int date, char orderType, int quantity);

    int getDate();

    int getQuantity();

    char getType();

};


#endif //VACCINEORDERSYSTEM_ORDER_HPP
