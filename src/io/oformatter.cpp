// -----------------------------------------------------------------------------
// File OFORMATTER.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ��������� - ����� ��� ���������� ������ ���������� - ������������ ����������
// ������������ ������������ PRINTF. ������������� �������� ��� ��� ������
// ���������� � ����� ���������� IOStreams C++.
//
// ��������� ������������ �������������� (������ ���������� �������) ������
// ����� ������� � ������������ ����� (������������ ������ �������, �����������
// �� Stream, ������� ����� ������ ���� � pipe �� ��������� ���������).
//
// ��� ������ ��������, ��� ������ �������������� ������, ������������
// ���������� ������� printf, ����� ������ ��� �������� ������, �������� -
// ����������� ��������� ��������. ������� � ����������� �������� �����������
// printf'�, ���� �� ��������� ���������� - ���������� ��� �������� �����
// ������� - ����������, �������, �� �������.
//
// 30.05.2006 - ������� ���������� ������ ������� '\b'
// 14.05.2008 - ������� ������ cprintf(...), �������������� �������� ���������
//              ������� printf.
// 17.06.2008 - ��� ������������� � CRT printf ������ ������ %ls, �������������
//              %us, ��� ������ UNICODE �����.
// 27.05.2010 - �������� ��������� utf16 U16Formatter
// -----------------------------------------------------------------------------
//
// CD->29.01.1996
// LC->11.08.2014
// --------------

#include <cstdarg>
#include <cctype>

#undef printf

#include <lem/math/real_functions.h>
#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/char_buffer.h>
#include <lem/oformatter.h>


using namespace std;
using namespace lem;
//using namespace lem::Math;
using namespace lem::Char_Stream;

/**************************************************************************************

   ����� OFormatter ������������ ��� ������ ������������ ������ ����������
 ������ ���������� � ��������� ������ (�������� � �����) �� C, �� ����
 �������� ...printf. ������������� ����� ������ ����������� ������������
 ����������� ������������ ������ ����� ������ � ���������� INDEPENDENCE,
 � ���������, ������������ ����� String, FString, INT64, REAL18 � ������.
 ����������� ��������� ����������� �������������� ��������� �����. �������������
 �������������� ��������� �� ������� ��� REAL, ��� ��� � ���������� ���
 ���������� ���������� ������������ %e �� %le � ��� �����, ����������
 �������� %re (��������� ��. �����). ��������� C-�������� printf ��� ����������
 ������ � ���������� ������ ���������� � ����� �������. ���� �� ���������
 ���������� ������ ������� ������ ������ - ������������ ������������ �������
 ������ ������� ������� ��������������, ������� �� ����������� ��������� ��
 ������ �������� ����������� ��������� �����, �� � �������� ����������� �����
 ��������������, ��������, ������������ �� ������� ���� � ��� �����.

   ������� ��������, ��� ��� ����� ������������ ������������ �� ...printf
 ��������, � ���������, %x. �����, ������ %e, %le, %f, %lf, %g, %lg �����������
 ������ ����� ��������������, ����� ��������������� ��� ����� ����������, ���
 ����� �������� ������������ � %e, %f, %g.

   ��� ��������� �������� ������������� �������������� %%, %c, %s, %d, %ld.
 �������, ����������� ��������� ����������� ������ (��������������) �����
 �����.

   ��� ��� ����� ������ ������������ � '����������� ����' Stream, �� ��
 ���������� ����� ����������� ����������� ������ ������ - ���������� ��������
 �����-������� Stream � ����������� � ��� ����� ������� (� �������������
 ����� ����������� � "lem_bstr.h").

   ������, � ����� ���������� ������������ OFormatter �������������� ��������
 ���������� �������� ���������� ����� ����. ���������� ������ ������� - ���������
 ���������� ������������ �� ������ ����� ����� ������. ������� ����� OFormatter
 ��������� � ������ ������, � ������ ���, ��� �������� � ���������� IOStream �����
 C++. �� ����, �� �������������� ��������� << ��� ���� ������� �����������
 ����� ����������, � ���������� ����������� ����� �������� ����������� �����
 �������������� ������� OFormatter& operator<<(...) ��� ����� �����. ������
 ���������� ��������, ��� ���������� �������� �������������� ��� ������ �������
 ������������ �� ����� ������, ��� ��� ������ ����� ����� OFormatter::printf.
 ������, ����� ���������� �������� ���������� ����� ����� OFormatter::printf �
 operator<<, ��� �����-���� ������������� ������� (��� ���������� � IOStream C++).

   ����� ��������� ��������� ������������� OFormatter ������ ������������
 printf, ��� ������ �� �������� � ���������� ������� �������� ������ mout. �
 ����������, ������ ����

              printf( "Hello, world!\n" );

 ������ ���� �������� ��

              mout.printf( "Hello, world!\n" );


 ����� �������� ������ merr ��� ������ ��������� �� ������� (�����������
 ����� stderr).

 ��� ������ ���������������� ������ � ������� �������� ���� ���������� ��������
 ����� �����:

             OFormatter mfile( "filename.txt" );
             mfile.printf( "Hello, disk file!\n" );


 ��� ������������ ������� LEM_NOREAL ����������� (���������� �����������������)
 ��� ������������, ������������� ���� REAL/REAL4/... (����������� - � ������
 "lem_real.h").


                         --------------

       �������� �������� ���������� ������ � ��������� ������.


                        ���� ������������:

  %XYYY.ZZZZ
   | |   |
   | |   +------ ����� ���� �������� ����� ���.�����, ��������� � �����.
   | +---------- ����� ����� ����.
   |
   +------------ ���� ��� �������� ������� �������� ����� �����.
                 X = '+' - ���������� '+' ��� '-' ��������������.
                 X = ' ' - ���������� ' ', ���� �����>0, ����� ���������� '-'

                 �� ��������� ���������� ������ '-', ����� ����� <0.

  %...Xn...    - ��������� ������� ��������� ����� ����� 'n' ��� ����. ����.

  %...Wn...    - ����� ��������� ����� ����� n.

  %...An...    - ��������������� ��� ������������ ��� ���� � ���������.

                 Al - ������������ � ������ ����.

                 Ac - �������������.

                 Ar - ������������ � ������� ����.

  %...Ln...    - �������������� ��������.

                 Lc - ��� � �������.

                 Ls - ��� � �����.

  %...Knnn...  - ��������� ��������, ������� ����� �������� �� ����� (������
                 ����� ������������ s), ����� � ��������� nnn (�������� 1251 -
                 ��������� MS Windows). ����� ���������� ������ �����
                 ������������� �������������� � 866 ��������� MSDOS.

  %...in...    - �������������� ���������� ������������� ���� ��������
                 ������ n ���, � ����� ���������� ��������� ������������ ������
                 ���� ���.

  %...Fnm...   - ����������� ���� ���������� ������ ���� � ������������ 'n'
                 ��������������� � ��������� 'm'. �������� ������ � �� ���������
                 ������������ ��������� ��� ������ �����. ������ ���������� �,
                 ������������ ���������, ���� ���������� ����������� ��� ������
                 ���� ��������� ����� �� ���� �������, ����� ������ ������� %Fnm
                 ������� ��� ��������.

  %...^n...    - ����� ��������� ��� ������� ����� � ��������� ������.


  %...n...     - ��� ���������� ����� ( double, INT16 ).

  %...l...     - ��� � ���������� 'long' ( long int, long double )

  %...u...     - ��� � ���������� 'unsigned' ( unsigned int, unsigned long )

  %...q...     - ��� � ���������� 'quatro' ( int64, REAL18 )


  %v           - ��������� ������ ������ �������� ��� ������������� (������ MSDOS).

     %vl - LOWVIDEO
     %vh - HIGHVIDEO
     %vn - NORMALVIDEO
     %vx - ����� ������ BLINK/�� BLINK
     %vb# - ����� ���� ���� ('#' == 0,...,9,A,...F )
     %vf# - ����� ���� ��������

            #    ����

            0    BLACK
            1    BLUE
            2    GREEN
            3    CYAN
            4    RED
            5    MAGENTA
            6    BROWN
            7    LIGHTGRAY
            8    DARKGRAY
            9    LIGHTBLUE
            A    LIGHTGREEN
            B    LIGHTCYAN
            C    LIGHTRED
            D    LIGHTMAGENTA
            E    YELLOW
            F    WHITE


                     ������������� �����.


   d,D - ������������� ��� int, unsigned int, long, unsigned long.
       ����� D ��������, ��� ����� ���� ����� ������� �����, �����
       ��������� ���������� ����� ������� ����.

   s - ��������� C-������.
   us - ��������� UNICODE-������

   re, rg, rf - ������� ��� REAL.
   e, g, f    -

   Re, Rf, Rg - ������� REAL � ������� ���� �������� ����.

   rre,rrg,rrf,Rre,Rrg,Rrf - ������������� ��� REAL4...REAL18
   rce, rcf, rcg - ���� LemComplex.
   Rce, Rcg, Rcf - ���� ���� LemComplex � ������� ��������� ������.

   Rde, Rdf, Rdg, rde, rdf, rdg - ���� DUPEL.

   hc - ������ ������ �������� 'c'. ����� ������������������ �����
        ������������� ����� ����.

   Hc - ������ ������ �������� 'c', ����� ������ ������� �� �����.

   x  - ������ ������������������ �� �������, ������� ����������� �� �����.

   c - ������ ���������� �������.
   uc - ������ ���������� UNICODE-�������.

   b - ���������� bool.

   t - ��������� �� ������� field_len �� ������ ������� ������.

   T - ��������� �� �������, ��������� �� �����.

   Yc - ����� �������� 'c' �� ������� ������� �� field_len.

   M, m - ��������� ������������ ������ �����:

        Ml, ml - ��������� ���� �����, ����� �������� ������� �� ����� (M) ��� �� ��������� ������ (m)
        Mw, mw - ������ ��������, ������ � ����� ����, ����� ��������� ������� �� ����� (M) ��� �� ��������� ������ (m)
        Mn, mn - ������� � ���������� �� ���������


   *:lang(�����[,�����]) - ����� �����, �������������� � �������� ���������� ����
                         int, ��� ���������� ������. ������������ �������
                         ����� lang. ���������� �������� lang: 'ru' � 'en' ���
                         �������. ������: %*:en(file) ��� %*:ru(����,��)

                         �� ��������� - ������������ �����.


               �������� ����������� ������ ...Fnm...


  1. ��� ����������� �������������.

  Fz1  - ���� ������ ���� ������, ��� ���������� �������� ����, �� �����
         ������������ ����. ������� �������, ��� �� ���������, ���� ��
         ���������� ������������ ...k[.l]..., �� ����� ���� ����������
         ������������ ��� ���� [unsigned][long]int, ����� ����������
         ����� MAXINT, UINT_MAX � ��� �����. ���� ������������ ...k[.l]...
         ���� ������ ���� ������, ��� ���������� ���������, �� ���� Fz1
         �����������.


  2. ��� �����������.

  Ff0 - ����� � ���� '{re,im}' (����� �� ���������).
  Ff1 - ����� � ���� '(re,im)'
  Ff2 - ����� � ���� 're im'
  Ff3 - ����� � ���� 're=x im=y'


  3. ��� bool.

  Ff0 - 'true'/'false' (����� �� ���������)
  Ff1 - '.TRUE.'/'.FALSE.' (��� ������������� ��������)
  Ff2 - '1'/'0'

  4. ��� ���� DUPELxxx

  Ff1 - ����� � ���� { ������� +/- ���������� }

  5. ������.

  F$3 - ������ ������ �������� ���� � ����������� ������� �� 3 ����� ������.
  F$4 - ���������� �����������, �� � ����������� ��������

****************************************************************************/

