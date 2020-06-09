cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

option(HAVE_EMX "Build with EMX")

if(HAVE_EMX)
message("-- Building with EMX")
add_definitions("-DHAVE_EMX=1")
set (quickfix_PROJECT_NAME quickfix-emx)
else()
set (quickfix_PROJECT_NAME quickfix)
endif()

project(${quickfix_PROJECT_NAME} VERSION 0.1 LANGUAGES CXX C)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
message("-- Project name ${CMAKE_PROJECT_NAME}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(QuickfixPlatformSettings)
include(QuickfixPrebuildSetup)

# Call cmake with-DHAVE_SSL=ON to compile with SSL. Similarly for others.
option(HAVE_SSL "Build with SSL")
option(HAVE_MYSQL "Build with MySQL")
option(HAVE_POSTGRESQL "Build with PostgreSQL")
option(HAVE_PYTHON "Build with default Python version")
option(HAVE_PYTHON2 "Build with default Python2 version")
option(HAVE_PYTHON3 "Build with default Python3 version")


#Make sure that a previous config.h has not undefined HAVE_SSL
if(HAVE_SSL)
# Can set location explicitly, example, cmake -DOPENSSL_ROOT_DIR=/usr/local/ssl -DOPENSSL_LIBRARIES=/usr/local/ssl/lib

message("-- Building with SSL")
add_definitions("-DHAVE_SSL=1")

file(APPEND ${CMAKE_SOURCE_DIR}/config.h
        "#ifndef HAVE_SSL\n"
        "#define HAVE_SSL 1\n"
        "#endif\n")
endif()

if(HAVE_MYSQL)
find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})

message("-- Building with MySQL")
add_definitions("-DHAVE_MYSQL=1")
endif()

if(HAVE_POSTGRESQL)
find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})

message("-- Building with POSTGRESQL")
add_definitions("-DHAVE_POSTGRESQL=1")
endif()

message(STATUS "Checking for nullptr.")
unset(HAVE_NULLPTR CACHE)
set(NULLPTR_FOUND FALSE)
check_include_file_cxx(cstddef HAVE_STD_CSTDDEF_HEADER)
if (HAVE_STD_CSTDDEF_HEADER)
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("#include <cstddef>
                               int main() {
                                 std::nullptr_t null = nullptr;
                                 return 0;
                               }"
            HAVE_NULLPTR)
    if (HAVE_NULLPTR)
        message(STATUS "Found support to nullptr.")
        set(NULLPTR_FOUND TRUE)
    endif(HAVE_NULLPTR)
endif(HAVE_STD_CSTDDEF_HEADER)

if (HAVE_NULLPTR)
    message(STATUS "set HAVE_NULLPTR")
    add_definitions("-DHAVE_NULLPTR=1")
    file(APPEND ${CMAKE_SOURCE_DIR}/config.h
     "#ifndef HAVE_NULLPTR\n"
     "#define HAVE_NULLPTR\n"
     "#endif\n" )
endif (HAVE_NULLPTR)

message(STATUS "Checking for use of enumeration in nested specifier.")
unset(HAVE_ENUM_NESTED CACHE)
set(ENUM_NESTED_FOUND FALSE)
check_cxx_source_compiles("namespace NS {
                           enum E {
                           Item
                           };
                           }
                           int main() {
                             NS::E e = NS::E::Item;
                           }"
                          HAVE_ENUM_NESTED)
if (HAVE_ENUM_NESTED)
    message(STATUS "Found support to use of enumeration in nested specifier.")
    set(ENUM_NESTED_FOUND TRUE)

    message(STATUS "set HAVE_ENUM_NESTED")
    add_definitions("-DHAVE_ENUM_NESTED=1")

    file(APPEND ${CMAKE_SOURCE_DIR}/config.h
     "#ifndef HAVE_ENUM_NESTED\n"
     "#define HAVE_ENUM_NESTED\n"
     "#endif\n" )
