cmake_minimum_required(VERSION 3.16)
project(Lab_Test_Week_13)

set(CMAKE_CXX_STANDARD 11)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

set(CMAKE_MODULE_PATH "/Users/taveeh/Qt/5.14.2/clang_64/lib/cmake/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_executable(Lab_Test_Week_13 main.cpp
        Car.h Car.cpp Repository.cpp Repository.h Service.cpp Service.h GUI.cpp GUI.h)
target_link_libraries(Lab_Test_Week_13 Qt5::Widgets)
target_link_libraries(Lab_Test_Week_13 Qt5::Charts)
