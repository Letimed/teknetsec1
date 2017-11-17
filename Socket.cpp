#include "Socket.hh"
#include <iostream>
#include <unistd.h>

Socket::Socket()
{

}

Socket::~Socket()
{
	close(_socket);
}

int Socket::getSocket() const
{
  return _socket;
}

int Socket::getConnection(int prot)
{
  if ((_socket = socket(AF_INET, SOCK_RAW, prot)) == -1)
    {
      std::cout << "echec open socket" << std::endl;
      return -1;
    }
  else
    return _socket;
}

int Socket::Connect(int protocol)
{
    for (int i = 0; i < 10; ++i)
    {
        if((_socket = socket(AF_INET, SOCK_RAW, protocol)) != -1)
        {
            return 0;
        }
        else
        {
            std::cerr << "Attempt " << i << " / 10" << std::endl;
            sleep(1);
        }
    }
    std::cerr << strerror(errno) << std::endl;
    return -1;
}