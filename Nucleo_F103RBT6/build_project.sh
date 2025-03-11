rm -r build

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug .. 
cmake --build . -- -j 14