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
    int lineNumber;
    char typeOfRecord{};
    int invoice = 1000;
    int currentEOD{};
    int currentOrderDate{};
    char currentOrderType{};
    int currentOrderQuantity{};
    int currentCustomerNo{};
    int currentOrderTotal;
    int currentEODCustomer{};

public:
    OrderProcessor();

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notifyObservers() override;

    void processCustomerRecord(const std::string& line);

    void processSaleOrderRecord(std::string line);

    void processEODRecord(const std::string& line);

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
