# Minimal HTTP Backend Framework in C++ for C++

## Overview

This project provides a minimal C++ framework for creating a simple HTTP server. It's a lightweight solution suitable for learning purposes, prototyping, or quick deployments where full-fledged web server frameworks are unnecessary. 

## Features 
- **HTTP Request Handling**: Supports basic `GET` requests. 
- **Routing**: Simple routing mechanism to handle different endpoints. 
- **Error Handling**: Provides a 404 Not Found response for unrecognized paths. 
- **Port Configuration**: Allows running the server on a specified port.

## Getting Started

### Platforms 

This project is compatible with the following platforms: 
- **Linux**
- **macOS**
- **Windows Subsystem for Linux (WSL)**

### Requirements
* C++11 (or later) compiler
* CMake 3.10+
* Unix-based system (Linux, macOS) or WSL on Windows

### Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/devrajeshthapa/http-server.git
    cd http-server
    ```

2. **Build the project using CMake**:
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

3. **Install the executables**:
    ```sh
    cmake --install . --prefix ../dist
    ```
   > Note: The `dist` directory will be created at the root of the project.

4. **Write your server code**:
    ```cpp
    #include "http_server.hpp"
    #include <iostream>
    #include <cstring>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

    void setup_routes(HTTPServer &server) {
        server.get("/", [](int client_fd) {
            const char *response = "HTTP/1.1 200 OK\r\n"
                                   "Content-Type: text/html\r\n"
                                   "Content-Length: 13\r\n"
                                   "\r\n"
                                   "<h1>Hello</h1>";
            send(client_fd, response, strlen(response), 0);
            close(client_fd);
        });
    }

    int main() {
        try {
            HTTPServer server(8080);
            setup_routes(server);
            server.run_server();
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        return 0;
    }
    ```

5. **Compile your server code**:
    ```sh
    g++ -I [path to dist/include] -L [path to dist/lib] -lhttp_server your_code_file.cpp -o your_output
    ```
   Replace `[path to dist/include]` and `[path to dist/lib]` with the actual paths to the `include` and `lib` directories inside the `dist` folder. Replace `your_code_file.cpp` with your server code file name and `your_output` with the desired name of the output executable.

6. **Run your server**:
    ```sh
    ./your_output
    ```
   Replace `your_output` with the name of the compiled output executable. Then your server will listen on the port you have provided in the server code. 

7. **Access your server**:
    Open a web browser and navigate to `http://localhost:8080/`, replacing `8080` with the port number you used in your server code. You should see the response specified in your handler, such as `<h1>Hello</h1>`.

### Contributing

We welcome contributions! Please see CONTRIBUTING.md for details on how to get involved.

### License

This project is licensed under the MIT License. See the LICENSE file for details.

### Code of Conduct

Please read our Code of Conduct to understand the standards we expect from our community.

### Acknowledgements

This implementation demonstrates basic socket programming in C++ using Unix APIs. Inspired by various online resources and tutorials on socket programming.
