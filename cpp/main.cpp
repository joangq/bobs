#include <string>
#include <iostream>
#include "helpers.h"
#include "bobs.h"

using namespace std;

int parser(const std::string& s) {
    string left = s.substr(0, s.find(':'));
    int value = std::strtol(left.c_str(), nullptr, 10);
    return value;
}

int comparator(int a, int b) {
    return basicCompare(a, b);
}

bool validator(const string& s) {
    return s.length() > 0 and (iswalnum(s[0]) or s[0] == ':');
}

int main() {
    string inputFile = R"(test.bin)";
    int target = 1;

    string output = bobs(inputFile, target, parser, validator, comparator);
    cout << "Output: " << output << endl;

    return 0;
}
