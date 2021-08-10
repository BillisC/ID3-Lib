include_directories(${id3tag_SOURCE_DIR}/include/ID3/v1 ${id3tag_SOURCE_DIR}/include/ID3/v2)

set(v1_SRC v1/ID3v1.cpp v1/ID3v1_Return.cpp v1/ID3v1_Set.cpp)
set(v2_SRC v2/ID3v2.cpp v2/ID3v2_Return.cpp v2/ID3v2_Set.cpp)

add_library(id3tag STATIC ${v1_SRC} ${v2_SRC})
