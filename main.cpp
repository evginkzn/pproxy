#include <iostream>
#include <cstring>
#include <cerrno>
#include <netdb.h>

#include "Socket.hpp"

#define BUFFER_LENGTH 1024
#define TEST_PORT htons((unsigned short)atoi("1234"));
#define SOCKET_QUEUE_SIZE 25

extern errno;

static uint8_t buffer[BUFFER_LENGTH];

static void create_bind_addr(Socket::Address& address);
static bool create_connect_addr(Socket::Address& address, const char *host, const char *port);

int main(int argc, char* argv[])
{
    Socket client_socket;

    if (client_socket.get_descriptor() < 0)
    {
        std::cout << "Failed to create socket: "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    Socket::Address server_address;
    if ( ! create_connect_addr(server_address, "127.0.0.1", "1234"))
    {
        std::cout << "Can't create connection address" << std::endl;
        return -1;
    }

    if (client_socket.connect(server_address) < 0)
    {
        std::cout << "Can't connect to server: "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    memset(buffer, 0, BUFFER_LENGTH);
    strcpy((char*)buffer, "hello");
    
    if (client_socket.send(buffer, BUFFER_LENGTH) < 0)
    {
        std::cout << "Can't send data to server: "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }
    
    memset(buffer, 0, BUFFER_LENGTH);
    if (client_socket.receive(buffer, BUFFER_LENGTH) < 0)
    {
        std::cout << "Can't receive data from server: "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Server response: "
                  << buffer
                  << std::endl;
    }
    client_socket.close();

    std::getchar();
    return 0;
}

static void create_bind_addr(Socket::Address& address)
{
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = TEST_PORT;

    memcpy(&address, &addr, sizeof(addr));
    address.length = sizeof(addr);
}

static bool create_connect_addr(Socket::Address& address, const char *host, const char *port)
{
    if (host == nullptr || port == nullptr)
    {
        return false;
    }

    std::cout << "Creating address for connection server " 
              << host << ":" << port << std::endl;

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