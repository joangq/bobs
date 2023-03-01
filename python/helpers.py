from io import TextIOWrapper, BufferedWriter
from typing import BinaryIO
from definitions import ValidatorFunction, ComparatorFunction, ParserFunction, T


def read_line(f: TextIOWrapper, pointer: int) -> str:
    f.seek(pointer, 0)
    line = f.readline()
    return str(line, encoding='utf-8')


def complete_string(f: BinaryIO | TextIOWrapper | BufferedWriter, pointer: int, max_size: int,
                    validate: ValidatorFunction):
    offset = 0
    boundary_pointer = pointer + offset

    line = read_line(f, pointer)

    while boundary_pointer > 0 and validate(line):
        offset -= 1
        boundary_pointer = pointer + offset
        line = read_line(f, boundary_pointer)

    while boundary_pointer < max_size and not validate(line):
        offset += 1
        boundary_pointer = pointer + offset
        line = read_line(f, boundary_pointer)

    return line, boundary_pointer


def basic_compare(x: T, y: T) -> 0 | 1 | -1:
    return 0 if x == y else -1 if x < y else 1