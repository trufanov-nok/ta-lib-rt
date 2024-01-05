#!/usr/bin/bash

cd ta-lib-rt
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./ ..
make -j8
make install
