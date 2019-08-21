#!/usr/bin/env bash

set -euxo pipefail

if [[ "${TRAVIS_OS_NAME}" == "linux" ]] || [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
    mkdir -p build
    cd build
    cmake -D CMAKE_BUILD_TYPE="Debug" -D CopyResources:BOOL=ON \
          -D WarningsAsErrors:BOOL=ON ..
    cmake --build .
fi

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
    mkdir -p build
    cd build
	cmake -D CMAKE_BUILD_TYPE="Debug" -D VCPKG_TARGET_TRIPLET=x64-windows \
		  -D CMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
		  -D CMAKE_GENERATOR_PLATFORM=x64 -D CopyResources:BOOL=ON \
          -D WarningsAsErrors:BOOL=ON ..
	cmake --build .
fi
