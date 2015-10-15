cmake_minimum_required(VERSION 3.0.2)
project(simplex-testing)

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googlemock/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googlemock/
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set ( SIMPLEX_TEST_INCLUDES ${INCLUDES} CACHE INTERNAL "simplex-test-includes")

include_directories ( ${INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library ( simplex-testing STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/src/gtest-all.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googlemock/src/gmock-all.cc
  ${CODE}
)