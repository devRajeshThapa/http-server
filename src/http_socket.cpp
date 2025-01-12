#include <winsock2.h>
#include "../include/http_socket.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

HTTPSocket::HTTPSocket(int port)
{
    WSADATA wsaData;
    this->port_ = port;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("WSAStartup failed");
    }

    this->server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd_ == INVALID_SOCKET)
    {
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(this->port_);
    if (bind(this->server_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        closesocket(this->server_fd_);
        WSACleanup();
        throw std::runtime_error("Bind failed");
    }
    if (listen(server_fd_, 3) == SOCKET_ERROR)
    {
        closesocket(this->server_fd_);
        WSACleanup();
        throw std::runtime_error("Listen failed");
    }
}

HTTPSocket::~HTTPSocket()
{
    closesocket(this->server_fd_);
    WSACleanup();
}

void HTTPSocket::get(const std::string &path, std::function<void(SOCKET)> handler)
{
    this->routes_[path] = handler;
}

void HTTPSocket::run_server()
{
    std::cout << "HTTP Server is listening on port " << this->port_ << std::endl;
    SOCKET client_fd;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[1024] = {0};
    while (true)
    {
        client_fd = accept(this->server_fd_, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd == INVALID_SOCKET)
        {
            std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
        if (bytes_read > 0)
        {
            std::cout << "Received request: " << buffer << std::endl;
            handle_request(client_fd, buffer);
        }
        else
        {
            closesocket(client_fd);
        }
    }
}

void HTTPSocket::handle_request(SOCKET client_fd, char *request)
{
    for (const auto &route : routes_)
    {
        if (strstr(request, ("GET " + route.first + " HTTP/1.1").c_str()))
        {
            route.second(client_fd);
            return;
        }
    } // Default 404 Not Found response
    const char *RESPONSE_404 = "HTTP/1.1 404 Not Found\r\n"
                               "Content-Type: text/html\r\n"
                               "Content-Length: 23\r\n"
                               "\r\n"
                               "<p>404 - Not Found</p>";
    send(client_fd, RESPONSE_404, strlen(RESPONSE_404), 0);
    std::cout << "404 Not Found response sent to client." << std::endl;
    closesocket(client_fd);
};

