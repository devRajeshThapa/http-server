#include "http_server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <stdexcept>

HTTPServer::HTTPServer(int port) {
    this->port_ = port;
    this->server_fd_ = socket(AF_INET, SOCK_STREAM, 0);

    if (this->server_fd_ < 0) {
        throw std::runtime_error("Socket creation failed");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(this->port_);

    if (bind(this->server_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(this->server_fd_);
        throw std::runtime_error("Bind failed");
    }

    if (listen(this->server_fd_, 3) < 0) {
        close(this->server_fd_);
        throw std::runtime_error("Listen failed");
    }
}

HTTPServer::~HTTPServer() {
    close(this->server_fd_);
}

void HTTPServer::get(const std::string &path, std::function<void(int)> handler) {
    this->routes_[path] = handler;
}

void HTTPServer::run_server() {
    std::cout << "HTTP Server is listening on port " << this->port_ << std::endl;
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[1024] = {0};

    while (true) {
        client_fd = accept(this->server_fd_, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_read > 0) {
            std::cout << "Received request: " << buffer << std::endl;
            handle_request(client_fd, buffer);
        } else {
            close(client_fd);
        }
    }
}

void HTTPServer::handle_request(int client_fd, char *request) {
    for (const auto &route : this->routes_) {
        if (strstr(request, ("GET " + route.first + " HTTP/1.1").c_str())) {
            route.second(client_fd);
            return;
        }
    }

    const char *RESPONSE_404 = "HTTP/1.1 404 Not Found\r\n"
                               "Content-Type: text/html\r\n"
                               "Content-Length: 23\r\n"
                               "\r\n"
                               "<p>404 - Not Found</p>";
    send(client_fd, RESPONSE_404, strlen(RESPONSE_404), 0);
    std::cout << "404 Not Found response sent to client." << std::endl;
    close(client_fd);
}
