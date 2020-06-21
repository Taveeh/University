cmake_minimum_required(VERSION 3.16)
project(finalExam)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

set(CMAKE_MODULE_PATH "/Users/taveeh/Qt/5.14.2/clang_64/lib/cmake/")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)

add_executable(finalExam main.cpp Service.cpp Service.h Repository.h Domain.cpp Domain.h WindowModel.cpp WindowModel.h Window.cpp Window.h Observer.cpp Observer.h SearchModel.cpp SearchModel.h Drawing.cpp Drawing.h)
target_link_libraries(finalExam Qt5::Widgets)
target_link_libraries(finalExam Qt5::Charts)
