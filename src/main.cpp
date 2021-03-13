#include <iostream>
#include <fstream>
#include "Customer.h"
#include "EODRecord.h"
#include "SalesOrder.h"
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <utility>

using namespace std;

/* Check format fo the command line args */
void verifyCommandLineFormat(int argc)
{
	/* verify format of stdin from command line */
	if(argc != 2)
	{
		cerr << "Invalid format. The correct format is:\n./ordering <inputFile>\n";
		exit(-1);
	}
}

static int invoice = 1000;

void expressShip(vector<Customer>& customers, SalesOrder S) {
	for (auto & customer : customers) {
		if (customer.getCustomerNumber() == S.getCustomerNumber()) {
			cout << "OP: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": shipped quantity " << customer.getOrderQuantity() << endl;
			cout << "SC: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": invoice " << invoice++ << ": date " << S.getOrderDate() << ": quantity " << customer.getOrderQuantity() << endl;
			customer.setOrderQuantity(0);
		}
	}
}

void updateQuantity(vector<Customer> &customerRecord, SalesOrder s) {
	for (int i = 0; i < customerRecord.size(); i++) {
		if (customerRecord.at(i).getCustomerNumber() == s.getCustomerNumber()) {
			if (s.getOrderType() == 'N') {
				customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
				cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber() << ": normal order: quantity " << s.getOrderQuantity() << endl;
			}
			else {
				customerRecord.at(i).incrementQuantity(s.getOrderQuantity());
				cout << "OP: customer " << setfill('0') << setw(4) << s.getCustomerNumber() << ": EXPRESS order: quantity " << s.getOrderQuantity() << endl;
				expressShip(customerRecord, s);
			}
			return;
		}
	}
}

vector<int> canShip(vector<SalesOrder> salesOrderRec, EODRecord E) {
	vector<int> customerNumbers;
	for (auto & i : salesOrderRec) {
		if (i.getOrderDate() == E.getDate() && i.getOrderQuantity() != 0) {
			customerNumbers.push_back(i.getCustomerNumber());
			i.setOrderQuantity(0);
		}
	}
	return customerNumbers;
}

void removeDuplicates(vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}


void ship(vector<Customer>& customers, vector<SalesOrder> salesOrderRec, EODRecord eod ) {
	cout << "OP: end of day " << eod.getDate() << endl;
	vector<int> customerNumbers = canShip(std::move(salesOrderRec), eod);
	removeDuplicates(customerNumbers);
	if (customerNumbers.empty()) {
		return;
	}
	else {
		for (auto & customer : customers) {
			for (int customerNumber : customerNumbers) {
				if (customer.getCustomerNumber() == customerNumber && customer.getOrderQuantity() != 0 ) {
					cout << "OP: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": shipped quantity " << customer.getOrderQuantity() << endl;
					cout << "SC: customer " << setfill('0') << setw(4) << customer.getCustomerNumber() << ": invoice " << invoice++ << ": date " << eod.getDate() << ": quantity " << customer.getOrderQuantity() << endl;
					customer.setOrderQuantity(0);
				}
			}
		}
	}

}


void readFile(const char* filename, vector<Customer> &customerRecord, vector <SalesOrder> &salesOrderRecord, vector<EODRecord> &EODs) {
	ifstream infile;
	string line;
	infile.open(filename);
	if (infile.is_open()) {
		while (!infile.eof()) {
			getline(infile,line);
			if (line.at(0) == 'C') {
				Customer C(line);
				customerRecord.push_back(C);
				cout << "OP: Customer " << setfill('0') << setw(4) << C.getCustomerNumber() << " added\n";
                cout << "TEST >>>>>> :" << C.getCustomerName() << "\n";
            }
			else if (line.at(0) == 'S') {
				SalesOrder S(line);
				salesOrderRecord.push_back(S);
				updateQuantity(customerRecord, S);
			}
			else if (line.at(0) == 'E') {
				EODRecord E(line);
				EODs.push_back(E);
				ship(customerRecord, salesOrderRecord, E);
			}
		}
	}
	else {
		cerr << "Failed opening file: \"" << filename << "\". Error " << errno << ": " << std::strerror(errno) << endl;
		exit(-1);
	}
}

int main(int argc, char *argv[]) {
	/* check format fo the command line args */
    verifyCommandLineFormat(argc);
	/* create vectors for each record */
	vector<Customer> customerRecord;
	vector<SalesOrder> salesOrderRecord;
	vector<EODRecord> EODs;
	readFile(argv[1], customerRecord, salesOrderRecord, EODs);

	return 0;
}
