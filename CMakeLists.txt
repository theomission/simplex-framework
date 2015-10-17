cmake_minimum_required(VERSION 2.8)
project(simplex-framework)

option(BUILD_TESTS "Build tests" OFF)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=gnu++11" CACHE INTERNAL "cmake_cxx_flags")

if ( ${COVERAGE} )
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -O0" CACHE INTERNAL "cmake_cxx_flags")
endif ( ${COVERAGE})


# OS Detection
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -D__LINUX__" CACHE INTERNAL "cmake_cxx_flags" )

    # OpenGL
    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
    if(NOT OPENGL_FOUND)
      message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)

endif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

file (GLOB MODULES "modules/*")

foreach ( MODULE ${MODULES} )
  include_directories ( "${MODULE}/include/" )
endforeach ()

add_subdirectory ( "modules/support" )
add_subdirectory ( "modules/graphics" )
add_subdirectory ( "modules/editor" )
add_subdirectory ( "modules/application" )
add_subdirectory ( "modules/testing" )

# foreach ( MODULE ${MODULES} )
#   add_subdirectory ( "${MODULE}" )
# endforeach ()

if ( BUILD_TESTS )
    include_directories ( ${SIMPLEX_FRAMEWORK_INCLUDES} ${SIMPLEX_TEST_INCLUDES})
    add_executable ( tests ${TEST_CODE} )
    target_link_libraries ( tests ${SIMPLEX_FRAMEWORK_LIBRARIES} ${SIMPLEX_TEST_LIBRARIES} )
    add_test ( simplex-framework-tests tests )
endif ( BUILD_TESTS )