/*********************************************************
 ����� ����� ������������ ����� ��� �� ����� � ������,
 ����� ��������� ��������� ���������� � ������ ������� ��
 ������ ������ ::printf().
**********************************************************/
OFormatter::OFormatter(void)
{
 CONTROLFLAG        = 0x00000000L;
 stream             = NULL;
 doubler            = NULL;
 can_i_close        = false;
 npos               = 0;
 left_margin        = 0;
 page_width         = 0;

 ClearFlags();

 return;
}


OFormatter::OFormatter( FILE *file )
{
 doubler            = NULL;

 ClearFlags();

 CONTROLFLAG        = 0x00000000L;
 npos               = 0;
 left_margin        = 0;
 page_width         = 0;

 Init(file);

 return;
}

/***************************************************************
 ��������� ����� ������ � ��������� ���� (����� ������). ������
 ����� ������� ������� �� ��.
****************************************************************/
OFormatter::OFormatter( const lem::Path& filename )
{
 doubler            = NULL;
 stream             = NULL;
 can_i_close        = false;

 ClearFlags();

 CONTROLFLAG        =
 npos               =
 left_margin        =
 page_width         = 0;

 Open(filename,false);

 can_i_close        = true;

 return;
}

/********************************************************************
 �������� ������ ������ ��� ������������ �����, ������� ��� ������ �
 ����� ����� ���-�� �� ������� ����.
*********************************************************************/
OFormatter::OFormatter( Stream *file, bool CanClose )
{
 doubler            = NULL;

 CONTROLFLAG        =
 npos               =
 left_margin        =
 page_width         = 0;

 ClearFlags();

 stream = file;
 can_i_close = CanClose;

 return;
}

void OFormatter::Open( FILE *file )
{
 Delete();
 Init(file);
 return;
}


// ***************************************************
// ��������� ���� � ������ filename. ��������� �����
// ������ � ��������� ���� (����� TextFile).
// ***************************************************
void OFormatter::Open( const Path& filename, bool write_bom )
{
 // ��� ��� ���� ��������� �������� � ASCII �������� ������, �� write_bom 
 // ������ ���� false.
 LEM_CHECKIT_Z(write_bom==false);

 Delete();

 stream = new TextFile(filename,false,true);

 can_i_close = true;
 left_margin=page_width=npos=0;
 return;
}


void OFormatter::Open( Stream *file, bool CanClose )
{
 Delete();
 stream      = file;
 can_i_close = CanClose;
 return;
}


void OFormatter::ClearFlags(void)
{
 total_len   =
 after       =
 exp_len     =
 field_len   =
 after       =
 caps        = -1;

 aligment    =
 sign_out    =
 nflag       = 0;

 // ��������� ������� ��������� �� ���������
 radix       = 10;

 nrepeate    = 1;

 is_normal   =
 is_unsigned =
 is_long     =
 is_quatro   =
 is_complex  = false;

 autoflush   = false;

// local_cp    = cp1251;
 local_cp    = &lem::UI::get_UI().GetSessionCp();
 out_cp      = &lem::UI::get_UI().GetSessionCp();

 return;
}


void OFormatter::Init( FILE *file )
{
 npos=0;

 if( file )
  {
   if( can_i_close )
    delete stream;

   stream = new BinaryFile(file);
   can_i_close = true;
  }

 left_margin=page_width=0;
 can_i_close = false;

 return;
}



void OFormatter::Init( const OFormatter &ms )
{
 can_i_close = ms.can_i_close;

 // �������� �� �������� ���� �������������� �����,
 // ������� �� ����� ������������� �������������
 // �����.
 LEM_CHECKIT_Z( !can_i_close );

 stream      = ms.stream;
 doubler     = ms.doubler;

 CONTROLFLAG = ms.CONTROLFLAG;
 left_margin = ms.left_margin;
 page_width  = ms.page_width;
 npos        = ms.npos;
 out_cp      = ms.out_cp;

 return;
}

void OFormatter::Delete(void)
{
 if( can_i_close && stream )
  {
   stream->close();
   delete stream;
  }

 stream  = NULL;
 doubler = NULL;
 return;
}


OFormatter::~OFormatter(void)
{
 Delete();
 return;
}

void OFormatter::operator=( FILE *file )
{
 Delete();
 Init(file);
 return;
}

void OFormatter::operator=( const OFormatter &ms )
{
 Delete();
 Init(ms);
 return;
}

