#ifndef LEM_SHELL__H
#define LEM_SHELL__H
#pragma once

// CD->14.12.2006
// LC->06.03.2010
// --------------

 #include <lem/config.h>
 #include <lem/containers.h>
 #include <lem/path.h>

 #if defined LEM_QT
  #include <QWidget>
 #endif

 namespace lem
 {
  namespace Shell
  {
   // �������� ��������� � ��������������� � ��� ���������, ��������
   // ���-������ � �.�.
   extern bool Execute( const wchar_t *Filename );
   extern bool Execute( const UFString &Filename );
   extern bool Execute( const UFString& Appname, const UFString &Filename, bool Silent=false );
   extern bool Execute( const lem::Path &Filename );

   // ���������� ��������� ������, ������� ����� �������� ����� ���������� ���
   // �� ��������.
   extern int CommandLine( const lem::UFString &cmdline );


   // ����������� ��������� ���� � ����� ������
   extern bool PathToClipboard( void* hWnd, const wchar_t *path );

   // ����������� ������ ���� ������ � ����� ������
   extern bool PathsToClipboard( void* hWnd, const lem::Collect<UFString> &lst );

   // ���� ������
   extern void ErrorBeep(void);

   // ������� ��������� �� ������
   extern void Error( const wchar_t *Text ); 
   extern void Error( const char *Text ); 
   extern void Error( const lem::FString &Text ); 
   extern void Error( const wchar_t *Text, const wchar_t *Title ); 
   extern void Error( const lem::UFString& Text, const lem::UFString& Title );
   extern void Error( const lem::UFString& Text );
   extern void Error( const std::wstring &Text ); 
   extern void Error( const std::string &Text ); 

   #if defined LEM_DOT_NET
   extern void Error( System::String *Text, System::String *Title=NULL ); 
   #endif

   // ������ �� ������������ ������ �� ���� ��������� ������ YES ��� NO �� ������.
   extern bool YesNo( const char *Text, const char *Title=NULL );
   extern bool YesNo( const wchar_t *Text, const wchar_t *Title=NULL );
   extern bool YesNo( const lem::UFString& Text, const lem::UFString& Title );

   // ������ � ������������ ������������� (Ok-Cancel)
   extern bool OkCancel( const wchar_t *Text, const wchar_t *Title );
   extern bool OkCancel( const lem::UFString& Text, const lem::UFString& Title );

   // ����������� ������� � ��������� ���������� (� ��������� - �������� ���������).
   extern void Message( const char *Text ); 
   extern void Message( const wchar_t *Text ); 
   extern void Message( const lem::UFString& Text );


   // �������� e-mail �� ���������� ������, ����������� ����� ������ ���� ������
   // � ��� ����.
   extern bool SendMail( const wchar_t *adr, const wchar_t *subject, const wchar_t *body );


   // ����� ������� ��� ��������� ���������� ��������� (� IE).
   extern bool ConfigureInternet(void);


   // ����������� ������������ ���� ��� ���������� �����.
   extern void ShowContextMenu( void* hWnd, const wchar_t* pszPath, int mx=-1, int my=-1 );
   extern void ShowContextMenu( const lem::UFString& pszPath, int mx=-1, int my=-1 );
   extern void ShowContextMenu( const lem::FString& pszPath, int mx=-1, int my=-1 );
   extern void ShowContextMenu( const wchar_t* pszPath, int mx=-1, int my=-1 );
   extern void ShowContextMenu( const char* pszPath, int mx=-1, int my=-1 );
   #if defined LEM_WXWIDGETS
   extern void ShowContextMenu( const wxString& pszPath, int mx=-1, int my=-1 );
   #endif
  
   // ����������� ������ ��� ������ ��������
   #if defined LEM_QT
   extern lem::Path AskFolder( const wchar_t *message, QWidget* qWnd, const lem::Path &start_path );
   extern lem::Path AskFolder( const wchar_t *message=NULL, QWidget* qWnd=NULL );
   #else
   extern lem::Path AskFolder( const wchar_t *message, void* hWnd, const lem::Path &start_path );
   extern lem::Path AskFolder( const wchar_t *message=NULL, void* hWnd=NULL );
   #endif


   // Ask the user to select the filename to open or to save
   extern lem::Path AskFilename(
                                bool for_open,
                                const wchar_t *message,
                                const lem::Path &folder=lem::Path(),
                                const wchar_t *mask=NULL
                               );
   extern lem::Path AskFilename(
                                bool for_open,
                                const lem::UFString &message,
                                const lem::Path &folder=lem::Path(),
                                const wchar_t *mask=NULL
                               );


   #if defined LEM_DOT_NET
   extern void OleDbError( System::Data::OleDb::OleDbException *x, System::String *text );
   #endif

   // ���������� ������� ��������� ������� � �������� ����������.
   extern lem::Path GetCurrentFolder(void);


   #if defined LEM_WINDOWS
   // �������� ����� ��������� ���������� ����������
   extern void ConfigMSIE(void);
   #endif


   // ���� ���� ��������� �� ����, �� ��������� ��������� ��� ����� � �������� � ���
   // ���� ����, ����� - ������ ��������� ���� � ����������
   void ExplorePath( const lem::Path &path );


  } // namespace Shell
 } // namespace lem

#endif
