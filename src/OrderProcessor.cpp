#include "OrderProcessor.h"

using namespace std;

int OrderProcessor::invoice = 1000;


void OrderProcessor::expressShip(vector<CustomerRecord> &customers, SalesOrderRecord S) {
    for (auto &customer : customers) {
        if (customer.getCustomerNumber() == S.getCustomerNumber()) {
            cout << "OP: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": shipped quantity "
                 << customer.getOrderQuantity() << endl;
            cout << "SC: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": invoice "
                 << invoice++ << ": date " << S.getOrderDate() << ": quantity " << customer.getOrderQuantity() << endl;
            customer.setOrderQuantity(0);
        }
    }
}

void OrderProcessor::updateQuantity(vector<CustomerRecord> &customerRecord, SalesOrderRecord s) {
    for (int i = 0; i < customerRecord.size(); i++) {
        if (customerRecord.at(i).getCustomerNumber() == s.getCustomerNumber()) {
            if (s.getOrderType() == 'N') {
                customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
                cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber()
                     << ": normal order: quantity " << s.getOrderQuantity() << endl;
            } else {
                customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
                cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber()
                     << ": EXPRESS order: quantity " << s.getOrderQuantity() << endl;
                expressShip(customerRecord, s);
            }
            return;
        }
    }
}

vector<int> OrderProcessor::canShip(vector<SalesOrderRecord> salesOrderRec, EODRecord E) {
    vector<int> customerNumbers;
    for (auto &i : salesOrderRec) {
        if (i.getOrderDate() == E.getDate() && i.getOrderQuantity() != 0) {
            customerNumbers.push_back(i.getCustomerNumber());
            i.setOrderQuantity(0);
        }
    }
    return customerNumbers;
}

void OrderProcessor::removeDuplicates(vector<int> &v) {
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}

void OrderProcessor::ship(vector<CustomerRecord> &customers, vector<SalesOrderRecord> salesOrderRec, EODRecord eod) {
    cout << "OP: end of day " << eod.getDate() << endl;
    vector<int> customerNumbers = canShip(std::move(salesOrderRec), eod);
    removeDuplicates(customerNumbers);
    if (customerNumbers.empty()) {
        return;
    } else {
        for (auto &customer : customers) {
            for (int customerNumber : customerNumbers) {
                if (customer.getCustomerNumber() == customerNumber && customer.getOrderQuantity() != 0) {
                    cout << "OP: customer " << setfill('0') << setw(4) << customer.getCustomerNumber()
                         << ": shipped quantity " << customer.getOrderQuantity() << endl;
                    cout << "SC: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": invoice "
                         << invoice++ << ": date " << eod.getDate() << ": quantity " << customer.getOrderQuantity()
                         << endl;
                    customer.setOrderQuantity(0);
                }
            }
        }
    }
}


void
OrderProcessor::processOrder(const char *filename, vector<CustomerRecord> &customerRecords, vector<SalesOrderRecord>
&salesOrderRecords, vector<EODRecord> &EODs) {

    ifstream inFile;
    string line;
    inFile.open(filename);
    int lineNumber;

    if (inFile.is_open()) {
        while (!inFile.eof()) {
//            cout << lineNumber << "\n";
            getline(inFile, line);

            /* if C then turn line to Cus rec & add to vec */
            if (line.at(0) == 'C') {
                CustomerRecord customerRecord(line, lineNumber);
                customerRecords.push_back(customerRecord);
                cout << "OP: CustomerRecord " << setfill('0') << setw(4) << customerRecord.getCustomerNumber() << " added\n";
                lineNumber++;

                /* if S then turn line to SO rec & add to vec */
            } else if (line.at(0) == 'S') {
                SalesOrderRecord salesOrderRecord(line, lineNumber);
                // check & compare if cusID in cus records
                salesOrderRecords.push_back(salesOrderRecord);
                updateQuantity(customerRecords, salesOrderRecord);
                lineNumber++;

                /* if E then turn line to EOD rec & add to vec */
            } else if (line.at(0) == 'E') {
                EODRecord E(line);
                EODs.push_back(E);
                ship(customerRecords, salesOrderRecords, E);
                lineNumber++;

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
