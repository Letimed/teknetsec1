#include "Network.hh"
#include "Socket.hh"
#include "PacketDecrypt.hh"
#include <vector>

int main(int argc, char *argv[])
{
  Socket mySocketTcp;
  Socket mySocketUdp;
  Socket mySocketIcmp;
  Socket mySocket;
  PacketDecrypt myPacketTcp;
  PacketDecrypt myPacketUdp;
  
  if ((mySocketUdp.getConnection(IPPROTO_UDP)) == -1 || (mySocketTcp.getConnection(IPPROTO_TCP)) == -1)
    return -1;
  else
    {
      std::cout << "socket open" << std::endl;
      while(1)
	{

	  //	  myPacketTcp.Decrypt(mySocketUdp.getSocket());
	  //std::cout << "111111111111111" << std::cout;
	  myPacketUdp.Decrypt(mySocketTcp.getSocket());
	  //std::cout << "111111111111111" << std::cout;
	}
    }
  return (0);
}
