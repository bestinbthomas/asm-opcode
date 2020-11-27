cmake_minimum_required(VERSION 3.15.0)
project(encoder)

set(SOURCE_FILES encoder.cpp)
set(INCLUDE_PATH include)

add_library(encoder SHARED ${SOURCE_FILES})

target_link_libraries(encoder mapping converter)

target_include_directories(
  encoder
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_PATH}>)

install(TARGETS encoder)

install(DIRECTORY ${INCLUDE_PATH}/ DESTINATION include)
