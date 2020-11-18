cmake_minimum_required(VERSION 3.15.0)
project(converter)

set(SOURCE_FILES converter.cpp)
set(INCLUDE_PATH include)

add_library(converter SHARED ${SOURCE_FILES})


target_include_directories(
  converter
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_PATH}>)

install(TARGETS converter)

install(DIRECTORY ${INCLUDE_PATH}/ DESTINATION include)
