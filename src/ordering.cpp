#include <iostream>
#include "CustomerRecord.h"
#include "EODRecord.h"
#include "SalesOrderRecord.h"
#include "OrderProcessor.h"
#include <algorithm>
#include <utility>

using namespace std;

/**
 * Function prototypes
 */
string getFileExtension(const string &fileName);

void verifyCommandLineFormat(int argc, char **argv);

void errorChecker(int err);

/**
 * The Main Function
 */
int main(int argc, char *argv[]) {
    /* check format fo the command line args */
    verifyCommandLineFormat(argc, argv);

    /* create vectors for each record */
    vector<CustomerRecord> customerRecord;
    vector<SalesOrderRecord> salesOrderRecord;
    vector<EODRecord> EODs;

    /* calls static function from OrderProcessor */
    OrderProcessor::processOrder(argv[1], customerRecord, salesOrderRecord, EODs);

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
 * Function that takes in error type and outputs the error to stderr
 *
 * @param errNo: the error number
 */
void errorChecker(int err) {
    if (err == -1) {
        // cerr << "Failed opening file: \"" << filename << "\". Error " << errno << ": " << std::strerror(errno) << endl;
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
    if (fileName.find_last_of(".") != std::string::npos)
        return fileName.substr(fileName.find_last_of(".") + 1);
    return "";
}