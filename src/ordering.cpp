/**
* File:         ordering.cpp
*
* Description:  Starting point of this program.
*
* Author:       074038
*
* Date:         10/03/2021
*/

#include <algorithm>
#include <utility>
#include <iostream>
#include "OrderProcessor.hpp"

using namespace std;

/**
 * Function prototypes
 */
string getFileExtension(const string &fileName);
void verifyCommandLineFormat(int argc, char **argv);
void errCheck(int err, OrderProcessor p);

/**
 * The Main Function
 */
int main(int argc, char *argv[]) {
    verifyCommandLineFormat(argc, argv);
    OrderProcessor orderProcessor;
    errCheck(orderProcessor.processFile(argv[1]), orderProcessor);
    return EXIT_SUCCESS;
}

/**
 * Check format for the command line args
 *
 * @param argc: the number of arguments given in
 */
void verifyCommandLineFormat(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Invalid format. The correct format is:\n./ordering <inputFile>\n";
        exit(-1);
    }
    if (getFileExtension(argv[1]) != "txt") {
        cerr << "Invalid file type. Use a \".txt\" file\n";
        exit(-1);
    }
}

/**
 * Function to get the extension of a file
 *
 * @param fileName: file that you want to get the extension for
 * @return the extension of the file
 */
string getFileExtension(const string &fileName) {
    if (fileName.find_last_of('.') != std::string::npos)
        return fileName.substr(fileName.find_last_of('.') + 1);
    return "";
}

/**
 * Takes an error number and output correct error message.
 *
 * @param err: err number output from processFile function
 * @param p: OrderProcessor
 */
void errCheck(int err, OrderProcessor p){
    if(err == -1) {
        cerr << "Error in input file line " << p.getLineNumber()
             << ", invalid line - empty line detected" << endl;
        exit(-1);
    }
    if (err == -2) {
        cerr << "Error in input file line " << p.getLineNumber()
             << ", invalid line - doesn't start with C, S or E" << endl;
        exit(-1);
    }
    if (err == -3) {
        cerr << "Finished program successfully but last line of input file is empty" << endl;
        exit(-1);
    }
    if (err == -4) {
        cerr << "Failed opening file: \"" << p.getCurrentFile() << "\". Error " << errno << ": "
             << strerror(errno) << endl;
        exit(-1);
    }
}