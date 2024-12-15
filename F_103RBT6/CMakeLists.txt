cmake_minimum_required(VERSION 3.17)

project(F_103RBT6 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)

## Set include directories
set(INCLUDE_DIRECTORIES
    Core/Inc
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32F1xx_HAL_Driver/Inc
    Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
    Middlewares/Third_Party/FreeRTOS/Source/include
    Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3)

## Set source files
# Core files
set(CORE_PATH Core/Src)
set(CORE_C_FILES
    ${CORE_PATH}/freertos.c
    ${CORE_PATH}/main.c
    ${CORE_PATH}/stm32f1xx_hal_msp.c
    ${CORE_PATH}/stm32f1xx_it.c
    ${CORE_PATH}/syscalls.c
    ${CORE_PATH}/sysmem.c
    ${CORE_PATH}/system_stm32f1xx.c)

# Drivers files
set(DRIVERS_SMT32F1_PATH Drivers/STM32F1xx_HAL_Driver/Src)
set(DRIVERS_C_FILES
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_cortex.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_dma.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_exti.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_flash_ex.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_flash.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_gpio_ex.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_gpio.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_pwr.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_rcc_ex.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_rcc.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal.c)

# FreeRTOS files
set(FREERTOS_PATH Middlewares/Third_Party/FreeRTOS/Source)
set(FREERTOS_C_FILES
    ${FREERTOS_PATH}/CMSIS_RTOS/cmsis_os.c

    ${FREERTOS_PATH}/portable/GCC/ARM_CM3/port.c
    ${FREERTOS_PATH}/portable/MemMang/heap_4.c
    
    ${FREERTOS_PATH}/croutine.c
    ${FREERTOS_PATH}/event_groups.c
    ${FREERTOS_PATH}/list.c
    ${FREERTOS_PATH}/queue.c
    ${FREERTOS_PATH}/stream_buffer.c
    ${FREERTOS_PATH}/tasks.c
    ${FREERTOS_PATH}/timers.c)

# Gather files
set(EXEUTABLE_C_FILES_LIST)
list(APPEND EXEUTABLE_C_FILES_LIST ${CORE_C_FILES} ${DRIVERS_C_FILES} ${FREERTOS_C_FILES})

# Add executable(s)
set(EXECUTABLE_C_FILES_NAME "STMF103RBT6_executable")
add_executable(${EXECUTABLE_C_FILES_NAME} ${EXEUTABLE_C_FILES_LIST})

# Link include files
target_include_directories(${EXECUTABLE_C_FILES_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

# Define the target STM32F1xx device in your project
target_compile_definitions(${EXECUTABLE_C_FILES_NAME} PRIVATE STM32F103xB)

# Set startup file
set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32f103rbtx.s)
target_sources(${EXECUTABLE_C_FILES_NAME} PRIVATE ${STARTUP_FILE})

# Apply linker flags to the executable
set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32F103RBTX_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -static -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_C_FLAGS "-std=gnu11 ${RUNTIME_LIBRARY} -mcpu=Cortex-M3 -mthumb -Wall -Werror")
set(CMAKE_CXX_FLAGS "-std=gnu11 ${RUNTIME_LIBRARY} -mcpu=Cortex-M3 -mthumb -Wall -Werror")

# Add custom command to convert ELF to BIN
add_custom_command(TARGET ${EXECUTABLE_C_FILES_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary 
   ${CMAKE_BINARY_DIR}/${EXECUTABLE_C_FILES_NAME}.elf 
   ${CMAKE_BINARY_DIR}/${EXECUTABLE_C_FILES_NAME}.bin
    COMMENT "Converting ELF to BIN"
    VERBATIM
)

add_custom_target(flash_stm
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program ${CMAKE_BINARY_DIR}/${EXECUTABLE_C_FILES_NAME}.bin 0x08000000 verify reset exit"
    COMMENT "Flashing STM32F103RBT6 using OpenOCD"
    DEPENDS ${EXECUTABLE_C_FILES_NAME}  # Ensure flashing happens after the executable is built
)
