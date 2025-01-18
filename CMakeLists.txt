cmake_minimum_required(VERSION 3.28.3)

project(http-server LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(http_server STATIC src/http_server.cpp) 

install(TARGETS http_server ARCHIVE DESTINATION lib)
install(FILES LICENSE DESTINATION docs)
install(FILES docs/README_DIST.md DESTINATION docs RENAME README.md)


