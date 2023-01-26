cmake_minimum_required(VERSION 3.20)

project(LibParsingCSV VERSION 1.0.0)

add_library(parscsv src/parsingcsv.cpp header/parsingcsv.h)
set_target_properties(
    parscsv PROPERTIES 
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    parscsv
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header
)
target_include_directories(
    parscsv
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../exceptionCSV/header
)

target_link_libraries(parscsv PRIVATE exceptcsv)