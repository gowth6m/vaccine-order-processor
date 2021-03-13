#include "EODRecord.h"

EODRecord::EODRecord(string EOD)
{
    this->date = stoi(EOD.substr(1, 8));
}

int EODRecord::getDate()
{
    return this->date;
}


