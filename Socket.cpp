#include "Socket.hh"
#include <iostream>
#include <unistd.h>

Socket::Socket()
{

}

Socket::~Socket()
{

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
