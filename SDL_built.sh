#!/bin/bash

PROJECT_DIR=$(pwd)
tar xfvz SDL2-2.0.12.tar.gz
tar xfvz SDL2_image-2.0.5.tar.gz
cd SDL2-2.0.12

mkdir -p build
cd build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
mkdir -p {PROJECT_DIR}/SDL2_image-2.0.5/build
cd ${PROJECT_DIR}/SDL2_image-2.0.5/build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
exit 0;
