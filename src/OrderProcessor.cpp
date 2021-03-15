//
// Created by Gowtham Ravindrathas on 15/03/2021.
//

#include <iostream>
#include <fstream>
#include "OrderProcessor.hpp"
#include "Customer.hpp"
#include "Utilities.hpp"

using namespace std;

OrderProcessor::OrderProcessor(const char *filename) {
    this->lineNumber = 0;
    this->filename = filename;
    this->currentOrderTotal = 0;
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
    int customerNo = Utilities::extractNumberFromString(line, 1, 4, lineNumber);
    string customerName = line.substr(5, line.size() - 4);
    this->currentLine = line;
    this->typeOfRecord = 'C';
    this->lineNumber++;
    this->registerObserver(new Customer(*this, customerNo, customerName));
    Customer *currentCustomer = dynamic_cast<Customer *>(this->observers.back());
    cout << "OP: customer " << setfill('0') << setw(4) << currentCustomer->getCustomerNumber() << " added\n";
}

void OrderProcessor::processSaleOrderRecord(string line) {
    this->currentLine = line;
    this->typeOfRecord = 'S';
    this->lineNumber++;
    this->currentOrderDate = Utilities::extractNumberFromString(line, 1, 9, this->lineNumber);
    this->currentOrderType = line.at(9);
    this->currentOrderQuantity = Utilities::extractNumberFromString(line, 14, 3, this->lineNumber);
    this->currentCustomerNo = Utilities::extractNumberFromString(line, 10, 4, this->lineNumber);
    this->currentOrderTotal += currentOrderQuantity;

    if (currentOrderType == 'N') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
             << ": normal order: quantity " << currentOrderQuantity << std::endl;
        notifyObservers();
    } else if (currentOrderType == 'X') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
             << ": EXPRESS order: quantity " << currentOrderQuantity << std::endl;
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
             << ": shipped quantity " << currentOrderTotal << endl;
        notifyObservers();
        this->invoice++;
    }
}

void OrderProcessor::processEODRecord(string line) {
    this->currentLine = line;
    this->typeOfRecord = 'E';
    this->lineNumber++;
    this->currentEOD = Utilities::extractNumberFromString(line, 1, 8, lineNumber);
    cout << "OP: end of day " << this->currentEOD << "\n";
    for(auto &observer : observers) {
        if(dynamic_cast<Customer *>(observer)->getOrderQuantity() > 0) {
            cout << "OP: customer " << setfill('0') << setw(4)
                 << dynamic_cast<Customer *>(observer)->getCustomerNumber()
                 << ": shipped quantity " << dynamic_cast<Customer *>(observer)->getOrderQuantity() << endl;
            notifyObservers();
        }
    }

//    cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
//         << ": shipped quantity " << currentOrderTotal << endl;
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
int OrderProcessor::getLineNumber() {
    return this->lineNumber;
}

char OrderProcessor::getTypeOfRecord() {
    return this->typeOfRecord;
}

std::string OrderProcessor::getCurrentLine() {
    return this->currentLine;
}

int OrderProcessor::getInvoice() {
    return this->invoice;
}

int OrderProcessor::getCurrentOrderDate() {
    return this->currentOrderDate;
}

char OrderProcessor::getCurrentOrderType() {
    return this->currentOrderType;
}

int OrderProcessor::getCurrentOrderQuantity() {
    return this->currentOrderQuantity;
}

int OrderProcessor::getCurrentCustomerNo() {
    return this->currentCustomerNo;
}

int OrderProcessor::getCurrentOrderTotal() {
    return this->currentOrderTotal;
}

int OrderProcessor::getCurrentEOD() {
    return this->currentEOD;
}

void OrderProcessor::setCurrentOrderTotal(int total) {
    this->currentOrderTotal = total;
}