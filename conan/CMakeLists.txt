cmake_minimum_required(VERSION 3.0)
project(cmake_wrapper)

message( STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}" )

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
else()
  include(conanbuildinfo.cmake)
endif()
conan_basic_setup()

add_subdirectory(".." ${CMAKE_CURRENT_BINARY_DIR}/quickfix)
