cmake_minimum_required(VERSION 2.8)
project(simplex-support)

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set ( SIMPLEX_TEST_INCLUDES ${SIMPLEX_TEST_INCLUDES} ${INCLUDES} CACHE INTERNAL "simplex-test-includes")
set ( SIMPLEX_TEST_LIBRARIES ${SIMPLEX_TEST_LIBRARIES} simplex-support  CACHE INTERNAL "simplex-test-libraries")

set ( SIMPLEX_SUPPORT_INCLUDES ${INCLUDES} CACHE INTERNAL "simplex-support-includes")

include_directories ( ${INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file ( GLOB_RECURSE TESTS
 ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/*.cpp
)

set ( TEST_CODE ${TEST_CODE} ${TESTS} CACHE INTERNAL "simplex-tests")

add_library ( simplex-support STATIC
  ${CODE}
)