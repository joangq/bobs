#include "helpers.h"
#include "definitions.h"
#include <string>
#include <fstream>
#include <tuple>

template<typename T>
string bobs(const string& inputFile, T target,
            parserFunction<T> parser,
            validatorFunction validate,
            comparatorFunction<T> comparator) {

    ifstream file(inputFile, ios::binary);
    string output = "not found";
    int comparison = -1;
    int steps = 0;
    int fileSize = (int) file.seekg(0, ifstream::end).tellg();

    // TODO: If the file is *too* large, the int range may not be enough.
    int start = (int) file.seekg(0, ifstream::beg).tellg();
    int end = fileSize;

    while (comparison != 0) {
        steps++;
        int mid = (start + end) / 2;
        auto complete = completeString(file, mid, fileSize, validate);
        string s = get<0>(complete);
        int index = get<1>(complete);

        if (index >= fileSize or start >= end) break;

        T value = parser(s);

        comparison = comparator(value, target);


        switch (comparison) {
            case 0:
                output = s;
                break;
            case 1:
                end = (int) index;
                break;
            case -1:
                start = (int) index + (int) s.length() + 1;
                break;
            default:
                throw runtime_error("Comparator function gave non-comparable value: " + to_string(comparison));
        }

    }

    file.close();

    cout << "Done! In "+to_string(steps)+" steps." << endl;

    return output;
}