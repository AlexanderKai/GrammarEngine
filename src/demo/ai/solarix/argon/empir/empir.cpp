// -----------------------------------------------------------------------------
// File EMPIR.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// EMPIRIKA program
//
// ��������� ����� - ��������� ������� (������ ������������), ����������
// ���������� � ����� �� ������ ��������� ����, ������, ����. ����� ���
// �������������� ������ (�� ���� ������������) ������������ �����������
// ������� SOLARIS ��� ����������� ������� � �������. ��������� �� ����������
// �������������� �������� ����������� (��� ������ ��������� SENTAN).
//
// ����� ��������: �������������� ����� � ��������� ���������� (����� � �.�.).
// �� ������� ����� ��������������� ����������� �������.
// ������ ��������� ������� �������������� � ������. �� ���������
// ����� ������ ������ �� ���������� �� ��������� � ������. ����� ������
// ������� ������������� - ����������� �� �����, �����. ����� ����, ���
// ������ ������� �������� ������� ����� �� ��� ���������� � �������, ����������
// ������ ����� �������������, � ��������� - ���������� ������� ���� ���������
// ������, ��������� � �������.
//
// ��������� ������������� ������� ��� ������� �������: ��� �������� � ���
// ���������.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->21.03.2013
// --------------

#include <lem/oformatter.h>
#include <lem/date_time.h>
#include <lem/startup.h>

#include "empir.h"

using namespace std;
using namespace boost::posix_time;

int main( int argc, char *argv[] )
{
 #if LEM_DEBUGGING==1 && defined LEM_MSC
 //_CrtSetBreakAlloc(6203);
 _CrtSetDbgFlag(
                _CRTDBG_ALLOC_MEM_DF |
//                _CRTDBG_DELAY_FREE_MEM_DF |
//                _CRTDBG_CHECK_ALWAYS_DF |
                _CRTDBG_LEAK_CHECK_DF
               );

 #endif
 lem::LemInit initer;

 // Text processing object.
 EmpirTextProcessor *P = new EmpirTextProcessor;

 if(
    argc==1 ||
    (argc==2 && (
                 !strcmp(argv[1]+1,"help") ||
                 !strcmp(argv[1]+1,"?") ||
                 !strcmp(argv[1]+1,"h") ||
                 !strcmp(argv[1]+1,"-version")
                )
    )
   )
  return 0;  

 ptime t0 = second_clock::local_time();


 Collect<UFString> args;
 for( int i=0; i<argc; i++ )
  args.push_back( to_unicode( FString(argv[i]) ) );//, &lem::UI::get_UI().get_Tty_Cp() ) );

 try
  {
   P->Parse_Command( args ); 

   // ��������� ��������� ������� ������.
   P->Scan();

   ptime t2 = second_clock::local_time();
   time_duration dt = t2-t0;

   mout->printf( "\nAll files have been processed, %vfE%d%vn second elapsed\n", dt.total_seconds() );

   // Print the statiscital report on processed texts.
   // �������� �������������� �����.
   P->Report();

   ptime t1 = second_clock::local_time();
   dt = t1-t0;
   mout->printf( "All done, %vfE%d%vn second elapsed\n", dt.total_seconds() );

   if( lem::LogFile::IsOpen() )
    lem::LogFile::Print( lem::format_str( L"All files have been processed: %d second\n", dt.total_seconds() ) );
  }
 catch( const std::exception &e )
  {
   mout->printf( "Command line error\n%s\n", e.what() );
   lem::Process::Exit(1);
  }
 catch( const lem::E_BaseException &e )
  {
   mout->printf( "Command line error\n%us\n", e.what() );
   lem::Process::Exit(1);
  }
 catch( ... )
  {
   mout->printf( "Command line error\n" );
   lem::Process::Exit(1);
  }

 return 0;
}
