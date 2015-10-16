cmake_minimum_required(VERSION 2.8)
project(simplex-ui)

set ( INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/
)

set ( SIMPLEX_FRAMEWORK_INCLUDES ${SIMPLEX_FRAMEWORK_INCLUDES} ${INCLUDES} CACHE INTERNAL "simplex-framework-includes")
set ( SIMPLEX_FRAMEWORK_LIBRARIES ${SIMPLEX_FRAMEWORK_LIBRARIES} simplex-ui  CACHE INTERNAL "simplex-framework-libraries")

include_directories ( ${SIMPLEX_FRAMEWORK_INCLUDES} )

file ( GLOB_RECURSE CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

file ( GLOB IMGUI_CODE
 ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/*.cpp
 ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/*.h
)

file ( GLOB_RECURSE TESTS
 ${CMAKE_CURRENT_SOURCE_DIR}/tests/src/*.cpp
)

set ( TEST_CODE ${TEST_CODE} ${TESTS} CACHE INTERNAL "simplex-tests")

add_library ( simplex-ui STATIC
  ${IMGUI_CODE}
  ${CODE}
)

add_dependencies (  simplex-ui simplex-support )
