#!/usr/bin/env bash
set -euxo pipefail

cd build
cmake --build . -- package
