#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    int lowerBound, upperBound, numOfNodes;
    char option;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-l") {
            lowerBound = std::stoi(argv[++i]);
        } else if (arg == "-u") {
            upperBound = std::stoi(argv[++i]);
        } else if (arg == "-e") {
            option = 'e';
        } else if (arg == "-r") {
            option = 'r';
        } else if (arg == "-n") {
            numOfNodes = std::stoi(argv[++i]);
        }
    }

    cout << lowerBound << endl;
    cout << upperBound << endl;
    cout << numOfNodes << endl;
    cout << option << endl;
}

