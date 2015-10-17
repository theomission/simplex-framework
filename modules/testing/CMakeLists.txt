cmake_minimum_required(VERSION 2.8)
project(simplex-testing)

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set ( SIMPLEX_TEST_INCLUDES ${SIMPLEX_TEST_INCLUDES} ${INCLUDES} CACHE INTERNAL "simplex-test-includes")
set ( SIMPLEX_TEST_LIBRARIES simplex-testing pthread ${SIMPLEX_TEST_LIBRARIES}  CACHE INTERNAL "simplex-test-libraries")

include_directories ( ${INCLUDES} ${SIMPLEX_FRAMEWORK_INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library ( simplex-testing STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/googletest/googletest/src/gtest-all.cc
  ${CODE}
)

