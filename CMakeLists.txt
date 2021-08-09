cmake_minimum_required(VERSION 3.10)

project(id3tag VERSION 1.0 DESCRIPTION "ID3 Tag Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/ID3/v1/*.cpp"
                  "src/ID3/v2/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

include_directories({PROJECT_NAME} include)