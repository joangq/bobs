# Byte-Oriented Binary Search

This is an algorithm designed to search a value inside a huge file. Instead of loading the whole file into memory, or doing linear search by loading chunks, it instead performs a binary search using pointers to the raw file data. The implementation presented here is flexible, providing functions as parameters to provide customization for parsing the values, checking if the characters read are valid, and comparing them.

Because dividing a file in half will not give the middle element (Rather the middle byte), it's necessary to first determine the full information of the element. Because we're dealing with pointers to raw data, the pointer moves backwards and forwards searching a delimiter, this specific program assumes that the delimiter between values is a `newline` (Either `\n` or `\r\n`), that way we can read entire lines from the current pointer to the rightmost `newline`.

The example below demonstrates the line-completion algorithm with lines formatted in a `key:value` fashion.

![](./assets/completeLine.gif)

# Usage

### C++

```cpp
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
    cout << "Output: " << output << endl; // Done! In 4 steps. Output: 1:1

    return 0;
}
```

### Python

```python
def parser(s: str):
    return int(s.split(':')[0], 10)


def compare(a: int, b: int):
    return basic_compare(a, b)


def validator(s: str):
    return len(s) > 0 and (s[0].isalnum() or s[0] == ':')


if __name__ == '__main__':
    file = 'test.bin'
    target = 12345
    output = bobs(file, target, parser, validator, compare)
    print(output) # Done! In 2 steps. 12345:77

```
