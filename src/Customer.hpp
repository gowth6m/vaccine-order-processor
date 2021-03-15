//
// Created by Gowtham Ravindrathas on 15/03/2021.
//
#pragma once

#ifndef VACCINEORDERSYSTEM_CUSTOMER_HPP
#define VACCINEORDERSYSTEM_CUSTOMER_HPP

#include <string>
#include "Observer.hpp"
#include "OrderProcessor.hpp"
#include "Order.hpp"

class Customer : public Observer {

private:
    OrderProcessor &processor;         /** pointer to the subject - OrderProcessor */
    std::string customerName;          /** name of the customer */
    int customerNumber;                /** customer's unique number, can't be 0000 */
    int orderQuantity;                 /** the amount the customer orders */
    std::vector<Order> listOfOrders;   /** vector holding all customer orders */

    // ========================

public:
    /** Constructor */
    explicit Customer(OrderProcessor &processor, int, std::string);

    /** Destructor */
    ~Customer();

    void update() override;

    int getCustomerNumber();

    int getOrderQuantity();

    void processSalesOrder(std::string basicString);

    void shipOrders();
};


#endif //VACCINEORDERSYSTEM_CUSTOMER_HPP
