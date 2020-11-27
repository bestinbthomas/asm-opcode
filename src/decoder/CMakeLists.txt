cmake_minimum_required(VERSION 3.15.0)
project(decoder)

set(SOURCE_FILES decoder.cpp)
set(INCLUDE_PATH include)

add_library(decoder SHARED ${SOURCE_FILES})

target_link_libraries(decoder mapping converter)

target_include_directories(
  decoder
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_PATH}>)

install(TARGETS decoder)

install(DIRECTORY ${INCLUDE_PATH}/ DESTINATION include)
