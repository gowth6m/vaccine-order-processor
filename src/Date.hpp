/**
* File:         Date.hpp
*
* Description:  Represents a date entity.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#ifndef __DATE_HPP
#define __DATE_HPP

#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>
#include "Utilities.hpp"

class Date {

private:
    int day;
    int month;
    int year;
    int all;             /* date in format of yyyyMMdd */
    int lineNo;          /* line in input file where this was found */

public:
    /**
     * Constructor
     */
    Date(std::string, int);

    /**
     * Destructor
     */
    ~Date();

    /**
     * Gets date from a record from the input file
     */
    static std::string getDateFromRecord(std::string, int);

    /**
     * Validates date if its within the limit for month and days.
     */
    void validateDate();

    /** Getter for date */
    int getDate();

};


#endif
