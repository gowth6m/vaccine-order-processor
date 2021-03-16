//
// Created by Gowtham Ravindrathas on 15/03/2021.
//
#include <iostream>
#include <stdexcept>
#include "Utilities.hpp"

int Utilities::extractNumberFromString(const std::string &line, int startPos, int endPos, int lineNo) {
    try {
        int customerNo = std::stoi(line.substr(startPos, endPos));
        if(customerNo == 0) {
            std::cerr << "Error in input file line " << lineNo<< ": invalid conversion of customer number of 0000"
                      << std::endl;
            exit(-1);
        }
        return customerNo;
    }
    catch(std::invalid_argument &e){
        // if no conversion could be performed
        std::cerr << "Error in input file line " << lineNo << ": invalid conversion of customer number to "
                  << &e << std::endl;
        exit(-1);
    }
    catch(std::out_of_range &e){
        std::cerr << "Error in input file line " << lineNo << ": customer record: customer number out of range during conversion "
                  << &e << std::endl;
        exit(-1);
    }
}