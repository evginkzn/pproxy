#include "Proxy.hpp"

#include <iostream>
#include <cstring>
#include <cerrno>

#include <netdb.h>

extern errno;

#define BIND_PORT htons((unsigned short)atoi("1234"));

static void create_bind_addr(Socket::Address& address);
static bool create_connect_addr(Socket::Address& address, const char *host, const char *port);

Socket::Address bind_address;

Proxy::Proxy()
{

}

Proxy::~Proxy()
{

}

bool Proxy::set_server_addr()
{
    return false;
}

bool Proxy::set_client_addr()
{
    return false;
}

bool Proxy::init()
{
    create_bind_addr(bind_address);

    if (server_s_.bind(bind_address) < 0)
    {
        std::cout << "Error on binding socket: " 
            << strerror(errno) 
            << std::endl;
        return false;
    }
    if (server_s_.listen(SocketQueueItemCount) < 0)
    {
        std::cout << "Error on listening operation: " 
            << strerror(errno) 
            << std::endl;
        return false;
    }

    std::cout << "Server socket created & bind" << std::endl;

    if (client_s_.get_descriptor() < 0)
    {
        std::cout << "Failed to create socket: "
                  << strerror(errno)
                  << std::endl;
        return false;
    }

    Socket::Address server_address;
    if ( ! create_connect_addr(server_address, "127.0.0.1", "5432"))
    {
        std::cout << "Can't create connection address" << std::endl;
        return false;
    }

    if (client_s_.connect(server_address) < 0)
    {
        std::cout << "Can't connect to server: "
                  << strerror(errno)
                  << std::endl;
        return false;
    }

    std::cout << "Client socket created and connected" << std::endl;

    return true;
}

bool Proxy::attach_logger()
{
    return false;
}

static Socket::Address down_client_addr;

int Proxy::run()
{
    while(1)
    {
        int client_sock_descr = server_s_.accept(&down_client_addr);
        if (client_sock_descr < 0)
        {
            std::cout << "Error on accepting connection: " 
                      << strerror(errno) 
                      << std::endl;
        }
        else
        {
            std::cout << "Accepted connection from:"
                      << inet_ntoa(down_client_addr.is.sin_addr)
                      << std::endl;
            Socket  down_client_sock(client_sock_descr, down_client_addr);
            memset(buffer_, 0, BufferSize);
            if (down_client_sock.receive(buffer_, BufferSize))
            {
                std::cout << buffer_ << std::endl;
                server_s_.send(buffer_, BufferSize);
            }
            /*down_client_sock.close();
            std::cout << "Connection closed" << std::endl;*/
        }
    }
}

static void create_bind_addr(Socket::Address& address)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = BIND_PORT;

    memcpy(&address, &addr, sizeof(addr));
    address.length = sizeof(addr);
}

static bool create_connect_addr(Socket::Address& address, const char *host, const char *port)
{
    if (host == nullptr || port == nullptr)
    {
        return false;
    }

    sockaddr_in addr;
    struct hostent *phe;

    addr.sin_family = AF_INET;
    addr.sin_port = htons((unsigned short)atoi(port));

    if (phe == gethostbyname(host))
    {
        memcpy(&addr.sin_addr, phe->h_addr, phe->h_length);
    }

    memcpy(&address, &addr, sizeof(addr));
    address.length = sizeof(addr);

    return true;
}