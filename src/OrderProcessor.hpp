//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#ifndef VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP
#define VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP

#include <vector>
#include "Subject.hpp"
//#include "Customer.hpp"

class OrderProcessor : public Subject {

private:
    std::vector<Observer *> observers;
    std::string currentLine;
    int lineNumber;
    char typeOfRecord;
    const char *filename;
    int invoice = 1000;
    int currentEOD;
    int currentOrderDate;
    char currentOrderType;
    int currentOrderQuantity;
    int currentCustomerNo;
    int currentOrderTotal;
    int currentEODCustomer;

public:
    OrderProcessor(const char *filename);

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notifyObservers() override;

    void processCustomerRecord(std::string line);

    void processSaleOrderRecord(std::string line);

    void processEODRecord(std::string line);

    void processFile(const char *filename);

    void incrementInvoice();

//    void processLine(std::string line);

    std::string getCurrentLine();

    char getTypeOfRecord();

    int getLineNumber();

    int getInvoice();

    int getCurrentOrderDate();

    char getCurrentOrderType();

    int getCurrentOrderQuantity();

    int getCurrentCustomerNo();

    int getCurrentOrderTotal();

    int getCurrentEOD();

    int getCurrentEODCustomer();

    void setCurrentOrderTotal(int);
};

#endif //VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP
