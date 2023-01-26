cmake_minimum_required(VERSION 3.20)

project(LibExceptionCSV VERSION 1.0.0)

add_library(exceptcsv src/exceptions.cpp header/exceptions.h)
set_target_properties(
    exceptcsv PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    exceptcsv
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header
)