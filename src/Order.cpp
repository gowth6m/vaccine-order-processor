/**
* File:         Order.cpp
*
* Description:  Represents an order made by a customer.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#include "Order.hpp"

/**
 * Constructor
 *
 * @param date: date of the order
 * @param type: type of order eg:N(normal) or X(express)
 * @param quantity: the amount of order
 */
Order::Order(Date *date, char type, int quantity) : date(date) {
    this->date = date;
    this->type = type;
    this->quantity = quantity;
}

/**
 * Destructor
 */
Order::~Order() = default;

/**
 * Getter for date
 *
 * @return date
 */
int Order::getDate() {
    return 0;
}

/**
 * Getter for quantity
 *
 * @return quantity
 */
int Order::getQuantity() {
    return 0;
}

/**
 * Getter for type
 *
 * @return type
 */
char Order::getType() {
    return 0;
}
