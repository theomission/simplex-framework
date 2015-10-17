cmake_minimum_required(VERSION 2.8)
project(simplex-graphics)

# Configure GLFW
set ( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" )
set ( GLFW_BUILD_TESTS OFF  CACHE BOOL "Build the GLFW test programs" )
set ( GLFW_BUILD_DOCS OFF  CACHE BOOL "Build the GLFW documentation" )
set ( GLFW_INSTALL OFF  CACHE BOOL "Generate installation target" )
set ( GLFW_DOCUMENT_INTERNALS OFF  CACHE BOOL "Include internals in documentation" )

add_subdirectory( "third-party/glfw" )

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/glfw/include
)

set ( SIMPLEX_FRAMEWORK_INCLUDES ${SIMPLEX_FRAMEWORK_INCLUDES} ${INCLUDES} CACHE INTERNAL "simplex-framework-includes")
set ( SIMPLEX_FRAMEWORK_LIBRARIES simplex-graphics ${SIMPLEX_FRAMEWORK_LIBRARIES} glfw GL ${GLFW_LIBRARIES} CACHE INTERNAL "simplex-framework-libraries")

include_directories ( ${SIMPLEX_FRAMEWORK_INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file ( GLOB_RECURSE TESTS
 ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/*.cpp
)

set ( TEST_CODE ${TEST_CODE} ${TESTS} CACHE INTERNAL "simplex-tests")

add_library ( simplex-graphics STATIC ${CODE} )
add_dependencies (simplex-graphics glfw)