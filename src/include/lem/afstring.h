#ifndef LEM_AFSTRING__H
#define LEM_AFSTRING__H
#pragma once

// -----------------------------------------------------------------------------
// File AFSTRING.H
//
// (c) by Elijah Koziev   all rights reserved
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix
//
// Content:
// FString ASCII mutable strings template class.
// ������ �������� � �������������� ���������� ������������ ������.
//
// 19.08.2004 - ��������� �������������� ������ ��� ���������� ������. ��� ����
// �� ��������� ������������ � ��������� ������������ �������� ������ �������,
// ������� ����� ����� ��� �������� ������ (���� ����������). ������ ���
// ������ ��������� += ���������� ��������� ������ � �������, ����� ���������
// ���������������� ������� �������� ������������� ����������.
//
// ��������� ������������ ������� - �� ���� � �� ���� �����.
//
// 27.09.2004 - ��������� �������� front() � back()
// 01.11.2004 - ���������� ������ ������, ����������� � ������������ ������,
//              � subst(...) 
//
// 13.12.2004 - ������� ������ SaveBin � LoadBin, ����� ���� ������ ��������
//              � ������������ (���������� � �������� Collect<FString>). 
//
// 26.01.2005 - ��������� ��� ���� � insert(...)
//
// 17.09.2005 - ��� ��� ������� realloc � MSVS ������ ��� ��������� NULL �����,
//              ����������� �������� �������� � malloc
//
// 07.01.2006 - ��� ������� ����������� ����� Guardian (��. runtime_checks.h).
//
// 30.11.2006 - ����������� �� wchar_t* ������ explicit
//
// 09.02.2007 - �������� ����� eqi - ��������� ��� ����� ��������
//
// 26.02.2007 - ���������� ������ � ������������ ������, �������� �����
//              �����������.
//
// 18.06.2007 - ������ ����� eq_begi ��� �������������� �������� ����������
//              ������ ������.
//
// 01.07.2007 - ����������� FString( char ) ������ explicit.
//
// 16.11.2007 - ��������� ��� � ::UnRef
// 18.07.2008 - ��������� ������ Alloc � Free
// 02.02.2009 - �������� ����� Realloc
// -----------------------------------------------------------------------------
//
// CD->02.07.1996
// LC->07.03.2010
// --------------

#include <string>
#include <vector>
#include <set>

#include <lem/config.h>
#include <lem/strings.h>

#if LEM_DEBUGGING==1 && defined LEM_MSC
#include <crtdbg.h>
#endif

#if defined LEM_MFC
 #include <atlstr.h>
