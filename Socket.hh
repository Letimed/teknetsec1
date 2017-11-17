#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

class Socket
{
 private:
  int _socket;

 public:
  Socket();
  ~Socket();
  int getSocket() const;
  int getConnection(int);
  int Connect(int);
};
