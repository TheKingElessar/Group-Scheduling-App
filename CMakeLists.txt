cmake_minimum_required(VERSION 3.19)
project(CSCI261)

set(CMAKE_CXX_STANDARD 14)

add_executable(csci-261 AvailableTimeBlock.cpp AvailableTimeBlock.h Person.cpp Person.h EventTime.cpp EventTime.h Util.cpp Util.h main.cpp)