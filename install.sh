#!/bin/bash
rm -rf ../asm-install build
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../../asm-install
make -j install
