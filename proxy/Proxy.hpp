#ifndef PROXY_HPP
#define PROXY_HPP

#include "Socket.hpp"

class Proxy
{
private:
    enum
    {
        SocketQueueItemCount = 16,
        BufferSize = 1024
    };

public:
    Proxy();
    ~Proxy();

public:
    bool set_server_addr();
    bool set_client_addr();

    bool init();
    
    bool attach_logger();
    
    int run();

private:
    Socket server_s_;
    Socket client_s_;
    uint8_t buffer_[BufferSize];
};

#endif // ! PROXY_HPP