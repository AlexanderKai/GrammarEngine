// -----------------------------------------------------------------------------
// File IO_SOCKET.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ��������� ��������������� ������ ����� ������ �����-������ �� ������ pipe'��.
// ���� ������ ��� WinNT/Win2000
//
// ������� �� ������ ���������� Trapper McFerron ( trapzz@hotmail.ru )
// -----------------------------------------------------------------------------
//
// CD->11.04.2002
// LC->15.01.2005
// --------------

#include <lem/config.h>

#include <io_socket.h>
#include <lem/conversions.h>

using namespace lem;
using namespace lem::Sockets;


Lem_IP::Lem_IP(void)
{
 memset( addr, 0, sizeof(addr) );
 iport=0;
 null=false;
 return;
}

// **********************************************************************
// ��������� ������ Str ��������� �� ������ ����� ������������� IP-������
// � ��� ������������� - �� ����� �����.
//
//                123.123.123.123:80
//
// **********************************************************************
Lem_IP::Lem_IP( const char *Str )
{
 memset( addr, 0, sizeof(addr) );
 iport=0;

 str = Str;
 null=false;

 // ��������� �� ������ ��������.
 int i=0, i8=0;
 CString s8;
 int d8;

 while( i<2048 && i8<4 )
  {
   if( Str[i]=='.' || Str[i]==':' || Str[i]=='\0' )
    {
     d8=0;

     if( !to_int(s8.c_str(),&d8) )
      {
       // ����� ����� ����������� - �� � ����� BBB.BBB.BBB.BBB
       null=true;
       break;
      }

     // �������� ��������� ������� - ���������� ����.
     addr[i8++] = d8;
     s8 = "";

     if( Str[i]=='.' )
      i++;
     else
      break;
    }
   else
    s8 += Str[i++];
  }

 if( Str[i]==':' )
  {
   // ��������� ����� �����.
   if( !to_int( Str+i+1, &iport ) )
    {
     // ������ ������� ������ �����.
     null=true;
     return;
    }
  }
 else
  iport=2500; // ����� ����� �� ���������.

 return;
}

// **************************************************
// ���������� ����� � ���� ������ 123.123.123.123
// **************************************************
const CString Lem_IP::get_ip(void) const
{
 CString res;

 if( IsNull() )
  // ��� ������������ ������ ���������� ������ ������.
  return res;

 res += to_str( addr[0] );
 res += '.';
 res += to_str( addr[1] );
 res += '.';
 res += to_str( addr[2] );
 res += '.';
 res += to_str( addr[3] );

 return res;
}

// #########################################################

bool SocketStream::winsock_inited=false;
WSADATA SocketStream::ws;

// **********************************************************************
// ����� IP-����� �����������. ���� bServer=true, �� - � ������ �������.
// **********************************************************************
SocketStream::SocketStream( const char *addr, bool bServer )
{
 failed=false;

 InitWinSocket();

 connected = false;
 IP        = addr;
 sckt      = NULL;

 server = bServer;
 if( server )
  openServerConn();
 else
  openConn();

 return;
}

SocketStream::~SocketStream()
{
 closeConn();
 return;
}

void SocketStream::InitWinSocket(void)
{
 if( !winsock_inited )
  {
   winsock_inited=true;

   if( !!WSAStartup(0x0101,&ws) ) // ���������� 0, ���� ������ ���.
    {
     // ������ ������� ���������� WinSock!!!
     failed = true;
    }
  }

 return;
}

// ********************************************
// ������� �����.
// ********************************************
void SocketStream::openConn(void)
{
 if( failed )
  return;

// int e;

 // ��������� ��������� sockaddr - ��� ������������� � ���������� TCP/IP.
 san.sin_family = AF_INET;
 san.sin_port = htons( IP.get_port() );
 san.sin_addr.s_addr = inet_addr( IP.get_ip().c_str() );
 sanSize = sizeof(san);

 sckt = socket( AF_INET, SOCK_DGRAM, 0 );

 if( sckt==INVALID_SOCKET || !!WSAGetLastError() )
  {
   // ������ �����������!
   connected=false;
   failed=true;
  }

 if( !failed )
  connected = true;

 return;
}

