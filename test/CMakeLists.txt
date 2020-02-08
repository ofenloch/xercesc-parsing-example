# CMakeLists.txt: CMakeLists.txt for test of project xercesc-parsing-example

add_executable(xercesc-parsing-exampletest ${CMAKE_SOURCE_DIR}/test/source/main.cpp)

target_link_libraries(xercesc-parsing-exampletest xercesc-parsing-examplelib)