// *******************************************************
// ����� ��� ������ ������������ ������������� ...PRINTF
// *******************************************************
void OFormatter::printf( const char *format, ... )
{
 #if defined LEM_THREADS
  // ��������� ��������� ��������� � �����, ��� ��� ��� ������
  // ���������������.
  lock_mstr.Enter();
 #endif

 LEM_CHECKIT_Z( !!(stream) );
 if( !stream )
  return;

 va_list ap;
 va_start( ap, format );

 int i=0;
 char ch;

 while( (ch=format[i++]) )
  {
   if( ch=='%' )
    {
     read_field_spec(format,i);
     ch=format[i++];

     switch(ch)
      {
       case 'v':
        {
         // ����������� ���������� ������������ ��� ������ �� �������.
         VideoControl( format, i );
         break;
        }

       case 's':
        {
         // C-������
         if( is_unsigned || is_long )
          {
           const wchar_t *val = va_arg(ap,const wchar_t*);
           Print_C_String(val);
          }
         else
          {
           const char *val = va_arg(ap,const char*);
           Print_C_String(val);
          }

         break;
        }

       case 'h':
       case 'H':
        {
         LEM_CHECKIT_Z(after<1);
         LEM_CHECKIT_Z(radix==10);

         if( ch=='H' )
          field_len = va_arg(ap,int);

         char filler = format[i++];

         do
          for( int i=0; i<field_len; i++ )
           printf( filler );
         while( --nrepeate>0 );

         break;
        }

       case 'Y':
        {
         char filler = format[i++];
         Print_Tab(field_len,filler);
         break;
        }

/*
       case 'x':
        {
         LEM_CHECKIT_Z(after<1);
         LEM_CHECKIT_Z(radix==10);

//         char filler = va_arg(ap,char);
         char filler = va_arg(ap,int);

         do
          for( int i=0; i<field_len; i++ )
           printf( filler );
         while( --nrepeate>0 );

         break;
        }
*/

       case 'c':
        {
         if( is_unsigned )
          {
           wchar_t buffer[2];

//           buffer[0]=va_arg(ap,wchar_t); buffer[1]=0;
           buffer[0]=va_arg(ap,int); buffer[1]=0;
           Print_C_String(buffer);
          }
         else
          {
           char buffer[2];
//           buffer[0]=va_arg(ap,char); buffer[1]=0;
           buffer[0]=va_arg(ap,int); buffer[1]=0;
           Print_C_String(buffer);
          }

         break;
        }

       case 'b':
        {
//         bool b = va_arg(ap,bool);
         bool b = !!va_arg(ap,int);
         Print_Boolean(b);
         break;
        }

       case '%':
        {
         printf( '%' );
         break;
        }

       case 't':
        {
         Print_Tab();
         break;
        }

       case 'T':
        {
         int to = va_arg(ap,int);
         Print_Tab(to);
         break;
        }

       case 'k':
        {
         // ����� ������� �������� ��� ������.
         out_cp = CodeConverter::getConverter( read_digits(format,i) );
         break;
        }

       case 'M':
        {
         char m = format[i++];
         switch(m)
          {
           case 'n':
            left_margin=page_width=0;
            break;

           case 'l':
            {
             left_margin = va_arg(ap,int);
             break;
            }

           case 'w':
            {
             page_width = va_arg(ap,int);
             break;
            }

           default:
            LEM_STOPIT;
          }

         break;
        }

       case 'm':
        {
         char m = format[i++];

         switch(m)
          {
           case 'n':
            left_margin=page_width=0;
            break;

           case 'l':
            {
             left_margin = read_digits(format,i);
             break;
            }

           case 'w':
            {
             page_width = read_digits(format,i);
             break;
            }

           default:
            LEM_STOPIT;
          }

         break;
        }

       case 'p':
       {
        // ���������.
        char p_str[ 20 ];
        const void * ptr = va_arg(ap,const void*);
        sprintf( p_str, "%p", ptr );
        Print_C_String( p_str );
        break;
       }

       case 'x':
       {
        char p_str[ 20 ];
        const void * ptr = va_arg(ap,const void*);
        sprintf( p_str, "%x", ptr );
        Print_C_String( p_str );
        break;
       }

       case 'd':
       case 'D':
        {
         // *********************************************
         // *             ���� ���� int.                *
         // *********************************************

         LEM_CHECKIT_Z(after==-1);
         is_complete=ch=='D';

         if( is_normal )
          {
           if( is_unsigned )
            {
             unsigned int val = va_arg(ap,int);
             Print_UINT(val);
            }
           else
            {
             int val = va_arg(ap,int);
             Print_INT(val);
            }

           break;
          }

         if( !is_long && !is_quatro )
          {
           if( is_unsigned )
            {
             unsigned int val = va_arg(ap,unsigned int);
             Print_UINT(val);
            }
           else
            {
             int val = va_arg(ap,int);
             Print_INT(val);
            }

           break;
          }

         if( is_long )
          {
           if( is_unsigned )
            {
             lem::uint32_t val = va_arg(ap,lem::uint32_t);
             Print_UINT32(val);
            }
           else
            {
             lem::int32_t val = va_arg(ap,lem::int32_t);
             Print_INT32(val);
            }

           break;
          }

         if( is_quatro )
          {
           if( is_unsigned )
            {
             #if defined LEM_UI64
              lem::uint64_t val = va_arg(ap,lem::uint64_t);
              Print_UINT64(val);
             #else
              LEM_STOPIT; // ��� uinteger64 �� ���������!
             #endif
            }
           else
            {
             #if defined LEM_I64
              lem::int64_t val = va_arg(ap,lem::int64_t);
              Print_INT64(val);
             #else
              LEM_STOPIT; // ��� integer64 �� ���������!
             #endif
            }
          }

         break;
        } // end case INT


       // ***************************************************************
       #if !defined(LEM_NOREAL)
       case 'r':
       case 'R':
       case 'e':
       case 'f':
       case 'g':
        {
         char FORMAT[80];
         MakeRealFormat( format, i, FORMAT );

         // ���� ���� REAL.
         if(is_complex)
          {
           // ����������� ��������.
//           LemComplex cx = va_arg(ap,LemComplex);
//           Print_Complex( FORMAT, cx );
           break;
          }

         #if !defined LEM_NODUP
         if(is_dupel)
          {
           char BUFFER[256];
           if( is_normal )
            {
             DUPEL8 cx = va_arg(ap,DUPEL8);
             Print_Dupel( BUFFER, FORMAT, cx );
            }

           if( is_long )
            {
             DUPEL10 cx = va_arg(ap,DUPEL10);
             Print_Dupel( BUFFER, FORMAT, cx );
            }
/*
           #if (defined(SETREAL18) || defined(DEFREAL18))
           if( is_quatro )
            {
             DUPEL18 val = va_arg(ap,DUPEL18);
             Print_Dupel( BUFFER, FORMAT, val );
            }
           #endif
*/
           print_field(BUFFER);

           break;
          }
         #endif

         if( is_normal )
          {
           double val = va_arg(ap,double);
           Print_Real8( FORMAT, val );
           break;
          }

         if( is_long )
          {
           long double val = va_arg(ap,long double);
           Print_Real10( FORMAT, val );
           break;
          }

         #if (defined(SETREAL18) || defined(DEFREAL18) )
         if( is_quatro )
          {
           REAL18 val = va_arg(ap,REAL18);
           Print_Real18( FORMAT, val );
           break;
          }
         #endif

         break;
        } // end case REAL
       #endif

       default:
        {
         char b[48];
         sprintf( b, "Invalid specification [%c]\n", ch );
         throw E_BaseException( wstring( UFString(b).c_str() ) );
        }
      } // end switch(ch)

    } // end if ch=='%'
   else
    printf(ch,true);

  } // end while

 va_end(ap);

 if( autoflush )
  stream->flush();

 End_Of_Printf();

 #if defined LEM_THREADS
  lock_mstr.Leave();
 #endif

 return;
}