endif (HAVE_ENUM_NESTED)

message(STATUS "Checking support in-class initialization of non-static data member.")
unset(HAVE_IN_CLASS_NON_STATIC CACHE)
set(IN_CLASS_NON_STATIC_FOUND FALSE)
check_cxx_source_compiles("namespace NS {
                           class C {
                           int f = 0;
                           };
                           }
                           int main() {
                             NS::C c;
                           }"
                          HAVE_IN_CLASS_NON_STATIC)
if (HAVE_IN_CLASS_NON_STATIC)
    message(STATUS "Found support to in-class initialization of non-static data member.")
    set(IN_CLASS_NON_STATIC_FOUND TRUE)

    message(STATUS "set HAVE_IN_CLASS_NON_STATIC")
    add_definitions("-DHAVE_IN_CLASS_NON_STATIC=1")

    file(APPEND ${CMAKE_SOURCE_DIR}/config.h
     "#ifndef HAVE_IN_CLASS_NON_STATIC\n"
     "#define HAVE_IN_CLASS_NON_STATIC\n"
     "#endif\n" )
endif (HAVE_IN_CLASS_NON_STATIC)

include(FindSharedPtr)



FIND_SHARED_PTR()
if (HAVE_SHARED_PTR_IN_STD_NAMESPACE)
message("-- set HAVE_STD_SHARED_PTR")

add_definitions("-DHAVE_STD_SHARED_PTR=1")
file(APPEND ${CMAKE_SOURCE_DIR}/config.h
 "#ifndef HAVE_STD_SHARED_PTR\n"
 "#define HAVE_STD_SHARED_PTR\n"
 "#endif\n" )

elseif(HAVE_SHARED_PTR_IN_TR1_NAMESPACE)
message("-- set HAVE_STD_TR1_SHARED_PTR")

add_definitions("-DHAVE_STD_TR1_SHARED_PTR=1")
file(APPEND ${CMAKE_SOURCE_DIR}/config.h
 "#ifndef HAVE_STD_TR1_SHARED_PTR\n"
 "#define HAVE_STD_TR1_SHARED_PTR\n"
 "#endif\n" )

elseif(HAVE_SHARED_PTR_IN_TR1_NAMESPACE_FROM_TR1_MEMORY_HEADER)
message("-- set HAVE_STD_TR1_SHARED_PTR_FROM_TR1_MEMORY_HEADER")

add_definitions("-DHAVE_STD_TR1_SHARED_PTR_FROM_TR1_MEMORY_HEADER=1")
file(APPEND ${CMAKE_SOURCE_DIR}/config.h
 "#ifndef HAVE_STD_TR1_SHARED_PTR_FROM_TR1_MEMORY_HEADER\n"
 "#define HAVE_STD_TR1_SHARED_PTR_FROM_TR1_MEMORY_HEADER\n"
 "#endif\n" )

else()
message("-- shared_ptr not found.")
endif()

include(FindUniquePtr)
FIND_UNIQUE_PTR()
if (HAVE_UNIQUE_PTR_IN_STD_NAMESPACE)
message("-- set HAVE_STD_UNIQUE_PTR")

add_definitions("-DHAVE_STD_UNIQUE_PTR=1")
file(APPEND ${CMAKE_SOURCE_DIR}/config.h
 "#ifndef HAVE_STD_UNIQUE_PTR\n"
 "#define HAVE_STD_UNIQUE_PTR\n"
 "#endif\n" )

endif()

if (HAVE_PYTHON)
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
elseif (HAVE_PYTHON2)
find_package(PythonLibs 2 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
elseif (HAVE_PYTHON3)
find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
endif ()

if( WIN32 OR ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
add_subdirectory(UnitTest++)
endif()

add_subdirectory(src)
add_subdirectory(examples)
if( WIN32)
add_subdirectory(test)
endif()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/spec/ DESTINATION share/quickfix
  FILES_MATCHING PATTERN "FIX*.xml")
