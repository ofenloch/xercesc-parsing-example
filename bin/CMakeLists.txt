# CMakeLists.txt: CMakeLists.txt for bin of project xercesc-parsing-example

add_executable(xercesc-parsing-examplebin ${CMAKE_SOURCE_DIR}/bin/source/main.cpp)

target_link_libraries(xercesc-parsing-examplebin xercesc-parsing-examplelib ${XERCES_LIBRARIES})

