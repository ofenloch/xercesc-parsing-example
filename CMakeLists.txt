# CMakeLists.txt: top level CMakeLists.txt for project xercesc-parsing-example

# set minimum CMake version
cmake_minimum_required(VERSION 3.13)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(xercesc-parsing-example VERSION 0.1 LANGUAGES CXX)

# set the project's root folder
set(PROJECT_ROOT /home/ofenloch/workspaces/cpp/xercesc-parsing-example)
set(PROJECT_NAME xercesc-parsing-example)

# set C++ standard
set(CMAKE_CXX_STANDARD 14) # try C++14, then fall back to C++11 and C++98 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# use find_package to get the xerces-c stuff
find_package(PkgConfig)
pkg_check_modules (XERCES REQUIRED xerces-c)

# set include directories
include_directories(
  ${XERCES_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/bin/include"
  "${CMAKE_SOURCE_DIR}/lib/include"
  "${CMAKE_SOURCE_DIR}/test/include"
)

# set link directories
link_directories(${XERCES_LIBRARY_DIRS})

# include the sub-projects in bin, lib and test
add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(test)

# add the executable

# add_executable(xercesc-parsing-example /home/ofenloch/workspaces/cpp/xercesc-parsing-example/bin/source/main.cpp)

# add test executable
# add_executable(xercesc-parsing-exampleTest /home/ofenloch/workspaces/cpp/xercesc-parsing-example/test/source/main.cpp)

enable_testing()
add_test(NAME xercesc-parsing-exampleTest COMMAND MyExample)


# add your own stuff here
message("The project's name is ${PROJECT_NAME}")
message("The project's folder is ${PROJECT_ROOT}")