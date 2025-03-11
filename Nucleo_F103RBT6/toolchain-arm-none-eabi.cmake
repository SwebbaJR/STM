set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Apply linker flags to the executable
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")
set(CMAKE_C_FLAGS "-std=gnu11 ${RUNTIME_LIBRARY} -mcpu=Cortex-M3 -mthumb -Wall -Werror -O3")
set(CMAKE_CXX_FLAGS "${RUNTIME_LIBRARY} -mcpu=Cortex-M3 -mthumb -Wall -Werror -O3")
