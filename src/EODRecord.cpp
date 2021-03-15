#include "EODRecord.h"

EODRecord::EODRecord(const string &EOD) {
    this->date = stoi(EOD.substr(1, 8));
}

int EODRecord::getDate() const {
    return this->date;
}


