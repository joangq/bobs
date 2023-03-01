cmake_minimum_required(VERSION 3.23)
project(bobs2)

set(CMAKE_CXX_STANDARD 11)

add_executable(bobs2 main.cpp helpers.h helpers.cpp bobs.h definitions.h)
