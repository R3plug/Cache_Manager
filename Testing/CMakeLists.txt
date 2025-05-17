#
#
# @author - Phillip Davis
# @CMakelist.txt -  CMake instructions for compiling the project main files and linking to GTest if needed.
#
#2/13/2025 - P. Davis Created and setup to link to GTest
#
#


cmake_minimum_required(VERSION 3.14)

set(This testing)

#need both C and C++
project(${This} C CXX)

set((CMAKE_C_STANDARD 99))
set(CMAKE_CXX_STANDARD 20)

#any sources from the testing directory
set(SOURCES
    testing.cpp
)


#create an executable from test dir
add_executable(${This} ${SOURCES})

#adding project library and gtest library
target_link_libraries(${This} PUBLIC
    gtest_main
    milestone_5_cache_manager_bst_R3plug
    )

add_test(
    NAME ${This}
    COMMAND ${This}
)