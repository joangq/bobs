from typing import Callable, BinaryIO, TypeVar

ValidatorFunction = Callable[[str], bool]

T = TypeVar("T")
ParserFunction = Callable[[str], T]
ComparatorFunction = Callable[[T, T], int]