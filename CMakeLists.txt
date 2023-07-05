cmake_minimum_required(VERSION 3.26)
PROJECT(FilterDNS)

set(CMAKE_BUILD_TYPE, Debug)

SET(libserver_src
    src/server/server.cpp
)
ADD_LIBRARY(libserver STATIC "${libserver_src}")

add_executable(executable src/main.cpp)
target_link_libraries(executable libserver)
set_target_properties(executable PROPERTIES OUTPUT_NAME "filterdns")
