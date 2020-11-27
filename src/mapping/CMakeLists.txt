cmake_minimum_required(VERSION 3.15.0)
project(mapping)

set(SOURCE_FILES mapping.cpp)
set(INCLUDE_PATH include)

add_library(mapping SHARED ${SOURCE_FILES})


target_include_directories(
  mapping
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_PATH}>)

install(TARGETS mapping)

install(DIRECTORY ${INCLUDE_PATH}/ DESTINATION include)
