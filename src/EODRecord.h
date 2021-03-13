/*
* File:
* Description:
* Author: 		gowth6m
* Date:
*/

#ifndef __EODRECORD_H
#define __EODRECORD_H
#pragma once
#include "Customer.h"
#include <vector>

using std::vector;

class EODRecord {
private:
	int date;
public:
	explicit EODRecord(const string&);
	int getDate() const;
};


#endif