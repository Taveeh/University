cmake_minimum_required(VERSION 3.15)
project(Assignment_9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage -lsqlite3")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

set(CMAKE_MODULE_PATH "/Users/taveeh/Qt/5.14.2/clang_64/lib/cmake/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(Assignment_9 main.cpp Footage.cpp Footage.h Repository.h MemoryRepository.cpp MemoryRepository.h FileRepository.cpp FileRepository.h Service.cpp Service.h TestFootage.cpp TestFootage.h TestMemoryRepository.cpp TestMemoryRepository.h TestService.cpp TestService.h TestFileRepository.cpp TestFileRepository.h HtmlFileRepository.cpp HtmlFileRepository.h Exceptions.cpp Exceptions.h Validator.cpp Validator.h SQLRepository.cpp SQLRepository.h GUI.cpp GUI.h)
target_link_libraries(Assignment_9 Qt5::Widgets)
target_link_libraries(Assignment_9 Qt5::Charts)

