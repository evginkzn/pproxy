#ifndef PROXY_HPP
#define PROXY_HPP

#include "Socket.hpp"

class Proxy
{
public:
    Proxy();
    ~Proxy();

public:
    bool set_server_addr();
    bool set_client_addr();

    bool init();
    
    bool attach_logger();
    
private:
    Socket s;
};

#endif // ! PROXY_HPP