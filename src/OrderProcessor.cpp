//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#include <iostream>
#include <fstream>
#include "OrderProcessor.hpp"
#include "Customer.hpp"

using namespace std;

OrderProcessor::OrderProcessor(const char *filename) {
    this->lineNumber = 0;
    this->filename = filename;
}

void OrderProcessor::registerObserver(Observer *observer) {
    observers.push_back(observer);
}

void OrderProcessor::removeObserver(Observer *observer) {
    auto iterator = std::find(observers.begin(), observers.end(), observer);

    if (iterator != observers.end()) {
        observers.erase(iterator);
    }
}

void OrderProcessor::notifyObservers() {
    for (Observer *observer : observers) {
        observer->update();
    }
}

void OrderProcessor::processCustomerRecord(string line) {
    this->currentLine = line;
    this->typeOfRecord = 'C';
    this->lineNumber++;
    this->registerObserver(new Customer(*this, line));
    Customer* currentCustomer = dynamic_cast<Customer *>(this->observers.back());
    cout << "OP: customer " << setfill('0') << setw(4) << currentCustomer->getCustomerNumber() << " added\n";
}

void OrderProcessor::processSaleOrderRecord(string line) {
    this->currentLine = line;
    this->typeOfRecord = 'S';
    this->lineNumber++;
    notifyObservers();
    this->invoice++;
    Customer* currentCustomer = dynamic_cast<Customer *>(this->observers.back());

    if (this->currentOrderType == 'N') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomer->getCustomerNumber()
             << ": normal order: quantity " << this->currentOrderQuantity << std::endl;
    } else if (this->currentOrderType == 'X') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomer->getCustomerNumber()
             << ": EXPRESS order: quantity " << this->currentOrderQuantity << std::endl;
    }
}

void OrderProcessor::processEODRecord(string line) {
    this->currentLine = line;
    this->typeOfRecord = 'E';
    this->lineNumber++;
    notifyObservers();
}

// read file & check 0th char -> processOrder()
void OrderProcessor::processFile(const char *filename) {
    // read file -> update typeOfRecord -> check error -> OrderProcessesor(fileLine)
    ifstream inFile;
    string line;
    inFile.open(filename);
    int lineNumber;

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            getline(inFile, line);
            /* if C then turn line to Cus rec & add to vec */
            if (line.at(0) == 'C') {
                processCustomerRecord(line);

            } else if (line.at(0) == 'S') {
                processSaleOrderRecord(line);

            } else if (line.at(0) == 'E') {
                processEODRecord(line);
            } else {
                std::cerr << "Error in input file line " << lineNumber
                          << ", invalid line - doesn't start with C, S or E" << std::endl;
                inFile.close();
                exit(-1);
            }
        }
    } else {
        cerr << "Failed opening file: \"" << filename << "\". Error " << errno << ": " << std::strerror(errno) << endl;
        inFile.close();
        exit(-1);
    }
}


// Getters and Setters
int OrderProcessor::getLineNumber(){
    return this->lineNumber;
}

char OrderProcessor::getTypeOfRecord() {
    return this->typeOfRecord;
}

std::string OrderProcessor::getCurrentLine() {
    return this->currentLine;
}

int OrderProcessor::getInvoice(){
    return this->invoice;
}

void OrderProcessor::setCurrentOrderInfo(int date, char type, int quantity){
    this->currentOrderDate = date;
    this->currentOrderType = type;
    this->currentOrderQuantity = quantity;
}