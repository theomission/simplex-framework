cmake_minimum_required(VERSION 2.8)
project(simplex-editor)

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/examples/libs/gl3w/
)

set ( SIMPLEX_FRAMEWORK_INCLUDES ${SIMPLEX_FRAMEWORK_INCLUDES} ${INCLUDES} CACHE INTERNAL "simplex-framework-includes")
set ( SIMPLEX_FRAMEWORK_LIBRARIES  simplex-editor ${SIMPLEX_FRAMEWORK_LIBRARIES} CACHE INTERNAL "simplex-framework-libraries")

include_directories ( ${SIMPLEX_FRAMEWORK_INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file ( GLOB IMGUI_CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/*.h
 ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/examples/libs/gl3w/GL/*.c
)

file ( GLOB_RECURSE TESTS
 ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/*.cpp
)

set ( TEST_CODE ${TEST_CODE} ${TESTS} CACHE INTERNAL "simplex-tests")

add_library ( simplex-editor STATIC
  ${IMGUI_CODE}
  ${CODE}
)

add_dependencies (  simplex-editor simplex-support )
