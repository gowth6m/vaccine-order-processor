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
    int currentOrderDate;
    char currentOrderType;
    int currentOrderQuantity;

public:
    OrderProcessor(const char *filename);

    void registerObserver(Observer *observer) override;

    void removeObserver(Observer *observer) override;

    void notifyObservers() override;


    void processCustomerRecord(std::string line);

    void processSaleOrderRecord(std::string line);

    void processEODRecord(std::string line);

    void processFile(const char *filename);

    void processLine(std::string line);

    std::string getCurrentLine();

    char getTypeOfRecord();

    int getLineNumber();

    int getInvoice();

    void addOrder();

    void setCurrentOrderInfo(int, char, int);
};

#endif //VACCINEORDERSYSTEM_ORDERPROCESSOR_HPP
