# Byte-Oriented Binary Search

This is an algorithm designed to search a value inside a huge file. Instead of loading the whole file into memory, or doing linear search by loading chunks, it instead performs a binary search using pointers to the raw file data. The implementation presented here is flexible, providing functions as parameters to provide customization for parsing the values, checking if the characters read are valid, and comparing them.

Because dividing a file in half will not give the middle element (Rather the middle byte), it's necessary to first determine the full information of the element. Because we're dealing with pointers to raw data, the pointer moves backwards and forwards searching a delimiter, this specific program assumes that the delimiter between values is a `newline` (Either `\n` or `\r\n`), that way we can read entire lines from the current pointer to the rightmost `newline`.

The example below demostrates the line-completion algorithm with lines formatted in a `value:key` fashion.

![](./assets/completeLine.gif)
