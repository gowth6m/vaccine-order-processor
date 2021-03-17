/**
* File:         Utilities.hpp
*
* Description:  Contains static utility functions with as error checks.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#ifndef __UTILITIES_HPP
#define __UTILITIES_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class Utilities {

public:
    /**
     * Function to extract a number from a string.
     */
    static int extractNumberFromString(const std::string &, int, int, int);

    /**
     * Function to extract order type from input file line.
     */
    static char extractOrderType(const std::string &, int, int);

    /**
     * Function to check if the string length is correct for the input file.
     */
    static void checkStringLen(const std::string &, int, int, std::string, int);

    /**
     * Function to check if the last line has the correct length since it doesn't have '\n' or '\r'.
     */
    static void validateLastLine(std::string);

    /**
     * Function to get the extension of the input file.
     */
    static std::string getFileExtension(const std::string &);
};


#endif
