#include <iostream>

#include "Proxy.hpp"

int main(int argc, char* argv[])
{
    Proxy proxy;

    if ( ! proxy.init())
    {
        std::cout << "Can't initialize proxy" << std::endl;
        return -1;
    }

    proxy.run();

    std::getchar();
    return 0;
}