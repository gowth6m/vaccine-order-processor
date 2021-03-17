/**
* File:         OrderProcessor.hpp
*
* Description:  Represents the OrderProcessing entity, implements Subject interface.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#ifndef __ORDERPROCESSOR_HPP
#define __ORDERPROCESSOR_HPP

#include <vector>
#include <cerrno>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Subject.hpp"
#include "Utilities.hpp"
#include "Date.hpp"

using namespace std;

class OrderProcessor : public Subject {

private:
    std::vector<Observer *> observers;   /** vector of observers registered to an instance of orderProcessor */
    std::vector<Date *> endOfDates;      /** vector of dates of End of dates records */
    std::vector<Date *> orderDates;      /** vector of dates of Sale order dates */
    std::string currentFile;             /** name of the current file */
    int lineNumber = 1;                  /** line number of the input file - used for error output */
    int currentOrderTotal = 0;           /** current order total of the customer being processed */
    int invoice = 1000;                  /** invoice for customers when order shipped, starting from 1000 */
    char typeOfRecord{};                 /** type of record read by the for the line in input file */
    char currentOrderType{};             /** type for current sales order - eg:normal or express */
    int currentOrderQuantity{};          /** current order quantity of the customer being processed */
    int currentCustomerNo{};             /** currently being processed unique customer number */
    int currentEODCustomer{};            /** currently being processed customer number for EOD function */

public:
    /**
     * Constructor
     */
    OrderProcessor();

    /**
     * Destructor
     */
    ~OrderProcessor();

    /**
     * Registers observer by adding to vectors of observers.
     * (From Subject interface)
     */
    void registerObserver(Observer *) override;

    /**
     * Unregisters observer by removing from vector. Called in Observer's destructor.
     * (From Subject interface)
     */
    void removeObserver(Observer *) override;

    /**
     * Notifies all observers registered to this concrete subject hence their update function is ran.
     * (From Subject interface)
     */
    void notifyObservers() override;

    /**
     * Validates if the customer number already registered, else it's invalid.
     */
    void validateCustomerNo(int);

    /**
     * Checks if the date passed in has already passed the EOD date.
     */
    void validateOrderDate(int);

    /**
     * Increase the invoice number by 1
     */
    void incrementInvoice();

    /**
     * Processes a customer record read by the order processor.
     */
    void processCustomerRecord(const std::string &);

    /**
     * Processes a sales order record read by the order processor.
     */
    void processSaleOrderRecord(const std::string &);

    /**
     * Processes a end of day record read by the order processor.
     */
    void processEODRecord(const std::string &);

    /**
     * This function deals with the read file by checking the first character of each line.
     */
    int processFile(const char *);

    /** Getters and Setters: used by observers to see states of the subject **/

    /** Setter for currentOrderTotal */
    void setCurrentOrderTotal(int);

    /** Getter for typeOfRecord */
    char getTypeOfRecord();

    /** Getter for lineNumber */
    int getLineNumber();

    /** Getter for invoice */
    int getInvoice();

    /** Getter for currentOrderDate */
    Date *getCurrentOrderDate();

    /** Getter for currentOrderType */
    char getCurrentOrderType();

    /** Getter for currentOrderQuantity */
    int getCurrentOrderQuantity();

    /** Getter for currentCustomerNo */
    int getCurrentCustomerNo();

    /** Getter for currentEODCustomer */
    int getCurrentEODCustomer();

    /** Getter for currentFile */
    std::string getCurrentFile();
};

#endif
