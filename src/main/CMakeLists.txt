cmake_minimum_required(VERSION 3.15.0)
project(main)

set(SOURCE_FILES main.cpp)

add_executable(asm-opcode ${SOURCE_FILES})

target_link_libraries(asm-opcode encoder decoder)

install(TARGETS asm-opcode)
