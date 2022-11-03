#include <iostream>

#include "Socket.hpp"

int main(int argc, char* argv[])
{
    Socket sock;

    std::cout << "Hello!" << std::endl;

    while(1)
    {
        sock.accept();
    }

    return 0;
}

