cmake_minimum_required(VERSION 2.8)
project(simplex-framework)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11" )


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