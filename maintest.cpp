#include "Network.hh"

int  recvfrom(int  s,  void  *buf,  size_t len, int flags,
	      struct sockaddr *from, socklen_t *fromlen);


struct sockaddr {
  sa_family_t     sa_family;      /* address family, AF_xxx       */
  char            sa_data[14];    /* 14 bytes of protocol address */
};


struct sockaddr_ll
{
  unsigned short  sll_family;    /* Always AF_PACKET */
  unsigned short  sll_protocol;  /* Physical layer protocol */
  int             sll_ifindex;   /* Interface number */
  unsigned short  sll_hatype;    /* Header type */
  unsigned char   sll_pkttype;   /* Packet type */
  unsigned char   sll_halen;     /* Length of address */
  unsigned char   sll_addr[8];   /* Physical layer address */
};

int main()
{
  sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));      
}
/*
	Decript paquet
 */
paquetDecrypt()
{
    while (1) {
    int n_read;
    char buffer[BUFFER_MAX];
    struct sockaddr_ll      from;
    socklen_t               fromlen = sizeof(from);
    n_read = recvfrom(sock, buffer, 2048, 0, (struct sockaddr*)&from, &fromlen);

    if((from.sll_pkttype==PACKET_BROADCAST)||(from.sll_pkttype==PACKET_MULTICAST))

      continue;
    printf("=====> Packet intercepted, %d bytes sniffed <===== ", n_read);
    switch (from.sll_pkttype) {
    case PACKET_HOST:      printf("Host"); break;
    case PACKET_BROADCAST: printf("Broadcast"); break;
    case PACKET_MULTICAST: printf("Multicast"); break;
    case PACKET_OTHERHOST: printf("Other host"); break;
    case PACKET_OUTGOING:  printf("Outgoing"); break;
    }
    printf("\n");
    switch(level)
      {
      case LEVEL_RAW:
	if(from.sll_hatype==ARPHRD_ETHER)
	  decode(LEVEL_ETH,buffer,n_read);
	break;
      case LEVEL_DGRAM:
	printf("sll_hatype=%x, sll_protocol=%x, sll_ifindex=%u\n",from.sll_hatype,from.sll_protocol,from.sll_ifindex);
      case LEVEL_IP:
	decode(LEVEL_IP,buffer,n_read);
	break;
      }
  }
}
