// -----------------------------------------------------------------------------
// File LEM_DIR.CPP
//
// (c) by Elijah Koziev      all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ��������� �������� ��� ������� � ��������� ������. ������� ��� ��������-
// ����������� �������. ���������� ������ Path.
//
// 28.02.2006 - ������� �������� ������� �������� (� ����������� ������� ����
//              ���������) Purge_Folder(). 
//
// 30.06.2006 - �������� ���������� ��������� Purge_Folder, ������� ����������
//              ������� ��������� �������. ������� ���������� �����
//              SHFileOperationW ����� ����� �������� ��� �������
//              ���������������.
//
// 27.07.2006 - ������ GetFileAttributesEx() ������������ GetFileAttributes()
//
// 10.01.2007 - ����������� CopyFolder
//
// 16.01.2007 - ���������� ������� DoRemove: ��� ������� ����������� ����������.
// 01.06.2007 - � CdDvdEject ������� ��� ��� ���������� ����� CDROM'� ��� Linux.
// 09.06.2007 - ������������ Path::GetMyDocuments().
// 17.06.2007 - ������ ����� ::List, ������������ ������ ��������� � ��������.
// 18.06.2007 - ������ ����� ::Match ��� ��������� � ������ (shell-�������).
// 03.08.2007 - ��� Path::FolderSize ������ �������������� �������� - ���������
//              �� ������-������� ��� �������������� ��������� ���������
//              ������ � ���������.
// 09.08.2007 - ������� ��������� ������� Crawl ��� ����������� ���������
//              ��������� � ������������� �������� �������.
// 16.08.2007 - ��� ������������������� �������������� ������� ��������� ==, >,
//              <, != 
// 06.10.2007 - �������� ����� GetDiskFreeSpace
// 08.11.2007 - ���������� ������ CdDvdEject � Unicode ������
// 03.03.2008 - �������� ����� GetAbsolutePath()
// 21.03.2008 - ��������� �������� � wxFileName
// 21.03.2008 - ��������� ��������� swap
// 21.03.2008 - ��������� ��������� � boost::filesystem::path/wpath ���
//              ������������ ������� LEM_USE_BOOST_FILESYSTEM
// 02.04.2008 - ��� *nix ����� GetCD ������� �������� ����� /cdrom, /mnt/cdrom,
//              /dev/cdrom
// 08.10.2009 - ������� �������� �������� ��������� ����� �� ���������� �����
//              � IDirTraverser � ����������� ������� - ������ �����������
//              �� ������ ����, � ������ ��� �����
// -----------------------------------------------------------------------------
//
// CD->01.05.1995
// LC->12.04.2010
// --------------

#include <lem/config.h>

#if defined LEM_MFC
 #include <afx.h>
#endif

#include <cstring>
#include <cctype>

#if defined LEM_BORLAND || defined LEM_MSC
 #include <io.h>
#endif

#if defined LEM_DOS
 #include <dos.h>
#endif

#include <sys/stat.h>

#if defined LEM_WINDOWS

 #if defined LEM_MFC
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif

 #include <winbase.h>
 #include <direct.h>
 #include <shellapi.h>
 #include <mmsystem.h>
 #include <shlobj.h>

 #if !defined LEM_QT
  #include <urlmon.h>
 #endif

 #include <winioctl.h>

/*
 #if _WIN32_WINNT>=0x0500

  #include <SetupAPI.h>

  #if defined(LEM_MSC)
   #pragma comment(lib,"Setupapi.lib")
  #endif

 #endif
*/

#endif

#if defined LEM_QT
 #include <QDir>
#endif

#if defined LEM_LINUX
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <fcntl.h>
 #include <linux/cdrom.h>
#endif

#if defined LEM_BSD && defined __FreeBSD__
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <fcntl.h>
 #include <sys/cdio.h>
#endif

#if defined LEM_DARWIN
 #include <fcntl.h>
#endif

#if defined LEM_UNIX
 #include <dirent.h>
#endif

#if defined LEM_WXWIDGETS
 #include <wx/filename.h>
 #include <wx/utils.h>
#endif

#if !defined LEM_WINDOWS && !defined LEM_UNIX
 #include <boost/filesystem/operations.hpp>
#endif

#include <lem/system_config.h>
#include <lem/runtime_checks.h>
#include <lem/quantors.h>
#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/unicode.h>
#include <lem/user_interface.h>
#include <lem/logfile.h>
#include <lem/regex.h>
#include <lem/application.h>
#include <lem/path.h>

#if defined(LEM_MSC) && defined(LEM_WINDOWS)
 #pragma comment ( lib, "winmm.lib" )
 #pragma comment ( lib, "urlmon.lib" )
 #pragma comment(lib,"Setupapi.lib")
#endif

#undef GetDiskFreeSpace

using namespace std;
using namespace lem;
using namespace lem::UI;

// *******************************************
// names for standard i/o devices
// *******************************************
#if defined LEM_UNIX
 const char lem::NULL_DEVICE[] = "/dev/null";
 const char lem::TTY_DEVICE[]  = "/dev/tty";
 const char lem::ERR_DEVICE[]  = "/dev/tty";
 const char lem::KBD_DEVICE[]  = "/dev/tty";
 const char lem::CD_DEVICE[]   = "/dev/cdrom";
#else // DOS and WIN
 const char lem::NULL_DEVICE[] = "nul";
 const char lem::TTY_DEVICE[]  = "con";
 const char lem::ERR_DEVICE[]  = "con";
 const char lem::KBD_DEVICE[]  = "con";
#endif

static const size_t LEM_BLOCKSIZE = 16384; // ������ ����� ��� ����������� ������.
                                           // ��������, ��� ��������� �������
                                           // �������������� ��� ���������� ��.


std::vector< std::pair<lem::Path::EventHandler,void*> > lem::Path::cd_event;
std::vector< std::pair<lem::Path::EventHandler,void*> > lem::Path::filemon_event;


#if defined LEM_DOT_NET
lem::Path::Path( System::String *s )
{
 uname = to_ustr(s);
}


lem::Path::Path( System::IO::Path *p )
{
 uname = to_ustr( p->ToString() );
}
#endif




/********************************************************************
 ���������� ���������� �������, �� ���������� ������ ��������� �����,
 ����������� ������������ file. ��������, ����� �������� ����� file
 ������ ��������� ����������� ��������� �� ����. ����� ���������
 ������� ��������� ����� � ��� �� �����, ��� � �� ����������.
*********************************************************************/
size_t lem::get_file_size( FILE *file )
{
 if(!file)
  return 0;

 #if defined LEM_BORLAND_3_1
 // Incompatible runtime library function may be used - why not?
 const long size = filelength( fileno(file) );
 if( size<0 )
  // -1 is error indicator, so we change it to 0 and do not bother the user.
  return 0;

 return size;

 #elif defined LEM_MSC

 return _filelength( _fileno(file) );

 #else

 // Let use the standard C function only - this must work on any platform.
 const long cur = ftell(file);

 fseek( file, 0, SEEK_END );
 const long eof_ftell = ftell(file);
 fseek( file, cur, SEEK_SET );

 return eof_ftell;

 #endif
}

/*-----------------------------------------------------------------------------------*

 lem_file_name_split takes a file's full path name (path) as a string
 in the form

                        X:\DIR\SUBDIR\NAME.EXT

 and splits path into its four components. ����� ������������ ��������:
 drive name, directory name, file name and file extention. �����������
 ����� drive name � directory name ������� �� ������������ ������������
 �������.

 ��� ����� ����� ����� ������������ ����� � ��������� ����� �������. ���
 �� ��������� � ���������� �����.

 When sol_file_name_split splits path, it treats the punctuation as
 follows:

 * drive does not keep the colon attached (C:, A:, etc.)
 * dir keeps the leading and trailing backslashes
   (\turboc\include\,\source\, etc.)

 * ext does not keep the dot preceding the extension (.c, .exe, etc.)

 ��������� �������� ����� ������� � ������ ���� ����������� ���������
 lem_file_name_merge.
*-----------------------------------------------------------------------------------*/

/*
void lem::file_name_split(
                          const char *path,
                          FString &drive,
                          FString &dir,
                          FString &name,
                          FString &ext
                         )
{
 int cur=0;
 const int pathlen = strlen(path);
 if( lem_find(path,LEM_DRIVE_DELIMITER_CHAR,1) != UNKNOWN )
  {
   // ��������� ��� �������� (drive name). ����� ������� - ��� �������
   // �� ������� � ������������ ����� � ����.
   while( cur<pathlen )
    if( path[cur] == LEM_DRIVE_DELIMITER_CHAR )
     {
      cur++;
      break;
     }
    else
     drive += path[cur++];

   if( LEM_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) )
    dir += path[cur++];
  }

 char *buf = new char[pathlen+1];

 FOREVER
  {
   // ��������� ��������� �������� ����.
   int i=0;
   buf[0]='\0';
   while( (buf[i++]=path[cur])!='\0' )
    if(
       LEM_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) ||
       path[cur]==LEM_EXTENTION_DELIMITER_CHAR
      )
     {
      buf[i-1]='\0';
      break;
     }
    else
     cur++;

   if( LEM_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) )
    {
     // ��� ��� ���������� ��������.
     dir += buf;
     dir += path[cur++];
     continue;
    }

   if( path[cur]=='\0' )
    {
     if( buf[0]!='\0' )
      name = buf;
     break;
    }

   if( path[cur]==LEM_EXTENTION_DELIMITER_CHAR )
    {
     // ���� ��������� ��� �����, � ����� �������� ����������, ����
     // ����� �������� ����������� ������ ��������.
     if(
        strrchr( LEM_PATH_BAD_CHARS, path[cur+1] )==NULL &&
         (
          path[cur+1]=='\0' ||
          isalnum(path[cur+1])
         )
       )
      {
       name = buf;
       // ������ ����������.
       cur++;

       while( path[cur] )
        ext += path[cur++];

       break;
      }
     else
      {
       while( path[cur++]==LEM_EXTENTION_DELIMITER_CHAR )
        dir += LEM_EXTENTION_DELIMITER_CHAR;

       dir += LEM_DIRECTORY_DELIMITER_CHAR;
       continue;
      }
    }
  }

 delete[] buf;
 return;
}
*/

/*---------------------------------------------------------------------*

Name            FileNameMerge - makes new file name

Description     FileNameMerge makes a file name from its components. The
                new file's full path name is

                        X:\DIR\SUBDIR\NAME.EXT

                where

                        X is given by drive
                        \DIR\SUBDIR\ is given by dir
                        NAME.EXT is given by name and ext

                If the drive, dir, name, or ext parameters are null or empty,
                they are not inserted in the path string.  Otherwise, if
                the drive doesn't end a colon, one is inserted in the path.
                If the dir doesn't end in a slash, one is inserted in the
                path.  If the ext doesn't start with a dot, one is inserted
                in the path.

                The maximum sizes for the path string is given by the
                constant MAXPATH (defined in dir.h), which includes space
                for the null-terminator.

                fnsplit and fnmerge are invertible; if you split a given path
                with fnsplit, then merge the resultant components with fnmerge,
                you end up with path.

Return value    None
*---------------------------------------------------------------------*/
/*
const FString lem::file_name_merge(
                                   const FString &driveP,
                                   const FString &dirP,
                                   const FString &nameP,
                                   const FString &extP
                                  )
{
 FString res = driveP;
 if(
    res.length() &&
    res.last_char()!=LEM_DIRECTORY_DELIMITER_CHAR
   )
  {
   res += LEM_DRIVE_DELIMITER_CHAR;

   if( dirP[0]!=LEM_DIRECTORY_DELIMITER_CHAR )
    res += LEM_DIRECTORY_DELIMITER_CHAR;
  }

 res += dirP;
 if(
    res.length() &&
    dirP.length() &&
    res.last_char()!=LEM_DIRECTORY_DELIMITER_CHAR
   )
  res += LEM_DIRECTORY_DELIMITER_CHAR;

 res += nameP;

 if( extP.length() )
  {
   res += LEM_EXTENTION_DELIMITER_CHAR;
   res += extP;
  }

 return res;
}
*/




/****************************************************************
 ������� ���������, ������ �� ����� ��� �������� (����� "b" �
 ����������� ������ ��� sol_fopen). ������� ����������
 ������������������� �������� � ��������� FILE, ������� ��
 ������ ������������ � ����� ����������� �������������.
*****************************************************************/
bool lem::is_binary_file( FILE *File )
{
 #if defined LEM_WATCOM
  return !!(File->_flag & _BINARY);
 #elif defined LEM_BORLAND
  return !!(File->flags & _F_BIN);
 #elif defined LEM_SYMANTEC
  return !!(File->_flag & _F_BIN);
 #elif defined LEM_MSC
  return true;
 #elif defined LEM_GNUC
  return true;
 #else
  #error unknown C++ compiler
 #endif
}



/**************************************************************************
 ��� ���������� ����� src ������������ � ���� dst.
 ���������:
           src - input stream,
           dst - output stream,
           size - number of bytes to copy. If 0, get src file size.
***************************************************************************/
void lem::copy_file( lem::Stream &src, lem::Stream &dst, size_t size )
{
 const size_t Size = size ? size : src.fsize();

 if( !Size )
  return;

 // ��������� �������� ���� ����� ����� ������
 // ��������� ������, ���������� ����� ���������.
 const size_t nblock = Size/LEM_BLOCKSIZE;        // ����� ������ ������.
 const size_t tail = Size - nblock*LEM_BLOCKSIZE; // �������.

 lem::uint8_t *block = new lem::uint8_t[LEM_BLOCKSIZE];

 for( size_t i=0; i<nblock+1; i++ )
  {
   const size_t len = i==nblock ? (size_t)tail : (size_t)LEM_BLOCKSIZE;
   src.read( block, len );
   dst.write( block, len );
  }

 delete[] block;
 return;
}


/*************************************************************************
 ���������� ��� �������� ������ (����������� ����� C � ���� ����������),
 ��� ��� ���������� ��������� ��������� ���������, � ���������� ������
 ������ � ������������ ������� ��������� �������� � ������� ����.
**************************************************************************/
/*
void do_flushall(void)
{
 #if defined LEM_UNIX
  // I don't know what is equivalent to flushall under Linux/GNUC
  fflush( stdout );
  fflush( stderr );
 #elif defined LEM_GNUC
  fflush( stdout );
  fflush( stderr );
 #else
  flushall();
 #endif

 return;
}
*/


long lem::get_file_time( FILE *file )
{
 if( file==NULL )
  // Don't you know what to do?
  return 0;

 #if defined LEM_DOS || defined LEM_WINDOWS

 struct stat statbuf;
 if( fstat( fileno(file), &statbuf ) == -1 )
  return 0;

 return statbuf.st_ctime;

 #elif defined LEM_UNIX

 struct stat s;
 if( fstat( fileno(file), &s ) == -1 )
  return 0;

 return s.st_ctime;

 #else
  #error Define [lem_get_file_time] function for taget OS!
 #endif
}



// ��� �������� ��� ���������� ��������� ������.
static const char* get_tmp_dir(void)
{
 const char* dir=NULL;

 dir = getenv("TMP");
 if( dir==NULL )
  dir = getenv("TEMP");

 if( dir==NULL )
  {
   #if defined LEM_LINUX

   static bool use_tmp=false;
   static bool inited=false;

   if( !inited )
    {
     if( lem::Path::DoesExist("/tmp") )
      use_tmp = true;

     inited = true;
    }

   if( use_tmp )
    dir = "/tmp";

   #endif

   if( dir==NULL )
    dir="";
  }

 return dir;
}



