#pragma once
#include "Customer.h"
#include <vector>
using std::vector;

class EODRecord {
private:
	int date;
public:
	EODRecord(string);
	int getDate();
};