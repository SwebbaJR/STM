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

# Add the path to the message_system library (assuming it's a sibling directory)
add_subdirectory(../message_system ${CMAKE_BINARY_DIR}/message_system)

# Include the headers of message_system
target_include_directories(node_system PRIVATE
    ${CMAKE_SOURCE_DIR}/../message_system/include
)

# Link the message_system library to node_system
target_link_libraries(node_system PRIVATE message_system)
