//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#ifndef VACCINEORDERSYSTEM_CUSTOMER_HPP
#define VACCINEORDERSYSTEM_CUSTOMER_HPP

#include <string>
#include "Observer.hpp"
#include "OrderProcessor.hpp"
#include "Order.hpp"

class Customer : public Observer {

private:
    OrderProcessor &processor;         /** pointer to the subject - OrderProcessor */
    bool errorInLine;                  /** boolean that tracks whether there is an error for this customer record */
    int lineNumber;                    /** number of the line being read from input file, used for error processing */
    std::string customerName;          /** name of the customer */
    int customerNumber;                /** customer's unique number, can't be 0000 */
    int orderQuantity;                 /** the amount the customer orders */
    std::vector<Order> listOfOrders;   /** vector holding all customer orders */

    // =========================
    /** Functions */
    int processCustomerNumber(const std::string &line, int startPos, int endPos) ;

    void addOrder(std::string saleOrderRecord);

public:
    /** Constructor */
    explicit Customer(OrderProcessor &processor, std::string line);

    /** Destructor */
    ~Customer();

    void update() override;

    // =========================


//    getter
    int getCustomerNumber();
};


#endif //VACCINEORDERSYSTEM_CUSTOMER_HPP
