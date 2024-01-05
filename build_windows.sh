#!/usr/bin/bash
sudo apt-get install mingw-w64
cd ta-lib-rt
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./ -DCMAKE_TOOLCHAIN_FILE=mingw-w64-x86_64.cmake ..
make -j8
make install 

