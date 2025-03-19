rm -r build

mkdir build
cd build
cmake ..
cmake --build . --clean-first