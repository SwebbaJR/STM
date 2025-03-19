cmake_minimum_required(VERSION 3.28)

project(observers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIRECTORIES include)

# Add cpp files
file(GLOB_RECURSE CPP_FILES "src/*.cpp")
set(EXECUTABLE_NAME "observers")

find_package(Eigen3 3.3 REQUIRED)

#add_executable(${EXECUTABLE_NAME} ${CPP_FILES})
add_library(${EXECUTABLE_NAME} STATIC ${CPP_FILES})

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

# Link packages
target_link_libraries(${EXECUTABLE_NAME} PUBLIC Eigen3::Eigen)

set(DEPENDENCIES 
)

foreach(DEPENDENCY ${DEPENDENCIES})
    if (NOT TARGET ${DEPENDENCY})
        add_subdirectory(../${DEPENDENCY} ${CMAKE_BINARY_DIR}/${DEPENDENCY})
    endif()
    target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${DEPENDENCY})
endforeach()