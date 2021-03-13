/*
* File:			customerQueue.h
* Description:
* Author: 		gowth6m
* Date:
*/

#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <string>

using std::string;

class Utilities {

public:
    static bool checkNumber(const string &str);

    static string extractNameFromLine(const string &s);
};

#endif