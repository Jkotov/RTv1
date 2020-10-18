#!/bin/bash

PROJECT_DIR=$(pwd)
rm -rf ${PROJECT_DIR}/SDL2
rm -rf ${PROJECT_DIR}/SDL2-2.0.12
rf -rf ${PROJECT_DIR}/SDL2_image-2.0.5
tar xfvz SDL2-2.0.12.tar.gz
tar xfvz SDL2_image-2.0.5.tar.gz
cd SDL2-2.0.12

rm -rf build
mkdir build
cd build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
rm -rf ${PROJECT_DIR}/SDL2_image-2.0.5/build
mkdir ${PROJECT_DIR}/SDL2_image-2.0.5/build
cd ${PROJECT_DIR}/SDL2_image-2.0.5/build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
exit 0;
