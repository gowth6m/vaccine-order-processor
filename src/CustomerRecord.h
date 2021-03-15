#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#pragma once

#include <string>

using std::string;

class CustomerRecord {

private:
    bool errorInLine;      /** boolean that tracks whether there is an error for this customer record */
    int lineNumber;        /** number of the line being read from input file, used for error processing */
    string customerName;   /** name of the customer */
    int customerNumber;    /** customer's unique number, can't be 0000 */
    int orderQuantity;     /** the amount the customer orders */

    /**
     * Function that checks if customer number in the line from input file is valid.
     *
     * @param line: line of record from input file
     * @return the customer number
     */
    int processCustomerNumber(const string &line);

public:
    /**
     * Constructor
     *
     * A parameterized constructor for the customer. A line read from file and passed to the constructor that is parsed
     * and stored in each variable of customer.
     *
     * @param customer: a customer record line from input file
     * */
    explicit CustomerRecord(const string &, int);

    /**
     * Destructor
     */
    ~CustomerRecord();

    /**
     * Function to add more to existing quantity
     *
     * @param quantity: the amount you want the quantity to increase
     */
    void incrementQuantity(int);

    /**
     * Setter for orderQuantity
     *
     * @param quantity: initial order quantity that you would like to set for a customer
     */
    void setOrderQuantity(int);

    /**
     * Getter for errorInLine
     *
     * @return true if there is an error in read line
     */
    bool isErrorInLine() const;

    /**
     * Getter for customerName
     *
     * @return name of the customer
     */
    string getCustomerName();

    /**
     * Getter for customerName
     *
     * @return customer number
     */
    int getCustomerNumber() const;

    /**
     * Getter for orderQuality
     *
     * @return order quantity
     */
    int getOrderQuantity() const;

};


#endif