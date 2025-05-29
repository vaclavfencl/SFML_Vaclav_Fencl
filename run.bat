@echo off
echo [INFO] Creating build directory...
if not exist build mkdir build

echo [INFO] Running CMake...
cmake -S . -B build -DSFML_DIR=Thirdparty/SFML-2.6.1/bin

echo [INFO] Building project...
cmake --build build || exit 1

echo [INFO] Copying Thirdparty folders...
xcopy /E /I /Y "Thirdparty\fonts" "build\Thirdparty\fonts"
xcopy /E /I /Y "Thirdparty\sounds" "build\Thirdparty\sounds"
xcopy /E /I /Y "Thirdparty\textures" "build\Thirdparty\textures"

echo [INFO] Copying SFML DLLs...
xcopy /Y /Q "Thirdparty\SFML-2.6.1\bin\*.dll" "build"

echo [INFO] Running the app from build folder...
cd build
SFML_Vaclav_Fencl.exe
