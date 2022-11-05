#include "Socket.hpp"

#include <cstdlib>
#include <cstring>
#include <unistd.h>

Socket::Socket()
    : s_(-1)
{
	s_ = socket(PF_INET, SOCK_STREAM, 0);
}

Socket::Socket(int descr, Address address)
    : s_(descr)
{
    memcpy(&addr_, &address, sizeof(address));
}

int Socket::connect(Address address)
{
    return ::connect(s_, (struct sockaddr*)&(address.is), address.length);
}

int Socket::bind(Address address)
{
    memcpy(&addr_, &address, sizeof(address));
    return ::bind(s_, (struct sockaddr*)&(addr_.is), addr_.length);
}

int Socket::listen(int queue_size)
{
    return ::listen(s_, queue_size);
}

int Socket::accept(Address& address)
{
    int result = -1;
    result = ::accept(s_, (struct sockaddr*)&(address.is), (socklen_t*)&(address.length));
    return result;
}

int Socket::receive(uint8_t* data, size_t length)
{
    if (data == nullptr)
    {
        return -1;
    }

    return ::read(s_, data, length);
}

int Socket::send(const uint8_t* data, size_t length)
{
    if (data == nullptr)
    {
        return -1;
    }
    
    return ::write(s_, data, length);
}

int Socket::close()
{
    return ::close(s_);
}