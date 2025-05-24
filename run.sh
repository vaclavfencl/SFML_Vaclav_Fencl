#!/bin/bash

echo "[INFO] Creating build directory..."
mkdir -p build

echo "[INFO] Running CMake..."
cmake -S . -B build || exit 1

echo "[INFO] Building project..."
cmake --build build || exit 1

echo "[INFO] Copying Thirdparty folders..."
mkdir -p build/Thirdparty/fonts
mkdir -p build/Thirdparty/sounds
mkdir -p build/Thirdparty/textures

cp -r Thirdparty/fonts/* build/Thirdparty/fonts/ 2>/dev/null
cp -r Thirdparty/sounds/* build/Thirdparty/sounds/ 2>/dev/null
cp -r Thirdparty/textures/* build/Thirdparty/textures/ 2>/dev/null

echo "[INFO] Running the app from correct directory..."
./build/SFML_Vaclav_Fencl 
