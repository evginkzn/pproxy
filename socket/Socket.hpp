#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>

class Socket
{
public:
    Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    ~Socket(){}

    bool connect();
    bool bind();
    bool listen();
    bool accept();
    bool read();
    bool write();

private:
    int s_;
};

#endif // ! SOCKET_HPP