cmake_minimum_required(VERSION 3.17)

project(Nucleo_F103RBT6 LANGUAGES C CXX ASM)

set(DEPENDENCIES 
    #observers
)

#find_package(Eigen3 3.3 REQUIRED)

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
    ${CORE_PATH}/stm32f1xx_hal_timebase_tim.c
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
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_tim_ex.c
    ${DRIVERS_SMT32F1_PATH}/stm32f1xx_hal_tim.c
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

# Gather C files
set(EXECUTABLE_C_FILES_LIST)
list(APPEND EXECUTABLE_C_FILES_LIST ${CORE_C_FILES} ${DRIVERS_C_FILES} ${FREERTOS_C_FILES})

set(CPP_FILES
    )

# Gather cpp files
set(EXECUTABLE_CPP_FILES_LIST)
list(APPEND EXECUTABLE_CPP_FILES_LIST ${CPP_FILES})

# Add executable(s)
set(EXECUTABLE_NAME "Nucleo_F103RBT6")
add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_C_FILES_LIST} ${EXECUTABLE_CPP_FILES_LIST})

# Link include files
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# Link packages

# Define the target STM32F1xx device in your project
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE STM32F103xB)

# Set startup file
set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/Core/Startup/startup_stm32f103rbtx.s)
target_sources(${EXECUTABLE_NAME} PRIVATE ${STARTUP_FILE})

foreach(DEPENDENCY ${DEPENDENCIES})
    set(DEPENDENCY_PATH ${CMAKE_SOURCE_DIR}/../resources/${DEPENDENCY})
    if (NOT TARGET ${DEPENDENCY})
        add_subdirectory(${DEPENDENCY_PATH} ${CMAKE_BINARY_DIR}/${DEPENDENCY})
    endif()
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${DEPENDENCY})
endforeach()

# Set executable properties
set (CMAKE_EXECUTABLE_SUFFIX ".elf")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F103RBTX_FLASH.ld)
target_link_options(${EXECUTABLE_NAME} PRIVATE -T ${LINKER_SCRIPT})

# Add custom command to convert ELF to BIN
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary 
   ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.elf 
   ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.bin
    COMMENT "Converting ELF to BIN"
    VERBATIM
)

add_custom_target(flash_stm_with_bin
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.bin 0x08000000 verify reset exit"
    COMMENT "Flashing Nucleo_F103RBT6 using OpenOCD"
    DEPENDS ${EXECUTABLE_NAME}  # Ensure flashing happens after the executable is built
)

add_custom_target(flash_stm_with_elf
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.elf verify reset exit"
    COMMENT "Flashing Nucleo_F103RBT6 using OpenOCD"
    DEPENDS ${EXECUTABLE_NAME}  # Ensure flashing happens after the executable is built
)
