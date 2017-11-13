#include "PacketDecrypt.hh"
#include <iostream>
#include <unistd.h>

int PacketDecrypt::Decrypt(const int sock)
{
  struct sockaddr _sockaddr;
  char buff[64000];
  ssize_t size;

  if ((size = recv(sock, buff, 64000, 0)) == -1 || size == 0)
    {
      std::cerr << "echec receive packet or packet null" << std::endl;
      return -1;
    }
  else
    {
      std::cout << "receive ok" << std::endl;
      Display(size, buff);
      return 0;
    }
}

void PacketDecrypt::Display(int size, char *buff)
{
  struct iphdr* mystruct = (struct iphdr*)buff;
  
  print_header(mystruct ,size);
  if (mystruct->protocol == 1)
    {
      //icmp
    }
  else if (mystruct->protocol == 2)
    {
      //igmp
    }
  else if (mystruct->protocol == 6)
    {
      print_tcp(buff, size); // tcp
      //print_header(buff, ipheadersize);
      //print_data(buff, size);
    }
  else if (mystruct->protocol == 17)
    {
      print_udp(buff, size);// udp
      //    print_data(buff, size);
    }
  return;
}

void PacketDecrypt::print_header(struct iphdr* mystruct, int length)
{
  struct sockaddr_in source;
  struct sockaddr_in destination;

  source.sin_addr.s_addr = mystruct->saddr;
  destination.sin_addr.s_addr = mystruct->daddr;
  
  std::cout << "===========IPHEADER===========" << std::endl;
  std::cout << "   |-iph_header_len : " << mystruct->ihl << std::endl;
  std::cout << "   |-iph_version : " << mystruct->version << std::endl;
  std::cout << "   |-iph_tos : "<< mystruct->tos << std::endl;
  std::cout << "   |-iph_total_length : " << mystruct->tot_len << std::endl;
  std::cout << "   |-iph_id : " << mystruct->id << std::endl;
  std::cout << "   |-iph_ttl : "<< mystruct->ttl << std::endl;
  std::cout << "   |-iph_checksum : "<< mystruct->check << std::endl;
  std::cout << "   |-iph_source :  "<< inet_ntoa(source.sin_addr) << std::endl;
  std::cout << "   |-iph_destination : "  << inet_ntoa(destination.sin_addr) << std::endl;
}

void PacketDecrypt::print_tcp(char* buff, int size)
{
  struct iphdr *iph = (struct iphdr *)buff;
  int iphdrlen = iph->ihl*4;

  struct tcphdr *tcpheader=(struct tcphdr*)(buff + iphdrlen);
  
  std::cout << "===========TCP===========" << std::endl;
  std::cout << "   |-Source Port : " << tcpheader->source << std::endl;
  std::cout << "   |-Destination Port : " << tcpheader->dest << std::endl;
  std::cout << "   |-Sequence Number : " << tcpheader->seq << std::endl;
  std::cout << "   |-Acknowledge Number : "<< tcpheader->ack_seq << std::endl;
  std::cout << "   |-Header Length : " << tcpheader->doff << std::endl;
  std::cout << "   |-Urgent Flag : "<< tcpheader->urg << std::endl;
  std::cout << "   |-Acknowledgement Flag :  "<< tcpheader->ack << std::endl;
  std::cout << "   |-Push Flag : " << tcpheader->psh << std::endl;
  std::cout << "   |-Reset Flag : " << tcpheader->rst << std::endl;
  std::cout << "   |-Synchronise Flag : " << tcpheader->syn << std::endl;
  std::cout << "   |-Finish Flag : " << tcpheader->fin << std::endl;
  std::cout << "   |-Window : " << tcpheader->window << std::endl;
  std::cout << "   |-Checksum : " << tcpheader->check << std::endl;
  std::cout << "   |-Urgent Pointer : " << tcpheader->urg_ptr << std::endl;

  std::cout << "ip header " << std::endl;
  print_data(buff, iphdrlen);
  std::cout << "tcp header " << std::endl;
  print_data(buff + iphdrlen, tcpheader->doff * 4);
  std::cout << "tcp data" << std::endl;
  print_data(buff + iphdrlen + tcpheader->doff * 4, (size - tcpheader->doff*4 - iph->ihl*4));
}

void PacketDecrypt::print_udp(char* buff, int size)
{
  struct udphdr* udpheader;
  udpheader = (struct udphdr *)(buff, size);

  std::cout << "===========UDP===========" << std::endl;
  std::cout << "4444444'" << std::endl;
  std::cout << "   |-Source Port      : %d\n" << ntohs(udpheader->source) << std::endl; // segfault
  std::cout << "555555" << std::endl;
  std::cout << "   |-Destination Port : %d\n" << ntohs(udpheader->dest) << std::endl;
  std::cout << "   |-UDP Length       : %d\n" << ntohs(udpheader->len) << std::endl;
  std::cout << "   |-UDP Checksum     : %d\n" << ntohs(udpheader->check) << std::endl;
}

void PacketDecrypt::print_data(char *buff, int size)
{
  int i;

  i = 0;
  while (i < size)
    {
      if (buff[i] > 32 && buff[i] < 128)
	  std::cout << buff[i];
      else
	std::cout << ".";
      i++;
    }
  std::cout <<  std::endl;
}
