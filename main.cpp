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
  Socket mySocketIcmp;
  Socket *mySocket = new Socket();
  PacketDecrypt *myPacket = new PacketDecrypt();
  PacketDecrypt *myPacketUdp = new PacketDecrypt();
  PacketDecrypt myPacketTcp;
  bool log = false;
  //PacketDecrypt myPacketUdp;
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
    //std::thread udpthread (process, myPacketUdp, mySocketUdp, log);
    tcpthread.join();
    //udpthread.join();
  }  
  /*  while(1)
    {
      myPacket->Decrypt(mySocketTcp->getSocket(), log);
      myPacketUdp->Decrypt(mySocketUdp->getSocket(), log);
    }
    free(mySocketUdp);
    free(mySocketTcp);
  }*/
 

  /*
  if ((mySocketUdp.getConnection(IPPROTO_UDP)) == -1 || (mySocketTcp.getConnection(IPPROTO_TCP)) == -1)
    {
      return -1;
      //free(mySocketTcp);
      //free(mySocketUdp);
    }
  else
    {
      std::cout << "socket open" << std::endl;
      while(1)
    	{
	  	    myPacketTcp.Decrypt(mySocketUdp.getSocket());
          myPacketUdp.Decrypt(mySocketTcp.getSocket());
        //  free(mySocketTcp);
          //free(mySocketTcp);
	   }
    }
    */
  return (0);
}
