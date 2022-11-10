#!/bin/bash

BUILD_TYPE=
ARCH=

for param in "$@"
do
	echo "Parameter: $param";
	if [ "$param" = "release" -a "$BUILD_TYPE" = "" ] ; then BUILD_TYPE="Release"; fi
	if [ "$param" = "debug" -a "$BUILD_TYPE" = "" ] ; then BUILD_TYPE="Debug"; fi
done

if [ "$BUILD_TYPE" = "" ] ; then BUILD_TYPE="Release"; fi
if [ "$ARCH" = "" ] ; then ARCH="x64"; fi

ABSOLUTE=`readlink -e "$0"`
SRC_PATH=`dirname "${ABSOLUTE}"`
export QTDIR=/opt/Qt5.9.2/5.9.2/gcc_64
echo "Sources are here: ${SRC_PATH}"
echo "Build directory are here: ${BUILD_DIR}"

### Delete build directory ###
if [ -d "./build" ] ; then
	echo "Deleting build directory...";
	rm -r "./build";
else
	echo "There is not build directory. Nothing to delete..."
fi

### Create bulding directory again ###
mkdir ./build

echo "+++ cmake -DCMAKE_BINARY_DIR=./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE ."
cmake -DCMAKE_BINARY_DIR=./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE .
echo "+++ cmake --build . --config $BUILD_TYPE";
cmake --build . --config $BUILD_TYPE;
cp ${SRC_PATH}/db/korpus_1.db ${SRC_PATH}/bin;
cp ${SRC_PATH}/db/settings.json ${SRC_PATH}/bin;



