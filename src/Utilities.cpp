#include "Utilities.h"

bool Utilities::checkNumber(const string& str) {
    for (char i : str) {
        if (isdigit(i) == false) return false;
    }
    return true;
}

string Utilities::extractNameFromLine(std::string const& s) {
    std::string::size_type pos = s.find('\n');
    if (pos != std::string::npos)
    {
        return s.substr(0, pos);
    }
    else
    {
        return s;
    }
}
