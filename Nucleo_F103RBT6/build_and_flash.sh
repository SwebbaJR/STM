rm -r build

mkdir build
cd build
cmake ..
cmake --build .

# Flash stm using command:
make flash_stm_with_elf