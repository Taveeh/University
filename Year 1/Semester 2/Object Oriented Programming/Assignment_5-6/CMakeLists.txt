cmake_minimum_required(VERSION 3.15)
project(Assignment_5_6)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "--coverage")
add_executable(Assignment_5_6 main.cpp DynamicArray.h Footage.cpp Footage.h Repository.cpp Repository.h Service.cpp Service.h UI.cpp UI.h TestFootage.cpp TestFootage.h TestDynamicArray.cpp TestDynamicArray.h TestRepository.cpp TestRepository.h TestService.cpp TestService.h)