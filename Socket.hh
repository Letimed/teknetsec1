#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket
{
 private:
  int _socket;

 public:
  Socket();
  ~Socket();
  int getSocket() const;
  int getConnection(int);
};
