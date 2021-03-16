/**
* File:         Customer.hpp
*
* Description:  Represents a Customer of the order system, implements Observer interface.
*
* Author:       gowth6m
*
* Date:         10/03/2021
*/

#ifndef __CUSTOMER_HPP
#define __CUSTOMER_HPP

#include <string>
#include "Observer.hpp"
#include "OrderProcessor.hpp"
#include "Order.hpp"

class Customer : public Observer {

private:
    OrderProcessor &processor;         /** pointer to the OrderProcessor(Subject) */
    std::string customerName;          /** name of the customer */
    int customerNumber;                /** customer's unique number, can't be 0000 */
    int orderQuantity;                 /** the amount the customer ordered */
    std::vector<Order> listOfOrders;   /** vector holding all customer orders */

public:

    /**
     * Constructor
     */
    explicit Customer(OrderProcessor &, int, std::string);

    /**
     * Destructor
     */
    ~Customer();

    /**
     * This function is ran when notifyObserver function is called in OrderProcessor(Concrete Subject instance).
     */
    void update() override;

    /**
     * Function that runs when SaleOrder is read in the OrderProcessor.
     */
    void processSalesOrder();

    /**
     * Function to ship orders.
     */
    void shipOrders();

    /**
     * Getter for customerNumber
     */
    int getCustomerNumber() const;

    /**
     * Getter for orderQuantity
     */
    int getOrderQuantity() const;
};


#endif
