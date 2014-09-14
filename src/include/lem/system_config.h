#ifndef LEM_SYSTEM_CONFIG__H
#define LEM_SYSTEM_CONFIG__H
#pragma once

 // 07-04-2007 ��������� ������� GetHostOs()
 // 21.04.2007 - PrintInfo() added.
 // 27.04.2007 - ������������ ����������� GetHomeDir() � GetAppdataDir() ���� ����� ��� lem::Path
 // 22.04.2008 - ��������� IsFilesystemUtf8() � GetFilesystemCP()
 // 23.05.2008 - ��������� IsWin2k()
 // 30.09.2009 - ��������� IsVistaOrNewer() ��� ������ � Server 2008 � WIndows 7

 #include <lem/config.h>
 #include <lem/path.h>
 #include <string>

 namespace lem
 {
  class OFormatter;
  class CodeConverter;

  namespace System_Config
  {
   // ���������� ��� ��������� �������� ��� �������� �����.
   extern const lem::Path GetHomeDir(void);

   extern const lem::Path GetAppdataDir(void);

     // �� ����� ��������� ����������� ���������
   extern const std::string GetHostOs( bool detailed=true );

   // 64-������ �� (��������� ����� ���� 32-������).
   extern bool IsOS64(void);

   // ������������ �� ��������� Unicode ������ � ������� API
   extern bool SupportUnicodeAPI(void);

   // ������������ �� ������� ��������� ���������� ������ _wfopen �
   // ������ ������� ��� UNICODE-���� ������
   extern bool SupportUnicodeFilenames(void);

   // ����� �� � ��������� ������� ������������ ���������� ����� 
   // UNICODE ������
   extern bool SupportUnicodeConsole(void);

   // ������������ �� ������� ��������� UNICODE ��� GUI
   extern bool SupportUnicodeGui(void);

   // Filename are case sensitive (false for Windows, true for Unix by default).
   extern bool FilenamesCaseSensitive(void);

   // ��� ������� ������� (���� � ��������� ����)
   extern const std::string GetHostName(void);

   // ������� ��������� ������
   // \r\n ��� Windows
   // \n ��� Linux
   //
   // ���� escaped=true, �� ������������ ������ ����� ����� ������� ����
   extern const std::string GetLineTerminator( bool escaped );

   // ���������� ������ ������������ ��� ���������������� ���������
   // (� ������).
   extern int GetAlignmentSize(void);

   // ���������� ��� ������������ (�����) ��� ������� ������
   extern const std::string GetUserLogin(void);

   extern bool IsWin9x(void);
   extern bool IsNT4(void);
   extern bool IsWin2k(void);
   extern bool IsUnix(void);
   extern bool IsLinux(void);
   extern bool IsFreeBSD(void);
   extern bool IsTabletPC(void);
   extern bool IsMediaCenter(void);
   extern bool IsVista(void);
   extern bool IsVistaOrNewer(void);

   extern bool IsNetfx10Installed(void);
   extern bool IsNetfx11Installed(void);
   extern int GetNetfx10SPLevel(void);
   extern int GetNetfx11SPLevel(void);

   // ���������� ��������� �������� ������������� ������ .NET�
   extern const std::string GetNetfxInfo(void);

   // ******************************
   // ���������� ��� ���������
   // ******************************
   typedef enum {
                 ADDRESSING_UNKNOWN=-1,
                 ADDRESSING_16_16,     // ������ large memory model �������:��������
                 ADDRESSING_32,        // 32 ���
                 ADDRESSING_64         // 64 ���
                } AddressingType;


   extern AddressingType GetAddressingType(void);

   // Show some brief info about current session.
   extern void PrintInfo( lem::OFormatter &dst );

   // Returns true for L'-' on Unix/Windows and L'/' on Windows/Dos
   extern bool IsCmdLineOption( wchar_t ch );
   extern bool IsCmdLineOption( char ch );


   extern bool IsServiceRunning( const char *DaemonName );
   extern void ShowIndexingServiceControlDialog(void);
   extern bool IsIndexingServiceRunning(void);

   extern bool IsFilesystemUtf8( const lem::Path *path=NULL );
   extern const lem::CodeConverter* GetFilesystemCP( const lem::Path *path=NULL );

  } // namespace System_Config
 } // namespace lem

#endif
 
