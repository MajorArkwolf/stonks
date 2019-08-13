#!/usr/bin/env bash

set -euxo pipefail

if [[ "$TRAVIS_OS_NAME" = "linux" ]] || [[ "$TRAVIS_OS_NAME" = "osx" ]]; then
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
fi

if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
    mkdir -p build
    cd build
	cmake -DVCPKG_TARGET_TRIPLET=x64-windows \
		-DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
		-DCMAKE_GENERATOR_PLATFORM=x64 -DDisablePostBuild:BOOL=ON ..
	cmake --build .
fi
