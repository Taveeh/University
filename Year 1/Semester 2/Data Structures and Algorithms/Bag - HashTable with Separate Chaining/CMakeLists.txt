cmake_minimum_required(VERSION 3.16)
project(Bag)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bag
        App.cpp
        Bag.cpp
        Bag.h
        BagIterator.cpp
        BagIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)
