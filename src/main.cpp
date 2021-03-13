#include <iostream>
#include <fstream>
#include "Customer.h"
#include "EODRecord.h"
#include "SalesOrder.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

/* Check format fo the command line args */
void verifyCommandLineFormat(int argc, char **argv)
{
	/* verify format of stdin from command line */
	if(argc != 2)
	{	
		cerr << "Invalid format. The correcct format is:\n./ordering <inputFile>\n";
		// fprintf(stderr, "Invalid format. The correcct format is:\n./ordering <inputFile>\n");
		exit(-1);
	}
}

static int invoice = 1000;

void expressShip(vector<Customer>& customers, SalesOrder S) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers.at(i).getCustomerNumber() == S.getCustomerNumber()) {
			cout << "OP: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": shipped quantity " << customers.at(i).getOrderQuantity() << endl;
			cout << "SC: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": invoice " << invoice++ << ": date " << S.getOrderDate() << ": quantity " << customers.at(i).getOrderQuantity() << endl;
			customers.at(i).setOrderQuantity(0);
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
	for (int i = 0; i < salesOrderRec.size(); i++) {
		if (salesOrderRec.at(i).getOrderDate() == E.getDate() && salesOrderRec.at(i).getOrderQuantity() != 0) {
			customerNumbers.push_back(salesOrderRec.at(i).getCustomerNumber());
			salesOrderRec.at(i).setOrderQuantity(0);
		}
	}
	return customerNumbers;
}

void removeDuplicates(vector<int>& v)
{
	vector<int>::iterator end = v.end();
	for (vector<int>::iterator it = v.begin(); it != end; ++it) {
		end = remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}


void ship(vector<Customer>& customers, vector<SalesOrder> salesOrderRec, EODRecord eod ) {
	cout << "OP: end of day " << eod.getDate() << endl;
	vector<int> customerNumbers = canShip(salesOrderRec, eod);
	removeDuplicates(customerNumbers);
	if (customerNumbers.size() == 0) {
		return;
	}
	else {
		for (int i = 0; i < customers.size(); i++) {
			for (int j = 0; j < customerNumbers.size(); j++) {
				if (customers.at(i).getCustomerNumber() == customerNumbers.at(j) && customers.at(i).getOrderQuantity() != 0 ) {
					cout << "OP: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": shipped quantity " << customers.at(i).getOrderQuantity() << endl;
					cout << "SC: customer " << setfill('0') << setw(4) << customers.at(i).getCustomerNumber() << ": invoice " << invoice++ << ": date " << eod.getDate() << ": quantity " << customers.at(i).getOrderQuantity() << endl;
					customers.at(i).setOrderQuantity(0);
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
		cerr << "Failed opening file: " << filename << ". Error " << errno << ": " << strerror(errno);
		exit(-1);
	}
}

int main(int argc, char *argv[]) {

	/* check format fo the command line args */
	verifyCommandLineFormat(argc, argv);
	/* create vectors for each record */
	vector<Customer> customerRecord;
	vector<SalesOrder> salesOrderRecord;
	vector<EODRecord> EODs;
	readFile(argv[1], customerRecord, salesOrderRecord, EODs);

	return 0;
}
