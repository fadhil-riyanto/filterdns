cmake_minimum_required(VERSION 3.26)
PROJECT(FilterDNS)
add_compile_options("-g3")

set(CMAKE_BUILD_TYPE, Debug)

SET(libparser_src
    src/parser/parser.cpp
)
ADD_LIBRARY(libparser STATIC "${libparser_src}")

set(CMAKE_BUILD_TYPE, Debug)
add_executable(executable src/main.cpp)
target_link_libraries(executable libparser)
set_target_properties(executable PROPERTIES OUTPUT_NAME "filterdns")
