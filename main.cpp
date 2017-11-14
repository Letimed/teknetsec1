#include "Network.hh"
#include "Socket.hh"
#include "PacketDecrypt.hh"
#include <vector>
#include <thread>
#include <iostream>

int main(int argc, char *argv[])
{
  Socket mySocketTcp;
  Socket mySocketUdp;
  Socket mySocketIcmp;
  Socket mySocket;
  PacketDecrypt myPacketTcp;
  PacketDecrypt myPacketUdp;
  
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
  return (0);
}
