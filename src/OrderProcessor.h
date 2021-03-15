
#ifndef __ORDERMANGER_H
#define __ORDERMANGER_H

#include <iostream>
#include <fstream>
#include "CustomerRecord.h"
#include "EODRecord.h"
#include "SalesOrderRecord.h"
#include <cstring>
#include <iomanip>
#include <algorithm>

class OrderProcessor {

private:

public:
    static int invoice;

    static void errorChecker();

    static void expressShip(vector<CustomerRecord> &customers, SalesOrderRecord S);

    static void updateQuantity(vector<CustomerRecord> &customerRecord, SalesOrderRecord s);

    static vector<int> canShip(vector<SalesOrderRecord> salesOrderRec, EODRecord E);

    static void removeDuplicates(vector<int> &v);

    static void ship(vector<CustomerRecord> &customers, vector<SalesOrderRecord> salesOrderRec, EODRecord eod);

    static void processOrder(const char *filename, vector<CustomerRecord> &customerRecord, vector<SalesOrderRecord>
    &salesOrderRecord, vector<EODRecord> &EODs);
};


#endif
