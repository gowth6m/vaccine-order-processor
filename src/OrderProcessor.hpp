//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#ifndef VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP
#define VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP

#include <vector>
#include <cerrno>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Subject.hpp"
#include "Utilities.hpp"

using namespace std;

class OrderProcessor : public Subject {

private:
    std::vector<Observer *> observers;
    std::string currentLine;
    int lineNumber = 0;
    int currentOrderTotal = 0;
    int invoice = 1000;
    char typeOfRecord{};
    int currentEOD{};
    int currentOrderDate{};
    char currentOrderType{};
    int currentOrderQuantity{};
    int currentCustomerNo{};
    int currentEODCustomer{};

public:
    OrderProcessor();

    ~OrderProcessor();

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notifyObservers() override;

    void processCustomerRecord(const std::string& line);

    void processSaleOrderRecord(const std::string& line);

    void processEODRecord(const std::string& line);

    void processFile(const char *filename);

    void incrementInvoice();

    char getTypeOfRecord();

    int getLineNumber();

    int getInvoice();

    int getCurrentOrderDate();

    char getCurrentOrderType();

    int getCurrentOrderQuantity();

    int getCurrentCustomerNo();

    int getCurrentEODCustomer();

    void setCurrentOrderTotal(int);
};

#endif //VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP
