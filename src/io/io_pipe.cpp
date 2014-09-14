// -----------------------------------------------------------------------------
// File IO_PIPE.CPP
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
// ����� PipeStream - �������� ��������� ������ ����������� ����������
// ������� pipe'��.
// -----------------------------------------------------------------------------
//
// CD->05.11.2000
// LC->16.01.2005
// --------------

#include <io_pipe.h>

using namespace lem;

PipeStream::PipeStream(
                       const lem::Path& Name,
                       bool r,
                       bool w,
                       bool IsItServer,
                       int TimeOut
                      )
:BaseStream( r, w, Name )
{
 failed = false;
 attached = false;
 saPipe.lpSecurityDescriptor = NULL;

 is_it_server = IsItServer;
 if( IsItServer )
  AttachToClient(TimeOut);
 else
  AttachToServer(TimeOut);

 return;
}

PipeStream::~PipeStream(void)
{
 if( is_it_server )
  DetachFromClient();
 else
  DetachFromServer();

 return;
}

// *********************************************************
// ���������� ��������� - ������������ � �������.
// *********************************************************
void PipeStream::AttachToServer( int TimeOut )
{
 bool bSuccess      = false;
 bool bNotConnected = true;

 while( bNotConnected )
  {
   /* attempt to connect to pipe instance */
   hPipe = CreateFile(
                      GetName().Get_Ascii().c_str(),
                      GENERIC_READ | GENERIC_WRITE,
                      0,
                      NULL,
                      OPEN_EXISTING,
                      0,
                      NULL
                     );

   if( GetLastError() == ERROR_PIPE_BUSY )
    {
     // Waiting for a pipe instance...
     bSuccess = WaitNamedPipe( GetName().Get_Ascii().c_str(), TimeOut );
     if( !bSuccess )
      {
       // ������������ �� �������...
       attached = false;
       break;
      }
    }
   else
    {
     if( hPipe==INVALID_HANDLE_VALUE )
      {
       // fault in 'CreateFile'
       attached = false;
       break;
      }

     bNotConnected = (hPipe == INVALID_HANDLE_VALUE);
     if( !bNotConnected )
      attached = true;
    }
  } /* while */

 // ���� attached ����� ���������� ��� true, ���� ����� ����������� �������.

 if( attached==false )
  failed=true;

 return;
}

// **************************************************
// ����������� �� �������.
// **************************************************
void PipeStream::DetachFromServer(void)
{
 CloseHandle(hPipe);
 hPipe = NULL;
 attached = false;
 return;
}

// *********************************************************
// ���������� ��������� - ������������ � �������.
// *********************************************************
void PipeStream::AttachToClient( int TimeOut )
{
 bool bSuccess;
 char *szPname;

 /* set up a NULL DACL in our pipe security descriptor to allow anyone to
    connect to the pipe server */
 saPipe.lpSecurityDescriptor =
       (PSECURITY_DESCRIPTOR)malloc(SECURITY_DESCRIPTOR_MIN_LENGTH);

 InitializeSecurityDescriptor(
                              saPipe.lpSecurityDescriptor,
                              SECURITY_DESCRIPTOR_REVISION
                             );

 SetSecurityDescriptorDacl(
                           saPipe.lpSecurityDescriptor,
                           TRUE,
                           (PACL)NULL,
                           FALSE
                          );

 saPipe.nLength = sizeof(saPipe);
 saPipe.bInheritHandle = TRUE;

 // Create a named pipe: duplex, type byte, readmode byte, unlimited
 // instances, default timeout of 60s
 hPipe = CreateNamedPipe(
                         GetName().Get_Ascii().c_str(),
                         PIPE_ACCESS_DUPLEX | 0,
                         PIPE_TYPE_BYTE |
                         PIPE_READMODE_BYTE |
                         PIPE_WAIT,
                         PIPE_UNLIMITED_INSTANCES,
                         0,
                         0,
                         TimeOut,
                         &saPipe
                        );

 if( hPipe==INVALID_HANDLE_VALUE )
  {
   attached = false;
   failed = true;
   hPipe = NULL;
   return;
  }

 // Wait for a client application to connent.
 bSuccess = ConnectNamedPipe( hPipe, NULL );

 // check return from either ConnectNamedPipe or GetOverlappedResult.
 // If a client managed to connect between the CreateNamedPipe and
 //  ConnectNamedPipe calls, ERROR_PIPE_CONNECTED will result.
 if( !bSuccess && GetLastError()!=ERROR_PIPE_CONNECTED )
  {
   /* something went wrong, report error, close instance and try again */
   attached = false;
   failed = true;
   CloseHandle(hPipe);
   return;
  }
 else
  attached = true;

 if( attached==false )
  failed=true;

 return;
}

// **************************************************
// ����������� �� �������.
// **************************************************
void PipeStream::DetachFromClient(void)
{
 free(saPipe.lpSecurityDescriptor);
 DisconnectNamedPipe(hPipe);
 CloseHandle(hPipe);

 hPipe=NULL;
 attached=false;
 return;
}

// ***********************************************************************
// ������ ����� ����������, �� ������� ��������� src, �������� size, �
// ����� � ������� �������.
// **************************************************
void PipeStream::write( const void *src, BaseStream::pos_type size )
{
 if( !attached || failed || hPipe==NULL )
  return;

 /**/ GetLastError(); // Clear error flag...
 DWORD dwWritten;

 // ������ ���������� ��� ���� ������.
 const bool bSuccess = WriteFile(
                                 hPipe,
                                 src,
                                 size,
                                 &dwWritten,
                                 NULL
                                );

 // ��������� ���������. �������� ���������� ��������.
 IFDEBUG(Check());
 if( !bSuccess )
  {
   attached = false;
   failed = true;
  }
 else
  {
   failed = false;
  }

 return;
}

// *********************************************************************
// ������ ����� ���������� � ������� ������, �� ������� ��������� dest,
// �������� size, � ������� �������.
// *********************************************************************
BaseStream::pos_type PipeStream::read( void *dest, BaseStream::pos_type size )
{
 if( !attached || hPipe==NULL )
  return -1;

 DWORD dwRead=0;

 const bool Success = ReadFile(
                               hPipe,
                               dest,
                               size,
                               &dwRead,
                               NULL
                              );

 // If ReadFile fails, check pipe.
 IFDEBUG(Check());
 if( !Success )
  {
   failed = true;
   attached = false;
   return -1;
  }

 return 0;
}

// *********************************************************************
// ������ �� ������ ��� ���������� ��� ����� �� ����� ��������� ������?
// ����� ����� ��� �������, ������� �������� � ������������ ����
// ���������� ��� �����.
// *********************************************************************
bool PipeStream::isready(void) const
{
 return true;
}

// **************************************************
// ���� ���������� ������ ������.
// **************************************************
void PipeStream::wait_ready(void) const
{
 return;
}

// ********************************************************************
// ������ ���������� �������. ����� ���������� EOF (-1) ��� ����������
// ����� �����. ������������� ������� ������ � ����� �����.
// ********************************************************************
int PipeStream::get(void)
{
 char c;
 read( &c, 1 );
 return 0x00ff & int(c);
}

// **************************************************
// ��������� ������ � ������� ������� � �����.
// **************************************************
void PipeStream::put( char ch )
{
 char b=ch;
 write( &b, 1 );
 return;
}

// **************************************************
// ��������� ���������� ������ ������ � �������.
// **************************************************
void PipeStream::Check(void) const
{
 LEM_CHECKIT( hPipe!=INVALID_HANDLE_VALUE );
 LEM_CHECKIT( !failed );
 LEM_CHECKIT( attached );

 const DWORD dwLastError = GetLastError();
 if( dwLastError == ERROR_BROKEN_PIPE || dwLastError == ERROR_NO_DATA )
  LEM_STOPIT;

 return;
}

// **************************************************
// ���������� ������ �� ������� ������.
// **************************************************
void PipeStream::flush(void)
{
 FlushFileBuffers(hPipe);
 return;
}

// ******************************************************
// ��������� ���������� ����� ����� ��� ��������� ������.
// ******************************************************
bool PipeStream::eof(void) const
{
 // �������, ��� ���� ������ - ��� ����� ������.
 return is_failed();
}

// ***************************************************************************
// �������� ������� ������� ������-������ � ������ - ��� pipe'�� �� ��������.
// ***************************************************************************
BaseStream::pos_type PipeStream::tellp(void) const
{
 LEM_STOPIT;
 return 0;
}

// ***************************************************************************
// ���������� ������ �� �������� �������: ����������� ������� �� ������
// �����, ������� ������� ��� ����� �����, �������� ��������� where_to.
// ��� ������� - ��. �������� ����������� ������� fseek(...).
// ��� pipe'�� �� ��������.
// ***************************************************************************
BaseStream::pos_type PipeStream::seekp( off_type pos, int whereto )
{
 LEM_STOPIT;
 return 0;
}

// ***************************************************************************
// ����������� ������� ������������ ������� �������, � ������ ��� � �����
// ����� �������� ����� �������� offset.
// ��� pipe'�� �� ��������.
// ***************************************************************************
BaseStream::pos_type PipeStream::move( off_type offset )
{
 LEM_STOPIT;
 return 0;
}

// **************************************************
// ���������� ������ ������ � ��������� �����.
// **************************************************
void PipeStream::close(void)
{
 DetachFromServer();
 return;
}

// **************************************************
// ���������� ������� ������ ������.
// ��� pipe'�� �� ��������.
// **************************************************
BaseStream::pos_type PipeStream::fsize(void) const
{
 LEM_STOPIT;
 return 0;
}

// -------------------------- End Of File [IO_PIPE.CPP] ------------------------
