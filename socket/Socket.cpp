#include "Socket.hpp"

Socket::Socket()
    : s_(-1)
{
	s_ = socket(PF_INET, SOCK_STREAM, 0);
}

bool Socket::connect()
{
    return false;
}

bool Socket::bind()
{
    return false;
}

bool Socket::listen()
{
    return false;
}

int Socket::accept()
{
    return ::accept(s_, (struct sockaddr*)&addr_, &addr_len_);
}

bool Socket::read()
{
    return ::read();
}

bool Socket::write()
{
    return false;
}