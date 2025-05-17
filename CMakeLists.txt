#
#
# @author - Phillip Davis
# @CMakelist.txt -  CMake instructions for compiling the project main files and linking to GTest if needed.
#
# 4/24/2025 - P. Davis Created and setup to link to GTest
#
#

#Specify CMake Version
cmake_minimum_required(VERSION 3.31)

#Creates Variable to refer to the project repo
set(This milestone_5_cache_manager_bst_R3plug)

set(GTEST False)

#Denote Languages used in the project
project(${This} C CXX)

#Specify which version to use of each language
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

#Enabled for compatability
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(GTEST)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_subdirectory(Testing)

endif()

#Sets Header files that will be used in this project
set(Headers
    cache_manager.h
    binary_search_tree.h
    tree_node.h
    json.hpp
    doubly_linked_list.h
    hash_node.h
    hash_table.h
    )

    #Sets .cpp files that will be used in this project
set(Sources
    milestone5.cpp
    tree_node.cpp
    binary_search_tree.cpp
    cache_manager.cpp
    dll_node.cpp
    doubly_linked_list.cpp
    
    )

#Makes sure the Json Config files are accessible during compiling
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/milestone5_config.json
    ${CMAKE_CURRENT_BINARY_DIR}/milestone5_config.json
    COPYONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/milestone5.json
    ${CMAKE_CURRENT_BINARY_DIR}/milestone5.json
    COPYONLY
)


if(GTEST)
    
    #Creates a static library to be used by google test when testing
    add_library(${This} STATIC ${Sources} ${Headers}) 
   
else()
    #Used to compile project when not testing
    add_executable(${This} ${Sources} ${Headers}) 
endif()