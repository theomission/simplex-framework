cmake_minimum_required(VERSION 2.8)
project(simplex-framework)

option(BUILD_TESTS "Build tests" OFF)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11" )

if ( ${COVERAGE} )
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -O0" )
endif ( ${COVERAGE})


# OS Detection
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D__LINUX__" )
endif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

file (GLOB MODULES "modules/*")

foreach ( MODULE ${MODULES} )
  include_directories ( "${MODULE}/include/" )
endforeach ()

foreach ( MODULE ${MODULES} )
  message(${MODULE})
  add_subdirectory ( "${MODULE}" )
endforeach ()

if ( BUILD_TESTS )
    message ( ${SIMPLEX_TEST_INCLUDES} )
    include_directories ( ${SIMPLEX_TEST_INCLUDES} )
    add_executable ( tests ${TEST_CODE} )
    target_link_libraries ( tests ${SIMPLEX_TEST_LIBRARIES} )
    add_test ( simplex-framework-tests tests )
endif ( BUILD_TESTS )
