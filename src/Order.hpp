/**
* File:         Order.hpp
*
* Description:  Represents an order made by a customer.
*
* Author:       gowth6m
*
* Date:         10/03/2021
*/

#ifndef __ORDER_HPP
#define __ORDER_HPP


#include <string>

class Order {

private:
    int date;       /** order date */
    int quantity;   /** order quantity */
    char type;      /** type of order */

public:
    /**
     * Constructor
     */
    Order(int date, char orderType, int quantity);

    /**
     * Destructor
     */
    ~Order();

    /**
     * Getter for date
     */
    int getDate();

    /**
     * Getter for quantity
     */
    int getQuantity();

    /**
     * Getter for type of order
     */
    char getType();

};


#endif
