cmake_minimum_required(VERSION 3.20)

project(Main VERSION 1.0.0)

add_executable(csvreader main.cpp)
set_target_properties(
    csvreader PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    csvreader 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../parsingCSV/header
)

target_include_directories(
    csvreader
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../exceptionCSV/header
)

target_link_libraries(csvreader PRIVATE parscsv)
target_link_libraries(csvreader PRIVATE exceptcsv)