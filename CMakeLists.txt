cmake_minimum_required(VERSION 3.10)

# Define the project name and specify languages
project(server++ LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Specify platform-specific settings
if(WIN32)
    message(STATUS "Building for Windows")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/lib/windows)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin/windows)
   
elseif(APPLE)
    message(STATUS "Building for macOS")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/lib/windows)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin/windows)
  
elseif(UNIX)
    message(STATUS "Building for Unix-like OS")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/lib/windows)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin/windows)
 endif()

# Create the static library 
add_library(http_socket STATIC src/http_socket.cpp) 

# Add the executable target and the source files
add_executable(server++ src/server++.cpp)

# Link library (only on Windows) 
if(WIN32) 
    target_link_libraries(http_socket PRIVATE Ws2_32) 
    target_link_libraries(server++ PRIVATE stdc++fs) 
endif()

# Ensuring no binaries in root 
set_target_properties(http_socket PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set_target_properties(server++ PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


# Install commands to copy files to the appropriate directories
install(TARGETS http_socket ARCHIVE DESTINATION lib)
install(TARGETS server++ RUNTIME  DESTINATION bin)

install(FILES LICENSE DESTINATION docs)
install(FILES docs/README_DIST.md DESTINATION docs/README.md)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY dependencies/gcc-14.2.0 DESTINATION bin/)


