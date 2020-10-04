#!/bin/bash

PROJECT_DIR=$(pwd)
rm -rf ${PROJECT_DIR}/SDL2
rm -rf ${PROJECT_DIR}/SDL2-2.0.12
rf -rf ${PROJECT_DIR}/SDL2_image-2.0.5
rm -rf ${PROJECT_DIR}/SDL2_ttf-2.0.15
tar xfvz SDL2-2.0.12.tar.gz
tar xfvz SDL2_image-2.0.5.tar.gz
tar xfvz SDL2_image-2.0.5.tar.gz
cd SDL2-2.0.12
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        CC=
elif [[ "$OSTYPE" == "darwin"* ]]; then
	CC=$(pwd)/build-scripts/gcc-fat.sh
else
	exit 0;
fi

rm -rf build
mkdir build
cd build
${CC} ../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
rm -rf ${PROJECT_DIR}/SDL2_image-2.0.5/build
mkdir ${PROJECT_DIR}/SDL2_image-2.0.5/build
cd ${PROJECT_DIR}/SDL2_image-2.0.5/build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
rm -rf ${PROJECT_DIR}/SDL2_ttf-2.0.15/build
mkdir ${PROJECT_DIR}/SDL2_ttf-2.0.15/build
cd ${PROJECT_DIR}/SDL2_ttf-2.0.15/build
../configure --prefix=${PROJECT_DIR}/SDL2
make
make install
exit 0;
