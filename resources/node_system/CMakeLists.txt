cmake_minimum_required(VERSION 3.28)

project(node_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++)

set(INCLUDE_DIRECTORIES include)

# Add cpp files
file(GLOB_RECURSE CPP_FILES "src/*.cpp")
set(EXECUTABLE_NAME "node_system")

#add_executable(${EXECUTABLE_NAME} ${CPP_FILES})
add_library(${EXECUTABLE_NAME} ${CPP_FILES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

set(DEPENDENCIES 
    message_system
)

foreach(DEPENDENCY ${DEPENDENCIES})
    add_subdirectory(../${DEPENDENCY} ${CMAKE_BINARY_DIR}/${DEPENDENCY})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../${DEPENDENCY}/include)
    target_include_directories(${EXECUTABLE_NAME} INTERFACE ${CMAKE_SOURCE_DIR}/../${DEPENDENCY}/include)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${DEPENDENCY})
endforeach()
