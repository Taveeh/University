cmake_minimum_required(VERSION 3.15)
project(Assignment_7_8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage")

add_executable(Assignment_7_8 main.cpp Footage.cpp Footage.h Repository.h MemoryRepository.cpp MemoryRepository.h FileRepository.cpp FileRepository.h Service.cpp Service.h UI.cpp UI.h TestFootage.cpp TestFootage.h TestMemoryRepository.cpp TestMemoryRepository.h TestService.cpp TestService.h TestFileRepository.cpp TestFileRepository.h)