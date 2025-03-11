rm -r build

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake ..
cmake --build . -- -j 14

# Flash stm using command:
make flash_stm_with_elf