static const lem::FString get_tmp_name( const char *ext )
{
 static int fn_counter=1973;

 // ������� ��� �������� ��� ���������� ��������� ������.

 #if defined LEM_QT
 QString s = QDir::toNativeSeparators(QDir::tempPath());
 lem::FString dir = lem::to_ascii( lem::to_ustr(s) );
 #else
 lem::FString dir=get_tmp_dir();
 #endif

 char *n = new char[lem::Path::MaxLen+1];
 char *b = new char[lem::Path::MaxLen+1];

 char infix[32]="";
 #if defined LEM_WINDOWS
 _snprintf( infix, sizeof(infix), "_%d", GetCurrentThreadId() );
 #elif defined LEM_UNIX
 snprintf( infix, sizeof(infix), "_%d", (int)getpid() );
 #endif 

 char slash[2] = { char(lem::Path::GetPathDelimiter()), 0 };

 FOREVER
  {
   if( !dir.empty() )
    strcpy( n, dir.c_str() );
   else
    n[0]=0;

   if( !dir.empty() )
    strcat( n, slash );

   // ��������� ����� ���������� ���.
   if( ext )
    {
     #if defined LEM_WINDOWS
     _snprintf( b, lem::Path::MaxLen, "%d%s.%s", fn_counter, infix, ext );
     #else
     snprintf( b, lem::Path::MaxLen, "%d%s.%s", fn_counter, infix, ext );
     #endif
    }
   else
    {
     // ���������� �� �������.
     #if defined LEM_WINDOWS
     _snprintf( b, lem::Path::MaxLen, "%d%s", fn_counter, infix );
     #else
     snprintf( b, lem::Path::MaxLen, "%d%s", fn_counter, infix );
     #endif
    }

   strcat( n, b );

   fn_counter++;

   if( !lem::Path::DoesExist(n) )
    break;

   // ������� ������ ���.
  }

 // ����� ���.
 const FString res = n;

 delete[] b;
 delete[] n;

 return res;
}



/**************************************************************
 Delete a file if possible.  Don't complain if it's not there.
 �������� ����� � �������� ������ filename. �����������
 ����������� UNIX-�����. � ������ ������ ������������ true,
 ��� ������� false. ������� �� ��������� � ��������� ���������
 �����!
***************************************************************/
/*
bool lem::do_remove( const char *filename )
{
 if( !!(filename) && *filename )
  {
   const int res = remove( filename );
   return res==0; // 0 is OK...
  }

 // ������ ��������.
 return false;
}
*/




/*-----------------------------------------------------------------------------------*

 sol_file_name_split takes a file's full path name (path) as a string
 in the form

                        X:\DIR\SUBDIR\NAME.EXT

 and splits path into its four components. ����� ������������ ��������:
 drive name, directory name, file name and file extention. �����������
 ����� drive name � directory name ������� �� ������������ ������������
 �������, ������� ������������ ��������� �� ����� <sol_sys.h>.

 ��� ����� ����� ����� ������������ ����� � ��������� ����� �������. ���
 �� ��������� � ���������� �����.

 When sol_file_name_split splits path, it treats the punctuation as
 follows:

 * drive does not keep the colon attached (C:, A:, etc.)
 * dir keeps the leading and trailing backslashes
   (\turboc\include\,\source\, etc.)

 * ext does not keep the dot preceding the extension (.c, .exe, etc.)

 ��������� �������� ����� ������� � ������ ���� ����������� ���������
 sol_file_name_merge.
*-----------------------------------------------------------------------------------*/
/*
void lem::file_name_split(
                          const wchar_t *path,
                          UFString &drive,
                          UFString &dir,
                          UFString &name,
                          UFString &ext
                         )
{
 int cur=0;
 const int pathlen = lem_strlen(path);
 if( lem_find(path,LEM_DRIVE_DELIMITER_CHAR,1) != UNKNOWN )
  {
   // ��������� ��� �������� (drive name). ����� ������� - ��� �������
   // �� ������� � ������������ ����� � ����.
   while( cur<pathlen )
    if( path[cur] == LEM_DRIVE_DELIMITER_CHAR )
     {
      cur++;
      break;
     }
    else
     drive += path[cur++];

   if( SOL_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) )
    dir += path[cur++];
  }

 wchar_t *buf = new wchar_t[pathlen+1];

 FOREVER
  {
   // ��������� ��������� �������� ����.
   int i=0;
   buf[0]=0;
   while( (buf[i++]=path[cur])!=0 )
    if(
       SOL_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) ||
       path[cur]==LEM_EXTENTION_DELIMITER_CHAR
      )
     {
      buf[i-1]=0;
      break;
     }
    else
     cur++;

   if( SOL_IS_DIRECTORY_DELIMITER_CHAR(path[cur]) )
    {
     // ��� ��� ���������� ��������.
     dir += buf;
     dir += path[cur++];
     continue;
    }

   if( path[cur]==0 )
    {
     if( buf[0]!=0 )
      name = buf;
     break;
    }

   if( path[cur]==SOL_EXTENTION_DELIMITER_CHAR )
    {
     // ���� ��������� ��� �����, � ����� �������� ����������, ����
     // ����� �������� ����������� ������ ��������.
     if( path[cur+1]==0 || is_correct_path_uchar(path[cur+1]) )
      {
       // � ������ ������ ����� ���� ��������� ����� - ���
       // ����� ���������.
 
       name = buf;
       // ������ ����������.
       cur++;

       while( path[cur] )
        ext += path[cur++];

       break;
      }
     else
      {
       while( path[cur++]==SOL_EXTENTION_DELIMITER_CHAR )
        dir += SOL_EXTENTION_DELIMITER_CHAR;

       dir += SOL_DIRECTORY_DELIMITER_CHAR;
       continue;
      }
    }
  }

 delete buf;
 return;
}
*/


/****************************************************************************
 ������ ������ ���� � ����� �� ������ ������ ���������, ����������
 ���������� ����������� ��������� sol_file_name_split. �� �������
 ����� ���������������� �������, ���������� � �������� sol_file_name_split.
*****************************************************************************/

/*
const UFString lem::file_name_merge(
                                    const UFString &drive,
                                    const UFString &dir,
                                    const UFString &name,
                                    const UFString &ext
                                   )
{
 UFString res = drive;

 if( !drive.empty() )
  res += LEM_DRIVE_DELIMITER_CHAR;

 res += dir;
 res += name;

 if( !ext.empty() )
  res += LEM_EXTENTION_DELIMITER_CHAR;

 res += ext;
 return res;
}
*/



/************************************************************
 ��������� � ����������� ANSI-������� �������� ������.
*************************************************************/
FILE *lem::fopen( const wchar_t *filename, const char *mode )
{
 if( !(filename) || !(mode) )
  return NULL;

 #if defined LEM_USE_WCHAR
  uch wmode[4]={ mode[0], mode[1], mode[2], 0 };
  FILE *res = _wfopen( filename, wmode );
 #else
  const int len = lem_strlen(filename);
  char *ascii_filename = new char[len+1];

  lem_unicode_to_ascii( ascii_filename, filename );
  FILE *res = /*std::*/::fopen( ascii_filename, mode );
  delete[] ascii_filename;
 #endif

 return res;
}

/*************************************************************************
 ��������� ���������� ��������� ��� ���������� �����. ��� �������
 ANSII-������������� ����� �������� ����������� ��������� tmpnam.
 ������, ������� ������������ ��� ���������� ����� ���������� �����,
 �������� ������� �� �����������. ����� ������� ���������� ������������
 ����� ����� ext (���� ������� NULL ��� ��������������� ������). ���
 ���������� �� ������ ��������� �����-�����������.
**************************************************************************/
/*
static const UFString lem_get_tmp_uname( const wchar_t *ext )
{
 static int fn_counter=666;

 // ������� ��� �������� ��� ���������� ��������� ������.
 char* dir = get_tmp_dir();
 char* Ext = lem_unicode_to_ascii(ext);

 char *n = new char[LEM_MAX_PATH+1];
 char b[LEM_MAX_FILENAME];

 FOREVER
  {
   if( dir!=NULL )
    strcpy( n, dir );
   else
    n[0]=0;

   if( dir!=NULL )
    strcat( n, "\\" );

   // ��������� ����� ���������� ���.
   sprintf( b, "%d.%s", fn_counter, Ext );
   strcat( n, b );

   fn_counter++;

   if( !does_exist(n) )
    break;

   // ������� ������ ���.
  }

 // ����� ���.
 const UFString res = lem_ascii_to_unicode( n );

 delete[] n;
 delete[] Ext;
 delete[] dir;

 return res;
}
*/




/******************************************************************
 ���������� ��������� ����� ��������� ����������� ���������� �����.
*******************************************************************/
long lem::get_file_change_time( const wchar_t *filename )
{
 if( !(filename) )
  return 0;

 #if defined LEM_USE_WCHAR

  struct _wstat fs;
  const int ok = _wstat(filename,&fs);
  if( ok!=0 )
   return -1;

  const long res = fs.st_atime;

 #else

  char *buf = new char[lem_strlen(filename)+1];
  lem_unicode_to_ascii( buf, filename );

  struct stat fs;
  const int ok = stat(buf,&fs);
  if( ok!=0 )
   return -1;

  const long res = fs.st_atime;

  delete[] buf;
 #endif

 return res;
}

/*****************************************************************
 � ����� � ������ f1 ������������ (� �����) ���������� ����� f2.
******************************************************************/
static void concatenate_files( const wchar_t *f1, const wchar_t *f2 )
{
 FILE *file1 = fopen( f1, "ab" );
 FILE *file2 = fopen( f2, "rb" );

 LEM_CHECKIT_Z( file1!=NULL );
 LEM_CHECKIT_Z( file2!=NULL );

 // ������������ � ����� ������������ �����.
 fseek( file1, 0, SEEK_END );

 // ������ �������.
 const long Size = get_file_size(file2);

 const long nblock = Size/LEM_BLOCKSIZE;        // ����� ������ ������.
 const long tail = Size - nblock*LEM_BLOCKSIZE; // �������.

 char *block = new char[LEM_BLOCKSIZE];

 for( int i=0; i<nblock+1; i++ )
  {
   const size_t len = i==nblock ? (size_t)tail : (size_t)LEM_BLOCKSIZE;
   fread( block, len, 1, file2 );
   fwrite( block, len, 1, file1 );
  }

 delete block;

 fclose(file2);
 fclose(file1);

 return;
}

/****************************************************************************
   Filter out illegal chars.  This is virtually identical for the Amiga,
   Atari ST, MSDOS, OS/2, and Unix, the only differences being '#' for the
   Amiga, ':', ';', '+', ',', '=' for the Atari ST, DOS and OS/2, and '&',
   '!' for Unix.  The Mac only has ':' as an illegal char, the Arc has its
   own wierd selection, and VMS has everything except '_' illegal.  Note that
   the space char must be the first one in the exclusion list if it's used

   Copyright 1990 - 1992  Peter C.Gutmann.  All rights reserved
*****************************************************************************/

/*
bool lem::is_correct_path_uchar( wchar_t ch )
{
 return is_ulitera(ch) ||
        ((ch&0xff00)==0 &&
          lem_find( LEM_PATH_BAD_CHARS, char(ch) )==UNKNOWN
        );
}
*/


/**************************************************************
 Delete a file if possible.  Don't complain if it's not there.
 �������� ����� � �������� ������ filename. �����������
 ����������� UNIX-�����. � ������ ������ ������������ true,
 ��� ������� false. ������� �� ��������� � ��������� ���������
 �����!
***************************************************************/
/*
bool lem::do_remove( const wchar_t *filename )
{
 if( !!(filename) )
  {
   #if defined LEM_WINDOWS

   return _wunlink( filename ) == 0;

//   #elif defined LEM_UNIX
//   return wunlink( filename ) == 0;

   #else
   // �������� ANSI-������������ ��� �����...
   const int len = lem_strlen(filename);
   char *ascii_filename = new char[len+1];
   lem_unicode_to_ascii( ascii_filename, filename );
   const int res = do_remove( ascii_filename );
   delete[] ascii_filename;
   return res==0; // 0 is OK...
   #endif
  }

 // ������ ��������.
 return false;
}
*/



#if defined LEM_WXWIDGETS
lem::Path::Path( const wxFileName &x )
 #if defined UNICODE
 : uname( x.GetFullPath() )
 #else 
 : name( x.GetFullPath() )
 #endif
{}
#endif



#if defined LEM_WXWIDGETS
void Path::operator=( const wxFileName &x )
{
 #if defined UNICODE
 name.clear();
 uname = x.GetFullPath();
 #else 
 uname.clear();
 name = x.GetFullPath();
 #endif
}
#endif



#if defined LEM_USE_BOOST_FILESYSTEM
lem::Path::Path( const boost::filesystem::path &p )
 : name(p.string())
{}
#endif


#if defined LEM_USE_BOOST_FILESYSTEM
void lem::Path::operator=( const boost::filesystem::path &p )
{
 uname.clear();
 name = p.string();
 return;
}
#endif


#if defined LEM_USE_BOOST_FILESYSTEM
#ifndef BOOST_FILESYSTEM_NARROW_ONLY
lem::Path::Path( const boost::filesystem::wpath &p )
 : uname(p.string())
{
}

void lem::Path::operator=( const boost::filesystem::wpath &p )
{
 name.clear();
 uname = p.string();
 return;
}
#endif
#endif


#if defined LEM_WXWIDGETS
lem::Path::Path( const wxString &x )
 #if defined LEM_UNICODE
 : uname(x)
 #else
 : name(x)
 #endif
{}



void lem::Path::operator=( const wxString &x )
{
 #if defined LEM_UNICODE
 uname = x;
 name.clear(); 
 #else
 name = x;
 uname.clear(); 
 #endif
}
#endif




bool lem::Path::IsExtDelimiter( wchar_t ch )
{
 LEM_CHECKIT_Z(ch!=0);
 return ch==SOL_EXTENTION_DELIMITER_CHAR;
}


bool lem::Path::IsDriveDelimiter( wchar_t ch )
{
 LEM_CHECKIT_Z(ch!=0);

 #if defined LEM_WXWIDGETS
 return ch==wxFileName::GetVolumeSeparator();
 #elif defined LEM_WINDOWS || defined LEM_DOS
 return LEM_DRIVE_DELIMITER_CHAR == ch;
 #else
 return false;
 #endif
}


bool lem::Path::IsPathDelimiter( wchar_t ch )
{
 LEM_CHECKIT_Z(ch!=0);

 #if defined LEM_WXWIDGETS
 return wxFileName::IsPathSeparator(ch);
 #else
 return ch==L'\\' || ch==L'/';
 #endif
}




const UFString lem::Path::GetFileNameWithoutExtension( const UFString &path )
{
 // ���� ��������� ������� ����� ������.
 UFString res = path;

 if( path.empty() )
  return res;

 int len = path.length();

 // ���� ������-����������� ���������� - � ������� �����.
 for( int i=len-1; i>=0; i-- )
  {
   if( lem::Path::IsExtDelimiter( path[i] ) )
    {
     // ������� ������ ����������
     res.ShrinkTo(i);
     break;
    }
   else if( lem::Path::IsDriveDelimiter(path[i]) || lem::Path::IsPathDelimiter(path[i]) )
    // No extention found.
    break;
  }

 return res;
}


UFString Path::GetUnicode(void) const
{
 if( !uname.empty() )
  return uname;

 const CodeConverter *cp = &get_UI().GetSessionCp(); 
 return to_unicode( name, cp );
// return UFString( name.c_str() );
}


FString Path::GetAscii(void) const
{
 if( !name.empty() )
  return name;
  
 const CodeConverter *cp = &get_UI().GetSessionCp(); 
 return to_ascii( uname, cp );
// return FString( uname.c_str() );
}



