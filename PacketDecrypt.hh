#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <string.h>

struct header
{
    unsigned char  iph_header_len;
    unsigned char  iph_version;
    unsigned char  iph_tos; // type service
    unsigned short iph_total_length;
    unsigned short iph_id;
    unsigned char  iph_ttl;
    unsigned char  iph_protocol;
    unsigned short iph_checksum;
    char           *iph_source;
  char        *iph_destination;
};

struct packetHeader
{
  int length;
  char *header;
};

struct packetData
{
  int length;
  char *data;
};


class PacketDecrypt
{
public :
  int Decrypt(const int);
  void Display(int, char*);
  void print_tcp(char*, int);
  void print_udp(char*, int);
  void print_header(struct iphdr*, int);  
  void print_data(char *, int);
};
