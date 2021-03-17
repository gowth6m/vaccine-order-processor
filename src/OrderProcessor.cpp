/**
* File:         OrderProcessor.cpp
*
* Description:  Represents the OrderProcessing entity, implements Subject interface.
*
* Author:       074038
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
 * Validates if the customer number is already registered, else it's invalid and
 * outputs error message.
 *
 * @param customerNo: customer number
 */
void OrderProcessor::validateCustomerNo(int customerNo) {
    bool exist = false;
    for (auto observer : observers) {
        if (customerNo == dynamic_cast<Customer *>(observer)->getCustomerNumber()) {
            exist = true;
        }
    }
    if (!exist) {
        std::cerr << "Error in input file line " << this->lineNumber
                  << ": unregistered customer number found: "
                  << customerNo << std::endl;
        exit(-1);
    }
}

/**
 * Checks if the date passed in has already passed the EOD date.
 *
 * @param date: the date wanting to be validated
 */
void OrderProcessor::validateOrderDate(int date) {
    if (!this->endOfDates.empty()) {
        if (date <= this->endOfDates.back()->getDate()) {
            std::cerr << "Error in input file line " << this->lineNumber
                      << ": invalid date in record" << std::endl;
            exit(-1);
        }
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
void OrderProcessor::processCustomerRecord(const string &line) {
    int customerNo = Utilities::extractNumberFromString(line, 1, 4, lineNumber);
    string customerName = line.substr(5, line.size() - 4);
    this->typeOfRecord = 'C';
    this->registerObserver(new Customer(*this, customerNo, customerName));
    auto *currentCustomer = dynamic_cast<Customer *>(this->observers.back());
    cout << "OP: customer " << setfill('0') << setw(4)
         << currentCustomer->getCustomerNumber() << " added\n";
    this->lineNumber++;
}

/**
 * Processes a sales order record read by the order processor.
 * Changes states of this class instance depending info read in the line of string.
 * Changes typeOfRecord to 'S' = Sales Order Record
 *
 * @param line: takes address of the string line being read
 */
void OrderProcessor::processSaleOrderRecord(const string &line) {

    /* checking if length of line is valid for sales order */
    Utilities::checkStringLen(line, 18, this->lineNumber, "Sales order record");

    this->typeOfRecord = 'S';
    this->orderDates.push_back(new Date(Date::getDateFromRecord(line, this->lineNumber), this->lineNumber));
    this->currentOrderType = Utilities::extractOrderType(line, 9, this->lineNumber);
    this->currentOrderQuantity = Utilities::extractNumberFromString(line, 14, 3, this->lineNumber);
    this->currentCustomerNo = Utilities::extractNumberFromString(line, 10, 4, this->lineNumber);

    /* validates if customer number read is first registered from customer record */
    validateCustomerNo(this->currentCustomerNo);
    /* validates if date hasn't surpassed recent EOD date */
    validateOrderDate(this->orderDates.back()->getDate());

    /* updating current total for the processing customer */
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
    this->lineNumber++;
}

/**
 * Processes a end of day record read by the order processor.
 * Changes states of this class instance depending info read in the line of string.
 * Changes typeOfRecord to 'E' = End of Day Record
 *
 * @param line: takes address of the string line being read
 */
void OrderProcessor::processEODRecord(const string &line) {

    /* checking if length of line is valid for eod record */
    Utilities::checkStringLen(line, 10, this->lineNumber, "EOD record");

    this->typeOfRecord = 'E';
    std::string temp = Date::getDateFromRecord(line, this->lineNumber);
    this->endOfDates.push_back(new Date(temp, this->lineNumber));

    cout << "OP: end of day " << this->endOfDates.back()->getDate() << "\n";
    for (auto &observer : observers) {
        if (dynamic_cast<Customer *>(observer)->getOrderQuantity() > 0) {
            this->currentEODCustomer = dynamic_cast<Customer *>(observer)->getCustomerNumber();
            cout << "OP: customer " << setfill('0') << setw(4)
                 << dynamic_cast<Customer *>(observer)->getCustomerNumber()
                 << ": shipped quantity " << dynamic_cast<Customer *>(observer)->getOrderQuantity() << endl;
            notifyObservers();
        }
    }
    this->lineNumber++;
}

/**
 * This function deals with the read file by checking the first character of each line.
 *
 * @param filename: pointer of the file
 */
int OrderProcessor::processFile(const char *filename) {

    this->currentFile = filename;
    ifstream inFile;
    string line;
    inFile.open(filename);

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            try {
                getline(inFile, line);
                if (line.at(0) == 'C') {                /* C = process customer record */
                    processCustomerRecord(line);
                } else if (line.at(0) == 'S') {         /* S = process sales order record */
                    processSaleOrderRecord(line);
                } else if (line.at(0) == 'E') {         /* E = process end of day record */
                    processEODRecord(line);
                } else if (line.length() <= 1) {
                    inFile.close();
                    return -1;                             /* -1: Empty line error with '\n' */
                } else {
                    inFile.close();
                    return -2;                             /* -2: Not a valid starting char */
                }
            } catch (out_of_range &e) {
                inFile.close();
                return -3;                                 /* -3: Last line is empty */
            }
        }
        Utilities::validateLastLine(line);
    } else {
        inFile.close();
        return -4;                                         /* -4: Invalid starting char */
    }
    inFile.close();
    return 0;
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
Date *OrderProcessor::getCurrentOrderDate() {
    return this->orderDates.back();
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

/**
 * Getter for currentFile
 *
 * @return currentFile
 */
std::string OrderProcessor::getCurrentFile() {
    return this->currentFile;
}
