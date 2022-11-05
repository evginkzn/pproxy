#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Socket
{
public:
    struct Address
    {
        sockaddr_in is;
        int length;
    };

public:
    Socket();
    Socket(int descr, Address address);
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    ~Socket(){ close(); }

    int get_descriptor() const { return s_; }

    bool set_address();
    Address get_address() const
    {
        return addr_;
    }

    int connect(Address address);
    int bind(Address address);
    int listen(int queue_size);
    int accept(Address& address);
    int receive(uint8_t* data, size_t length);
    int send(const uint8_t* data, size_t length);
    int close();

private:
    int s_;
    Address addr_;
};

#endif // ! SOCKET_HPP