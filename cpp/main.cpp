#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <cstdlib>

using namespace std;

string readLine(ifstream& file, int index) {
    file.seekg(index, std::ifstream::beg);
    string line;
    getline(file, line);
    return line;
}

tuple<string, int, int, int> completeString(ifstream& file, int index, int maxSize, const function<bool(string)>& key) {
    int offset = 0;
    int boundaryIndex = index + offset;
    string line = readLine(file, index);

    //cout << line << endl;

    while (boundaryIndex > 0 && key(line)) {
        offset--;
        boundaryIndex = index + offset;
        line = readLine(file, boundaryIndex);
    }

    //cout << line << endl;

    while (boundaryIndex < maxSize && !key(line)) {
        offset++;
        boundaryIndex = index + offset;
        line = readLine(file, boundaryIndex);
    }

    //cout << line << endl;

    return make_tuple(line, boundaryIndex, 0, 0);
}

string bobs(const string& inputFile,
            int target,
            const function<bool(string)>& validator,
            const function<int(string, int)>& comparator) {

    ifstream f(inputFile, ios::binary);
    string output = "Null";
    int comparison = -1;
    int steps = 0;
    int fileSize = (int) f.seekg(0, std::ifstream::end).tellg();

    // TODO: If the file is *too* large, the int range may not be enough.
    int start = (int) f.seekg(0, std::ifstream::beg).tellg();
    int end = fileSize;
   // cout << start << ' ' << end << endl;

    while (comparison != 0) {
        steps++;
        int mid = (start + end) / 2;
        auto [s, index, z, l] = completeString(f, mid, fileSize, validator);

        if (index >= fileSize) break;

        string value = s;

        cout << "[" << to_string(index) << "] ";

        comparison = comparator(value, target);



        //cout << to_string(comparison) << endl;
        //cout << "----" << endl;

        switch (comparison) {
            case 0:
                output = s;
                break;
            case 1:
                end = (int)index;
                break;
            case -1:
                start = (int)index + s.length() + 1;
                break;
            default:
                throw runtime_error("Comparator function gave non-comparable value: " + to_string(comparison));
        }

    }

    f.close();

    return output;
}

int basicCompare(int x, int y) {
    return x == y? 0 : x < y? -1 : 1;
}

int parser(const std::string& s) {
    std::string hexString = s.substr(0, s.find(':'));
    int value = std::strtol(hexString.c_str(), nullptr, 10);
    return value;
}

int comparator(const string& a, int b) {
    printf("comparator(%d, %d) --> %d", parser(a), b, basicCompare(parser(a), b));
    cout << endl;
    return basicCompare(parser(a), b);
}

int main() {
    string inputFile = R"(.\test.bin)";
    int target = 1; // TODO: Change this to accept numbers larger than the int type.
    auto validator = [](const string& s) { return s.length() > 0 and (iswalnum(s[0]) or s[0] == ':'); };
    string output = bobs(inputFile, target, validator, comparator);
    cout << "Output: " << output << endl;

    return 0;
}
