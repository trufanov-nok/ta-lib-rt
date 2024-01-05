#!/usr/bin/bash

cd ta-lib-rt
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=./ -DTA_LIB_RT_BUILD_REGTEST_C=ON ..
make -j8
make install
