cmake_minimum_required(VERSION 3.16)
project("y-fight")

#BASICALLY REALEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
SET(CMAKE_CXX_FLAGS "-g")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_image SDL2_image)
find_package(SDL2_image REQUIRED)

#creating the executable of Money Man
include_directories(src/)
file(GLOB_RECURSE "y-fight" SRC src/*.cpp)
add_executable(y-fight ${y-fight})

target_link_libraries(y-fight LINK_PRIVATE "${SDL2}")
target_link_libraries(y-fight LINK_PRIVATE "${SDL2_ttf}")
target_link_libraries(y-fight LINK_PRIVATE "${SDL2_image}")

