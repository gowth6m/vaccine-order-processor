/**
* File:         OrderProcessor.cpp
*
* Description:  Represents the OrderProcessing entity, implements Subject interface.
*
* Author:       gowth6m
*
* Date:         10/03/2021
*/

#include "OrderProcessor.hpp"
#include "Customer.hpp"

/* using std as a lot of std functions are used */
using namespace std;

/**
 * Constructor
 */
OrderProcessor::OrderProcessor() = default;

/**
 * Destructor
 */
OrderProcessor::~OrderProcessor() = default;

/**
 * Registers observer by adding to vectors of observers.
 *
 * @param observer: pointer to a concrete observer, eg:Customer
 */
void OrderProcessor::registerObserver(Observer *observer) {
    observers.push_back(observer);
}

/**
 * Unregisters observer by removing from vector. Called in Observer's destructor.
 *
 * @param observer: pointer to a concrete observer, eg:Customer
 */
void OrderProcessor::removeObserver(Observer *observer) {
    auto iterator = find(observers.begin(), observers.end(), observer);

    if (iterator != observers.end()) {
        observers.erase(iterator);
    }
}

/**
 * Notifies all observers registered to this concrete subject hence their update
 * function is ran.
 */
void OrderProcessor::notifyObservers() {
    for (Observer *observer : observers) {
        observer->update();
    }
}

/**
 * Increase the invoice number by 1
 */
void OrderProcessor::incrementInvoice() {
    this->invoice++;
}

/**
 * Processes a customer record read by the order processor.
 * Changes states of this class instance depending info read in the line of string.
 * Changes typeOfRecord to 'C' = Customer Record
 *
 * @param line: takes address of the string line being read
 */
void OrderProcessor::processCustomerRecord(const string& line) {
    int customerNo = Utilities::extractNumberFromString(line, 1, 4, lineNumber);
    string customerName = line.substr(5, line.size() - 4);
    this->currentLine = line;
    this->typeOfRecord = 'C';
    this->lineNumber++;
    this->registerObserver(new Customer(*this, customerNo, customerName));
    auto *currentCustomer = dynamic_cast<Customer *>(this->observers.back());
    cout << "OP: customer " << setfill('0') << setw(4)
              << currentCustomer->getCustomerNumber() << " added\n";
}

/**
 * Processes a sales order record read by the order processor.
 * Changes states of this class instance depending info read in the line of string.
 * Changes typeOfRecord to 'S' = Sales Order Record
 *
 * @param line: takes address of the string line being read
 */
void OrderProcessor::processSaleOrderRecord(const string& line) {
    this->currentLine = line;
    this->typeOfRecord = 'S';
    this->lineNumber++;
    this->currentOrderDate = Utilities::extractNumberFromString(line, 1, 9, this->lineNumber);
    this->currentOrderType = line.at(9);
    this->currentOrderQuantity = Utilities::extractNumberFromString(line, 14, 3, this->lineNumber);
    this->currentCustomerNo = Utilities::extractNumberFromString(line, 10, 4, this->lineNumber);
    for (auto &observer : observers) {
        if (dynamic_cast<Customer *>(observer)->getCustomerNumber() == this->currentCustomerNo) {
            this->currentOrderTotal =
                    dynamic_cast<Customer *>(observer)->getOrderQuantity() + this->currentOrderQuantity;
        }
    }
    if (currentOrderType == 'N') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
                  << ": normal order: quantity " << currentOrderQuantity << "\n";
        notifyObservers();
    } else if (currentOrderType == 'X') {
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
                  << ": EXPRESS order: quantity " << currentOrderQuantity << "\n";
        cout << "OP: customer " << setfill('0') << setw(4) << currentCustomerNo
                  << ": shipped quantity " << currentOrderTotal << "\n";
        notifyObservers();
    }
}

/**
 * Processes a end of day record read by the order processor.
 * Changes states of this class instance depending info read in the line of string.
 * Changes typeOfRecord to 'E' = End of Day Record
 *
 * @param line: takes address of the string line being read
 */
void OrderProcessor::processEODRecord(const string& line) {
    this->currentLine = line;
    this->typeOfRecord = 'E';
    this->lineNumber++;
    this->currentEOD = Utilities::extractNumberFromString(line, 1, 8, lineNumber);
    cout << "OP: end of day " << this->currentEOD << "\n";
    for (auto &observer : observers) {
        if (dynamic_cast<Customer *>(observer)->getOrderQuantity() > 0) {
            this->currentEODCustomer = dynamic_cast<Customer *>(observer)->getCustomerNumber();
            cout << "OP: customer " << setfill('0') << setw(4)
                 << dynamic_cast<Customer *>(observer)->getCustomerNumber()
                 << ": shipped quantity " << dynamic_cast<Customer *>(observer)->getOrderQuantity() << endl;
            notifyObservers();
        }
    }
}

/**
 * This function deals with the read file by checking the first character of each line.
 *
 * @param filename: pointer of the file
 */
void OrderProcessor::processFile(const char *filename) {
    ifstream inFile;
    string line;
    inFile.open(filename);

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            getline(inFile, line);
                /* C = process customer record */
            if (line.at(0) == 'C') {
                processCustomerRecord(line);
                /* S = process sales order record */
            } else if (line.at(0) == 'S') {
                processSaleOrderRecord(line);
                /* E = process end of day record */
            } else if (line.at(0) == 'E') {
                processEODRecord(line);
                /* Not a valid starting char so out this message */
            } else {
                cerr << "Error in input file line " << this->lineNumber
                          << ", invalid line - doesn't start with C, S or E" << endl;
                inFile.close();
                exit(-1);
            }
        }
    } else {
        /* unable to open the file error message */
        cerr << "Failed opening file: \"" << filename << "\". Error " << errno << ": "
                  << strerror(errno) << endl;
        inFile.close();
        exit(-1);
    }
    inFile.close();
}

/** Getters and Setters: used by observers to see states of the subject **/

/**
 * Setter for currentOrderTotal
 *
 * @param total: current total of the customer being processed
 */
void OrderProcessor::setCurrentOrderTotal(int total) {
    this->currentOrderTotal = total;
}

/**
 * Getter for lineNumber
 *
 * @return lineNumber
 */
int OrderProcessor::getLineNumber() {
    return this->lineNumber;
}

/**
 * Getter for typeOfRecord
 *
 * @return typeOfRecord
 */
char OrderProcessor::getTypeOfRecord() {
    return this->typeOfRecord;
}

/**
 * Getter for invoice
 *
 * @return invoice
 */
int OrderProcessor::getInvoice() {
    return this->invoice;
}

/**
 * Getter for currentOrderDate
 *
 * @return currentOrderDate
 */
int OrderProcessor::getCurrentOrderDate() {
    return this->currentOrderDate;
}

/**
 * Getter for currentOrderType
 *
 * @return currentOrderType
 */
char OrderProcessor::getCurrentOrderType() {
    return this->currentOrderType;
}

/**
 * Getter for currentOrderQuantity
 *
 * @return currentOrderQuantity
 */
int OrderProcessor::getCurrentOrderQuantity() {
    return this->currentOrderQuantity;
}

/**
 * Getter for currentCustomerNo
 *
 * @return currentCustomerNo
 */
int OrderProcessor::getCurrentCustomerNo() {
    return this->currentCustomerNo;
}

/**
 * Getter for currentEODCustomer
 *
 * @return currentEODCustomer
 */
int OrderProcessor::getCurrentEODCustomer() {
    return this->currentEODCustomer;
}