/****************************************************************************
  ����� ���������� ������� � �����. ���� ��� �������� ����� ������ � ������
  ������ (��������� doubler), �� ����� ������� ������ � ����. ����� ������
  ���������� �������� ��������� ������� ����������� ������� ������� �������,
  ����� � ������� ���������� ���������� ������������ ���������� ���� � ������
  ������, ������� � �������.
****************************************************************************/
void OFormatter::printf( char CH, bool do_recode )
{
 LEM_CHECKIT_Z( !!(stream) );
 if( !(stream) ) return;

 if( !!(doubler) )
  doubler->printf(CH);

 if( CH == 7 )
  return;

 // ������������� ��� �������� ����������� ������
 #if defined LEM_UNIX
 char ch = CH;
 #else
 char ch = do_recode ? 
  recode_char( CH, local_cp->get_Index(), out_cp->get_Index() )
  :
  CH;
 #endif 

 if( GetControlFlag(LEM_MSTREAM_HTML) && ch=='\n' )
  // ����� � ������� HTML ������� �������� ������ <BR> � ����� ������.
  stream->puts( "<BR>" );
 else if( ch=='\t' )
  {
   after=0;

   if( GetControlFlag(LEM_MSTREAM_RAWTAB) )
    stream->put('\t');
   else
    Print_Tab( (npos/8+1)*8, ' ' );

   return;
  }
 else if( ch=='\n' && stream->IsBinary() )
  stream->put('\r'); 

 stream->put(ch);

 npos = ch=='\n' ? 0 : npos+1;
 if( npos==0 && left_margin )
  for( int i=left_margin-1; i>=0; i-- )
   printf(' ');

 if( page_width && npos==page_width )
  printf( '\n' );

 return;
}

void OFormatter::put_direct( char ch )
{
 LEM_CHECKIT_Z( !!(stream) );
 if( !(stream) ) return;

 if( !!(doubler) )
  doubler->put_direct(ch);

 stream->put(ch);
 return;
}


char OFormatter::get_flag_state( int fi )
{
 for( int i=0; i<nflag; i++ )
  if( flag_index[i]==fi )
   return flag_state[i];

 return 0;
}

// *************************************************************************
// ��������� ������ ��������� ����� (�� ������ � ������� SetControlFlag(...)
//
//   fi - ��� ����� (������)
//   state - ��������� ����� (������)
// *************************************************************************
void OFormatter::set_flag_state( int fi, int state )
{
 for( int i=0; i<nflag; i++ )
  if( flag_index[i]==fi )
   {
    flag_state[i]=char(state);
    break;
   }

 return;
}

int OFormatter::read_digits( const char* format, int& i )
{
 char buffer[16];
 int ii=0;

 while( is_digit( format[i] ) )
  {
   LEM_CHECKIT_Z( ii<(int)DIM_A(buffer) );
   buffer[ii++]=format[i++];
  }

 buffer[ii]='\0';
 LEM_CHECKIT_Z( (buffer[0]) );

 int d;
 to_int(buffer,&d);
 return d;
}

/******************************************************************
  ����� ��������� ����� ���������� ������ ������������.

   format - ��������� �� ������ ��������� ������
   i      - ������ ���������� � ��������� ������
*******************************************************************/
void OFormatter::read_field_spec( const char *format, int &i )
{
 total_len   =
 after       = -1;
 exp_len     = -1;
 field_len   = -1;
 after       = -1;
 aligment    = 0;
 sign_out    = 0;
 nflag       = 0;
 nrepeate    = 1;
 radix       = 10;
 caps        = -1;

 is_normal   =
 is_unsigned =
 is_long     =
 is_quatro   =
 is_complex  = false;

// local_cp    = 866;

 char ch=format[i];

 if( ch==' ' || ch=='+' )
  {
   // ����������� ������ �����.
   switch(ch)
    {
     case ' ': sign_out=1; break;
     case '+': sign_out=2; break;
    }

   i++;
  }

 if( is_digit(format[i]) )
  field_len = read_digits(format,i);

 // ���� ����� �������� ������������ ������� ����, ��
 // ������� ����� ������ �����.
 if( format[i]=='.' )
  {
   i++;

   // ����� ��������� �����.
   after = read_digits(format,i);
  }


 bool cont=true;
 while(cont)
  {
   switch(format[i++])
    {
     case 'A':
      {
       // ������������ ���� ������������ ����.
       char align_type = (char)to_lower(format[i++]);
       LEM_CHECKIT_Z( align_type=='l' || align_type=='c' || align_type=='r' );

       switch(align_type)
        {
         case 'l': aligment=0; break;
         case 'c': aligment=1; break;
         case 'r': aligment=2; break;
        }

        break;
       }


     case 'X':
      {
       // ������������ ��������� ������� ��������� ��� ������ �����.
       radix = read_digits(format,i);
       break;
      }

     case 'K':
      {
       // ����� ������� �������� ��� �������� ��������� ����������.
       local_cp = CodeConverter::getConverter( read_digits(format,i) );
       break;
      }

     case 'W':
      {
       // ����� ������ ����.
       total_len = read_digits(format,i);
       break;
      }

     case '^':
      {
       // ����� ��������� ��� ������� ����� � ��������� ������.
       exp_len = read_digits(format,i);
       break;
      }

     case 'u':
      {
       // ������ 'unsigned'
       LEM_CHECKIT_Z(!is_unsigned);
       is_unsigned = true;
       break;
      }

     case 'n':
      {
       // ������ 'single'
       LEM_CHECKIT_Z(!is_quatro);
       LEM_CHECKIT_Z(!is_long);
       LEM_CHECKIT_Z(!is_normal);
       is_normal = true;
       break;
      }

     case 'l':
      {
       // ������ 'long'
       LEM_CHECKIT_Z(!is_quatro);
       LEM_CHECKIT_Z(!is_long);
       LEM_CHECKIT_Z(!is_normal);
       is_long = true;
       break;
      }

     case 'q':
      {
       // ������ 'quatro'
       LEM_CHECKIT_Z(!is_long);
       LEM_CHECKIT_Z(!is_quatro);
       LEM_CHECKIT_Z(!is_normal);
       is_quatro=true;
       break;
      }


     case 'L':
      {
       // ��� �������������� ���� (��� ���������, ��� �������).

       char caps_type = to_lower(format[i++]);
       LEM_CHECKIT_Z( caps_type=='c' || caps_type=='s' );

       switch(caps_type)
        {
         case 'c': caps=0; break;
         case 's': caps=1; break;
        }

        break;
      }


     case 'F':
      {
       // ����������� ���� ����������, ������������� ���������� ����������
       // ����������� ����.
       char index = to_lower(format[i++]);
       char state = to_lower(format[i++]);

       LEM_CHECKIT_Z( is_al_num(state) );
       LEM_CHECKIT_Z(nflag<(int)DIM_A(flag_index));
       LEM_CHECKIT_Z( nflag!=LEM_MSTREAM_NFLAG );

       flag_index[nflag] = index;
       flag_state[nflag] = state;
       nflag++;

       break;
      }

     case 'i':
      {
       // �������� ������� ������.
       nrepeate = read_digits(format,i);
       break;
      }

     default:
      {
       i--;
       cont=false;
       break;
      }

    } // end switch
  }

 return;
}