// ******************************************************************
// �������� ����� ��� �������� (���������� � ������������� � �������)
// ******************************************************************
bool lem::Path::DoRemove(void) const
{
 if( empty() )
  return false;

 if( IsFolder() )
  {
   // ������� �������
   #if defined LEM_WINDOWS
   if( lem::System_Config::SupportUnicodeFilenames() )
    {
     SHFILEOPSTRUCTW op;
     op.hwnd = NULL;
     op.wFunc = FO_DELETE;

     UFString s = GetUnicode();
     wchar_t *buf = new wchar_t[ s.length()+2 ];
     lem_strcpy( buf, s.c_str() );
     buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
     op.pFrom = buf;
     op.pTo = NULL;
     op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
     op.lpszProgressTitle = NULL;

     int res = SHFileOperationW(&op);
     delete[] buf;
     return res==0;
    }
   else
    {
     SHFILEOPSTRUCTA op;
     op.hwnd = NULL;
     op.wFunc = FO_DELETE;

     FString s = GetAscii();
     char *buf = new char[ s.length()+2 ];
     lem_strcpy( buf, s.c_str() );
     buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
     op.pFrom = buf;
     op.pTo = NULL;
     op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
     op.lpszProgressTitle = NULL;

     int res = SHFileOperationA(&op);
     delete[] buf;
     return res==0;
    }

   #elif defined LEM_UNIX

   // ������� ������� ���������� ��������, � ����� � ��� �������.
   PurgeFolder();

   // ������� ������� 
   if( lem::System_Config::SupportUnicodeFilenames() )
    return rmdir( lem::to_utf8(GetUnicode()).c_str() )==0;
   else
    return rmdir( GetAscii().c_str() )==0;

   #else

    // ���������� ��� ����� � ��������
    boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
    boost::filesystem::path p1( GetAscii().c_str(), boost::filesystem::native );

    for(
        boost::filesystem::directory_iterator itr( p1 );
        itr != end_itr;
        ++itr
       )
     {
      boost::filesystem::path l = itr->leaf();

      if( is_directory( l ) )
       {
        // ����������� �� 1 ������� ���� �� ������ ���������
        lem::Path deeper( l.string() );
        deeper.DoRemove();
        continue;
       }

      try
       {
        lem::Path p( itr->string().c_str() );
        p.DoRemove();
       }
      catch(...)
       {
       }
     }

    return rmdir( GetAscii().c_str() )==0;
   #endif
  }
 else
  {
   // ������� ������������ ����
   if( lem::System_Config::SupportUnicodeFilenames() )
    {
     #if defined LEM_UNIX
     return ::remove( lem::to_utf8(GetUnicode()).c_str() )!=-1;
     #elif defined LEM_WINDOWS
     return ::DeleteFileW( GetUnicode().c_str() )==TRUE;
     #else
     LEM_STOPIT;
     return false;
     #endif
    }
   else
    {
     #if defined LEM_UNIX
     return ::remove( GetAscii().c_str() )!=-1;
     #elif defined LEM_WINDOWS
     return ::DeleteFileA( GetAscii().c_str() )==TRUE;
     #else
     return ::remove( GetAscii().c_str() )!=-1;
     #endif
    }
  }
}


void lem::Path::CopyFile( const lem::Path& src, const lem::Path& dst )
{
 #if defined LEM_WINDOWS

 // ���������� ������� ������� WinAPI ��� Win2000/XP/2003
 BOOL ret;
 if( lem::System_Config::SupportUnicodeFilenames() )
  ret = ::CopyFileW( src.GetUnicode().c_str(), dst.GetUnicode().c_str(), false );
 else
  ret = ::CopyFileA( src.GetAscii().c_str(), dst.GetAscii().c_str(), false );

 LEM_CHECKIT_Z( ret!=0 );

 #elif defined LEM_WXWIDGETS

  wxCopyFile( src.GetUnicode().c_str(), dst.GetUnicode().c_str() );

 #else

  try
  {   
   BinaryReader src_file( src );
   BinaryWriter dst_file( dst );
   copy_file( src_file, dst_file );
  }
  catch(...)
  {
  }

 #endif

 return;
}


/******************************************************************
 ������� ����, ��� �������� ����� dst, � ���������� �����
 ����� ����� ������ ����� � ������ src. ����������� �����������
 ����������� �������-�������� �������������� �������, � �� �������.
 ��� �������� ��������.
*******************************************************************/
void lem::Path::CopyFile( const wchar_t *src, const wchar_t *dst )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(src) );
 LEM_CHECKIT_Z( !lem::lem_is_empty(dst) );

 if( !(src) || !(dst) )
  return;

 lem::Path psrc(src), pdst(dst);
 CopyFile(psrc,pdst);

 /*
 // ������ ������ �����������: ���� ���������� �������� ������
 // �������, ���� �� ����������� ������� ����� �������� RAM ��
 // ������� ������.
 const int block_size=LEM_BLOCKSIZE;

 FILE *from = fopen( src, "rb" );
 check_file( from, src );

 FILE *to   = fopen( dst, "wb" );
 check_file( to, dst );

 int fs = get_file_size(from);

 char *buffer =new char[block_size];

 while( fs>0 )
  {
   const long size = std::min( fs, block_size );
   fread( buffer, (size_t)size, 1, from );
   fwrite( buffer, (size_t)size, 1, to );
   fs -= size;
  }

 fclose(from);
 fclose(to);
 delete[] buffer;
 */

 return;
}




void lem::Path::CopyFile( const char *src, const char *dst )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(src) );
 LEM_CHECKIT_Z( !lem::lem_is_empty(dst) );

 if( !(src) || !(dst) )
  return;

 lem::Path psrc(src), pdst(dst);
 CopyFile(psrc,pdst);

 /*
 // ������ ������ �����������: ���� ���������� �������� ������
 // �������, ���� �� ����������� ������� ����� �������� RAM ���
 // ������� ������.
 const int block_size=LEM_BLOCKSIZE;

 FILE *from = ::fopen( src, "rb" );
 check_file( from, src );

 FILE *to   = ::fopen( dst, "wb" );
 check_file( to, dst );

 int fs = get_file_size(from);

 char *buffer =new char[block_size];

 while( fs>0 )
  {
   const int size = std::min( fs, block_size );
   fread( buffer, (size_t)size, 1, from );
   fwrite( buffer, (size_t)size, 1, to );
   fs -= size;
  }

 fclose(from);
 fclose(to);
 delete[] buffer;
*/

 return;
}




void lem::Path::CopyFolder( const lem::Path& src, const lem::Path& dst )
{
 #if defined LEM_WINDOWS

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   SHFILEOPSTRUCTW op;
   op.hwnd = NULL;
   op.wFunc = FO_COPY;

   UFString s = src.GetUnicode();
   s += L"\\*.*";
   wchar_t *buf = new wchar_t[ s.length()+2 ];
   lem_strcpy( buf, s.c_str() );
   buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
   op.pFrom = buf;

   s = dst.GetUnicode();
//   s += L"\\*.*";
   wchar_t *buf2 = new wchar_t[ s.length()+2 ];
   lem_strcpy( buf2, s.c_str() );
   buf2[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
   op.pTo = buf2;
   op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
   op.lpszProgressTitle = NULL;

   int res = SHFileOperationW(&op);
   LEM_CHECKIT_Z(res==0);

   delete[] buf;
   delete[] buf2;
  }
 else
  {
   SHFILEOPSTRUCTA op;
   op.hwnd = NULL;
   op.wFunc = FO_COPY;

   FString s = src.GetAscii();
   s += "\\*.*";
   char *buf = new char[ s.length()+2 ];
   strcpy( buf, s.c_str() );
   buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
   op.pFrom = buf;

   s = dst.GetAscii();
   char *buf2 = new char[ s.length()+2 ];
   strcpy( buf2, s.c_str() );
   buf2[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
   op.pTo = buf2;

   op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
   op.lpszProgressTitle = NULL;

   int res = SHFileOperationA(&op);
   LEM_CHECKIT_Z(res==0);
   delete[] buf;
   delete[] buf2;
  }


 #else
  // ...
 #endif 
}





const lem::Path lem::Path::GetTmpFilename( const char *ext )
{
 return lem::Path(get_tmp_name( ext ) );
}



const lem::Path lem::Path::GetTmpFolder(void)
{
 #if defined LEM_WXWIDGETS
  wxString dir( wxFileName::GetTempDir() );
  lem::Path p(dir.c_str());
  return p;
 #elif defined LEM_QT
  QString t = QDir::tempPath();
  lem::Path p( (lem::UFString(t)) );
  return p;
 #else
  const char *dir = get_tmp_dir();
  LEM_CHECKIT_Z(dir!=NULL);
  return lem::Path(dir);
 #endif 
}



// ***************************************************************
// ��������� ���������� ���� � ������������ �������� � �����������
// ������������ ��� ������� ���������.
// ***************************************************************
const lem::Path lem::Path::GetMyDocuments(void)
{
 lem::Path home( lem::System_Config::GetHomeDir() );

 #if defined LEM_WINDOWS

 // ������� ������������ ��������� Shell-��������� ���
 // ��������� ���� � �������� '��� ���������'.
 // NB: ��� Win NT 4.0 ���������� ��������� ����������� � �������� 
 lem::Process::Dll shell32_dll;
 if( shell32_dll.Load( lem::Path("shell32.dll") ) )
  {
   typedef BOOL(STDAPICALLTYPE *ptr_SHGetSpecialFolderPathW)( HWND hwndOwner, wchar_t *lpszPath, int nFolder, BOOL fCreate );

   if( lem::System_Config::SupportUnicodeFilenames() )
    {
     ptr_SHGetSpecialFolderPathW fun_SHGetSpecialFolderPathW = (ptr_SHGetSpecialFolderPathW)shell32_dll.Import( "SHGetSpecialFolderPathW" );
     if( fun_SHGetSpecialFolderPathW!=NULL )
      {
       wchar_t path[ lem::Path::MaxLen+1 ];
       memset( path, 0, sizeof(path) );
       if( fun_SHGetSpecialFolderPathW( NULL, path, CSIDL_PERSONAL, FALSE )==TRUE )
        {
         home = lem::Path(path);
         if( home.DoesExist() )
          return home;
        }
      }
    }
   else
    {  
     typedef BOOL(STDAPICALLTYPE *ptr_SHGetSpecialFolderPathA)( HWND hwndOwner, char *lpszPath, int nFolder, BOOL fCreate );
  
     ptr_SHGetSpecialFolderPathA fun_SHGetSpecialFolderPathA = (ptr_SHGetSpecialFolderPathA)shell32_dll.Import( "SHGetSpecialFolderPathA" );
     if( fun_SHGetSpecialFolderPathA!=NULL )
      {
       char path[ lem::Path::MaxLen+1 ];
       memset( path, 0, sizeof(path) );
       if( fun_SHGetSpecialFolderPathA( NULL, path, CSIDL_PERSONAL, FALSE )==TRUE )
        {
         home = lem::Path(path);
         if( home.DoesExist() )
          return home;
        }
      }
    }
  }

 UFString my_docs( L"\x041C\x043e\x0438 \x0434\x043e\x043a\x0443\x043C\x0435\x043D\x0442\x044B" );

 if( lem::System_Config::IsWin9x() )
  {
   const char *windir = getenv("windir");
   if( windir!=NULL )
    { 
     lem::Path p(windir);
     p.RemoveLastLeaf();
     
     lem::Path p1(p);
     p1.ConcateLeaf( lem::Path(L"My documents") );
     if( p1.DoesExist() )
      return p1;

     lem::Path p2(p);
     p2.ConcateLeaf( lem::Path(my_docs) );
     if( p2.DoesExist() )
      return p2;
    }
  }

 // ������� ��� ������� �����������
 lem::Path rus(home);
 rus.ConcateLeaf( lem::Path(my_docs) );

 if( rus.DoesExist() )
  return rus;

 // ������� ����������.
 lem::Path eng(home);
 eng.ConcateLeaf(L"My documents");
 if( eng.DoesExist () )
  return eng;

 // ��� WinNT �� ����������� �����, ��� ��� ��� ���� OS ����������� ����� '��� ���������'
 // �� �������������. ���� � ������ �������� ����� '������', �� ����� ������ ���� �
 // ����� ��������� ��������. 
 if( home.DoesExist() )
  return home;

 if( lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf( "Can not find path to 'My Documents' folder" );

 #if LEM_DEBUGGING==1
 throw lem::E_BaseException( L"Can not find path to 'My Documents' folder" );
 #else
 return lem::Path();
 #endif

 #elif defined LEM_UNIX

 return lem::Path();

 #else

 return lem::Path();

 #endif
}



bool lem::Path::DoesExist(void) const
{
 if( empty() )
  return false; 

 #if defined LEM_WINDOWS

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
/*
   WIN32_FILE_ATTRIBUTE_DATA data;
   BOOL res = GetFileAttributesExW(
                                   GetUnicode().c_str(),
                                   GetFileExInfoStandard,
                                   &data
                                  );
   return res!=0;
*/
   return GetFileAttributesW( GetUnicode().c_str() ) !=(DWORD)-1;//INVALID_FILE_ATTRIBUTES;
  }
 else
  {
/*
   WIN32_FILE_ATTRIBUTE_DATA data;
   BOOL res = GetFileAttributesExA(
                                   GetAscii().c_str(),
                                   GetFileExInfoStandard,
                                   &data
                                  );
   return res!=0;
*/

   return GetFileAttributesA( GetAscii().c_str() ) != (DWORD)-1;//INVALID_FILE_ATTRIBUTES;
  }

 #elif defined LEM_WXWIDGETS

  return wxFileName::FileExists(GetUnicode().c_str()) || wxFileName::DirExists(GetUnicode().c_str());

 #elif defined LEM_UNIX

  if( lem::System_Config::SupportUnicodeFilenames() )
   {
    struct stat stbuf;
    return ( stat( lem::to_utf8(GetUnicode()).c_str(), &stbuf) != -1) ? true : false;
   }
  else
   {
    struct stat stbuf;
    return ( stat( GetAscii().c_str(), &stbuf) != -1) ? true : false;
   }

 #else

 boost::filesystem::path p( GetAscii().c_str(), boost::filesystem::native );

 try
  {
   if( boost::filesystem::is_directory( p ) )
    return true;
  }
 catch(...)
  {
  }

 if( lem::System_Config::SupportUnicodeFilenames() )
  return lem::Path::DoesExist( GetUnicode().c_str() );
 else
  return lem::Path::DoesExist( GetAscii().c_str() );

 #endif
}

bool lem::Path::DoesExist( const lem::UFString &p )
{
 if( p.empty() )
  return false; 

 return lem::Path::DoesExist( p.c_str() );
}

bool lem::Path::DoesExist( const lem::FString &p )
{
 if( p.empty() )
  return false; 

 return lem::Path::DoesExist( p.c_str() );
}



bool lem::Path::IsFolder(void) const
{
 if( empty() )
  return false; 

 #if defined LEM_WINDOWS

 DWORD res;
 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   res = GetFileAttributesW(GetUnicode().c_str());
  }
 else
  {
   res = GetFileAttributesA(GetAscii().c_str());
  }

 return res!=(DWORD)-1/*INVALID_FILE_ATTRIBUTES*/ && (res&FILE_ATTRIBUTE_DIRECTORY)==FILE_ATTRIBUTE_DIRECTORY;


 #elif defined LEM_DOT_NET

 try
  {
   return System::IO::Directory::Exists( GetUnicode().c_str() );
  }
 catch(...)
  {
   return false;
  }

 #elif defined LEM_UNIX

  if( lem::System_Config::SupportUnicodeFilenames() )
   {
    struct stat stbuf;
    if( stat( lem::to_utf8(GetUnicode()).c_str(), &stbuf) != -1 )
     {
      return (stbuf.st_mode&S_IFDIR)==S_IFDIR;
     }
   }
  else
   {
    struct stat stbuf;
    if( stat( GetAscii().c_str(), &stbuf) != -1 )
     {
      return (stbuf.st_mode&S_IFDIR)==S_IFDIR;
     }
   }

  return false;

 #else

 boost::filesystem::path p( GetAscii().c_str(), boost::filesystem::native );

 try
  {
   if( boost::filesystem::exists(p) )
    return boost::filesystem::is_directory(p);
  }
 catch(...)
  {
  }

 return false;
 #endif
}



