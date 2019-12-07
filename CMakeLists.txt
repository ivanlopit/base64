cmake_minimum_required(VERSION 3.5)

project(incr4k_base64 CXX)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)


set(BASE64_includes
        ${CMAKE_CURRENT_SOURCE_DIR}/include/incr4k/base64/block.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/incr4k/base64/simple.h)

set(BASE64_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/block.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/simple.cpp)


add_library(base64
        ${BASE64_includes}
        ${BASE64_sources})


add_library(incr4k::base64 ALIAS base64)


target_include_directories(base64 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)



set(GTEST_FOUND_INDIR FALSE)

find_package(GTest)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/googletest)
    set(GTEST_FOUND_INDIR TRUE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)
endif()

IF(${GTEST_FOUND} OR ${GTEST_FOUND_INDIR})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