void OFormatter::print_field( char *buffer )
{
 if( !(stream) ) return;

 int str_len = lem_strlen(buffer);   // ����� ���
 int nspace=0;

 switch(caps)
  {
   case 0:
    {
     to_upper(buffer);
     break;
    }

   case 1:
    {
     to_lower(buffer);
     break;
    }
  }

 if( get_flag_state('$')=='3' || get_flag_state('$')=='4' )
  {
   char delim=' ';
   if( get_flag_state('$')=='3' )
    delim=',';

   int is=0,es=0;
   char ip[100]="",fp[100]="",ep[100]="";

   split(
             buffer,
             &is, ip, sizeof(ip),
                  fp, sizeof(fp),
             &es, ep, sizeof(ep)
            );

   if( strlen(ep) )
    {
     set_flag_state( '$', 0 );
     if( int(npos+lem_strlen(buffer)) > (int)page_width )
      printf('\n');

     print_field(buffer);
     return;
    }

   lem_strcpy( buffer, ip );

   // ����������� ������ ������ �������� ����.
   int blen = lem_strlen(buffer);
   int nblen = blen + blen/3 + 1;
   char *nbuf = new char[nblen+1];
   nbuf[nblen]=0;

   // ��������� ������� ������.
   int iscan=blen-1, idest=nblen-1;
   while( buffer[iscan]==' ' && iscan>=0 ) nbuf[idest--]=buffer[iscan--];

   int iblock=0;
   while( iscan>=0 && is_digit(buffer[iscan]) )
    {
     nbuf[idest--] = buffer[iscan--];

     if( !(++iblock%3) && iscan>=0 && is_digit(buffer[iscan]) )
      {
       nbuf[idest--]=delim;
       iblock=0;
      }
    }

   while( iscan>=0 && buffer[iscan]==' ' )
    nbuf[idest--]=buffer[iscan--];

   set_flag_state( '$', 0 );

   if( page_width && int(npos+lem_strlen(nbuf+idest+1)) > int(page_width) )
    eol();

   print_field(nbuf+idest+1);
   delete[] nbuf;
   return;
  }

 if( total_len>0 )
  {
   nspace = total_len-str_len;   // ������� �������� ����������.

   if( nspace<0 )
    nspace=0;
  }
 else
  {
   do
    {
     int ip=0;
     while( buffer[ip] )
      printf(buffer[ip++]);
    }
   while( --nrepeate>0 );

   return;
  }


 switch(aligment)
  {
   case 0:
    {
     // �� ������ ���� (�� ���������).
     do
      {
       int ip=0,i=0;
       while( buffer[ip] )
        printf(buffer[ip++]);

       while( i++!=nspace )
        printf(' ');
      }
     while( --nrepeate>0 );

     break;
    }

   case 2:
    {
     // �� ������� ����.

     // ����, ���� ����� ��������� before ���������, �� �������
     // str_len ����������� ��������� ������, ��������� ����� �������.
     do
      {
       int i=0;
       while( i++!=nspace )
        printf(' ');

       int ip=0;
       while( buffer[ip] )
        printf(buffer[ip++]);
      }
     while( --nrepeate>0 );

     break;
    }

   case 1:
    {
     // � ��������������.

     do
      {
       int i=0;
       while( i++!=nspace/2 )
        printf(' ');

       int ip=0;
       while( buffer[ip] )
        printf(buffer[ip++]);

       i=0;
       while( i++!=(nspace/2+nspace%2) )
        printf(' ');
      }
     while( --nrepeate>0 );

     break;
    }
  }

 return;
}

// ************************************************************
// ���������� ��������� ����������� ���������� ������.
// �������� �� ��� ���� ��������! ���� ��������� �����������,
// �� ������ ������ �� ������.
// ************************************************************
void OFormatter::VideoControl( const char *format, int &i )
{
 switch( format[i++] )
  {
   case 'b':
    {
     // ��������� ����� ������� ����
     lem::uint8_t iColor = (lem::uint8_t) format[i++];
     iColor = iColor - (iColor>=lem::uint8_t('A') ? lem::uint8_t('A')-10 : lem::uint8_t('0'));
     stream->SetBackGroundColor(iColor);
     break;
    }

   case 'f':
    {
     // ��������� ����� ��������
     lem::uint8_t iColor = (lem::uint8_t)format[i++];
     iColor = iColor - (iColor>='A' ? 'A'-10:'0');
     stream->SetForeGroundColor(iColor);
     break;
    }

   case 'x':
    stream->SetBlinkMode(true);
    break;

   case 'n':
    stream->SetNormalMode();
    break;

   case 'l':
    stream->SetLowLightMode();
    break;

   case 'h':
    stream->SetHighLightMode();
    break;

   default:
    LEM_STOPIT;
  }

 return;
}

// ******************************************************
// �������� C-������ (���������� ���������).
// ******************************************************
void OFormatter::Print_C_String( const char *val )
{
 LEM_CHECKIT_Z(after==-1);
 LEM_CHECKIT_Z(!is_quatro);

 // ���� ������ - ����������� ���� ��� ������,
 // ���� �������� field_len � ������������ ���� �� ���������,
 // ���� field_len �������� �� ������.
 int len=lem_strlen(val);   // �������������� ����� ������
 if( field_len>0 && field_len<len )
  len = field_len;

 char *buffer = new char[len+1];

 if( buffer==NULL )
  return;

 if( !!(val) )
  strncpy(buffer,val,len);
 else
  *buffer='\0';

 buffer[len] = '\0'; // �� ������ ������ ����������� ������ (����� strncpy).

 print_field(buffer);

 delete[] buffer;
 return;
}

void OFormatter::Print_Boolean( bool b )
{
 LEM_CHECKIT_Z(after<1);
 LEM_CHECKIT_Z(radix==10);

 char buffer[20];

 if( get_flag_state('f')=='0' || get_flag_state('f')==0 )
  {
   if(b) strcpy(buffer,"true");
   else  strcpy(buffer,"false");
  }
 else
  if( get_flag_state('f')=='1' )
   {
    if(b) strcpy(buffer,".TRUE.");
    else  strcpy(buffer,".FALSE.");
   }
  else
   if( get_flag_state('f')=='1' )
    {
     if(b) strcpy(buffer,"1");
     else  strcpy(buffer,"0");
    }
   else
    LEM_STOPIT;

 print_field(buffer);
 return;
}


/*******************************************************************
  ����������� �� ��������� �������. ���� ������� ������
  ����� �����, �� ����������� �� �����. ���� �������� to!=SHT_MAX,
  �� ������ �� ������ ����� �������, ����� ����� ������� ������� ��
  ���� field_len.
********************************************************************/
void OFormatter::Print_Tab( int to, char ch )
{
 LEM_CHECKIT_Z(after<1);
 if( !(stream) ) return;

 int TO = to==INT_MAX ? field_len : to;
 int n = TO-npos;
 if( n<0 )
  n=0;

 for( int i=n-1; i>=0; i-- )
  printf(ch);

 return;
}

#if !defined LEM_NOREAL
/******************************************************************

  ��������� ����������� ����� ���������� ��� ������ ���� REAL.
  ��� ��������� ������ ���������� ������ � ��� ������, ����
  ����������� ������������ %R... ��� %r...

*******************************************************************/
void OFormatter::MakeRealFormat( const char *format, int &i, char *f1 )
{
 if( !(format) ) return;

 #if REAL_TYPE==1008 || REAL_TYPE==10010 || REAL_TYPE==10018
  // ��� REAL ��������� ��� ���� �� DUPELxx
  is_dupel=true;
 #else
  is_dupel=false;
 #endif

 // ���� ����� ���� ���� �� �������, �� ������ �� ���
 // ����� �������� ���� REAL.
 if( !is_normal && !is_long && !is_quatro )
  {
   //#if REAL_TYPE==4 || REAL_TYPE==8 || REAL_TYPE==1008
    is_normal=true;
   //#elif REAL_TYPE==10 || REAL_TYPE==10010
   // is_long=true;
   //#elif REAL_TYPE==18 || REAL_TYPE==10018
   // is_quatro=true;
   //#else
   // #error UNKNOWN REAL TYPE
   //#endif
  }

 // �������� ������ ������������ ���� �������, ���� ���������
 // Rxx � rxx ����������.
 char ch=format[i-1];
 is_complete=false;

 bool is_efg=false;

 if( ch=='e' || ch=='g' || ch=='f' )
  {
   is_complete=false;
   is_dupel=false;
   is_complex=false;
   is_efg=true;
  }
 else if( ch=='R' )
  {
   is_complete=true;

   // ��� ��� ���� ������ �������� ����� ���� ��������
   // ���� ����, �� ������ �������� ������� ���� �����������.
   LEM_CHECKIT_Z(field_len<1);
   LEM_CHECKIT_Z(after<1);

   if( !is_normal && !is_long && !is_quatro )
    {
     #if REAL_TYPE==4
      field_len = 14;
      after     = 7;
     #elif REAL_TYPE==8 || REAL_TYPE==1008
      field_len = 23;
      after     = 15;
     #elif REAL_TYPE==10 || REAL_TYPE==10010
      field_len = 26;
      after     = 17;
     #elif REAL_TYPE==18 || REAL_TYPE==10018
      field_len = 56;
      after     = 32;
     #endif
    }
   else
    {
     if( is_normal )
      {
       // ���� ��������� double
       field_len = 23;
       after     = 15;
      }

     if( is_long )
      {
       // ���� ��������� long double
       field_len = 26;
       after     = 17;
      }

     if( is_quatro )
      {
       // ���� ��������� REAL18
       field_len = 56;
       after     = 32;
      }
    }
  }

 if( !is_efg )
  {
   // ��������, ������� ������������ �����.
   ch=format[i++];

   if( ch=='c' )
    {
     // ������������� LemComplex
     is_complex = true;
     ch=format[i++];
    }

   if( ch=='d' )
    {
     // ������������� DUPELxx
     is_dupel = true;
     ch=format[i++];
     LEM_CHECKIT_Z(!is_complex);
    }

   if( ch=='r' )
    {
     // ������������� REALxx
     LEM_CHECKIT_Z(!is_dupel);
     LEM_CHECKIT_Z(!is_complex);
     is_dupel=false;
     ch=format[i++];
    }
  }

 char lc[2]=" ";
 if( is_long )
  lc[0]='L';
 else
  lc[0]=0;

 const char *sign_formats[] = { "", " ", "+" };

 if( field_len<1 && after==-1 )
  {
   sprintf( f1, "%c%s%s%c", '%', sign_formats[sign_out], lc, ch );
  }
 else
  {
   if( after!=-1 )
    sprintf( f1, "%c%s%d.%d%s%c", '%', sign_formats[sign_out], field_len, after, lc, ch );
   else
    sprintf( f1, "%c%s%d%s%c", '%', sign_formats[sign_out], field_len, lc, ch );
  }

 return;
}