#if defined LEM_WINDOWS

// IOCTL control code
#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

namespace {

#if defined _MSC_VER && _MSC_VER<1300

//// The following structures all can find at MSDN.
// enumeration type specifies the various types of storage buses
typedef enum _STORAGE_BUS_TYPE {
    BusTypeUnknown = 0x00,
    BusTypeScsi,
    BusTypeAtapi,
    BusTypeAta,
    BusType1394,
    BusTypeSsa,
    BusTypeFibre,
    BusTypeUsb,
    BusTypeRAID,
    BusTypeMaxReserved = 0x7F
} STORAGE_BUS_TYPE, *PSTORAGE_BUS_TYPE;
#endif

#if defined LEM_MSC
// retrieve the storage device descriptor data for a device. 
typedef struct _STORAGE_DEVICE_DESCRIPTOR {
  ULONG  Version;
  ULONG  Size;
  UCHAR  DeviceType;
  UCHAR  DeviceTypeModifier;
  BOOLEAN  RemovableMedia;
  BOOLEAN  CommandQueueing;
  ULONG  VendorIdOffset;
  ULONG  ProductIdOffset;
  ULONG  ProductRevisionOffset;
  ULONG  SerialNumberOffset;
  STORAGE_BUS_TYPE  BusType;
  ULONG  RawPropertiesLength;
  UCHAR  RawDeviceProperties[1];

} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_QUERY_TYPE {
  PropertyStandardQuery = 0,
  PropertyExistsQuery,
  PropertyMaskQuery,
  PropertyQueryMaxDefined

} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;

// retrieve the properties of a storage device or adapter. 
typedef enum _STORAGE_PROPERTY_ID {
  StorageDeviceProperty = 0,
  StorageAdapterProperty,
  StorageDeviceIdProperty

} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;

// retrieve the properties of a storage device or adapter. 
typedef struct _STORAGE_PROPERTY_QUERY {
  STORAGE_PROPERTY_ID  PropertyId;
  STORAGE_QUERY_TYPE  QueryType;
  UCHAR  AdditionalParameters[1];

} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;
#endif

}

/*
#if defined LEM_MSC 
static BOOL GetDisksProperty( HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc )
{
	STORAGE_PROPERTY_QUERY	Query;	// input param for query
	DWORD dwOutBytes;				// IOCTL output length
	BOOL bResult;					// IOCTL return val

	// specify the query type
	Query.PropertyId = StorageDeviceProperty;
	Query.QueryType = PropertyStandardQuery;

	// Query using IOCTL_STORAGE_QUERY_PROPERTY 
	bResult = ::DeviceIoControl(hDevice,			// device handle
			IOCTL_STORAGE_QUERY_PROPERTY,			// info of device property
			&Query, sizeof(STORAGE_PROPERTY_QUERY),	// input data buffer
			pDevDesc, pDevDesc->Size,				// output data buffer
			&dwOutBytes,							// out's length
			(LPOVERLAPPED)NULL);					

	return bResult;
}
#endif
*/

// **********************************************************
// ��������� ������ ������� ������������ USB ������
// **********************************************************
static void GetUsbDrives( std::vector< lem::Path > & list )
{
 #if defined LEM_MSC
/*
 const int bufferSize = 256;

 char szBuf[lem::Path::MaxLen+10];
 HANDLE hDevice;
 PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;

 char drive[4] = "A:\\";
// TCHAR volume[bufferSize];

 DWORD mask = ::GetLogicalDrives();

 if( mask )
  {
   for( int i=0; i<26; i++ )
    {
     if( mask & 1)
      {
       drive[0] = 'A' + i;

       UINT dtype=::GetDriveTypeA(drive); 
       if( dtype==DRIVE_FIXED )
        {
         sprintf(szBuf, "\\\\?\\%c:", drive[0] );
         hDevice = CreateFileA(szBuf, GENERIC_READ ,
							FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);

         if( hDevice != INVALID_HANDLE_VALUE )
          {
           pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];

           pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

           if(GetDisksProperty(hDevice, pDevDesc))
            {
             if(pDevDesc->BusType == BusTypeUsb)
              {
//               szMoveDiskName[k] = chFirstDriveFromMask(temp);
//               szMoveDiskName[0]=k;
//               k++;
               list.push_back( lem::Path(drive) );
              }
            }

           delete pDevDesc;
           CloseHandle(hDevice);
          }
        }
      }

     mask >>= 1;
    }
  }
*/
 #endif

 return;
}
#endif



void lem::Path::GetMyComputer(
                              std::vector<lem::Path> &list,
                              bool allow_floppies,
                              bool allow_attached
                             )
{
 #if defined LEM_UNIX

  list.push_back( lem::Path( L"/" ) );

 #elif defined LEM_WINDOWS

  std::vector< lem::Path > usb;

  if( !allow_attached )
   {
    GetUsbDrives( usb );
   }
  
  char buffer[256];
  *buffer=0;
 
  DWORD n = GetLogicalDriveStringsA( sizeof(buffer), buffer );
  LEM_CHECKIT_Z(n!=0);

  char *s = buffer;
  while( *s )
   {
    FString drive = s;
    if( drive.empty() ) 
     break;

    bool ok=true;

    if( drive=="A:\\" || drive=="B:\\" )
     {
      ok = allow_floppies;
     }
    else if( !allow_attached )
     {
      lem::Path pdrive(drive);

      if( std::find( usb.begin(), usb.end(), pdrive )!=usb.end() )
       ok = false;
      else if( GetDriveTypeA(drive.c_str()) != DRIVE_FIXED )
       ok = false;
     }

    if( ok )
     list.push_back( lem::Path( drive ) ); 

    s += (drive.length()+1);
   }

 #else
  #error
 #endif
}


// ******************************************************
// ������ ����� (������ 1) �� CD-drives
// ******************************************************
void lem::Path::GetCD( std::vector<lem::Path> &list )
{
 #if defined LEM_WINDOWS

  char buffer[256];
  *buffer=0;
 
  DWORD n = GetLogicalDriveStringsA( sizeof(buffer), buffer );
  LEM_CHECKIT_Z(n!=0);

  char *s = buffer;
  while( *s )
   {
    FString drive = s;
    if( drive.empty() ) 
     break;

    if( GetDriveTypeA( drive.c_str() ) == DRIVE_CDROM )
     list.push_back( lem::Path( drive ) ); 

    s += (drive.length()+1);
   }

 #else
  
  // ������ �������� *Nix ��-������� ���� ������ � CD Drive.

  if( lem::Path::DoesExist("/cdrom/") )
   list.push_back( lem::Path( "/cdrom/" ) );
  else if( lem::Path::DoesExist("/mnt/cdrom/") )
   list.push_back( lem::Path( "/mnt/cdrom/" ) );
  else if( lem::Path::DoesExist("/dev/cdrom/") )
   list.push_back( lem::Path( "/dev/cdrom/" ) );

//  list.push_back( lem::Path( CD_DEVICE ) );

 #endif
}


bool lem::Path::IsCD( char letter )
{
 #if defined LEM_WINDOWS
 char drv[3];
 drv[0]=letter;
 drv[1]=':';
 drv[2]=0;

 return GetDriveTypeA( drv ) == DRIVE_CDROM;
 #else
 return false;
 #endif
}


// *****************************************
// ��������� ����� �������
// *****************************************
bool lem::Path::CdDvdEject( char ch_drv )
{
 #if defined LEM_QT
  return false;
 #elif defined LEM_WINDOWS
 if( ch_drv==0 )
  {
   std::vector<lem::Path> cd;
   GetCD(cd);
 
   if( cd.size()==1 )
    ch_drv = cd.front().GetAscii().front();
   else
    {
     bool res=true;
     for( lem::Container::size_type i=0; i<cd.size(); i++ )
      {
       const char c = cd[i].GetAscii().front();
       bool res2 = CdDvdEject( c );
       res = res && res2;
      }

     return res;
    }
  }

 ch_drv = lem::to_upper(ch_drv);

 if( !lem::is_latin(ch_drv) )
  return false;

 TCHAR sz_drv[3] = { 0, TCHAR(':'), 0 };
 sz_drv[0] = ch_drv;
 MCI_OPEN_PARMS st_mcio;
 st_mcio.lpstrDeviceType  = (LPCTSTR)MCI_DEVTYPE_CD_AUDIO;
 st_mcio.lpstrElementName = (LPCTSTR)sz_drv;
 st_mcio.wDeviceID        = 0;

 if( 
    mciSendCommand(
                   0
                   ,MCI_OPEN
                   ,MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE | MCI_WAIT
                   ,(DWORD)&st_mcio
                  )) 
  return FALSE;

 MCI_STATUS_PARMS st_stat;
 st_stat.dwItem   = MCI_STATUS_MEDIA_PRESENT;
 st_stat.dwReturn = 0;
 mciSendCommand( st_mcio.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM | MCI_WAIT,(DWORD)&st_stat );
 DWORD rs;
 if(!st_stat.dwReturn) 
  {
   DWORD t_delay = GetTickCount();
   rs = mciSendCommand( st_mcio.wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED | MCI_WAIT, 0 );
   if( !rs && (GetTickCount() - t_delay) < 1500 )
    {
     rs = mciSendCommand( st_mcio.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN | MCI_WAIT, 0 );
    }
  } 
 else 
  {
   rs = mciSendCommand( st_mcio.wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN | MCI_WAIT, 0 );
  }

 mciSendCommand(st_mcio.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
 return !rs; 
 #elif defined LEM_LINUX || defined LEM_BSD

 int cdrom = open( CD_DEVICE, O_RDONLY | O_NONBLOCK );
 if( cdrom<0 )
  {
   if( lem::LogFile::IsOpen() )
    lem::LogFile::logfile->printf( "Error in lem::Path::CdDvdEject: can not open cdrom device '%s'\n", CD_DEVICE );

   return false;
  }

 #if defined LEM_LINUX
 const int res = ioctl( cdrom, CDROMEJECT, 0 );
 #elif defined LEM_DARWIN
 const int res=-1;
 #else
 const int res = ioctl( cdrom, CDIOCEJECT, 0 );
 #endif

 if( res < 0 )
  {
   if( lem::LogFile::IsOpen() )
    lem::LogFile::logfile->printf( "Error in lem::Path::CdDvdEject: ioctl returned error code %d\n", res );

   close(cdrom);
   return false;
  } 
 
 close(cdrom);
 return true;

 #else
 return false;
 #endif
}



bool lem::Path::CdDvdClose( char ch_drv )
{
 #if defined LEM_QT
  return false;
 #elif defined LEM_WINDOWS
 if( ch_drv==0 )
  {
   std::vector<lem::Path> cd;
   GetCD(cd);
 
   if( cd.size()==1 )
    ch_drv = cd.front().GetAscii().front();
   else
    return false;
  }

 // Local variables
 char drivePath[] = { ch_drv, ':', '\0' };
 MCI_OPEN_PARMSA openParams;

 // Code
 ZeroMemory(&openParams, sizeof(openParams));
 openParams.lpstrDeviceType = (const char*)MCI_DEVTYPE_CD_AUDIO;
 openParams.lpstrElementName = drivePath;
 if( mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE, (unsigned long)&openParams) == 0 )
  {
   mciSendCommand(openParams.wDeviceID, MCI_SET, /*MCI_SET_DOOR_OPEN :*/ MCI_SET_DOOR_CLOSED, 0 );
   mciSendCommand(openParams.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
  }

 #elif defined LEM_LINUX

 int cdrom = open( CD_DEVICE, O_RDONLY | O_NONBLOCK );
 if( cdrom<0 )
  {
   if( lem::LogFile::IsOpen() )
    lem::LogFile::logfile->printf( "Error in lem::Path::CdDvdClose: can not open cdrom device '%s'\n", CD_DEVICE );

   return false;
  }

 const int res = ioctl( cdrom, CDROMCLOSETRAY, 0 );
 if( res < 0 )
  {
   if( lem::LogFile::IsOpen() )
    lem::LogFile::logfile->printf( "Error in lem::Path::CdDvdClose: ioctl returned error code %d\n", res );

   close(cdrom);
   return false;
  } 
 
 close(cdrom);

 #endif

 return true;
}



// ****************************************************************
// ���� �������� �� ����������, ������� ���.
// ���� subfolders=true, �� ����� ����� ������� ��� ������������
// ��������.
// ****************************************************************
void lem::Path::CreateFolder( bool create_subfolders ) const
{
 #if defined LEM_WINDOWS
  if( create_subfolders )
   {
    // (c) Assaf Tzur-El http://www.codeguru.com/cpp/w-p/files/article.php/c4439/
    if( lem::System_Config::SupportUnicodeFilenames() )
     {
      UFString wsPath=GetUnicode(); 

      // Check for trailing slash:
      int pos = wsPath.find_last_of( lem::Path::GetPathDelimiter() );
      if( wsPath.length() == pos+1 )  // last character is "\"
       {
        wsPath.reduce(pos);
       }

      // Look for existing object:
      DWORD attr = GetFileAttributesW( wsPath.c_str() );
      if( 0xFFFFFFFF == attr )  // doesn't exist yet - create it!
       {
        pos = wsPath.find_last_of( lem::Path::GetPathDelimiter() );
        if( 0 < pos )
         {
          // Create parent dirs:
          lem::Path sub( lem::left(wsPath,pos) );
          sub.CreateFolder(true);
         }

        // Create node:
        BOOL ret = CreateDirectoryW( wsPath.c_str(), NULL );
        LEM_CHECKIT_Z(ret==TRUE);   
       }
      else if (FILE_ATTRIBUTE_DIRECTORY != attr)
       {  // object already exists, but is not a dir
        SetLastError(ERROR_FILE_EXISTS);
       }

      return;
     }
    else
     {
      FString wsPath=GetAscii(); 

      // Check for trailing slash:
      int pos = wsPath.find_last_of( (char)lem::Path::GetPathDelimiter() );
      if( wsPath.length() == pos+1 )  // last character is "\"
       {
        wsPath.reduce(pos);
       }

      // Look for existing object:
      DWORD attr = GetFileAttributesA(wsPath.c_str());
      if( 0xFFFFFFFF == attr )  // doesn't exist yet - create it!
       {
        pos = wsPath.find_last_of( (char)lem::Path::GetPathDelimiter() );
        if( 0 < pos )
         {
          // Create parent dirs:
          lem::Path sub( lem::left(wsPath,pos) );
          sub.CreateFolder(true);
         }

        // Create node:
        BOOL ret = CreateDirectoryA( wsPath.c_str(), NULL );
        LEM_CHECKIT_Z(ret==TRUE);   
       }
      else if (FILE_ATTRIBUTE_DIRECTORY != attr)
       {  // object already exists, but is not a dir
        SetLastError(ERROR_FILE_EXISTS);
       }

      return;
     }
    }
  else
   { 
    BOOL ret;   
    if( lem::System_Config::SupportUnicodeFilenames() )
     ret=CreateDirectoryW( GetUnicode().c_str(), NULL );
    else
     ret=CreateDirectoryA( GetAscii().c_str(), NULL );

    LEM_CHECKIT_Z(ret==TRUE); 
   }

 #elif defined LEM_UNIX

  const int ret = mkdir( GetAscii().c_str(), S_IRWXU );
  LEM_CHECKIT_Z(ret==0); 
     
 #else
  #error
 #endif
}


lem::Path& lem::Path::ConcateLeaf( const lem::Path &Filename )
{
 if( uname.empty() && name.empty() )
  {
   name = Filename.name;
   uname = Filename.uname;
   return *this;
  }

 if( !uname.empty() )
  {
   if( !IsPathDelimiter(uname.back()) )
    uname += lem::Path::GetPathDelimiter();
   uname += Filename.GetUnicode();
  }
 
 if( !name.empty() )
  {
   if( !IsPathDelimiter(name.back()) )
    name += (char)lem::Path::GetPathDelimiter();

   name += Filename.GetAscii();
  }

 return *this;
}


lem::Path& lem::Path::ConcateLeaf( const wchar_t *Filename )
{
 if( lem::lem_is_empty(Filename) )
  return *this;

 if( uname.empty() && name.empty() )
  {
   uname = Filename;
   return *this;
  }

 if( !uname.empty() )
  {
   if( !IsPathDelimiter(uname.back()) )
    uname += lem::Path::GetPathDelimiter();

   uname += Filename;
  }
 
 if( !name.empty() )
  {
   if( !IsPathDelimiter(name.back()) )
    name += (char)lem::Path::GetPathDelimiter();

   name += lem::to_ascii(Filename);
  }

 return *this;
}



lem::Path& lem::Path::ConcateLeaf( const lem::UFString &Filename )
{
 if( uname.empty() && name.empty() )
  {
   uname = Filename;
   return *this;
  }

 if( !uname.empty() )
  {
   if( !IsPathDelimiter(uname.back()) )
    uname += lem::Path::GetPathDelimiter();
   uname += Filename;
  }
 
 if( !name.empty() )
  {
   if( !IsPathDelimiter(name.back()) )
    name += (char)lem::Path::GetPathDelimiter();

   name += lem::to_ascii(Filename);
  }

 return *this;
}


lem::Path& lem::Path::ConcateLeaf( const std::wstring &Filename )
{
 if( uname.empty() && name.empty() )
  {
   uname = Filename;
   return *this;
  }

 if( !uname.empty() )
  {
   if( !IsPathDelimiter(uname.back()) )
    uname += lem::Path::GetPathDelimiter();
   uname += Filename;
  }
 
 if( !name.empty() )
  {
   if( !IsPathDelimiter(name.back()) )
    name += (char)lem::Path::GetPathDelimiter();

   name += lem::to_ascii(Filename);
  }

 return *this;
}


const UFString lem::Path::RemoveLeaf( const UFString &path )
{
 // ������� ��������� ������� � ���������� ���������. � ����� ����
 // path - ���� � �����, �� �������� ��� ��������.
 const int l=path.length();
 int i_break=UNKNOWN;

 // �������� �������� � �������������� �������, ��� ��� ���� � ��������
 // ������ ����� ������������ �� '\'
 for( int i=l-2; i>=0; i-- )
  if( IsPathDelimiter(path[i]) || IsDriveDelimiter(path[i]) )
   {
    i_break=i;
    break;
   }

 UFString res(path);
 if( i_break!=UNKNOWN )
  res.ShrinkTo(i_break);

 return res;
}


void lem::Path::ToUpper(void)
{
 if( !uname.empty() )
  uname.to_upper(); 
 else
  name.to_upper(); 
}


void lem::Path::ToLower(void)
{
 if( !uname.empty() )
  uname.to_lower(); 
 else
  name.to_lower(); 
}

// ********************************************
// ���� CD ��������� � ������� - ������ true.
// ********************************************
bool lem::Path::IsDiskMounted(void) const
{
 #if defined LEM_WINDOWS
 DWORD sn, dummy;

 if( uname.empty() )
  return GetVolumeInformationA( name.c_str(), NULL, 0, &sn, &dummy, &dummy, NULL, 0 )!=0;
 else
  return GetVolumeInformationW( uname.c_str(), NULL, 0, &sn, &dummy, &dummy, NULL, 0 )!=0;
 #else
  return true;
 #endif
}

// **********************************
// ���������� �������� ����� ����
// **********************************
lem::uint32_t lem::Path::GetDiskSerialNumber(void) const
{
 #if defined LEM_WINDOWS
 DWORD sn, dummy;

 BOOL ok;
 if( uname.empty() )
  ok=GetVolumeInformationA( name.c_str(), NULL, 0, &sn, &dummy, &dummy, NULL, 0 )!=0;
 else
  ok=GetVolumeInformationW( uname.c_str(), NULL, 0, &sn, &dummy, &dummy, NULL, 0 )!=0;

 if( ok ) 
  return sn;
 else
  return 0;  
 #else
 return 0;
 #endif
}


// *************************************************************
// ����������� ������� �������� �� ����������� � ��� ������ �
// ��������� ��������� (����������).
// *************************************************************
void lem::Path::PurgeFolder(void) const
{
 #if defined LEM_WINDOWS

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   SHFILEOPSTRUCTW op;
   op.hwnd = NULL;
   op.wFunc = FO_DELETE;

   UFString s = this->GetUnicode();
   s += L"\\*.*";
   wchar_t *buf = new wchar_t[ s.length()+2 ];
   lem_strcpy( buf, s.c_str() );
   buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
 
   op.pFrom = buf;
   op.pTo = NULL;
   op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
   op.lpszProgressTitle = NULL;

   int ret = SHFileOperationW(&op);
   LEM_CHECKIT_Z(ret==0);
   delete[] buf;
  }
 else
  {
   SHFILEOPSTRUCTA op;
   op.hwnd = NULL;
   op.wFunc = FO_DELETE;

   FString s = this->GetAscii();
   s += "\\*.*";
   char *buf = new char[ s.length()+2 ];
   strcpy( buf, s.c_str() );
   buf[ s.length()+1 ] = 0; // ������� SHFileOper ������� �������� '\0' � ����� ������
 
   op.pFrom = buf;
   op.pTo = NULL;
   op.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;
   op.lpszProgressTitle = NULL;

   int ret = SHFileOperationA(&op);
   LEM_CHECKIT_Z(ret==0);
   delete[] buf;
  }
 
 #elif defined LEM_UNIX

  PurgeFolderPosix();

 #else

  PurgeFolderPortable();

 #endif

 return;
}

