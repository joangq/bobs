#pragma once
#include <string>

using namespace std;

//typedef bool(*validatorFunction)(const string&);
using validatorFunction = bool(*)(const string&);

template<typename T>
using parserFunction = T(*)(const string&);

template<typename T>
using comparatorFunction = int(*)(T,T);