void OFormatter::Print_Real8( const char *FORMAT, double val )
{
 char aval[80];
 sprintf( aval, FORMAT, val );
 print_field(aval);
 return;
}

void OFormatter::Print_Real10( const char *FORMAT, long double val )
{
 char aval[80];
 sprintf( aval, FORMAT, val );
 print_field(aval);
 return;
}

#if (defined(SETREAL18) || defined(DEFREAL18))
void OFormatter::Print_Real18( const char *FORMAT, REAL18 val )
{
 char aval[80];
 qreal_to_str( val, aval, sign_out, true, false, after );

 print_field(aval);
 return;
}
#endif

/*
// ���������� ������������ �����.
void OFormatter::Print_Complex( const char *FORMAT, const LemComplex &cx )
{
 char re_part[256];
 char im_part[256];

 if( !is_dupel )
  {
   if( is_normal || is_long )
    {
     sprintf( re_part, FORMAT, cx.Re() );
     sprintf( im_part, FORMAT, cx.Im() );
    }
   else
    {
     #if (defined(SETREAL18) || defined(DEFREAL18)) && REAL_TYPE==18
      qreal_to_str( cx.Re(), re_part );
      qreal_to_str( cx.Re(), im_part );
     #else
      LEM_STOPIT;
     #endif
    }
  }
 else
  {
   #if REAL_TYPE==1008 || REAL_TYPE==10010 || REAL_TYPE==10018

   // ����������� ������: ��� LemComplex � ������������ DUPEL...
   if( is_normal || is_long )
    {
     Print_Dupel( re_part, FORMAT, cx.Re() );
     Print_Dupel( im_part, FORMAT, cx.Im() );
    }

   if( is_quatro )
    {
     #if (defined(SETREAL18) || defined(DEFREAL18))
      Print_Dupel( re_part, FORMAT, cx.Re() );
      Print_Dupel( im_part, FORMAT, cx.Im() );
     #else
      LEM_STOPIT;
     #endif
    }
   #endif
  }

 char buffer[256]; // ??? ����� 512 ???

 if( get_flag_state('f')=='0' || get_flag_state('f')==0 )
  sprintf( buffer, "{%s,%s}",  re_part, im_part );
 else
  if( get_flag_state('f')=='1' )
   sprintf( buffer, "(%s,%s)",  re_part, im_part );
  else
   if( get_flag_state('f')=='2' )
    sprintf( buffer, "%s %s",  re_part, im_part );
   else
    if( get_flag_state('f')=='3' )
     sprintf( buffer, "re=%s im=%s",  re_part, im_part );
    else
     LEM_STOPIT;

 print_field(buffer);
 return;
}
*/

#if !defined LEM_NODUP
void OFormatter::Print_Dupel(
                             char *BUFFER,
                             const char *FORMAT,
                             const DUPEL8 &D
                            )
{
 char a_part[128],b_part[32];

 sprintf( a_part, FORMAT, D.real() );

 if( !is_complete )
  {
   b_part[0]=0;
   sprintf( BUFFER, "{%s}", a_part );
  }
 else
  {
   if( get_flag_state('f')=='1' )
    sprintf( b_part, FORMAT, D.diverg() );
   else
    sprintf( b_part, "%7.1e%%", double(D.error()*100.) );

    sprintf( BUFFER, "{%s err=%s}",  a_part, b_part );
   }

 return;
}
#endif // !defined LEM_NODUP

#if !defined LEM_NODUP
#if !defined NOlong double
void OFormatter::Print_Dupel(
                             char *BUFFER,
                             const char *FORMAT,
                             DUPEL10 &D
                            )
{
 char a_part[128],b_part[128];

 sprintf( a_part, FORMAT, D.real() );

 if( !is_complete )
  {
   b_part[0]=0;
   sprintf( BUFFER, "{%s}", a_part );
  }
 else
  {
   if( get_flag_state('f')=='1' )
    sprintf( b_part, FORMAT, D.diverg() );
   else
    sprintf( b_part, "%7.1e%%", double(D.error()*100.) );

   sprintf( BUFFER, "{%s err=%s}",  a_part, b_part );
  }

 return;
}
#endif // !defined NOlong double
#endif // !defined LEM_NODUP

#if !defined LEM_NODUP
/*
#if defined(SETREAL18) || defined(DEFREAL18)
void OFormatter::Print_Dupel( char *BUFFER, const char *FORMAT, const DUPEL18 &D )
{
 char a_part[128],b_part[128];

 qreal_to_str( D.abs(), a_part );

 if( !is_complete )
  {
   b_part[0]=0;
   sprintf( BUFFER, "{%s}", a_part );
  }
 else
  {
   if( get_flag_state('f')=='1' )
   qreal_to_str( D.div(), b_part );
   else
    sprintf( b_part, "%7.1e%%", double(D.error()*100.) );

   sprintf( BUFFER, "{%s err=%s}",  a_part, b_part );
 }

 return;
}
#endif
*/
#endif // !defined LEM_NODUP

#endif // !defined LEM_NOREAL

void OFormatter::Print_UINT( unsigned int val )
{
 char aval[80]="";

 if( !field_len && is_complete )
  field_len = strlen( uint_to_str(UINT_MAX,aval,radix) );

 uint_to_str( val, aval, radix );
 int val_signum = val>0;

 PrintInt(aval,val_signum);
 return;
}

void OFormatter::Print_INT( int Val )
{
 char aval[80]="";
 int val_signum=0;
 int val=Val;

 if( !field_len && is_complete )
  field_len = strlen( int_to_str(INT_MIN,aval,radix) );

 if(val<0)
  {
   val=-val;
   val_signum = -1;
  }
 else
  if(val) val_signum=1;

 if(val<0)
  {
   // ���� �����-����� ��-�� ������� -MININT < 0 !
   // ��� ��� abs(MININT) �������� ��������. ����
   // ��� ����� ����� val_signum.
   #if INT_TYPE==2
    strcpy( aval, "32768" );
   #else
    strcpy( aval, "2147483648" );
   #endif
  }
 else
  int_to_str( val, aval, radix );

 PrintInt(aval,val_signum);
 return;
}

void OFormatter::Print_UINT32( unsigned int val )
{
 char aval[80]="";
 int val_signum=0;

 if( !field_len && is_complete )
  field_len = strlen( uint32_to_str(UINT_MAX,aval,radix) );

 uint32_to_str( val, aval, radix );
 val_signum = val>0;

 PrintInt(aval,val_signum);
 return;
}

void OFormatter::Print_INT32( int Val )
{
 char aval[80]="";
 int val_signum=0;
 lem::int32_t val=Val;

 if( field_len==0 && is_complete )
  field_len = strlen( int32_to_str(0,aval,radix) );

 if(val<0)
  {
   val=-val;
   val_signum = -1;
  }
 else
  if(val) val_signum=1;

 if(val<0)
  {
   // ���� �����-����� ��-�� ������� -MININT32 < 0 !
   // ��� ��� abs(MININT32) �������� ��������. ����
   // ��� ����� ����� val_signum.
   strcpy( aval, "2147483648" );
  }
 else
  uint_to_str( val, aval, radix );

 PrintInt(aval,val_signum);
 return;
}

