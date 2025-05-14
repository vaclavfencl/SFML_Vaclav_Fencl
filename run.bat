@echo off
echo [INFO] Creating build directory...
if not exist build mkdir build
cd build

echo [INFO] Running CMake...
cmake -DSFML_DIR=../Thirdparty/SFML-2.6.1/bin ..

echo [INFO] Building project...
cmake --build . --config Release

echo [INFO] Copying SFML DLLs...
xcopy /Y /Q "..\Thirdparty\SFML-2.6.1\bin\*.dll" "Release\"

echo [INFO] Copying Thirdparty folder...
xcopy /E /I /Y "..\Thirdparty\fonts" "Release\Thirdparty\fonts"
xcopy /E /I /Y "..\Thirdparty\sounds" "Release\Thirdparty\sounds"
xcopy /E /I /Y "..\Thirdparty\textures" "Release\Thirdparty\textures"

echo [INFO] Running the app...
cd .\Release
SFML_Vaclav_Fencl.exe

