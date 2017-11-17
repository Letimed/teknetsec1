#include "Network.hh"
#include "Socket.hh"
#include "PacketDecrypt.hh"
#include <vector>
#include <thread>
#include <iostream>
#include <string>

int process(PacketDecrypt *a, Socket *c, bool log)
{
  while (1)
  {  
    a->Decrypt(c->getSocket(), log);
  }
}

int main(int argc, char *argv[])
{
  Socket *mySocketTcp = new Socket();
  Socket *mySocketUdp = new Socket();
  PacketDecrypt *myPacket = new PacketDecrypt();
  PacketDecrypt *myPacketUdp = new PacketDecrypt();
  bool log = false;

  if (argc == 2)
  {
    std::string param = argv[1];
    if (param.compare("-save") == 0)
    {
      std::cout << "ok" << std::endl;
      log = true;
    }
    else
    {
      std::cout << "param non reconnu" << std::endl;
    }
  }

  if (mySocketUdp->Connect(IPPROTO_UDP) == -1 || mySocketTcp->Connect(IPPROTO_TCP) == -1)
  {
    return (-1);
  }  
  else
  {
    std::cout << "socket open" << std::endl;
    int sockettcp = mySocketTcp->getSocket();
    std::thread tcpthread (process, myPacket, mySocketTcp, log);
    std::thread udpthread (process, myPacketUdp, mySocketUdp, log);
    tcpthread.join();
    udpthread.join();
  } 
  return (0);
}