#endif

 #include <stdlib.h>

 #undef min
 #undef max

 namespace lem
 {
  extern int lem_strlen( const char* );
  extern int lem_strlen( const wchar_t* );
  extern char* to_lower( char *s );
  extern char* to_upper( char *s );

  extern void dos_to_win( char *s );
  extern void win_to_dos( char *s );
  extern void win_to_koi( char *s );
  extern void koi8_to_win( char *s );
  extern void dos_to_koi( char *s );
  extern void koi8_to_dos( char *s );

  extern int to_int( const char *s );
  extern bool to_bool( const char *s );

  class Stream;
 }

 namespace lem {


 class FString
 {
  friend void swap( FString &x, FString &y );

  public:
   // Types - ����������� � STL::basic_string
   typedef std::char_traits<char> traits_type;
   typedef char                   value_type;
   typedef size_t                 size_type;

   typedef char*                  pointer;
   typedef const char*            const_pointer;
   typedef char*                  iterator;
   typedef const char*            const_iterator;

   typedef unsigned char         hash_type;

   // ��������� - ������������ ����� ������. ������� ��� �������������
   // � ������� BaseCString, ��� ������������ ����������� ������������
   // �� ������ ����������.
   enum { max_len = INT_MAX };

  private:
   #if LEM_DEBUGGING==1
   Guardian guard1;
   #endif

   char *str; // ��������� �� ���� � ������������ ������.
   #if defined LEM_STRPOOL
   int *ref_count; // ��������� �� ������� ������
   #endif

   #if LEM_DEBUGGING==1
   Guardian guard2;
   #endif

   int len; // ����� �������� ������ (�� �������������� 0).
   int cap; // ������� ����������� ����� ������ (������������ ����� ������, ��
            // ������ ��������� 0)

   hash_type hash; // ���-��� ��� ��������� �������� ���������.

   static char static_zero;

   inline void SetContens( char *s )
   { str=s; calc_hash(); cap=len; }

   // ***********************************************************
   // ����� ������� ������ ������ ���������� ���������� �����,
   // ������� ����� ��������� ��������.
   // ***********************************************************
   #if defined LEM_STRPOOL
   void UnShare(void);
   #endif
 
   // ****************************************************************
   // ������� ������ �� ������ ����������� �� 1, � ���� ������ ������
   // ���, ������ ���������.
   //
   // ****************************************************************
   #if defined LEM_STRPOOL
   void UnRef(void);
   #endif

   void Init( const char *s );

  public:
   #if LEM_DEBUGGING==1
   inline void Assert(void) const
   {
    #if LEM_DEBUGGING==1 && defined LEM_MSC
    LEM_CHECKIT_Z( !str || _CrtIsValidHeapPointer(str) );
    #endif

    guard1.Assert();
    guard2.Assert();
   }
   #endif

   //! ��������� ����� ������ ��������, ����������� � ������������ ����� ������� FString
   static char* Alloc( size_type total_length )
   { 
    return (char*)malloc(total_length);
   }

   static char* Realloc( char *Ptr, size_type total_length )
   { 
    return (char*)realloc(Ptr,total_length);
   }

   static void Free( char *ptr ) { free(ptr); }

  public:
   FString( void );
   FString( const char *aStr );
   explicit FString( const wchar_t *uStr );
   explicit FString( const std::string &s );

   // ********************************************************************
   // ����� ������������, �� �������� ��� ����������� �����������:
   // ���� ������, �� ������� ��������� ��������, ����� ����������������
   // ��� �������� ����� ������, ��� ��� �� ����������� ���������
   // ������ ����� ������������ ����. �������� get_control ���������� ��
   // ������������, � ����� ������ ��� ��������������� ��������� �������
   // ������������.
   // ********************************************************************
   FString( char *str, bool get_control );

   // ************************************************************
   // �������� ������, ��������� �� ������ ��������� ������� ch.
   // ************************************************************
   explicit FString( char Ch );

   // ***************************************************
   // ��������� ������, ��������� �� nTime �������� ch.
   // ***************************************************
   FString( size_type nTime, char ch );

   // *************************************************************
   // ��������� ������ �� �������� �� beg �� end-1,
   // ������������� ���� ����������� � ���������� �������������.
   // *************************************************************
   FString( const char *beg, const char *end );

   FString( const FString& s );

   // ������������ ������������
   FString( const FString& s1, const FString& s2 );
   FString( const FString& s1, const FString& s2, const FString& s3 );

   //#if defined LEM_VCL
//   explicit FString( const AnsiString &s );
//   #endif

   #if defined LEM_QT && !defined LEM_UNICODE
   explicit FString( const QString &x );
   #endif
  
   #if defined LEM_WXWIDGETS && !defined LEM_UNICODE
   explicit FString( const wxString &s );
   #endif

   #if defined LEM_MFC
   explicit FString( const CStringA &s );
   #endif

   ~FString(void);

   FString& operator=( const char *s    );
   FString& operator=( const wchar_t *s );
   FString& operator=( const FString& s );
   FString& operator=( const std::string& s );
   FString& operator=( char ch );

   #if defined LEM_VCL
   //FString& operator=( const AnsiString &s );
   #endif

   #if defined LEM_QT && !defined LEM_UNICODE
   FString& operator=( const QString &x );
   #endif
  
   #if defined LEM_WXWIDGETS && !defined LEM_UNICODE
   FString& operator=( const wxString &s );
   #endif

   #if defined LEM_MFC
   FString& operator=( const CStringA &s );
   #endif

   void copy( const char *beg, const char *end );

   // Do NOT use it: for internal usage only!
   inline char* ptr(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif

    #if defined LEM_STRPOOL
    UnShare();
    #endif
    
    return str;
   }

   inline const char* c_str(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif

    return !(str) ? (char*)"\0" : str;
   }


   inline char front() const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str ? *str : 0;
   }

   inline char back() const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return (str && len) ? str[len-1] : 0;
   }

   inline iterator begin(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str;
   }

   inline iterator end(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str+len;
   }

   inline const_iterator begin(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str;
   }

   inline const_iterator end(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str+len;
   }

   // ***************************************
   // Recalculating the hash after changes.
   // ***************************************
   inline void calc_hash(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    hash=lem_calc_string_hash_len(str,&len);
   }

   // ���������� ���-���� ������ - ����� �� �����������
   inline void calc_hash_only(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    hash=lem_calc_string_hash(str);
   }

   inline hash_type GetHash(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return hash;
   }

   inline hash_type h(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return hash;
   }


   /************************************************************************
    Accessing the chars in string.

    �������� ������� � ��������� ������ - ��������. ��� ������� ����������
    �������� �� ��������� ������ ���������� ����. ���������� ��������� �����
    �������� ������ �� ������.
   *************************************************************************/
   inline char operator[]( int i ) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return i<0 || i>=length() ? 0 : str[i];
   }

   // *******************************************************************
   // ������������ ��������� ������ � ������ (����� ������������� '\0').
   // ��� ������ ������ ������������ '\0'
   // *******************************************************************
   char last_char( int i=0 ) const;

   // Returns the index of the rightmost character that matches any
   // character in the delimiters string.
   int LastDelimiter( const char *delimiters ) const;


   // ************************************************************
   // ������������ ����� ������. ��� ������ ������ ������������ 0.
   // ************************************************************

   inline int size(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return len;
   }

   inline int length(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return len;
   }

   inline bool empty(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return !len;
   }

   // ******************************************************
   // Setting the content
   // ******************************************************

   void set( int i, char ch );

   // ������� ������ - ������ �� �������������, � �������� � ������� ��
   // ���������� ������. ����� ������ ����������.
   void clear(void);

   void set_dir( int i, char ch );

   FString& reduce( int i );
   void insert( int pos, char ch );
   void remove( int pos );

   // Reduce string length to new_len.
   void ShrinkTo( int new_len );

   inline void Insert( int pos, char ch ) { insert(pos,ch); }
   inline void Remove( int pos ) { remove(pos); }

   FString& operator+=( const FString &s     );
   FString& operator+=( const char *s    );
   FString& operator+=( const wchar_t *s );
   FString& operator+=( char ch          );
   FString& operator+=( const std::string &s );

   #if defined LEM_VCL
