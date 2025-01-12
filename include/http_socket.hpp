#ifndef HTTPSocket_H
#define HTTPSocket_H

#include <winsock2.h>
#include <map>
#include <functional>
#include <string>

class HTTPSocket {
public:
    HTTPSocket(int port);
    ~HTTPSocket();
    void get(const std::string& path, std::function<void(SOCKET)> handler);
    void run_server();
    void handle_request(SOCKET client_fd, char* request);

private:
    int port_;
    SOCKET server_fd_;
    std::map<std::string, std::function<void(SOCKET)>> routes_;
};

#endif // HTTPSocket_H

