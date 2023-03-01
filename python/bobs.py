from io import TextIOWrapper, BufferedWriter
from typing import BinaryIO
from helpers import complete_string
from definitions import ValidatorFunction, ComparatorFunction, ParserFunction, T


def bobs(input_file: BinaryIO | str, target: T,
         parser: ParserFunction,
         validator: ValidatorFunction,
         comparator: ComparatorFunction):
    f: BufferedWriter | TextIOWrapper | BinaryIO | None = None
    closeFlag: bool = False
    if type(input_file) == str:
        f = open(input_file, 'rb')
        closeFlag = True
    else:
        f = input_file

    output: str = "None"
    comparison: 0 | 1 | -1 = -1
    steps: int = 0

    file_size: int = f.seek(0, 2)
    start: int = f.seek(0, 0)
    end: int = file_size

    while comparison != 0:
        steps += 1
        mid: int = (start + end) // 2
        s, index = complete_string(f, mid, file_size, validate=validator)

        if index >= file_size or start >= end:
            break

        value: T = parser(s)
        comparison = comparator(value, target)

        match comparison:
            case 0:
                output = s
            case 1:
                end = index
            case -1:
                start = index + len(s) + 1
            case _:
                raise ValueError('Comparator function gave non-comparable value: ' + str(comparison))

    print(f'Done! In {steps} steps.')

    if closeFlag:
        f.close()

    return output
