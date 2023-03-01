#pragma once
#include "definitions.h"

using namespace std;

template<typename T>
int basicCompare(T x, T y) {
    return x == y ? 0 : x < y ? -1 : 1;
};

string readLine(ifstream& file, int index);

tuple<string, int> completeString(ifstream& file, int index, int maxSize, validatorFunction validate);
