
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

/**
 * The Main Function
 */
int main(int argc, char *argv[]) {
    verifyCommandLineFormat(argc, argv);
    OrderProcessor orderProcessor;
    orderProcessor.processFile(argv[1]);
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