#if !defined LEM_UNIX && !defined LEM_WINDOWS
// ������������ �������� ������� �������� - �� ������ Boost.Filesystem
void lem::Path::PurgeFolderPortable(void) const
{
 boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
 boost::filesystem::path p1( (GetAscii()+LEM_DIRECTORY_DELIMITER_CHAR).c_str(), boost::filesystem::native );

 for(
     boost::filesystem::directory_iterator itr( p1 );
     itr != end_itr;
     ++itr
    )
  {
   if( boost::filesystem::is_directory( *itr ) )
    {
     // ����������� �� 1 ������� ���� �� ������ ���������
     lem::Path Deeper( itr->string().c_str() );
     Deeper.PurgeFolder();
     Deeper.DoRemove();
     continue;
    }

   lem::Path p( itr->string().c_str() );
   p.DoRemove();
  }

 return;
}
#endif


#if defined LEM_UNIX
void lem::Path::PurgeFolderPosix(void) const
{
 struct stat statbuf;

 DIR *dir = NULL;

 if( lem::System_Config::SupportUnicodeFilenames() )
  { 
   dir = opendir( lem::to_utf8(GetUnicode()).c_str() );
  }
 else
  {
   dir = opendir( GetAscii().c_str() );
  }

 if( dir==NULL )
  return;

 dirent *entry = NULL; 

 FString entry_name;
 entry_name.reserve( lem::Path::MaxLen );

 /* Loop through directory entries. */
 while(true)
  {
   entry = readdir(dir);

   if( entry==NULL )
    break;

   LEM_CHECKIT_Z( entry->d_name );

   if( lem::System_Config::SupportUnicodeFilenames() )
    entry_name = to_utf8(GetUnicode());
   else
    entry_name = GetAscii();

   if( entry_name.back()!=lem::Path::GetPathDelimiter() )    
    entry_name += lem::Path::GetPathDelimiter();
   entry_name += entry->d_name;          

   /* Get entry's information. */
   if( stat( entry_name.c_str(), &statbuf ) == -1 )
    continue;

   if( (statbuf.st_mode&S_IFDIR)==S_IFDIR )
    {
     if(
        (entry->d_name[1]==0 && *entry->d_name==L'.') ||
        (entry->d_name[2]==0 && *entry->d_name==L'.' && entry->d_name[1]==L'.') 
       )
      continue;

     // ���������� ������� ���� �������
     lem::Path foldername;
     if( lem::System_Config::SupportUnicodeFilenames() )
      foldername = lem::Path( lem::from_utf8(entry_name) );
     else
      foldername = lem::Path( entry_name );
       
     foldername.DoRemove();
    }
   else if( (statbuf.st_mode&S_IFREG)==S_IFREG ) 
    {
     // �������� ���������� �����.
     int ret = ::remove( entry_name.c_str() );
     LEM_CHECKIT_Z(ret==0);
    } 
  }
 
 closedir(dir);

 return;
}
#endif



const UFString lem::Path::GetExtension(void) const
{
 if( uname.empty() )
  return lem::Path::GetExtension( GetUnicode() );

 return lem::Path::GetExtension( uname );
}

void lem::Path::RemoveLastLeaf(void)
{
 UFString f = GetUnicode();
 int i=f.length()-2;

 while( i>=0 )
  { 
   if( lem::Path::IsPathDelimiter(f[i]) )
    break;

   i--;
  }

 if( i<=0 )
  {
   clear();
  }
 else
  {
   if( IsUnicode() )
    uname.ShrinkTo(i);
   else
    name.ShrinkTo(i);
  }

 return;
}


UFString lem::Path::GetFileName(void) const
{
 UFString f = GetUnicode();
 int i=f.length()-1;

 while( i>=0 )
  { 
   if( lem::Path::IsPathDelimiter(f[i]) )
    break;

   i--;
  }

 if( i<=0 )
  return f;

 if( i==f.length()-1 )
  return UFString();

 return UFString( f.c_str()+i+1 );
}


UFString lem::Path::GetLastLeaf(void) const
{
 // ���� ��� ������� � ������� � GetFileName(), �� ����� ���������� 
 // ������� ���� ����� ������ ��������� ��������� ������� ��������� ����������
 // ��������� � ����.
 return GetFileName();
}




wchar_t lem::Path::GetPathDelimiter(void)
{
 return LEM_DIRECTORY_DELIMITER_CHAR;
}


#if defined LEM_UNIX
void lem::Path::Win_2_Lin( FString &p )
{
 p.subst_all( '\\', static_cast<char>(GetPathDelimiter()) );
 return;
}

void lem::Path::Win_2_Lin( UFString &p )
{
 p.subst_all( L'\\', GetPathDelimiter() );
 return;
}
#endif


// ������ true, ���� ���� ��������� �� LPTx, �� ���� �� �������. ���
// �������� �������� � Windows �������� deadlock'� ��� ������� ��������
// � ����� ������.
bool lem::Path::IsLPT(void) const
{
 const int al = name.length();
 if( al>=4 )
  {
   return (name[al-4]=='l' || name[al-4]=='L') &&
          (name[al-3]=='p' || name[al-3]=='P') &&
          (name[al-2]=='t' || name[al-2]=='T') &&
          lem::is_digit(name[al-1]);
  }

 if( !uname.empty() )
  {
   const int l = uname.length();
   return (uname[l-4]==L'l' || uname[l-4]==L'L') &&
          (uname[l-3]==L'p' || uname[l-3]==L'P') &&
          (uname[l-2]==L't' || uname[l-2]==L'T') &&
          lem::is_udigit(uname[l-1]);
  }

 return false;
}



void lem::Path::SaveBin( Stream &bin ) const
{
 name.SaveBin(bin);
 uname.SaveBin(bin);
}

void lem::Path::LoadBin( Stream &bin )
{
 name.LoadBin(bin);
 uname.LoadBin(bin);
}


#if !defined LEM_WINDOWS && !defined LEM_UNIX
static lem::uint64_t CrawlPortable(
                                   boost::filesystem::path &org,
                                   bool recurse,
                                   IDirTraverser *traverser
                                  )
{
 lem::uint64_t tot_size=0;
 int count=0;

 boost::filesystem::directory_iterator end_itr;

 if( !boost::filesystem::exists(org) || !boost::filesystem::is_directory( org ) )
  return tot_size;

 for( boost::filesystem::directory_iterator itr( org ); itr != end_itr; ++itr )
  {
   if( traverser && !traverser->Continue() )
    break;

   try
    {
     if( boost::filesystem::is_directory( *itr ) && recurse )
      {
       // ����������� �� 1 ������� ���� �� ������ ���������
       boost::filesystem::path deeper( itr->string() );

       if( traverser )
        traverser->Folder( itr->string().c_str() );

       tot_size += CrawlPortable( deeper, recurse, traverser );
       continue;
      }

     // ��� ��������� ���������� � ����� ��������� ���. 
     if( !itr->string().empty() )
      {
       if( traverser )
        traverser->File( itr->string().c_str() );

       lem::Path p(itr->string().c_str());
       BinaryFile f( p, true, false );

       count++;
       tot_size += f.fsize64();
      }
    }
   catch(...)
    {
    }
  }

 return tot_size;
}

static lem::uint64_t CrawlPortable(
                                   const FString &org,
                                   bool recurse,
                                   IDirTraverser *traverser
                                  )
{
 LEM_CHECKIT_Z( !org.empty() );
 boost::filesystem::path p( org.c_str(), boost::filesystem::native );
 return CrawlPortable( p, recurse, traverser );
}
#endif


#if defined LEM_WINDOWS


static lem::uint64_t CrawlWin( const char *path, int plen, bool recurse, IDirTraverser *traverser )
{
 LEM_CHECKIT_Z( path!=NULL );
 LEM_CHECKIT_Z( plen>0 );

 lem::uint64_t tot_size=0;

 WIN32_FIND_DATAA find_data;
 HANDLE hfind = FindFirstFileA( path, &find_data );

 int buf_size = std::max( lem::Path::MaxLen+1, plen+1 );
 char *Buffer = new char[buf_size];
 strcpy( Buffer, path );

 if( hfind!=INVALID_HANDLE_VALUE )
  {
   do
    {
     if( traverser && !traverser->Continue() )
      break; 

     const char* FileName = find_data.cFileName;

     if(
        (FileName[1]==0 && *FileName=='.') ||
        (FileName[2]==0 && *FileName=='.' && FileName[1]=='.' )
       )
      continue;

     if(
        (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
        traverser!=NULL
       )
      {
       const int l = plen + strlen(FileName) + 8;
       if( l>buf_size )
        {
         buf_size = l+1024;
         char *Buffer2 = new char[buf_size];
         strcpy( Buffer2, Buffer );
         delete[] Buffer;
         Buffer = Buffer2;
        }

       Buffer[ plen-3 ] = 0;
       strcat( Buffer, FileName );
      }

     if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
       if( traverser )
        traverser->Folder( Buffer );

       if( recurse )
        { 
         int ln = strlen(Buffer);

         if( ln && Buffer[ ln-1 ]=='\\' )
          {
           strcat( Buffer, "*.*" );
           ln += 3;
          } 
         else     
          { 
           strcat( Buffer, "\\*.*" );
           ln += 4;  
          } 

         tot_size += CrawlWin( Buffer, ln, recurse, traverser );
        }
      }
     else
      { 
       if( traverser )
        traverser->File( Buffer, FileName );

       #if defined LEM_BORLAND
       tot_size += find_data.nFileSizeLow;
       #else
       lem::int64_t fsize = ( lem::uint64_t(find_data.nFileSizeHigh) << 32) | (0x00000000ffffffffUL & find_data.nFileSizeLow);
       tot_size += fsize;
       #endif
      }
    }
   while( FindNextFileA( hfind, &find_data ) );
  }

 FindClose(hfind);
 delete[] Buffer;
 
 return tot_size;
}




