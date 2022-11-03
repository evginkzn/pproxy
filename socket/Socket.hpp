#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Socket
{
public:

public:
    Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    ~Socket(){}

    bool set_address();

    bool connect();
    bool bind();
    bool listen();
    int accept();
    bool read();
    bool write();

private:
    int s_;
    sockaddr_in addr_;
    socklen_t addr_len_;
};

#endif // ! SOCKET_HPP