//   FString& operator+=( const AnsiString &s );
   #endif

   #if defined LEM_QT && !defined LEM_UNICODE
   FString& operator+=( const QString &x );
   #endif
  
   #if defined LEM_WXWIDGETS && !defined LEM_UNICODE
   FString& operator+=( const wxString &s );
   #endif

   #if defined LEM_MFC
   FString& operator+=( const CStringA &s );
   #endif

   FString& Add_Dirty( const FString &s     );
   FString& Add_Dirty( const char *s    );
   FString& Add_Dirty( const wchar_t *s );
   FString& Add_Dirty( char ch          );

   int count( char ch ) const;
   int find( char ch ) const;
   int find_last_of( char ch ) const;
   inline int rfind( char ch ) const { return find_last_of(ch); }

   int search( char to_find, int nentry=1 ) const;
   int search( const FString &to_find, int nentry=1 ) const;
   int search( const char *to_find, int nentry=1 ) const;
   int search( const wchar_t *to_find, int nentry=1 ) const;

   int search_from( char to_find, int start_pos ) const;
   int search_from( const FString &to_find, int start_pos ) const;
   int search_from( const char *to_find, int start_pos ) const;
   int search_from( const wchar_t *to_find, int start_pos ) const;

   bool eq_beg( const FString &to_find ) const;
   bool eq_beg( const char* to_find ) const;
   bool eq_beg( const wchar_t* to_find ) const;
   bool eq_begi( const char* to_find ) const;

   bool eqi( const FString &x ) const;
   bool eqi( const char *x ) const;


   FString& subst(
                  const FString &mask,
                  const FString &text,
                  int nentry=1
                 );

   // �������� ��� ��������� ������ mask �� ������ text.
   FString& subst_all( const FString &mask, const FString &text );
   FString& subst_all( const std::vector< std::pair<FString,FString> > &macros );
   FString& subst_all( char old_ch, char new_ch );
   FString& subst_all(
                      const std::vector< std::pair<FString,FString> > &macros,
                      const std::set<char> &first_chars 
                     );

   FString& to_upper(void);
   FString& to_lower(void);

   FString& to_Aa(void);

   FString& koi8_to_win(void);
   FString& koi8_to_dos(void);
   FString& dos_to_win(void);
   FString& win_to_dos(void);
   FString& dos_to_koi8(void);
   FString& win_to_koi8(void);

   // ***********************************************************************
   // ����������� ������� ��������, ����������� ������. ���� �� ������ ������
   // ��������� �� ���������, �� ������ �� ��������.
   // ***********************************************************************
   FString& strip( char Bound );
   FString& strip_quotes(void);
   FString& strip_apostrophes(void);

   FString& dress( char Bound );
   FString& dress_quotes(void);
   FString& dress_apostrophes(void);
   FString& dress_spaces(void);

   FString& cut_final_dot(void);
   FString& cut_final_commas(void);
   FString& trim(void);

   FString& add_sp(void);
   FString& add_nl(void);
   FString& add_spaces( int n );
   FString& expand_to( int n );

   FString& trancate_to( int new_len );
   FString& cut( int from, int upto );
   FString& reserve( FString::size_type new_cap );

   void re_clear(void);

   inline int    to_int(void)  const { return lem::to_int(str);  }
   inline bool   to_bool(void) const { return lem::to_bool(str); }
