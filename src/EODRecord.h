#ifndef __EODRECORD_H
#define __EODRECORD_H
#pragma once

#include "CustomerRecord.h"
#include <vector>

using std::vector;

class EODRecord {
private:
    int date;
public:
    explicit EODRecord(const string &);

    int getDate() const;
};


#endif