void SocketStream::closeConn(void)
{
 if( failed )
  return;

 shutdown( sckt, 1 );
 closesocket(sckt);
 connected = false;
 sckt = NULL;
 return;
}

void SocketStream::openServerConn(void)
{
 if( failed )
  return;

 //this acts as its own server and accepts any ip address
 //so we can direct connect to it

 san.sin_family = AF_INET;
 san.sin_port = htons(IP.get_port());
 san.sin_addr.s_addr = htonl(INADDR_ANY); // ����� ����� ���� ��������� ��
                                          // ��������� (����������� ����������
                                          // � ����).
 sanSize = sizeof(san);

 sckt = socket(AF_INET, SOCK_DGRAM,0);

 if( sckt==INVALID_SOCKET || !!WSAGetLastError() )
  {
   // ������ �����������!
   connected=false;
   failed=true;
   return;
  }

 if( bind( sckt, (sockaddr *) &san, sanSize )==SOCKET_ERROR )
  {
   // ������ ����������
   connected=false;
   failed=true;
  }

 if( !failed )
  connected = true;

 return;
}

BaseStream::pos_type SocketStream::read( void *dest, size_t size )
{
 int t=recvfrom(sckt,(char*)dest,size,0,(sockaddr *)&san,&sanSize);
 if( t==SOCKET_ERROR )
  failed = true;

 return failed ? -1 : 0;
}

void SocketStream::write( const void *src, size_t size )
{
 int t = sendto(sckt,(char*)src,size,0,(sockaddr *)&san,sanSize);
}

// *************************************************
// ��������� ���������� ������ ������ � �������.
// *************************************************
void SocketStream::Check(void) const
{
}

// ���������� ������ �� ������� ������.
void SocketStream::flush(void)
{
}

// *********************************************************
// ��������� ���������� ����� ����� ��� ��������� ������.
// *********************************************************
bool SocketStream::eof(void) const
{
 return failed || !connected;
}

// �������� ������� ������� ������-������ � ������.
BaseStream::pos_type SocketStream::tellp(void) const
{
 LEM_STOPIT;
 return -1;
}

// ���������� ������ �� �������� �������: ����������� ������� �� ������
// �����, ������� ������� ��� ����� �����, �������� ��������� where_to.
// ��� ������� - ��. �������� ����������� ������� fseek(...).
BaseStream::pos_type SocketStream::seekp( off_type pos, int whereto )
{
 LEM_STOPIT;
 return -1;
}


// ����������� ������� ������������ ������� �������, � ������ ��� � �����
// ����� �������� ����� �������� offset.
BaseStream::pos_type SocketStream::move( off_type offset )
{
 LEM_STOPIT;
 return -1;
}

// ���������� ������ ������ � ��������� �����.
void SocketStream::close(void)
{
 closeConn();
 return;
}

// ���������� ������� ������ ������.
BaseStream::pos_type SocketStream::fsize(void) const
{
 LEM_STOPIT;
 return 0;
}

// ������ �� ������ ��� ���������� ��� ����� �� ����� ��������� ������?
// ����� ����� ��� �������, ������� �������� � ������������ ����
// ���������� ��� �����.
bool SocketStream::isready(void) const
{
 LEM_STOPIT;
 return true;
}

// ���� ���������� ������ ������.
void SocketStream::wait_ready(void) const
{
 LEM_STOPIT;
}

// ������ ���������� �������. ����� ���������� EOF (-1) ��� ����������
// ����� �����. ������������� ������� ������ � ����� �����.
int SocketStream::get(void)
{
 char ch;
 read(&ch,1);
 return ch;
}

// ��������� ������ � ������� ������� � �����.
void SocketStream::put( char ch )
{
 write(&ch,1);
}

// -------------------------- End Of File [IO_SOCKET.CPP] -----------------------
