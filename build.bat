if not exist cmake-build mkdir cmake-build
cmake -Bcmake-build -H.
cmake --build cmake-build/
cmake-build\Debug\shader_guide.exe
