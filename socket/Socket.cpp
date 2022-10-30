#include "Socket.hpp"

Socket::Socket()
    : s_(-1)
{
	s_ = socket(PF_INET, SOCK_STREAM, 0);
}