static lem::uint64_t CrawlWin( const wchar_t *path, int plen, bool recurse, IDirTraverser *traverser )
{
 LEM_CHECKIT_Z( path!=NULL );
 LEM_CHECKIT_Z( plen>0 );
 
 static int dir_counter=0;
 dir_counter++;

 if( !(dir_counter%16) )
  lem::Application::DoEvents();

 lem::uint64_t tot_size=0;

 WIN32_FIND_DATAW find_data;
 HANDLE hfind = FindFirstFileW( path, &find_data );

 int buf_size = std::max( lem::Path::MaxLen+1, plen+1 );
 wchar_t *Buffer = new wchar_t[buf_size];
 wcscpy( Buffer, path );

 if( hfind!=INVALID_HANDLE_VALUE )
  {
   do
    {
     if( traverser && !traverser->Continue() )
      break; 

     const wchar_t* FileName = find_data.cFileName;

     if(
        (FileName[1]==0 && *FileName==L'.') ||
        (FileName[2]==0 && *FileName==L'.' && FileName[1]==L'.')
       )
      continue;

     if(
        (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
        traverser!=NULL
       )
      {
       const int l = plen + wcslen(FileName) + 8;
       if( l>buf_size )
        {
         buf_size = l+1024;
         wchar_t *Buffer2 = new wchar_t[buf_size];
         wcscpy( Buffer2, Buffer );
         delete[] Buffer;
         Buffer = Buffer2;
        }

       Buffer[ plen-3 ] = 0;
       wcscat( Buffer, FileName );
      }

     if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
       if( traverser )
        traverser->Folder( Buffer );

       if( recurse )
        { 
         int ln = wcslen(Buffer);

         if( ln && Buffer[ ln-1 ]==L'\\' )
          {
           wcscat( Buffer, L"*.*" );
           ln += 3;
          } 
         else     
          { 
           wcscat( Buffer, L"\\*.*" );
           ln += 4;  
          } 

         tot_size += CrawlWin( Buffer, ln, recurse, traverser );
        }
      } 
     else
      { 
       if( traverser )
        traverser->File( Buffer, FileName );

       #if defined LEM_BORLAND
       tot_size += find_data.nFileSizeLow;
       #else
       lem::uint64_t hi = find_data.nFileSizeHigh;
       lem::uint64_t lo = find_data.nFileSizeLow;
       lem::int64_t fsize = ( hi << 32) | (0x00000000ffffffffUL & lo );
       tot_size += fsize;
       #endif
      }
    }
   while( FindNextFileW( hfind, &find_data ) );
  }

 FindClose(hfind);
 delete[] Buffer;
 
 return tot_size;
}


