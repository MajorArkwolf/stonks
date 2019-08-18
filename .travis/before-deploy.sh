#!/usr/bin/env bash

set -euxo pipefail

cd build

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
    cd Debug
    tar -czvf "../${TRAVIS_TAG}-${TRAVIS_OS_NAME}.tar.gz" res shays-world.exe *.dll
elif [[ "${TRAVIS_OS_NAME}" == "osx" ]]; then
    tar -czvf "${TRAVIS_TAG}-${TRAVIS_OS_NAME}.tar.gz" res shays-world *.dylib
elif [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
    tar -czvf "${TRAVIS_TAG}-${TRAVIS_OS_NAME}.tar.gz" res shays-world *.so
fi