//   inline double to_real(void) const { return lem::to_real(str); }

   void LoadBin( lem::Stream &bin );
   void SaveBin( lem::Stream &bin ) const;

   friend bool operator==( const FString &s1, const FString &s2 );
   friend bool operator!=( const FString &s1, const FString &s2 );

   int ToInt(void) const;
   bool ToBool(void) const;
  };


 // *******************************************************
 // ����������� ��� ���������� ������� ������ ������.
 // �� ����� ���� ���������� ��������� ����� NULL, ��� ���
 // ��������� � ���������� ���� �� �����.
 // *******************************************************

 inline FString::FString(void)
 {
  str=NULL;
  hash=cap=len=0;
  #if defined LEM_STRPOOL
  ref_count=NULL;
  #endif
  return;
 }


 inline FString::FString( const char *source )
 {
  if( source && *source )
   {
    cap = len = (int)strlen(source);
    str=Alloc( len + 1 );
    #if defined LEM_STRPOOL
    ref_count = new int(1);
    #endif
    strcpy( str, source );
    calc_hash();
   }
  else
   {
    // ���� �������� = NULL, �� ��������������� ������ ������.
    str=NULL;

    #if defined LEM_STRPOOL
    ref_count=NULL;
    #endif

    hash=cap=len=0;
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }


 inline FString::FString( const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  cap = len = s.len;
  hash = s.hash;

  #if defined LEM_STRPOOL
  if( len )
   {
    str = s.str;
    ref_count = s.ref_count;
    ++*ref_count;
   }
  else
   {
    str=NULL;
    ref_count=NULL;
   }
  #else
  if( s.str && len )
   {
    str=Alloc( len+1 );
    strcpy( str, s.str );
   }
  else
   {
    str=NULL;
   }
  #endif

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }



 


 inline FString::FString( const char *beg, const char *end )
 {
  if( end < beg )
   throw std::bad_alloc();

  const FString::size_type l = end-beg;
  str=Alloc( l+1 );
  #if LEM_DEBUGGING==1
  if(!str)
   throw std::bad_alloc();
  #endif

  #if defined LEM_STRPOOL
  ref_count = new int(1);
  #endif

  std::copy( beg, end, str );
  str[l] = 0;
  calc_hash();
  cap=len;

  #if LEM_DEBUGGING==1
  Assert();
  #endif
 }

 // *********************************************************************
 // ������ ����������� ������ �� Str �� ������ ����� ��� ���� ��������
 // ��������� �� ���� ������, ��� ��� ������� ��� �� ������ �����������
 // ��������� Str. ������� �������� get_control �� ������������ � ������
 // ������ ��� ��������� �� ������ �������������. ������ �����������
 // ������-�� �� ������������ ��� �������� ������������� - ������ ��
 // ����������� ����� ����������� ����.
 // *********************************************************************

 inline FString::FString( char *Str, bool /*get_control*/ )
 {
  str = Str;
  #if defined LEM_STRPOOL
  ref_count = new int(1);
  #endif
  calc_hash();
  cap = len;
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return;
 }



 // *********************************************
 // ��������� ������ �� ������ �������.
 // *********************************************

 inline FString::FString( char c )
 {
  #if defined LEM_STRPOOL
  ref_count = new int(1);
  #endif
  str = Alloc( 2 );

  #if LEM_DEBUGGING==1
  if(!str)
   throw std::bad_alloc();
  #endif

  str[0]=c;
  str[1]='\0';
  calc_hash();
  cap=1;
  return;
 }

 


 inline FString::~FString(void)
 {
  #if defined LEM_STRPOOL
  UnRef();
  #else
  Free(str); str=NULL;
  #endif
 }


 inline FString& FString::operator=( const FString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  Assert();
  #endif

  LEM_CHECKIT_Z( &s!=this ); // ����� �� x=x !

  #if defined LEM_STRPOOL
/*
  if( ref_count && str && s.ref_count==ref_count && s.str==str )
   {
    *ref_count++;
    return *this;
   }
*/
  UnRef(); 
  len=s.len;
  if( !len )
   {
    hash='\0';
    // ���� str � ref_count ��� �������� � //UnRef()
    return *this;
   }

  cap = s.cap;
  str = s.str;
  ref_count = s.ref_count;
  ++*ref_count; 

  hash = s.hash;
  #else
  len=s.len;
  if( !len )
   {
    hash='\0';

    if( str )
     *str=0;

    return *this;
   }

  if( cap<len )
   {
    // � ������ ����� ����� ������� ���� - ������� �����.
    str = Realloc( str, len+1 );
    if(!str)
     throw std::bad_alloc();

    cap = len;
   }

  strcpy( str, s.str );
  hash = s.hash;
  #endif

  #if LEM_DEBUGGING==1
  s.Assert();
  Assert();
  #endif

  return *this;
 }


 

 inline FString& FString::operator=( const std::string &s )
 {
  return operator=(s.c_str());
 }




 inline void FString::set( int i, char ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  if( i>=0 && i<len )
   {
    #if defined LEM_STRPOOL
    UnShare();
    #endif
    str[i]=ch;
    calc_hash();
   }

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }

 // *************************************************************************
 // ������ �� ����� ::set(...), �� ���-��� �� ���������������, �������
 // ����� ����� �������� ��� ������-���� �������������� ���� ��������
 // ������, � �� ����� ����� ���� ��� ����������� ���-��� ������� calc_hash()
 // *************************************************************************

 inline void FString::set_dir( int i, char ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  LEM_CHECKIT_Z( i>=0 && i<len );
  #if defined LEM_STRPOOL
  UnShare();
  #endif

  str[i]=ch;

  #if LEM_DEBUGGING==1
  Assert();
  #endif
 }

 /**************************************************************************
   ���������� ������, ������������ � �������, ������������� �� ����� ������.
   �� ���� last_char(0) ������ ��������� ������ ����� '\0'. ��� ������ ��
   ������� ������������ ������ ���������� '\0'.
 ***************************************************************************/

 inline char FString::last_char( int i ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  
  const int pos=len-i-1;
  return pos>=len ? 0 : str[pos];
 }

 /************************************************************************
  ���������� ����� ��������� ������� ch � ������ s. ������� �����
  �������������� ��� ����������� ������ ����� ��������� ������� � ������
  ��� ��� ���������� ������� ���� ������� ��������� (�� ���� 'false'!).
 *************************************************************************/

 inline int FString::find( char ch ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_nentry( str, ch );
 }

 /**************************************************************************
   ������� n-�� (�� ��������� ������) ��������� ������� ch � ������-��������
   s. ���� ������ �� ������, ��� ����� ��� ��������� ����� nentry, ��
   ������������ -1.
 **************************************************************************/

 inline int FString::search( char ch, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, ch, nentry );
 }


 inline int FString::count( char ch ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  int n=0;
  for( const char *p=str; p!=str+len; p++ )
   if( *p==ch )
    n++;

  return n;
 }

 /***************************************************************************
  ���������� ��������� nentry-�� ��������� ��������� [f] � ������ [s].
  ���������� ������ ������� ���������� �������. ���� ��������� ��
  ����������, ��� ����� �� ��������� � ������ ����� nentry, �� ���������� -1.
 ****************************************************************************/

 inline int FString::search( const FString &f, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, f.c_str(), nentry );
 }


 inline int FString::search( const char *to_find, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, to_find, nentry );
 }


 inline int FString::search( const wchar_t *to_find, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, to_find, nentry );
 }



 inline int FString::search_from( const FString &to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find.c_str(), start_pos );
 }


 inline int FString::search_from( const char *to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 inline int FString::search_from( const wchar_t *to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 inline int FString::search_from( char to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 extern const FString add_sp( const FString& s );
 extern const FString add_nl( const FString& s );
 extern const FString add_spaces( const FString& s, int n );
 extern const FString trim( const FString &s );
 extern const FString expand_to( const FString &s, int n );

 /***************************************************************

                   ��������� ���������

 ****************************************************************/


 inline bool operator==( const FString &s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  return s1.hash==s2.hash && s1.len==s2.len && lem_eq( s1.c_str(), s2.c_str() );
 }


 inline bool operator==( const FString &s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_eq( s1.c_str(), s2 );
 }


 inline bool operator==( const FString &s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_eq( s1.c_str(), s2 );
 }


 inline bool operator==( const char *s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_eq( s2.c_str(), s1 );
 }


 inline bool operator==( const wchar_t *s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_eq( s2.c_str(), s1 );
 }


 inline bool operator==( const FString &s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch=='\0';

  return s.front()==ch && s[1]=='\0';
 }


 inline bool operator==( char ch, const FString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch=='\0';

  return s[0]==ch && s[1]=='\0';
 }

 // ************************************************************************


 inline bool operator!=( const FString &s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  return s1.hash != s2.hash || s1.len!=s2.len || lem_neq( s1.c_str(), s2.c_str() );
 }


 inline bool operator!=( const FString &s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_neq( s1.c_str(), s2 );
 }


 inline bool operator!=( const FString &s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_neq( s1.c_str(), s2 );
 }


 inline bool operator!=( const char *s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_neq( s1, s2.c_str() );
 }


 inline bool operator!=( const wchar_t *s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_neq( s1, s2.c_str() );
 }


 inline bool operator!=( const FString &s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch!='\0';

  return s[0]!=ch || s[1]!='\0';
 }


 inline bool operator!=( char ch, const FString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch!='\0';

  return s[0]!=ch || s[1]!='\0';
 }

 // ****************************************************************


 inline bool operator>( const FString& s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_gt( s1.c_str(), s2.c_str() );
 }


 inline bool operator>( const FString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_gt( s1.c_str(), s2 );
 }


 inline bool operator>( const FString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_gt( s1.c_str(), s2 );
 }


 inline bool operator>( const char *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_gt( s2.c_str(), s1 );
 }


 inline bool operator>( const wchar_t *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_gt( s2.c_str(), s1 );
 }


 inline bool operator>( const FString& s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  char s2[2]={ ch, '\0' };
  return lem_gt( s.c_str(), s2 );
 }


 inline bool operator>( char ch, const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  char s2[2]={ ch, '\0' };
  return lem_gt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator>=( const FString& s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_ge( s1.c_str(), s2.c_str() );
 }


 inline bool operator>=( const FString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_ge( s1.c_str(), s2 );
 }


 inline bool operator>=( const FString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_ge( s1.c_str(), s2 );
 }


 inline bool operator>=( const char *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_ge( s2.c_str(), s1 );
 }


 inline bool operator>=( const wchar_t *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_ge( s2.c_str(), s1 );
 }


 inline bool operator>=( const FString& s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  char s2[2]={ ch, '\0' };
  return lem_ge( s.c_str(), s2 );
 }


 inline bool operator>=( char ch, const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  char s2[2]={ ch, '\0' };
  return lem_ge( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator<( const FString& s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_lt( s1.c_str(), s2.c_str() );
 }


 inline bool operator<( const FString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_lt( s1.c_str(), s2 );
 }


 inline bool operator<( const FString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_lt( s1.c_str(), s2 );
 }


 inline bool operator<( const char *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_lt( s2.c_str(), s1 );
 }


 inline bool operator<( const wchar_t *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_lt( s2.c_str(), s1 );
 }


 inline bool operator<( const FString& s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  char s2[2]={ ch, '\0' };
  return lem_lt( s.c_str(), s2 );
 }


 inline bool operator<( char ch, const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  char s2[2]={ ch, '\0' };
  return lem_lt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator<=( const FString& s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_le( s1.c_str(), s2.c_str() );
 }


 inline bool operator<=( const FString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_le( s1.c_str(), s2 );
 }


 inline bool operator<=( const FString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_le( s1.c_str(), s2 );
 }


 inline bool operator<=( const char *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_le( s2.c_str(), s1 );
 }


 inline bool operator<=( const wchar_t *s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_le( s2.c_str(), s1 );
 }


 inline bool operator<=( const FString& s, char ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  char s2[2]={ ch, '\0' };
  return lem_le( s.c_str(), s2 );
 }


 inline bool operator<=( char ch, const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  char s2[2]={ ch, '\0' };
  return lem_le( s2, s.c_str() );
 }



 extern const FString remove_chars( const FString &str, const FString &chs );
 extern const FString remove_char( const FString &str, char chs );
 extern const FString strip( const FString &fs, char Bound );
 extern const FString strip_quotes( const FString &str );
 extern const FString strip_apostrophes( const FString &str );

 extern const FString dress( const FString &s, char Bound );
 extern const FString dress_quotes( const FString &s );
 extern const FString dress_apostrophes( const FString &s );
 extern const FString dress_spaces( const FString &s );

 inline FString& FString::to_upper(void)
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif
 
  lem::to_upper( str );
  calc_hash();
  return *this;
 }


 inline FString& FString::to_lower(void)
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  lem::to_lower( str );
  calc_hash();
  return *this;
 }


 inline const FString to_lower( const FString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  FString res(s);
  res.to_lower();
  return res;
 }


 inline const FString to_upper( const FString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  FString res(s);
  res.to_upper();
  return res;
 }


 inline const FString subst(
                        const FString &s,
                        const FString &mask,
                        const FString &text,
                        int nentry
                       )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  mask.Assert();
  text.Assert();
  #endif

  FString res(s);
  res.subst( mask, text, nentry );

  #if LEM_DEBUGGING==1
  res.Assert();
  #endif

  return res;
 }


 extern const FString cut_final_commas( const FString &s );
 extern const FString to_Aa( const FString &s );
 extern const FString win_to_dos( const FString &s );
 extern const FString dos_to_win( const FString &s );
 extern const FString koi8_to_dos( const FString &s );
 extern const FString dos_to_koi8( const FString &s );
 extern const FString koi8_to_win( const FString &s );
 extern const FString win_to_koi8( const FString &s );


 /***************************************************************

                  ��������� ������������

 ****************************************************************/

 inline const FString operator+( const FString& s1, const FString& s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  const int l1=s1.length();
  const int l2=s2.length();
 
  if( !l1 ) return s2;
  if( !l2 ) return s1;

  char *sum = lem::FString::Alloc( l1+l2+1 );
  sum[0]='\0';

  if( s1.c_str() )
   strcpy( sum, s1.c_str() );

  if( s2.c_str() )
   strcat( sum, s2.c_str() );

  FString res(sum,true);

  #if LEM_DEBUGGING==1
  res.Assert();
  s1.Assert();
  s2.Assert();
  #endif

  return res;
 }



 inline const FString operator+( const FString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1 = s1.length();
   if( !l1 ) return FString(s2);

  const int l2 = lem_strlen(s2);
  if( !l2 ) return s1;
 
  char *sum = lem::FString::Alloc( l1+l2+1 );
  sum[0]='\0';

  if( s1.c_str() )
   strcpy( sum, s1.c_str() );

  if( s2 )
   strcat( sum, s2 );

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return FString(sum,true);
 }



 inline const FString operator+( const FString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1 = s1.length();
  if( !l1 ) return FString(s2);
  const int l2 = lem_strlen(s2);
  if( !l2 ) return s1;
  char *sum = lem::FString::Alloc( l1+l2+1 );
  sum[0]='\0';

  if( s1.c_str() )
   lem_strcpy( sum, s1.c_str() );

  if( s2 )
   lem_strcat( sum, s2 );

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return FString(sum,true);
 }


 inline const FString operator+( const char *s1, const FString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif

  const int l1 = lem_strlen(s1);
  if( !l1  ) return s2;
  const int l2 = s2.length();
  if( !l2 ) return FString(s1);

  char *sum = lem::FString::Alloc( l1+l2+1 );
  sum[0]='\0';

  if( s1 )
   strcpy( sum, s1 );

  if( s2.c_str() )
   strcat( sum, s2.c_str() );

  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif

  return FString(sum,true);
 }


 inline const FString operator+( const FString& s1, char s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  const int l1=s1.length();
  char *sum = lem::FString::Alloc( l1+2 );
  sum[0]='\0';

  if( s1.c_str() )
   strcpy( sum, s1.c_str() );

  if( s2!='\0' )
   {
    sum[l1]=s2;
    sum[l1+1]='\0';
   }

  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif

  return FString(sum,true);
 }


 inline const FString operator+( char ch, const FString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  const int l2=s.length();
  char *sum = lem::FString::Alloc( l2+2 );

  *sum=ch;
  sum[1]='\0';

  if( !!(s.c_str()) )
   strcpy( sum, s.c_str() );

  return FString(sum,true);
 }


 /************************************************************************
   ��������� ����� ������, ��������� �� �������� ������-��������� s
   � i0-�� � ���������� nch. ���� i0<0, �� ��������������� i0=0. ����
   (i0+nch) ������, ��� ����� ������ s, ��� � ������������ ������ �����
   �������� �������������� ������ ��������.
 ************************************************************************/
 extern const FString mid( const FString &s, int I0, int nch );


 /**************************************************************************
   ������������ ������, ��������� �� �������� ������-��������� s, ������
   � ������� (������ 0) ������ nch. ���� ����� �������� ������ ������������,
   �� ��������� ����� ��������� �������������� ������� ���������� ��������.
 ***************************************************************************/
 extern const FString left( const FString &s, int NCH );

 /*****************************************************************************
   ������������ ������, ��������� �� ��������� nch �������� ������-��������� s.
   ���� ����� �������� ������ ������������, �� ��������� ����� ���������
   �������������� ������� ���������� ��������.
 ******************************************************************************/
 extern const FString right( const FString &s,  int NCH );





 inline bool find_char_in_string( char c, const char *str )
 { return !!strchr( str, c ); }


 // ***********************************************************************
 // ������������ ������ �������� ��� ������� ��������� str �� �����������
 // ��������, ������������� � ������ chs.
 // ***********************************************************************

 extern const FString remove_chars( const FString &str, const char *chs );

 // *************************************************************
 // ���������� ������, ��������� �� �������� ch, ������� ���������
 // � ������ ������ s.
 // *************************************************************
 extern const FString get_lead_chars( const FString &s, char ch );


 extern int LastDelimiter( const FString &s, const char *delimiters );


 // ***************************************************************
 // ������� '\n' � ������ ����������� � �������������� ���������,
 // ������� ������ ���������� C++ ����������� � '\n' � ��.
 // ***************************************************************
 extern const FString unpack_c( const char *Sent );


 inline bool in_quotes( const FString&s )
 { return s.length()>1 && s.front()=='"' && s.back()=='"'; }


 inline void FString::copy( const char *beg, const char *end )
 {
  if( end < beg )
   throw std::bad_alloc();

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  UnShare();
  #endif

  reserve( end-beg+1 );
  std::copy( beg, end, str );
  str[ end-beg ] = 0;
  calc_hash();
  cap=len;
 }


  // ***********************************************************
  // ����� ������� ������ ������ ���������� ���������� �����,
  // ������� ����� ��������� ��������.
  // ***********************************************************
  #if defined LEM_STRPOOL
  inline void FString::UnShare(void)
  {
   #if LEM_DEBUGGING==1
   if( ref_count!=NULL )
    {
     CheckHeapPtr(ref_count);
     LEM_CHECKIT_Z(*ref_count>0);
    }
   else
    {
     LEM_CHECKIT_Z(str==NULL);
     LEM_CHECKIT_Z(len==0);
     LEM_CHECKIT_Z(cap==0);
    } 
   #endif

   if( ref_count && *ref_count>1 )
    {
     --*ref_count;

     if( str==NULL )
      {
       cap = len = 0;
      }
     else
      {
       char *old=str;
       str=Alloc( len + 1 );
       lem_strcpy( str, old );
       cap = len;
      } 

     ref_count = new int(1);
    }
  }
  #endif

 
  // ****************************************************************
  // ������� ������ �� ������ ����������� �� 1, � ���� ������ ������
  // ���, ������ ���������.
  //
  // ****************************************************************
  #if defined LEM_STRPOOL
  inline void FString::UnRef(void)
  {
   if( ref_count )
    {
     CheckHeapPtr(ref_count);
     LEM_CHECKIT_Z(*ref_count>0);

     if( !--*ref_count )
      {
       delete ref_count;
       free(str);
      } 

     str       = NULL;
     ref_count = NULL;
    }
   else
    {
     LEM_CHECKIT_Z(str==NULL);
     LEM_CHECKIT_Z(len==0);
     LEM_CHECKIT_Z(cap==0);
     str = NULL;
     //ref_count = NULL;
    }

   len=cap=0;
  }
  #endif

   // ������� ������ - ������ �� �������������, � �������� � ������� ��
   // ���������� ������. ����� ������ ����������.
   inline void FString::clear(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif

    #if defined LEM_STRPOOL
    UnShare();
    #endif

    hash=len=0;
    if(str) *str=0;
   }


  extern FString format_str( const char *fmt, ... );

  // Cast unicode string to URL string
  class UFString;
  extern const FString encode_to_url( const UFString &str );

  inline const FString to_NULL( const FString &s )
  { return s.empty() ? FString("NULL") : dress_apostrophes(s); }


  #if defined LEM_VCL
//  extern bool operator==( const FString &s1, const AnsiString &s );
//  extern bool operator!=( const FString &s1, const AnsiString &s );
  #endif

  #if defined LEM_QT && !defined LEM_UNICODE
  extern bool operator==( const FString &s1, const QString &x ); 
  extern bool operator!=( const FString &s1, const QString &x );
  #endif
  
  #if defined LEM_WXWIDGETS && !defined LEM_UNICODE
  extern bool operator==( const FString &s1, const wxString &s );
  extern bool operator!=( const FString &s1, const wxString &s );
  #endif

  #if defined LEM_MFC
  extern bool operator==( const FString &s1, const CStringA &s );
  extern bool operator!=( const FString &s1, const CStringA &s );
  #endif

  #if !defined LEM_UNICODE
  typedef FString String;
  #endif

  extern void swap( FString &x, FString &y );
 } // end of namespace 'lem'


 namespace std
 {
  inline void swap( lem::FString &x, lem::FString &y )
  { lem::swap(x,y); }
 }

#endif
