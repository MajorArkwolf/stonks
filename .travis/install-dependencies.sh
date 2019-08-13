#!/usr/bin/env bash

set -euxo pipefail

if [[ "$TRAVIS_OS_NAME" = "windows" ]]; then
    git clone --depth=1 https://github.com/Microsoft/vcpkg.git $VCPKG_ROOT
    cd "$VCPKG_ROOT"
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '.\bootstrap-vcpkg.bat'"
    ./vcpkg.exe integrate install
    ./vcpkg.exe install $VCPKG_PACKAGES
fi

if [[ "$TRAVIS_OS_NAME" = "osx" ]]; then
    brew install cmake sdl2 sdl2_image sdl2_ttf sdl2_mixer glm || true
fi
