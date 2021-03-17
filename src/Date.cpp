/**
* File:         Date.cpp
*
* Description:  Represents a date entity.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#include "Date.hpp"

/**
 * Constructor
 *
 * @param d: date as a string in the format "yyyyMMdd"
 * @param lineNo: the line from input file where this date was from
 */
Date::Date(std::string d, int lineNo) {
    this->day = Utilities::extractNumberFromString(d, 6, 2, this->lineNo);
    this->month = Utilities::extractNumberFromString(d, 4, 2, this->lineNo);
    this->year = Utilities::extractNumberFromString(d, 0, 4, this->lineNo);
    this->all = this->year * 10000 + this->month * 100 + this->day;
    this->lineNo = lineNo;
    validateDate();
}

/**
 * Destructor
 */
Date::~Date() = default;

/**
 * Validates date if its within the limit for month and days.
 */
void Date::validateDate() {
    if (day > 31 || day < 0 || month > 12 || month < 1) {
        std::cerr << "Error in input file line " << this->lineNo
                  << ": invalid date in record" << std::endl;
        exit(-1);
    }
}

/**
 * Gets date from a record from the input file
 *
 * @param line: the string of record
 * @param lineNumber: the number of the line in input file
 * @return the 8 char string for a date
 */
std::string Date::getDateFromRecord(std::string line, int lineNumber) {
    try {
        return line.substr(1, 8);
    } catch (std::out_of_range &exception) {
        std::cerr << "Error in input file line " << lineNumber
                  << ": invalid date in record"
                  << std::endl;
        exit(-1);
    }
}

/**
 * Getter for date
 */
int Date::getDate() {
    return this->all;
}