#if defined LEM_UI64

void OFormatter::Print_UINT64( lem::uint64_t val )
{
 char aval[256]="";
 int val_signum=0;

 const int sl = strlen( lem::to_str( lem::uint64_max,aval,radix) );
 if( !field_len && is_complete )
  field_len = sl;

 val_signum = val>0;
 PrintInt(aval,val_signum);
 return;
}
#endif

#if defined LEM_I64
void OFormatter::Print_INT64( lem::int64_t val )
{
 char aval[256];
 int val_signum=0;

 if(val<0)
  {
   val=-val;
   val_signum = -1;
  }
 else
  if(!!val) val_signum=1;

 if(val<0)
  {
   sprintf( aval, "%I64d", val );
   val_signum=1;
  }
 else
  {
   lem::uint64_t uval = lem::uint64_t(val);
   to_str( uval, aval, radix );
  }

 PrintInt(aval,val_signum);
 return;
}
#endif


void OFormatter::PrintInt( const char *aval, int val_signum )
{
 char buffer[80]="";
 char zeros[80]="";
 char forsign[2]= { '\0', '\0' };

 switch( sign_out )
  {
   case 0:
    if(val_signum<0) *forsign='-';
    break;

   case 1:
    {
     if(val_signum>=0)
      *forsign=' ';
     else
      *forsign='-';

     break;
    }

   case 2:
    {
     if(val_signum>0)
      *forsign='+';
     else
      if(!val_signum)
       *forsign=' ';
      else
       *forsign='-';

     break;
    }
  }

 *zeros=0;

 // ���� ������ ���� field_len ������, ��� ����������
 // ����, �� ������� ���� �����.
 int nzero = field_len-strlen(aval)-strlen(forsign);

 if(nzero>0)
  {
   int iz=0;
   while(nzero--)
    zeros[iz++]= get_flag_state('z') == '1' ? '0': ' ';

   zeros[iz]=0;
  }

 sprintf( buffer, "%s%s%s", forsign, zeros, aval );
 print_field(buffer);
 return;
}


// ******************************************************
// ����������� ��������� ������ UNICODE-������.
// ******************************************************
void OFormatter::Print_C_String( const wchar_t *uStr )
{
 LEM_CHECKIT_Z(after==-1);
 LEM_CHECKIT_Z(!is_quatro);

 if( uStr==NULL )
  return;

 // ���� ������ - ����������� ���� ��� ������,
 // ���� �������� field_len � ������������ ���� �� ���������,
 // ���� field_len �������� �� ������.
 int len=lem_fullstrlen(uStr);   // �������������� ����� ������
 if( field_len>0 && field_len<len )
  len = field_len;

 wchar_t *buffer = new wchar_t[len+1];

 if( !(buffer) )
  return;

 if( uStr )
  lem_strncpy(buffer,uStr,len);
 else
  buffer[0]=0;

 print_field(buffer);

 delete[] buffer;
 return;
}


void OFormatter::print_field( wchar_t *buffer )
{
 if( !(stream) ) return;

 int str_len = lem_strlen(buffer);   // ����� ���
 int nspace=0;

 switch(caps)
  {
   case 0:
    {
     to_upper(buffer);
     break;
    }

   case 1:
    {
     to_lower(buffer);
     break;
    }
  }

 if( get_flag_state('$')=='3' || get_flag_state('$')=='4' )
  {
   wchar_t delim=' ';
   if( get_flag_state('$')=='3' )
    delim=',';

   int is=0,es=0;
   wchar_t ip[100]={0},fp[100]={0},ep[100]={0};

   split(
         buffer,
         &is, ip, sizeof(ip),
              fp, sizeof(fp),
         &es, ep, sizeof(ep)
        );

   if( lem_strlen(ep) )
    {
     set_flag_state( '$', 0 );
     if( int(npos+lem_strlen(buffer)) > (int)page_width )
      printf('\n');

     print_field(buffer);
     return;
    }

   lem_strcpy( buffer, ip );

   // ����������� ������ ������ �������� ����.
   int blen = lem_strlen(buffer);
   int nblen = blen + blen/3 + 1;
   wchar_t *nbuf = new wchar_t[nblen+1];
   nbuf[nblen]=0;

   // ��������� ������� ������.
   int iscan=blen-1, idest=nblen-1;

   while( buffer[iscan]==L' ' && iscan>=0 )
    nbuf[idest--]=buffer[iscan--];

   int iblock=0;
   while( is_udigit(buffer[iscan]) && iscan>=0 )
    {
     nbuf[idest--] = buffer[iscan--];

     if( !(++iblock%3) && iscan>=0 && is_udigit(buffer[iscan]) )
      {
       nbuf[idest--]=delim;
       iblock=0;
      }
    }

   while( buffer[iscan]==L' ' && iscan>=0 )
    nbuf[idest--]=buffer[iscan--];

   set_flag_state( '$', 0 );

   if( page_width && int(npos+lem_strlen(nbuf+idest+1)) > int(page_width) )
    eol();

   print_field(nbuf+idest+1);
   delete nbuf;
   return;
  }

 if( total_len>0 )
  {
   nspace = total_len-str_len;   // ������� �������� ����������.

   if( nspace<0 )
    nspace=0;
  }
 else
  {
   do
    {
     int ip=0;
     while( buffer[ip]!=0 )
      { uprintf( buffer[ip++] ); }
    }
   while( --nrepeate>0 );

   return;
  }

 switch(aligment)
  {
   case 0:
    {
     // �� ������ ���� (�� ���������).
     do
      {
       int ip=0,i=0;
       while( buffer[ip] )
        uprintf( buffer[ip++] );

       while( i++!=nspace )
        uprintf(L' ');
      }
     while( --nrepeate>0 );

     break;
    }

   case 2:
    {
     // �� ������� ����.

     // ����, ���� ����� ��������� before ���������, �� �������
     // str_len ����������� ��������� ������, ��������� ����� �������.
     do
      {
       int i=0;
       while( i++!=nspace )
        uprintf(L' ');

       int ip=0;
       while( buffer[ip] )
        uprintf(buffer[ip++]);
      }
     while( --nrepeate>0 );

     break;
    }

   case 1:
    {
     // � ��������������.

     do
      {
       int i=0;
       while( i++!=nspace/2 )
        uprintf(L' ');

       int ip=0;
       while( buffer[ip] )
        uprintf(buffer[ip++]);

       i=0;
       while( i++!=(nspace/2+nspace%2) )
        uprintf(L' ');
      }
     while( --nrepeate>0 );

     break;
    }
  }

 return;
}

// **************************************************************************
// ������������� ��������� ������ ���������� UNICODE-������� � ��������������
// � ASCII � ������� ������� ������� ��������.
// **************************************************************************
void OFormatter::uprintf( wchar_t uCh )
{
 LEM_CHECKIT_Z( out_cp );
 if( out_cp->IsSingleByte() )
  {
   printf( ((SBCodeConverter*)out_cp)->to_ascii(uCh), false );
  }
 else
  {
   lem::CharBuffer aCh( out_cp->EstimateAsciiLen(1)+1 );   
   int n = out_cp->to_ascii( uCh, aCh );
   for( int i=0; i<n; i++ ) 
    printf( aCh[i], false );
  }

 return;
}

void OFormatter::print_string( const wchar_t *buffer )
{ printf( "%us", buffer ); }

void OFormatter::print_string( const char *buffer )
{ printf( "%s", buffer ); }


// ***************************************************************


// ����������� ����� ������ � ����� � ������.
MemFormatter::MemFormatter(void)
: OUFormatter( new lem::Char_Stream::UTF16_MemWriter(), true )
{}


const UFString MemFormatter::string(void) const
{
 lem::Char_Stream::UTF16_MemWriter* s = static_cast<lem::Char_Stream::UTF16_MemWriter*>( stream );
 UFString res = s->string();
 s->clear();
 return res;
}

/*
const FString MemFormatter::stringa(void) const
{
 lem::Char_Stream::UTF16_MemWriter* s = static_cast<lem::Char_Stream::UTF16_MemWriter*>( stream );
 return lem::to_ascii(s->string());
}
*/

// ***************************************************************

OUFormatter::OUFormatter(void)
: OFormatter()
{}

