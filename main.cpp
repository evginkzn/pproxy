#include <iostream>
#include <cstring>
#include <cerrno>


#include "Socket.hpp"

#define BUFFER_LENGTH 1024
#define TEST_PORT htons((unsigned short)atoi("1234"));
#define SOCKET_QUEUE_SIZE 25

static uint8_t buffer[BUFFER_LENGTH];

static void create_bind_addr(Socket::Address& address);

int main(int argc, char* argv[])
{
    Socket server_sock;

    std::cout << "Hello!" << std::endl;

    Socket::Address bind_address;
    create_bind_addr(bind_address);

    if (server_sock.bind(bind_address) < 0)
    {
        std::cout << "Error on binding socket: " 
            << strerror(errno) 
            << std::endl;
        return - 1;
    }
    if (server_sock.listen(SOCKET_QUEUE_SIZE) < 0)
    {
        std::cout << "Error on listening operation: " 
            << strerror(errno) 
            << std::endl;
        return -1;
    }

    std::cout << "Socket binded" << std::endl;

    while(1)
    {
        Socket::Address client_address;
        int client_sock_descr = server_sock.accept(client_address);
        if (client_sock_descr < 0)
        {
            std::cout << "Error on accepting connection: " 
                      << strerror(errno) 
                      << std::endl;
        }
        else
        {
            std::cout << "Accepted connection from:"
                      << inet_ntoa(client_address.is.sin_addr)
                      << std::endl;
            Socket client_sock(client_sock_descr, client_address);
            if (client_sock.receive(buffer, BUFFER_LENGTH))
            {
                if(strstr((char*)buffer, "hello"))
                {
                    memset((char*)buffer, 0, BUFFER_LENGTH);
                    strcpy((char*)buffer, "kek, ");
                    strcat((char*)buffer, inet_ntoa(client_address.is.sin_addr));
                    strcat((char*)buffer, " !!!\n\0");
                    client_sock.send(buffer, BUFFER_LENGTH);
                }
            }
            std::cout << "Connection closed" << std::endl;
            client_sock.close();
        }
    }
    server_sock.close();
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