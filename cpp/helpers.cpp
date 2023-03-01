#include "definitions.h"
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

string readLine(ifstream& file, int index) {
    file.seekg(index, ifstream::beg);
    string line;
    getline(file, line);
    return line;
}

tuple<string, int> completeString(ifstream& file, int index, int maxSize, validatorFunction validate) {
    int offset = 0;
    int boundaryIndex = index + offset;
    string line = readLine(file, index);

    while (boundaryIndex > 0 && validate(line)) {
        offset--;
        boundaryIndex = index + offset;
        line = readLine(file, boundaryIndex);
    }

    while (boundaryIndex < maxSize && !validate(line)) {
        offset++;
        boundaryIndex = index + offset;
        line = readLine(file, boundaryIndex);
    }

    return make_tuple(line, boundaryIndex);
}