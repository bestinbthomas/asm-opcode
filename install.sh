#!/bin/bash
rm -rf build ../asm-install
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../../asm-install -DCMAKE_CXX_COMPILER=clang++
make -j install