static lem::uint64_t CrawlWin( const wchar_t *path, int plen, bool recurse, IDirTraverser2 *traverser )
{
 LEM_CHECKIT_Z( path!=NULL );
 LEM_CHECKIT_Z( plen>0 );

 static int dir_counter=0;
 dir_counter++;

 if( !(dir_counter%16) )
  lem::Application::DoEvents();

 lem::uint64_t tot_size=0;

 WIN32_FIND_DATAW find_data;
 HANDLE hfind = FindFirstFileW( path, &find_data );

 int buf_size = std::max( lem::Path::MaxLen+1, plen+1 );
 wchar_t *Buffer = new wchar_t[buf_size];
 wcscpy( Buffer, path );

 if( hfind!=INVALID_HANDLE_VALUE )
  {
   do
    {
     if( traverser && !traverser->Continue() )
      break; 

     const wchar_t* FileName = find_data.cFileName;

     if(
        (FileName[1]==0 && *FileName==L'.') ||
        (FileName[2]==0 && *FileName==L'.' && FileName[1]==L'.')
       )
      continue;

     if(
        (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
        traverser!=NULL
       )
      {
       const int l = plen + wcslen(FileName) + 8;
       if( l>buf_size )
        {
         buf_size = l+1024;
         wchar_t *Buffer2 = new wchar_t[buf_size];
         wcscpy( Buffer2, Buffer );
         delete[] Buffer;
         Buffer = Buffer2;
        }

       Buffer[ plen-3 ] = 0;
       wcscat( Buffer, FileName );
      }

     if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
      {
       if( traverser )
        {
         if( !traverser->CanEnterFolder(FileName) )
          continue; 

         traverser->Folder( Buffer );
        } 

       if( recurse )
        { 
         int ln = wcslen(Buffer);

         if( ln && Buffer[ ln-1 ]==L'\\' )
          {
           wcscat( Buffer, L"*.*" );
           ln += 3;
          } 
         else     
          { 
           wcscat( Buffer, L"\\*.*" );
           ln += 4;  
          } 

         tot_size += CrawlWin( Buffer, ln, recurse, traverser );
        }
      } 
     else
      {
       #if defined LEM_BORLAND
       unsigned int fs = find_data.nFileSizeLow;
       #else
       lem::int64_t fs = ( lem::uint64_t(find_data.nFileSizeHigh) << 32) | (0x00000000ffffffffUL & find_data.nFileSizeLow);
       #endif

       if( traverser )
        {
/*
         traverser->File(
                         Buffer,
                         fs,
                         boost::date_time::time_from_ftime<boost::posix_time::ptime>( find_data.ftCreationTime ),
                         boost::date_time::time_from_ftime<boost::posix_time::ptime>( find_data.ftLastWriteTime )
                        );

*/
         traverser->File( path, plen-3, &find_data );
        } 

       tot_size += fs;
      }
    }
   while( FindNextFileW( hfind, &find_data ) );
  }

 FindClose(hfind);
 delete[] Buffer;
 
 return tot_size;
}


static lem::uint64_t CrawlWin( const UFString &root, bool recurse, IDirTraverser *traverser )
{
 LEM_CHECKIT_Z( !root.empty() );

 UFString buffer = lem::Path::IsPathDelimiter(root.back()) ?
                         (root + L"*.*") :
                         (root + L"\\*.*");
                        
 return CrawlWin( buffer.c_str(), buffer.length(), recurse, traverser );
}

static lem::uint64_t CrawlWin( const UFString &root, bool recurse, IDirTraverser2 *traverser )
{
 LEM_CHECKIT_Z( !root.empty() );

 UFString buffer = lem::Path::IsPathDelimiter(root.back()) ?
                         (root + L"*.*") :
                         (root + L"\\*.*");
                        
 return CrawlWin( buffer.c_str(), buffer.length(), recurse, traverser );
}


static lem::uint64_t CrawlWin( const FString &root, bool recurse, IDirTraverser *traverser )
{
 LEM_CHECKIT_Z( !root.empty() );
 LEM_CHECKIT_Z( traverser!=NULL );

 FString buffer = lem::Path::IsPathDelimiter(root.back()) ?
                         (root + "*.*") :
                         (root + "\\*.*");
                        
 return CrawlWin( buffer.c_str(), buffer.length(), recurse, traverser );
}

#endif


#if defined LEM_UNIX
static lem::uint64_t CrawlPosix( const char *folder_name, bool recurse, IDirTraverser *traverser )
{
 LEM_CHECKIT_Z( folder_name!=NULL );
 LEM_CHECKIT_Z( traverser!=NULL );

 lem::uint64_t tot_size=0;

 struct stat statbuf;

 DIR *dir = opendir( folder_name );

 if( dir==NULL )
  return 0;

 dirent *entry = NULL; 

 FString entry_name;
 entry_name.reserve( lem::Path::MaxLen );

 /* Loop through directory entries. */
 while(true)
  {
   if( traverser && !traverser->Continue() )
    break;

   entry = readdir(dir);

   if( entry==NULL )
    break;

   LEM_CHECKIT_Z( entry->d_name );
   entry_name = folder_name;
   if( entry_name.back()!=lem::Path::GetPathDelimiter() )    
    entry_name += lem::Path::GetPathDelimiter();
   entry_name += entry->d_name;          

   /* Get entry's information. */
   if( stat( entry_name.c_str(), &statbuf ) == -1 )
    continue;

   if( (statbuf.st_mode&S_IFDIR)==S_IFDIR && recurse )
    {
     if(
        (entry->d_name[1]==0 && *entry->d_name==L'.') ||
        (entry->d_name[2]==0 && *entry->d_name==L'.' && entry->d_name[1]==L'.') 
       )
      continue;

     if( traverser )
      traverser->Folder( entry_name.c_str() );

     if( recurse )
      CrawlPosix( entry_name.c_str(), recurse, traverser );
    }
   else if( (statbuf.st_mode&S_IFREG)==S_IFREG ) 
    {
     // ��������� ���������� �����.
     if( traverser )
      traverser->File( entry_name.c_str(), entry->d_name );

     tot_size += statbuf.st_size;
    }
  }

 closedir(dir);

 return tot_size;
}
#endif


// ******************************************************
// ���������� ������ ������ � �������� (� � ������������,
// ���� recurse=true).
// ******************************************************
lem::uint64_t lem::Path::FolderSize( bool recurse ) const
{
 return Crawl( recurse, (IDirTraverser*)NULL );
}



lem::uint64_t lem::Path::Crawl( bool recurse, lem::IDirTraverser *traverser ) const
{
 #if defined LEM_WINDOWS
 if( lem::System_Config::SupportUnicodeFilenames() )
  return CrawlWin( GetUnicode(), recurse, traverser );
 else 
  return CrawlWin( GetAscii(), recurse, traverser );
 #elif defined LEM_UNIX
 if( lem::System_Config::SupportUnicodeFilenames() )
  return CrawlPosix( to_utf8(GetUnicode()).c_str(), recurse, traverser );
 else 
  return CrawlPosix( GetAscii().c_str(), recurse, traverser);
 #else 
 return CrawlPortable( GetAscii().c_str(), recurse, traverser);
 #endif
}

#if defined LEM_WINDOWS
lem::uint64_t lem::Path::Crawl( bool recurse, lem::IDirTraverser2 *traverser ) const
{
 return CrawlWin( GetUnicode(), recurse, traverser );
}
#endif


wchar_t lem::Path::GetExtDelimiter(void)
{
 return L'.';
}


void lem::Path::AddExtension( const char *ext )
{
 if( ext==NULL )
  return;

 if( !name.empty() )
  {
   if( *ext!=GetExtDelimiter() )
    name.Add_Dirty( static_cast<char>(GetExtDelimiter()) );

   name.Add_Dirty( ext );
   name.calc_hash();
  }

 if( !uname.empty() )
  {
   if( *ext!=GetExtDelimiter() )
    uname.Add_Dirty( GetExtDelimiter() );

   uname += ext;
   uname.calc_hash();
  }

 return;
}


// ********************************************
// Append '\' or '/' if not already appened
// ********************************************
void lem::Path::AppendPathDelimiter(void)
{
 if( !name.empty() )
  {
   if( !IsPathDelimiter(name.back()) )
    {
     name += static_cast<char>(GetPathDelimiter());
    }
  }

 if( !uname.empty() )
  {
   if( !IsPathDelimiter(uname.back()) )
    {
     uname += GetPathDelimiter();
    }
  }

 return;
}

// ***************************************
// ���������� ������ �����.
// ��� ��������������� ����� ���������� 0.
// ***************************************
size_t lem::Path::FileSize(void) const
{
 if( !uname.empty() )
  {
   return FileSize(uname.c_str());
  }
 else if( !name.empty() )
  {
   return FileSize(name.c_str());
  }

 return 0;
}



// ************************************************************************
// ���������� ������ ��������� (������ � ������������) � ������ ��������.
//
// N.B. ������������ ����� ���������� ��������� PtrCollect ������ ��-��
// �����-������������ � �������.
// ************************************************************************
void lem::Path::List( std::vector< std::pair< lem::Path, bool /*is_file*/ > > &list ) const
{
 list.reserve(1024);

 #if defined LEM_WINDOWS

  UFString folder = GetUnicode();
  UFString buffer = lem::Path::IsPathDelimiter(folder.back()) ?
                     (folder + L"*.*") :
                     (folder + L"\\*.*");

  if( lem::System_Config::SupportUnicodeFilenames() )
   {
    // WinNT/XP/2k3 - unicode
    WIN32_FIND_DATAW find_data;
    HANDLE hfind = FindFirstFileW( buffer.c_str(), &find_data );

    if( hfind==INVALID_HANDLE_VALUE )
     return;

    do
     {
      const wchar_t* FileName = find_data.cFileName;
      LEM_CHECKIT_Z(FileName!=NULL);

      if(
         (FileName[1]==0 && *FileName==L'.') ||
         (FileName[2]==0 && *FileName==L'.' && FileName[1]==L'.')
        )
       continue;

      bool is_dir = false;

      if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
       {
        is_dir = true;
       } 

      UFString filename( folder );

      if( filename.back()!=lem::Path::GetPathDelimiter() )
       filename += lem::Path::GetPathDelimiter();

      filename += FileName; 
      list.push_back( std::make_pair( lem::Path(filename), !is_dir ) );
     }
    while( FindNextFileW( hfind, &find_data ) );

   BOOL res = FindClose(hfind);
   LEM_CHECKIT_Z(res!=0); 
   return;
  }
 else
  {
   // Win9x - ascii
   FString abuffer( to_ascii(buffer) );
   FString afolder( to_ascii(folder) );

   WIN32_FIND_DATAA find_data;
   HANDLE hfind = FindFirstFileA( abuffer.c_str(), &find_data );

   if( hfind==INVALID_HANDLE_VALUE )
    return;

    do
     {
      const char* FileName = find_data.cFileName;
      LEM_CHECKIT_Z(FileName!=NULL);

      if(
         (FileName[1]==0 && *FileName=='.') ||
         (FileName[2]==0 && *FileName=='.' && FileName[1]=='.')
        )
       continue;

      bool is_dir = false;

      if( find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
       {
        is_dir = true;
       } 

      FString filename( afolder );

      if( filename.back()!=lem::Path::GetPathDelimiter() )
       filename += static_cast<FString::value_type>(lem::Path::GetPathDelimiter());

      filename += FileName; 
      list.push_back( std::make_pair( lem::Path(to_unicode(filename)), !is_dir ) );
     }
    while( FindNextFileA( hfind, &find_data ) );

   BOOL res = FindClose(hfind);
   LEM_CHECKIT_Z(res!=0); 
   return;

  }

 #elif defined LEM_UNIX

 struct stat statbuf;

 bool utf8=false; 
 FString folder_name;
 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   folder_name = lem::to_utf8(GetUnicode());
   utf8 = true;
  }
 else
  {
   if( !uname.empty() )
    folder_name = lem::to_ascii(uname);
   else if( !name.empty() )
    folder_name = name;
  }

 DIR *dir = opendir( folder_name.c_str() );
   
 if( dir==NULL )
  return;

 dirent *entry = NULL; 

 FString entry_name;
 entry_name.reserve( lem::Path::MaxLen );

 /* Loop through directory entries. */
 while(true)
  {
//   int r = readdir_r( dir, entry, &entry );
   entry = readdir(dir);

   if( entry==NULL )
    break;

   LEM_CHECKIT_Z( entry->d_name );
   entry_name = folder_name;
   if( entry_name.back()!=lem::Path::GetPathDelimiter() )    
    entry_name += lem::Path::GetPathDelimiter();
   entry_name += entry->d_name;          

   /* Get entry's information. */
   if( stat( entry_name.c_str(), &statbuf ) == -1 )
    continue;

   bool is_dir = false;
   bool is_file = false;

   if( (statbuf.st_mode&S_IFDIR)==S_IFDIR )
    {
     if(
        (entry->d_name[1]==0 && *entry->d_name==L'.') ||
        (entry->d_name[2]==0 && *entry->d_name==L'.' && entry->d_name[1]==L'.') 
       )
      continue;

     is_dir = true;
    }
   else if( (statbuf.st_mode&S_IFREG)==S_IFREG ) 
    {
     // ��������� ���������� �����.
     // ��������� find_data �������� ����� ������, ��� ����� ��������
     // � ����������� �����.
     is_file = true; 
    }

   if( !is_file && !is_dir )
    continue;

   lem::Path filename;
   if( utf8 )
    filename = lem::Path( lem::from_utf8(entry_name) );
   else
    filename = lem::Path( entry_name );
  
   list.push_back( std::make_pair( filename, is_file ) );
  }

 closedir(dir);

 #else

 boost::filesystem::path folder( GetAscii().c_str(), boost::filesystem::native );
 boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end

 for(
     boost::filesystem::directory_iterator itr( folder );
     itr != end_itr;
     ++itr
    )
  {
   lem::Path filename( itr->native_file_string().c_str() );
   list.push_back( std::make_pair( filename, !itr->is_directory() ) );
  }

 #endif
}


// ************************************************************************
// �������� ���������� ��������� ����. ���������� ������� ������ ��������.
// ************************************************************************
bool lem::Path::Check(void) const
{
 if( IsLocal() )
  {
   // ?
   return true;
  }
 else if( IsUrl() )
  {
   #if defined LEM_WINDOWS
    #if defined LEM_QT
     return true;
    #else
     if( !uname.empty() )
      return IsValidURL( NULL, uname.c_str(), 0 )==S_OK;
     else if( !name.empty() )
      return IsValidURL( NULL, lem::to_unicode(name).c_str(), 0 )==S_OK;
     else
      return false;
    #endif
   #endif
  }

 return false;
}


// ************************************************************************
// ������ true ��� ����� � ��������� �������� ������� (local file system)
// ��� � ��������� ����: � ������� UNC ��� Windows \\���_�����\���_�������,
// long UNCW: \\?\���� ��� \\?\���_�����\���_�������).
// ************************************************************************
bool lem::Path::IsLocal(void) const
{
 // ��������� ��������� �� �����, ������ ��������� �� ������ �������
 if( !uname.empty() )
  {
   const wchar_t c = uname.front();
   if( c==L'.' || c==L'\\' || c==L'/' )
    return true;

   if( lem::is_ualpha(c) && uname.length()>1 && uname[1]==L':' )
    return true; // ������� 'C:'

   // ��������, ��� ��� �� URL'� ���� ftp:// ��� http://
   return !IsFtp() && !IsHttp();
  }
 else if( !name.empty() )
  {
   const char c = name.front();
   if( c==L'.' || c==L'\\' || c==L'/' )
    return true;

   if( lem::is_alpha(c) && name.length()>1 && name[1]==':' )
    return true; // ������� 'C:'

   // ��������, ��� ��� �� URL'� ���� ftp:// ��� http://
   return !IsFtp() && !IsHttp();
  }

 return false;
}


// *************************************************
// ������ true, ���� ���� ��������� �� FTP-������
// *************************************************
bool lem::Path::IsFtp(void) const
{
 if( uname.length()>6 )
  {
   return uname.eq_begi( L"ftp://" );
  }
 else if( name.length()>6 )
  {
   return name.eq_begi( "ftp://" );
  }

 return false;
}


// *************************************************
// ������ true, ���� ���� ��������� �� HTTP-������
// *************************************************
bool lem::Path::IsHttp(void) const
{
 if( uname.length()>7 )
  {
   return uname.eq_begi( L"http://" ) || uname.eq_begi( L"https://" );
  }
 else if( name.length()>6 )
  {
   return name.eq_begi( "http://" ) || name.eq_begi( "https://" );
  }

 return false;
}


// ******************************************************************
// �������� �� �������� ���� ��� ��������� ����� (� ��������� * � ?)
// ******************************************************************
bool lem::Path::Match( const wchar_t *mask ) const
{
 if( !uname.empty() )
  {
   return lem::regex_match( mask, uname.c_str() );
  }
 else if( !name.empty() )
  {
   return lem::regex_match( lem::to_ascii(UFString(mask)).c_str(), name.c_str() );
  }

 return false;
}


bool lem::Path::Match( const lem::UFString & mask ) const
{
 if( !uname.empty() )
  {
   return lem::regex_match( mask.c_str(), uname.c_str() );
  }
 else if( !name.empty() )
  {
   return lem::regex_match( lem::to_ascii(mask).c_str(), name.c_str() );
  }

 return false;
}


// ************************************
// �������� �� �������� ������ URL��
// ************************************
bool lem::Path::IsUrl(void) const
{
 return IsFtp() || IsHttp();
}


void lem::Path::MonitorCD( lem::Path::EventHandler handler, void *data )
{
 for( lem::Container::size_type i=0; i<cd_event.size(); i++ )
  if( cd_event[i].first==handler && cd_event[i].second==data )
   return;

 cd_event.push_back( std::make_pair( handler, data ) );
 return;   
}

void lem::Path::RemoveCDEventHandler( lem::Path::EventHandler handler )
{
 for( lem::Container::size_type i=0; i<cd_event.size(); i++ )
  if( cd_event[i].first==handler )
   {
    cd_event.erase( cd_event.begin()+i );
    return;
   }

 return;
}

// *******************************************************************
// ������������� ������� � �������� CDROM - ���������� ���������� ���.
// ���� ����� ���������� ������� �����, ���������� �������� �������
// �� ������������� ����������. ��� ������� Windows �������� ������
// ������������ �������� ������������ ��������� WM_DEVICECHANGE.
// *******************************************************************
void lem::Path::OnCDEvent( int Message )
{
 for( lem::Container::size_type i=0; i<cd_event.size(); i++ )
  (*cd_event[i].first)( Message, cd_event[i].second );

 return;
}



void lem::Path::MonitorPath( lem::Path::EventHandler handler, void *data )
{
 for( lem::Container::size_type i=0; i<filemon_event.size(); i++ )
  if( filemon_event[i].first==handler && filemon_event[i].second==data )
   return;

 filemon_event.push_back( std::make_pair( handler, data ) );
 return;   
}

void lem::Path::RemovePathEventsHandler( lem::Path::EventHandler handler )
{
 for( lem::Container::size_type i=0; i<filemon_event.size(); i++ )
  if( filemon_event[i].first==handler )
   {
    filemon_event.erase( cd_event.begin()+i );
    return;
   }

 return;
}


// ************************************************************
// ��� MS Windows: ������������ ��� ����� (���� ������� ����).
// � ��������� ������� - ������������ ������ ������.
// ************************************************************
lem::UFString lem::Path::GetDiskName(void) const
{
 #if defined LEM_WINDOWS

  if( lem::System_Config::SupportUnicodeFilenames() )
   {
    wchar_t volume_name[ 256 ];
    memset( volume_name, 0, sizeof(volume_name) );
    DWORD d1, d2, d3;
    BOOL res = GetVolumeInformationW(
                                    GetUnicode().c_str(),
                                    volume_name, sizeof(volume_name)/sizeof(volume_name[0])-1,
                                    &d1, &d2, &d3,
                                    NULL, 0 );

    if( res!=0 )
     {
      return UFString(volume_name);
     }
   }
  else
   {
    char volume_name[ 256 ];
    memset( volume_name, 0, sizeof(volume_name) );
    DWORD d1, d2, d3;
    BOOL res = GetVolumeInformationA(
                                     GetAscii().c_str(),
                                     volume_name, sizeof(volume_name)/sizeof(volume_name[0])-1,
                                     &d1, &d2, &d3,
                                     NULL, 0 );

    if( res!=0 )
     {
      return lem::to_unicode(FString(volume_name));
     }
   }

  return UFString();

 #else
 return UFString();
 #endif
}


// �����, ��������������� ������ ����� ��� ������� ���������
// *.* ��� Dos/Win
// *   ��� Unix
lem::UFString lem::Path::AllFilesMask(void)
{
 #if defined LEM_DOS || defined LEM_WINDOWS
 return UFString( L"*.*" );
 #elif defined LEM_UNIX
 return UFString( L"*" );
 #else
 #error
 #endif
}


bool lem::Path::operator==( const Path &x ) const
{
 if( !uname.empty() && !x.uname.empty() )
  {
   #if defined LEM_WINDOWS
   return uname.eqi(x.uname);
   #else
   return uname==x.uname;
   #endif
  }

 if( !name.empty() && !x.name.empty() )
  {
   #if defined LEM_WINDOWS
   return name.eqi(x.name);
   #else
   return name==x.name;
   #endif
  }

 #if defined LEM_WINDOWS
 return GetUnicode().eqi(x.GetUnicode());
 #else
 return GetUnicode()==x.GetUnicode();
 #endif
}

bool lem::Path::operator!=( const Path &x ) const
{
 if( !uname.empty() && !x.uname.empty() )
  {
   #if defined LEM_WINDOWS
   return !uname.eqi(x.uname);
   #else
   return uname!=x.uname;
   #endif
  }

 if( !name.empty() && !x.name.empty() )
  {
   #if defined LEM_WINDOWS
   return !name.eqi(x.name);
   #else
   return name!=x.name;
   #endif
  }

 #if defined LEM_WINDOWS
 return !GetUnicode().eqi(x.GetUnicode());
 #else
 return GetUnicode()!=x.GetUnicode();
 #endif
}


bool lem::Path::operator>( const Path &x ) const
{
 if( !uname.empty() && !x.uname.empty() )
  return uname>x.uname;

 if( !name.empty() && !x.name.empty() )
  return name>x.name;

 return GetUnicode()>x.GetUnicode();
}

bool lem::Path::operator<( const Path &x ) const
{
 if( !uname.empty() && !x.uname.empty() )
  return uname<x.uname;

 if( !name.empty() && !x.name.empty() )
  return name<x.name;

 return GetUnicode()<x.GetUnicode();
}



namespace lem
{
 struct __FileCollector : public lem::IDirTraverser
 {
  lem::UFString mask;

  std::vector< lem::Path > *files;

  __FileCollector(void) { files=NULL; }

  virtual bool Continue(void) { return true; }

  virtual void File( const char *path, const char *filename ) 
  {
   if( mask.empty() )
    {
     files->push_back( lem::Path(path) );
    }
   else
    {
     lem::Path p(filename);
     if( p.Match(mask) )
      files->push_back( lem::Path(path) );
    }
  }

  virtual void File( const wchar_t *path, const wchar_t *filename )
  {
   if( mask.empty() )
    { 
     files->push_back( lem::Path(path) );
    }
   else
    {
     lem::Path p(filename);
     if( p.Match(mask) )
      files->push_back( lem::Path(path) );
    }
  }

  virtual void Folder( const char *path ) {}
  virtual void Folder( const wchar_t *path ) {}
 };


 struct __DummyScanner : public lem::IDirTraverser
 {
  lem::zbool cont;
  lem::zbool found;

  __DummyScanner(void) : cont(true) {}

  virtual bool Continue(void) { return cont; }

  virtual void File( const char *path, const char *filename ) { cont=false; found=true; }
  virtual void File( const wchar_t *path, const wchar_t *filename ) { cont=false; found=true; }
  virtual void Folder( const char *path ) { cont=false; found=true; }
  virtual void Folder( const wchar_t *path ) { cont=false; found=true; }
 };
}



void lem::Path::ListFiles( std::vector< lem::Path > &list, bool recursive ) const
{
 lem::__FileCollector c;
 c.files = &list;
 Crawl( recursive, &c );
 return;
}


void lem::Path::ListFiles( const wchar_t *mask, std::vector< lem::Path > &list, bool recursive ) const
{
 lem::__FileCollector c;
 c.files = &list;
 c.mask = mask;
 Crawl( recursive, &c );
 return;
}



// ********************************************************
// ���� �� � �������� ���� ���� ���� ��� ��������� �����?
// ********************************************************
bool lem::Path::IsFolderEmpty(void) const
{
// return PathIsDirectoryEmpty( GetUnicode().c_str() ); ??? ���� ��������� ������ ��������

 lem::__DummyScanner c;
 Crawl( false, &c );
 return !c.found;
}


// **********************************************************************
// ���������� ������ ���������� ����� �� �����, ���� ������� ����������
// ����� ���� ��������.
// **********************************************************************
lem::int64_t lem::Path::GetDiskFreeSpace(void) const
{
 #if defined LEM_WINDOWS

 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   ULARGE_INTEGER i64FreeBytesToCaller;
   BOOL (CALLBACK *pGetDiskFreeSpaceExW)(LPCWSTR lpDirectoryName,
		PULARGE_INTEGER lpFreeBytesAvailable,PULARGE_INTEGER lpTotalNumberOfBytes,
		PULARGE_INTEGER lpTotalNumberOfFreeBytes);

   *((FARPROC*)&pGetDiskFreeSpaceExW) = GetProcAddress( GetModuleHandleW(L"kernel32.dll"), "GetDiskFreeSpaceExW" );

   if(pGetDiskFreeSpaceExW!=NULL)
    {
     ULARGE_INTEGER i64TotalBytes,i64FreeBytes;
     if(!pGetDiskFreeSpaceExW( GetUnicode().c_str(), &i64FreeBytesToCaller,&i64TotalBytes,&i64FreeBytes))
      return 0;
    }
   else
    {
     DWORD nSectors,nBytes,nFreeClusters,nTolalClusters;
     if(!::GetDiskFreeSpaceW(GetUnicode().c_str(),&nSectors,&nBytes,&nFreeClusters,&nTolalClusters))
      return 0;
     i64FreeBytesToCaller.QuadPart=nBytes*nSectors*nFreeClusters;
    }

   return i64FreeBytesToCaller.QuadPart;
  }
 else
  {
   ULARGE_INTEGER i64FreeBytesToCaller;
   BOOL (CALLBACK *pGetDiskFreeSpaceEx)(LPCSTR lpDirectoryName,
         PULARGE_INTEGER lpFreeBytesAvailable,PULARGE_INTEGER lpTotalNumberOfBytes,
         PULARGE_INTEGER lpTotalNumberOfFreeBytes);
   *((FARPROC*)&pGetDiskFreeSpaceEx) = GetProcAddress( GetModuleHandleA("kernel32.dll"),"GetDiskFreeSpaceExA");
   if (pGetDiskFreeSpaceEx!=NULL)
    {
     ULARGE_INTEGER i64TotalBytes,i64FreeBytes;
     if(!pGetDiskFreeSpaceEx( GetAscii().c_str(),&i64FreeBytesToCaller,&i64TotalBytes,&i64FreeBytes))
      return 0;
	}
   else
    {
     DWORD nSectors,nBytes,nFreeClusters,nTolalClusters;
     if( !::GetDiskFreeSpaceA(GetAscii().c_str(),&nSectors,&nBytes,&nFreeClusters,&nTolalClusters))
      return 0;
     i64FreeBytesToCaller.QuadPart=nBytes*nSectors*nFreeClusters;
    }

   return i64FreeBytesToCaller.QuadPart;
  }
 #elif defined LEM_DOS
  unsigned char drive[2];
  drive[0]=GetAscii().front();
  drive[1]='\0';
  strupr((char*)drive);
	
  struct dfree df;
  getdfree(drive[0]-'A'+1,&df);
  return df.df_bsec*df.df_sclus*df.df_avail;
 #else
  return 0;
 #endif
}


