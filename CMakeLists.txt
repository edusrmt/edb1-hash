cmake_minimum_required(VERSION 3.5)
project (HashTable)

#=== FINDING PACKAGES ===#

# Locate GTest package (library)
find_package(GTest REQUIRED)
include_directories( ${GTEST_INCLUDE_DIRS})

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}" )

#Include dir
include_directories( include )

#=== Test target ===

# The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES_TEST "test/*.cpp" )
#file(GLOB SOURCES_TEST "src/*.cpp" )

# Define the sources
add_executable(run_tests ${SOURCES_TEST} )
#add_executable(run_drive ${SOURCES_TEST} )

# Link with the google test libraries.
#target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} PRIVATE pthread)