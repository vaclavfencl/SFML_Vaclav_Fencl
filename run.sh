#!/bin/bash

echo "[INFO] Creating build directory..."
mkdir -p build
cd build

echo "[INFO] Running CMake..."
cmake -DSFML_DIR=../Thirdparty/SFML-2.6.1 ..

echo "[INFO] Building project..."
cmake --build . --config Release

echo "[INFO] Copying SFML shared libraries..."
cp ../Thirdparty/SFML-2.6.1/bin/*.so* ./Release/ 2>/dev/null || echo "[WARN] No .so files found in bin/ (expected on Linux builds)"

echo "[INFO] Copying Thirdparty folders..."
mkdir -p Release/Thirdparty/fonts
mkdir -p Release/Thirdparty/sounds
mkdir -p Release/Thirdparty/textures

cp -r ../Thirdparty/fonts/* Release/Thirdparty/fonts/
cp -r ../Thirdparty/sounds/* Release/Thirdparty/sounds/
cp -r ../Thirdparty/textures/* Release/Thirdparty/textures/

echo "[INFO] Running the app..."
cd Release
./SFML_Vaclav_Fencl
