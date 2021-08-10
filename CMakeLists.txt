cmake_minimum_required(VERSION 3.10)

set(CMAKE_INSTALL_PREFIX ${id3tag_SOURCE_DIR}/output)

project(id3tag VERSION 1.0 DESCRIPTION "ID3 Tag Library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

install(TARGETS id3tag DESTINATION lib)
install(DIRECTORY ${id3tag_SOURCE_DIR}/include/v1 DESTINATION include)
install(DIRECTORY ${id3tag_SOURCE_DIR}/include/v2 DESTINATION include)
install(FILES ${id3tag_SOURCE_DIR}/include/tools.h DESTINATION include)