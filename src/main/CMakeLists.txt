cmake_minimum_required(VERSION 3.15.0)
project(main)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main PUBLIC converter)

install(TARGETS main)