OUFormatter::OUFormatter( const lem::Path &filename, bool write_bom )
:OFormatter() 
{
 UTF8_Reader *w = new UTF8_Reader( lem::Ptr<Stream>( new lem::BinaryWriter(filename) ) );

 if( write_bom )
  w->Write_Beginning();

 stream = w;
 can_i_close = true; 
 return;
}

OUFormatter::OUFormatter( FILE *file )
: OFormatter(file)
{}

OUFormatter::OUFormatter( Stream *file, bool CanClose )
: OFormatter(file,CanClose)
{}

void OUFormatter::Open( const lem::Path &filename, bool write_bom )
{
 Delete();

 UTF8_Reader *w = new UTF8_Reader( lem::Ptr<lem::Stream>( new lem::BinaryWriter(filename)  ) );

 if( write_bom )
  w->Write_Beginning();

 stream = w;
 can_i_close = true; 
 return;
}


void OUFormatter::uprintf( wchar_t ch )
{
 LEM_CHECKIT_Z( !!(stream) );
 if( !(stream) ) return;

 if( !!(doubler) )
  doubler->uprintf(ch);

 if( ch==7 )
  ch = L' ';

 if( GetControlFlag(LEM_MSTREAM_HTML) && ch=='\n' )
  // ����� � ������� HTML ������� �������� ������ <BR> � ����� ������.
  stream->puts( "<BR>" );
 else if( ch==L'\t' )
  {
   after=0;
   Print_Tab( (npos/8+1)*8, ' ' );
   return;
  }
 else if( ch==L'\n' && stream->IsBinary() )
  stream->put('\r'); 

 stream->wput(ch);

 npos = ch==L'\n' ? 0 : npos+1;
 if( npos==0 && left_margin )
  for( int i=left_margin-1; i>=0; i-- )
   uprintf(L' ');

 if( page_width && npos==page_width )
  uprintf( L'\n' );

 return;
}


OFormatter& lem::operator << ( OFormatter &o, int d )
 {
  o.printf( "%d", d );
  return o;
 }

OFormatter& lem::operator<<( OFormatter &to, const FString &s )
 {
  to.printf( "%s", s.c_str() );
  return to;
 }

OFormatter& lem::operator<<( OFormatter &to, const UFString &s )
 {
  to.printf( "%us", s.c_str() );
  return to;
 }

OFormatter& lem::operator<<( OFormatter &to, const CString &s )
 {
  to.print_field( (char*)s.c_str() );
  return to;
 }

OFormatter& lem::operator<<( OFormatter &to, const UCString &s )
 {
  to.print_field( (wchar_t*)s.c_str() );
  return to;
 }

void OFormatter::flush(void)
{
 if( !!(stream) )
  stream->flush();

 if( !!(doubler) )
  doubler->flush();

 return;
}


XmlFormatter::XmlFormatter( const lem::Path &filename )
:OUFormatter(filename,false) 
{
}


void XmlFormatter::WriteBeginning(void)
{
 printf( "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" );
 return;
}



void OFormatter::eol(void)
{
 printf('\n');
 return;
}



void OFormatter::cr(void)
{
 printf('\r');
 return;
}



void OFormatter::close(void)
{
 Delete();
 return;
}


void OFormatter::dot(void)
{
 printf('.');
 flush();
 return;
}

void OFormatter::SetControlFlag( unsigned long Flags, bool SetAction )
{
 CONTROLFLAG &= ~Flags;

 if( SetAction )
  CONTROLFLAG |= Flags;

 return;
}


bool OFormatter::GetControlFlag( unsigned long Flags ) const
{
 return !!(CONTROLFLAG&Flags);
}


void OFormatter::SetDoubler( OFormatter *Doubler )
{ doubler=Doubler; }

void OFormatter::ClearDoubler(void)
{ doubler=NULL; }

OFormatter* OFormatter::GetDoubler(void)
{ return doubler; }

Stream* OFormatter::GetStream(void)
{ return stream; }

void OFormatter::SetLeftMargin( int X )
{ left_margin=X; }


void OFormatter::SetLocalCP( const CodeConverter *Page )
{ local_cp=Page; }

void OFormatter::SetOutCP( const CodeConverter *Page )
{ out_cp=Page; }

void OFormatter::SetCP( const CodeConverter *Device, const CodeConverter *Local )
{ out_cp=Device; local_cp=Local; }

const CodeConverter* OFormatter::GetOutCP(void)
{ return out_cp; }


void OFormatter::SetAutoflush(void)
{ autoflush=true; }


void OFormatter::cprintf( const char *fmt, ... )
{
 if( fmt==NULL )
  return;

 va_list argptr;
 va_start(argptr,fmt);

 int size = 1024;

 char *buf=NULL;
 while(true)
  {
   buf = (char*)malloc( sizeof(char)*(size+1) );
   if( !buf )
    {
     // out of memory
     va_end(argptr);
     return;
    }

   #if defined LEM_WINDOWS
   int len = _vsnprintf( buf, size, fmt, argptr );
   #else
   int len = vsnprintf( buf, size, fmt, argptr ); 
   #endif


   // some implementations of vsnprintf() don't NUL terminate the string
   // if there is not enough space for it so always do it manually
   buf[size] = '\0';

   if( (len>=0) && (len<=size) )
    break;

   // still not enough, double it again
   size *= 2;
   free(buf);
  }

 va_end(argptr);

 if( buf!=NULL )
  {
   print_string(buf);
   free(buf);
  }

 return;
}


void OFormatter::cprintf( const wchar_t *fmt, ... )
{
 if( fmt==NULL )
  return;

 va_list argptr;
 va_start(argptr, fmt);

 int size = 1024;
 
 wchar_t *buf=NULL;
 while(true)
  {
   buf = (wchar_t*)malloc( sizeof(wchar_t)*(size+1) );
   if( !buf )
    {
     // out of memory
     va_end(argptr);
     return;
    }

   #if defined LEM_WINDOWS
   int len = _vsnwprintf( buf, size, fmt, argptr ); 
   #else
   int len = vswprintf( buf, size, fmt, argptr ); 
   #endif

   // some implementations of vsnprintf() don't NUL terminate the string
   // if there is not enough space for it so always do it manually
   buf[size] = L'\0';

   if( (len>=0) && (len<=size) )
    break;

   // still not enough, double it again
   size *= 2;
   free(buf); 
  }

 va_end(argptr);

 if( buf!=NULL )
  {
   print_string(buf);
   free(buf);
  }

 return;
}



U16Formatter::U16Formatter(void)
: OFormatter()
{}


U16Formatter::U16Formatter( const lem::Path &filename, bool write_bom )
:OFormatter() 
{
 UTF16_Reader *w = new UTF16_Reader( SET_UTF16, lem::Ptr<Stream>( new lem::BinaryWriter(filename) ) );

 if( write_bom )
  w->Write_Beginning();

 stream = w;
 can_i_close = true; 
 return;
}

void U16Formatter::Open( const lem::Path &filename, bool write_bom )
{
 Delete();

 UTF16_Reader *w = new UTF16_Reader( SET_UTF16, lem::Ptr<lem::Stream>( new lem::BinaryWriter(filename)  ) );

 if( write_bom )
  w->Write_Beginning();

 stream = w;
 can_i_close = true; 
 return;
}


void U16Formatter::uprintf( wchar_t ch )
{
 LEM_CHECKIT_Z( !!(stream) );
 if( !(stream) ) return;

 if( !!(doubler) )
  doubler->uprintf(ch);

 if( ch==7 )
  ch = L' ';

 if( GetControlFlag(LEM_MSTREAM_HTML) && ch=='\n' )
  // ����� � ������� HTML ������� �������� ������ <BR> � ����� ������.
  stream->puts( "<BR>" );
 else if( ch==L'\t' )
  {
   after=0;
   Print_Tab( (npos/8+1)*8, ' ' );
   return;
  }
 else if( ch==L'\n' && stream->IsBinary() )
  stream->put('\r'); 

 stream->wput(ch);

 npos = ch==L'\n' ? 0 : npos+1;
 if( npos==0 && left_margin )
  for( int i=left_margin-1; i>=0; i-- )
   uprintf(L' ');

 if( page_width && npos==page_width )
  uprintf( L'\n' );

 return;
}

