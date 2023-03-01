from helpers import basic_compare
from bobs import bobs
import hashlib


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
    print(output)
