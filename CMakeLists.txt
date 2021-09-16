cmake_minimum_required(VERSION 3.18)

project(point_location LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BigIntMultiplicator.h
    )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BigIntMultiplicator.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    )

add_executable(point_location ${SOURCES} ${HEADERS})