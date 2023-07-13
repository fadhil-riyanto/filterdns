cmake_minimum_required(VERSION 3.26)
PROJECT(FilterDNS)
add_compile_options("-g3")

set(CMAKE_BUILD_TYPE, Debug)

SET(libutils_src
    src/utils/parser.cpp
    src/utils/debugger.cpp
)

SET(libserver_src
    src/server/server.cpp
)

ADD_LIBRARY(liball STATIC "${libserver_src}" "${libutils_src}")

set(CMAKE_BUILD_TYPE, Debug)
add_executable(executable src/main.cpp)
target_link_libraries(executable liball)
set_target_properties(executable PROPERTIES OUTPUT_NAME "filterdns")
