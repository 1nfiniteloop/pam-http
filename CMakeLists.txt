cmake_minimum_required(VERSION 3.5)
project(pam-http VERSION 1.0.0)

option(WITH_UNITTEST "Add unittests and its dependencies into configuration")

# Language-specific settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3")

# Project structure
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)
set(SOURCE_DIR  ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/external)

add_subdirectory(src)

if(WITH_UNITTEST)
    enable_testing()
    add_subdirectory(tests)
endif()

include(CPackLists.cmake)