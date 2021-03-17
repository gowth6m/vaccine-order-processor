/**
* File:         Utilities.cpp
*
* Description:  Contains static utility functions with as error checks.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#include "Utilities.hpp"

/**
 * Function to extract a number from a string.
 *
 * @param line: string to extract from
 * @param pos: starting position in the string (inclusive)
 * @param len: the length from starting position
 * @param lineNo: the line number on input file (used for error processing
 * @return
 */
int Utilities::extractNumberFromString(const std::string &line, int pos, int len, int lineNo) {
    try {
        int customerNo = std::stoi(line.substr(pos, len));
        if (customerNo == 0) {
            std::cerr << "Error in input file line " << lineNo << ": invalid conversion of customer number of 0"
                      << std::endl;
            exit(-1);
        }
        return customerNo;
    }
    catch (std::invalid_argument &e) {
        // if no conversion could be performed
        std::cerr << "Error in input file line " << lineNo << ": invalid conversion of customer number to "
                  << &e << std::endl;
        exit(-1);
    }
    catch (std::out_of_range &e) {
        std::cerr << "Error in input file line " << lineNo
                  << ": Out of range during conversion "
                  << &e << std::endl;
        exit(-1);
    }
}

/**
 * Function to extract order type
 *
 * @param line: string to extract from
 * @param pos: position in the string (inclusive)
 * @param lineNo: the line number on input file (used for error processing
 * @return
 */
char Utilities::extractOrderType(const std::string &line, int pos, int lineNo) {
    if (line.at(pos) == 'N') {
        return 'N';
    } else if (line.at(pos) == 'X') {
        return 'X';
    } else {
        std::cerr << "Error in input file line "
                  << lineNo
                  << ": sales order type invalid"
                  << std::endl;
        exit(-1);
    }
}

/**
 * Function to check if the string length is correct for the input file.
 *
 * @param line: string to extract from
 * @param len: desired length of the string (inclusive)
 * @param lineNo: the line number on input file (used for error processing
 * @param recordType: the type of record to output in error message
 */
void Utilities::checkStringLen(const std::string &line, int len, int lineNo, std::string recordType, int lineCounter) {
    if(lineNo != lineCounter) {
        if (line.length() != len) {
            std::cerr << "Error in input file line "
                      << lineNo
                      << ": invalid line length for "
                      << recordType
                      << std::endl;
            exit(-1);
        }
    }
}

/**
 * Function to check if the last line has the correct length since it doesn't have '\n' or '\r'.
 *
 * @param line: the string for last line
 */
void Utilities::validateLastLine(std::string line) {
    if(line.at(0) == 'S' && line.length() != 17) {
        std::cerr << "Error in input file last line: invalid line length for Sales order record"
                  << std::endl;
        exit(-1);
    } else if(line.at(0) == 'E' && line.length() != 9) {
        std::cerr << "Error in input file last line: invalid line length for EOD record"
                  << std::endl;
        exit(-1);
    }
}

/**
 * Function to get the extension of a file
 *
 * @param fileName: file that you want to get the extension for
 * @return the extension of the file
 */
std::string Utilities::getFileExtension(const std::string &fileName) {
    if (fileName.find_last_of('.') != std::string::npos)
        return fileName.substr(fileName.find_last_of('.') + 1);
    return "";
}
