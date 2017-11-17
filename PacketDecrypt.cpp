#include "PacketDecrypt.hh"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

PacketDecrypt::PacketDecrypt()
{

}

int PacketDecrypt::Decrypt(const int sock, bool log)
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
      Display(size, buff, log);
      return 0;
    }
}

void PacketDecrypt::Display(int size, char *buff, bool log)
{
  struct iphdr* mystruct = (struct iphdr*)buff;
  /*if (FILTER)
  {
    if (PROTOCOL != mystruct->protocol)
    {
      std::cout << "heeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeellllllllllllllllllllllllllllllllllllllllllllllllllooooooooooooooooooooooooooooooooooooooo" << std::endl;
      return;
    }
  } */
  print_header(mystruct ,size, log);
  switch (mystruct->protocol)
  {
      case 6:
        print_tcp(buff, size, log);
      case 17:
        print_udp(buff,size, log);
      break;
  }
}

void PacketDecrypt::print_header(struct iphdr* mystruct, int length, bool log)
{
  std::ofstream myfile;
  myfile.open("./log.txt", std::ofstream::out | std::ofstream::app);
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

  if (log == true)
  {
    if (myfile)
    {
        myfile << "===========IPHEADER===========" << std::endl;
        myfile << "   |-iph_header_len : " << mystruct->ihl << std::endl;
        myfile << "   |-iph_version : " << mystruct->version << std::endl;
        myfile << "   |-iph_tos : "<< mystruct->tos << std::endl;
        myfile << "   |-iph_total_length : " << mystruct->tot_len << std::endl;
        myfile << "   |-iph_id : " << mystruct->id << std::endl;
        myfile << "   |-iph_ttl : "<< mystruct->ttl << std::endl;
        myfile << "   |-iph_checksum : "<< mystruct->check << std::endl;
        myfile << "   |-iph_source :  "<< inet_ntoa(source.sin_addr) << std::endl;
        myfile << "   |-iph_destination : "  << inet_ntoa(destination.sin_addr) << std::endl; 
    }
  }

}

void PacketDecrypt::print_tcp(char* buff, int size, bool log)
{
  std::ofstream myfile;
  myfile.open("./log.txt", std::ofstream::out | std::ofstream::app);
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

 if (log == true)
  {
    if (myfile)
    {
      myfile << "===========TCP===========" << std::endl;
      myfile << "   |-Source Port : " << tcpheader->source << std::endl;
      myfile << "   |-Destination Port : " << tcpheader->dest << std::endl;
      myfile << "   |-Sequence Number : " << tcpheader->seq << std::endl;
      myfile << "   |-Acknowledge Number : "<< tcpheader->ack_seq << std::endl;
      myfile << "   |-Header Length : " << tcpheader->doff << std::endl;
      myfile << "   |-Urgent Flag : "<< tcpheader->urg << std::endl;
      myfile << "   |-Acknowledgement Flag :  "<< tcpheader->ack << std::endl;
      myfile << "   |-Push Flag : " << tcpheader->psh << std::endl;
      myfile << "   |-Reset Flag : " << tcpheader->rst << std::endl;
      myfile << "   |-Synchronise Flag : " << tcpheader->syn << std::endl;
      myfile << "   |-Finish Flag : " << tcpheader->fin << std::endl;
      myfile << "   |-Window : " << tcpheader->window << std::endl;
      myfile << "   |-Checksum : " << tcpheader->check << std::endl;
      myfile << "   |-Urgent Pointer : " << tcpheader->urg_ptr << std::endl;
    }
  }

  print_data(buff, iphdrlen, log);
  std::cout << "TCP Header" << std::endl;
  myfile << "TCP Header" << std::endl;
  print_data(buff + iphdrlen, tcpheader->doff * 4, log);
  std::cout << "TCP body " << std::endl;
  myfile << "TCP body " << std::endl;
  print_data(buff + iphdrlen + tcpheader->doff * 4, size - (tcpheader->doff * 4 + iphdrlen), log);
}

void PacketDecrypt::print_udp(char* buff, int size, bool log)
{
  std::ofstream myfile;
  myfile.open("./log.txt", std::ofstream::out | std::ofstream::app);
  struct iphdr *iph = (struct iphdr *)buff;
  int iphdrlen = iph->ihl * 4;
  struct udphdr* udpheader = (struct udphdr *)(buff + size);

  std::cout << "===========UDP===========" << std::endl;
  std::cout << "   |-Source Port      : " << udpheader->source << std::endl;
  std::cout << "   |-Destination Port : " << ntohs(udpheader->dest) << std::endl;
  std::cout << "   |-UDP Length       : " << ntohs(udpheader->len) << std::endl;
  std::cout << "   |-UDP Checksum     : " << ntohs(udpheader->check) << std::endl;

  if (log == true)
  {
    if (myfile)
    {
      myfile << "===========UDP===========" << std::endl;
      myfile << "   |-Source Port      : " << udpheader->source << std::endl;
      myfile << "   |-Destination Port : " << ntohs(udpheader->dest) << std::endl;
      myfile << "   |-UDP Length       : " << ntohs(udpheader->len) << std::endl;
      myfile << "   |-UDP Checksum     : " << ntohs(udpheader->check) << std::endl;
    }
  }

  std::cout << "ip header " << std::endl;
  myfile << "ip header" << std::endl;
  print_data(buff, iphdrlen, log);
  std::cout << "udp header " << std::endl;
  myfile << "udp header" << std::endl;
  print_data(buff + iphdrlen, udpheader->len, log);
  std::cout << "udp data" << std::endl;
  myfile << "udp data " << std::endl;
  print_data(buff + iphdrlen + udpheader->len, (size - udpheader->len - iph->ihl*4), log);
}

void PacketDecrypt::print_data(char *buff, int size, bool log)
{
  int i;
  std::string mydata;

  i = 0;
  while (i < size)
    {
      if (buff[i] > 32 && buff[i] < 127)
	       mydata.push_back(buff[i]);
      else
	       mydata.push_back('.');
      i++;
    }
  mydata.push_back('\n');

  std::cout << mydata;
 if (log == true)
  {
    std::ofstream myfile;
    myfile.open("./log.txt", std::ofstream::out | std::ofstream::app);
    if (myfile)
    {
       myfile << mydata;
    }
  }
}

