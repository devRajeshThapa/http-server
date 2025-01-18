#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <map>
#include <functional>
#include <string>

class HTTPServer {
public:
    HTTPServer(int port);
    ~HTTPServer();
    void get(const std::string &path, std::function<void(int)> handler);
    void run_server();

private:
    void handle_request(int client_fd, char *request);

    int server_fd_;
    int port_;
    std::map<std::string, std::function<void(int)>> routes_;
};

#endif // HTTP_SERVER_HPP
