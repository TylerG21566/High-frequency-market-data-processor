#!/bin/bash
set -e

# Set compilers to clang/clang++ (recommended for macOS)
export CC=clang
export CXX=clang++

# Create build directory if it doesn't exist
[ -d build ] || mkdir build
cd build

# Configure with vcpkg toolchain and build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake

# This will automatically install dependencies from vcpkg.json
cmake --build .

# Run the executable
./cp_perfrom