// ********************************************
// ���������� ����� ��������� ��� �����/�����
// ********************************************
lem::PathAttr lem::Path::GetAttr(void) const
{
 lem::PathAttr attr;

 if( empty() )
  return attr;

 #if defined LEM_WINDOWS

 DWORD res;
 if( lem::System_Config::SupportUnicodeFilenames() )
  {
   res = GetFileAttributesW(GetUnicode().c_str());
  }
 else
  {
   res = GetFileAttributesA(GetAscii().c_str());
  }

 if( res!=(DWORD)-1 ) 
  {
   if( (res&FILE_ATTRIBUTE_HIDDEN)==FILE_ATTRIBUTE_HIDDEN )
    attr.hidden = true;

   if( (res&FILE_ATTRIBUTE_READONLY)==FILE_ATTRIBUTE_READONLY)
    attr.readonly = true;
    
   if( (res&FILE_ATTRIBUTE_SYSTEM)==FILE_ATTRIBUTE_SYSTEM)
    attr.system = true;

   if( (res&FILE_ATTRIBUTE_TEMPORARY)==FILE_ATTRIBUTE_TEMPORARY)
    attr.temp = true;
  }

 return attr;

 #elif defined LEM_UNIX

  if( lem::System_Config::SupportUnicodeFilenames() )
   {
    struct stat stbuf;
    if( stat( lem::to_utf8(GetUnicode()).c_str(), &stbuf) != -1 )
     {
      attr.readonly = (stbuf.st_mode & S_IWRITE) == 0;
      return attr;
     }
   }
  else
   {
    struct stat stbuf;
    if( stat( GetAscii().c_str(), &stbuf) != -1 )
     {
      attr.readonly = (stbuf.st_mode & S_IWRITE) == 0;
      return attr;
     }
   }

  return attr;

 #else

 boost::filesystem::path p( GetAscii().c_str(), boost::filesystem::native );

 try
  {
   if( boost::filesystem::exists(p) )
    {
     // ... ???     
    }
  }
 catch(...)
  {
  }

 return attr;
 #endif
}


lem::Path Path::GetAbsolutePath(void) const
{
 #if defined LEM_WINDOWS
 if( !uname.empty() && lem::System_Config::SupportUnicodeFilenames() )
  {
   wchar_t buf[ lem::Path::MaxLen+1 ];
   *buf=0;
   GetFullPathNameW( uname.c_str(), lem::Path::MaxLen, buf, NULL );
   return lem::Path(buf);
  }
 else
  {
   char buf[ lem::Path::MaxLen+1 ];
   *buf=0;
   GetFullPathNameA( GetAscii().c_str(), lem::Path::MaxLen, buf, NULL );
   return lem::Path(buf);
  }
 #elif defined LEM_UNIX

 if( !uname.empty() )
  {
   // ���� ���������� � '/'?
   if( uname.front()!=GetPathDelimiter() )
    {
     // ��� - ������ ����� ������������� ����.
     char buf[ lem::Path::MaxLen+1 ];
     *buf=0;
     lem::Path full_path( getcwd( buf, lem::Path::MaxLen ) );
     full_path.ConcateLeaf(*this);
     return full_path;
    }
  }
 else
  {
   if( name.front()!=GetPathDelimiter() )
    {
     // ��� - ������ ����� ������������� ����.
     char buf[ lem::Path::MaxLen+1 ];
     *buf=0;
     lem::Path full_path( getcwd( buf, lem::Path::MaxLen ) );
     full_path.ConcateLeaf(*this);
     return full_path;
    }
  }
  
  return lem::Path(*this);

 #else 

  return lem::Path(*this);

 #endif
}


#if defined LEM_WXWIDGETS
lem::Path::operator wxFileName(void) const
{
 #if defined UNICODE
 if( IsFolder() )
  return wxFileName( GetUnicode().c_str(), wxEmptyString );
 else
  return wxFileName( GetUnicode().c_str() );
 #else
 if( IsFolder() )
  return wxFileName( GetAscii().c_str(), wxEmptyString );
 else 
  return wxFileName( GetAscii().c_str() );
 #endif
}
#endif


void lem::swap( lem::Path &x, lem::Path &y )
{
 lem::swap( x.name, y.name );
 lem::swap( x.uname, y.uname );
 return;
}


#if defined LEM_USE_BOOST_FILESYSTEM
lem::Path::operator boost::filesystem::path(void) const
{
 boost::filesystem::path p( GetAscii().c_str(), boost::filesystem::native );
 return p;
}

#ifndef BOOST_FILESYSTEM_NARROW_ONLY
lem::Path::operator boost::filesystem::wpath(void) const
{
 boost::filesystem::wpath p( GetUnicode().c_str(), boost::filesystem::native );
 return p;
}
#endif
#endif



void lem::Path::ChangeExtension( const wchar_t *new_ext )
{
 if( IsUnicode() )
  {
   if( uname.empty() )
    return;

   const int len = uname.length();

   for( int i=len-1; i>=0; i-- )
    if( lem::Path::IsExtDelimiter(uname[i]) )
     {
      // ������� ������ ����������
      i++;
      uname.reduce(i);
      uname += lem::Path::GetExtDelimiter();
      uname += new_ext;
      break;
     } 
    else if( lem::Path::IsDriveDelimiter(uname[i]) || lem::Path::IsPathDelimiter(uname[i]) )
     {
      // No extention found.
      uname += lem::Path::GetExtDelimiter();
      uname += new_ext;
      break; 
     }  
  } 
 else
  {
   lem::FString as = to_ascii(new_ext);

   if( name.empty() )
    return;

   const int len = name.length();

   for( int i=len-1; i>=0; i-- )
    if( lem::Path::IsExtDelimiter(name[i]) )
     {
      // ������� ������ ����������
      i++;
      name.reduce(i);
      name += (char)lem::Path::GetExtDelimiter();
      name += as;
      break;
     } 
    else if( lem::Path::IsDriveDelimiter(name[i]) || lem::Path::IsPathDelimiter(name[i]) )
     {
      // No extention found.
      name += (char)lem::Path::GetExtDelimiter();
      name += as;
      break; 
     }  
  } 

 return;
}







// ********************************************************
// ���������� ���������� � ����� ����� filename (��� �����)
// ���������� ������������ ����� ext, ������������
// �� �����������.
// ********************************************************
static void get_ext( const char *filename, char *ext )
{
 ext[0]='\0';

 if( filename==NULL )
  return;

 int len = strlen(filename);
 for( int i=len-1; i>=0; i-- )
  if( filename[i]==lem::Path::GetExtDelimiter() )
   {
    // Ext beginning has been found.
    i++;
    size_t j=0;
    while( filename[i]!='\0' )
     ext[j++]=filename[i++];

    ext[j]='\0';
    break;
   }
  else if( lem::Path::IsDriveDelimiter(filename[i]) || lem::Path::IsPathDelimiter(filename[i]) )
   // No extention found.
   break;

 return;
}


const FString lem::Path::GetExtension( const char *filename )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(filename) );
 char ext[LEM_MAX_PATH+1];
 get_ext(filename,ext);
 return FString(ext);
}


const wstring lem::Path::GetExtension( const wstring &filename )
{
 wstring ext;

 if( filename.empty() )
  return ext;

 int len = filename.length();

 for( int i=len-1; i>=0; i-- )
  if( filename[i]==lem::Path::GetExtDelimiter() )
   {
    // ������� ������ ����������
    i++;
    while( i<len )
     ext += filename[i++];

    break;
   }
  else if( lem::Path::IsDriveDelimiter(filename[i]) || lem::Path::IsPathDelimiter(filename[i]) )
   // No extention found.
   break;

 return ext;
}



const UFString lem::Path::GetExtension( const UFString &path )
{
 UFString ext;

 if( path.empty() )
  return ext;

 const int len = path.length();

 // ���� ������-����������� ���������� - � ������� �����.
 // ��� ��� ��� ��������� Windows ���������� � ����������� ������� �����
 // ����� 3 �������, �� ����� ����� ����������� �����.
 if( len>4 )
  {
   if(
      lem::Path::IsExtDelimiter(path[len-4]) &&
      !lem::Path::IsExtDelimiter(path[len-2]) &&
      !lem::Path::IsPathDelimiter(path[len-2])
     )
    {
     return lem::right(path,3);
    }    
  }

 // ����� ������ - ��� ���������� ������ �����
 for( int i=len-1; i>=0; i-- )
  {
   if( lem::Path::IsExtDelimiter( path[i] ) )
    {
     // ������� ������ ����������
     i++;
     while( i<path.length() )
      ext += path[i++];
   
     break;
    }
   else if( lem::Path::IsDriveDelimiter(path[i]) || lem::Path::IsPathDelimiter(path[i]) )
    // No extention found.
    break;
  }

 return ext;
}




const lem::UFString lem::Path::GetExtension( const wchar_t *filename )
{
 UFString ext;

 if( lem::lem_is_empty(filename) )
  return ext;

 int len = lem_strlen(filename);

 for( int i=len-1; i>=0; i-- )
  if( filename[i]==lem::Path::GetExtDelimiter() )
   {
    // ������� ������ ����������
    i++;
    while( i<len )
     ext += filename[i++];

    break;
   }
  else if( lem::Path::IsDriveDelimiter(filename[i]) || lem::Path::IsPathDelimiter(filename[i]) )
   // No extention found.
   break;

 return ext;
}



// *******************************************************
// ������ true ���� ���� � �������� ������ ����������.
// *******************************************************
bool lem::Path::DoesExist( const char *filename )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(filename) );
 if( !(filename) || *filename==0 )
  // No file name given.
  return false;


 #if defined LEM_WINDOWS

 return GetFileAttributesA( filename )!=((DWORD)-1);//INVALID_FILE_ATTRIBUTES;

 #elif defined LEM_DOS

  #if defined LEM_MSC
   return _access( filename, 0 )==0;
  #elif defined LEM_GNUC
   struct stat stbuf;
   return ( stat(filename, &stbuf) != -1) ? true : false;
  #else
   return access( filename, 0 )==0;
  #endif

 #elif defined LEM_UNIX

 struct stat stbuf;
 return ( stat(filename, &stbuf) != -1) ? true : false;

 #else

 // ������, �� ������������� ������ - �������� ������� ���� �� ������, � ����
 // ��� �������, �� ������ ���� ����������. ������� ��������, ��� ���� � ��������
 // ��� ���� �� �������� �����, �� ��������� ����� �������.
 FILE *f = ::fopen( filename, "rb" );
 lem_fclose(f);
 return f!=NULL;

 #endif
}


/*************************************************************************
 Does given file exist? ������� ��������, ��� ������������ �����������
 ������� access(...), ���� ��������. �� ��� ������� ����������� � ANSI C
 ���������. ��� UNIX ������������ ������� stat - ��� �� ������, ��� �
 access ��� MSDOS. ������������� ����������� ������ - ����� ��������
 ����� �� ������ - ����� �������� �������. ��������, ���� �����������
 ������� �� ������ ������� ��� ���� ����, ��� ���� ���� is locked.
**************************************************************************/
bool lem::Path::DoesExist( const wchar_t *filename )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(filename) );
 if( !(filename) || *filename==0 )
  // No file name given.
  return false;

 #if defined LEM_WINDOWS

 return GetFileAttributesW( filename )!=((DWORD)-1);//INVALID_FILE_ATTRIBUTES;

 #elif defined LEM_DOS

  const int len = lem_strlen(filename);
  char *ascii_filename = new char[len+1];
  lem_unicode_to_ascii( ascii_filename, filename );

  #if defined LEM_MSC

  const bool res = _access( ascii_filename, 0 )==0;

  #elif defined LEM_GNUC

  struct stat stbuf;
  const bool res = ( stat(ascii_filename, &stbuf) != -1) ? true : false;

  #else
  const bool res = access( ascii_filename, 0 )==0;
  #endif

  delete[] ascii_filename;
  return res;

 #elif defined LEM_UNIX

  const int len = lem_strlen(filename);
  char *ascii_filename = new char[len+1];
  lem_unicode_to_ascii( ascii_filename, filename );

  struct stat stbuf;
  const bool res = ( stat(ascii_filename, &stbuf) != -1) ? true : false;
  delete[] ascii_filename;
  return res;

 #else

  FILE *f = lem_fopen( filename, "rb" );
  lem_fclose(f);
  return f!=NULL; 

 #endif
}


/* Rename a file */
bool lem::Path::RenameFile( const char *srcFile, const char *destFile )
{
 #if defined LEM_UNIX
 if( link( srcFile, destFile ) != 0 )
  return 0;

 return unlink( srcFile )==0;
 #else
 return /*std*/::rename( srcFile, destFile )==0;
 #endif
}


/*********************************************************************
 ���� � ������ oldname ����������������� ��� newname. ������
 ��������� ����� ����������� ���� � ������ �������!
**********************************************************************/
bool lem::Path::RenameFile( const wchar_t *oldname, const wchar_t *newname )
{
 if( !(oldname) || !(newname) )
  return false;

 #if defined LEM_USE_WCHAR
  const int res = _wrename( oldname, newname );
 #else
  const int old_len = lem_strlen(oldname);
  char *old_ascii_name = new char[old_len+1];
  lem_unicode_to_ascii( old_ascii_name, oldname );

  const int new_len = lem_strlen(newname);
  char *new_ascii_name = new char[new_len+1];
  lem_unicode_to_ascii( new_ascii_name, newname );

  const int res = /*std::*/rename( old_ascii_name, new_ascii_name );

  delete[] new_ascii_name;
  delete[] old_ascii_name;
 #endif

 return res==0; // 0 is OK, ��� � ������ � ���������� ����...
}



/************************************************************************
 ����������� ������� �����, ��������� ������. ������������� ��������, ���
 ��� ���������� ��������� ����, ���������� ��������� � �����, ���������
 ����. ������������ ������ �����, ������ ���� ���� �� ����������,
 �� ���������� 0. ���� ���������� ���������� ������ ��������� � ������
 ������ �����, �� ��������� ����� ������������� (������ ����� 0).
*************************************************************************/
size_t lem::Path::FileSize( const char *name )
{
 if( !name )
  return 0;

 #if defined LEM_WINDOWS

  WIN32_FILE_ATTRIBUTE_DATA data;
  if( GetFileAttributesExA( name, GetFileExInfoStandard, &data )==TRUE )
   return data.nFileSizeLow;

  return 0;

 #elif defined LEM_UNIX

  struct stat st;
  if( stat( name, &st )==0 )
   return st.st_size;

  return 0;

 #else

  // ������������� ������, ���������� �������.
  FILE *file = ::fopen( name, "rb" );

  if(!file)
   // Failed to open file - return zero as if it was OK.
   return 0;

  fseek( file, 0, SEEK_END );
  const long eof_ftell = ftell(file);
  fclose(file);

  return eof_ftell;
 #endif
}



size_t lem::Path::FileSize( const wchar_t *name )
{
 if( name )
  return 0;

 #if defined LEM_WINDOWS

  WIN32_FILE_ATTRIBUTE_DATA data;
  if( GetFileAttributesExW( name, GetFileExInfoStandard, &data )==TRUE )
   return data.nFileSizeLow;

  return 0;

 #elif defined LEM_UNIX

  FString aname;
  if( lem::System_Config::SupportUnicodeFilenames() )
   aname = lem::to_utf8(name);
  else
   aname = lem::to_ascii(name);

//  return lem::get_file_size(aname.c_str());
 FILE *f = ::fopen( aname.c_str(), "rb" );
 size_t r = f==NULL ? 0 : get_file_size(f);
 if(f!=NULL) fclose(f);
 return r;

 #else

  FILE *file = _wfopen( name, L"rb" );

  if( !file )
   // Failed to open file - return zero as if it was OK.
   return 0;

  fseek( file, 0, SEEK_END );
  const long eof_ftell = ftell(file);
  fclose(file);

  return eof_ftell;

 #endif
}

