#ifndef LEM_UFSTRING__H
#define LEM_UFSTRING__H
#pragma once

// -----------------------------------------------------------------------------
// File UFSTRING.H
//
// (c) by Elijah Koziev   all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// UFString UNICODE mutable strings template class.
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
// 21.01.2007 - ��������� ������ eqi - ��������� ��� ����� ��������.
//
// 26.02.2007 - ���������� ������ � ������������ ������, �������� �����
//              �����������.
// 01.07.2007 - ����������� UFString( char ) ������ explicit.
//
// 28.09.2007 - ��������� ��� � UnRef ��� LEM_STRPOOLING
// 28.09.2007 - encode_chars_to_html_2 ������������� � encode_chars_to_xml
// 16.11.2007 - ��������� ��� � ::UnRef
// 21.03.2008 - ��������� ��������� swap
// 18.07.2008 - ��������� ������ Alloc � Free
// 01.02.2009 - �������� ����� Realloc
// -----------------------------------------------------------------------------
//
// CD->02.07.1996
// LC->23.04.2011
// --------------

#include <lem/config.h>

#include <stdlib.h>
#include <string>
#include <vector>
#include <set>

#include <lem/strings.h>

#if defined LEM_QT
#include <QString>
#endif

#if defined LEM_ICU
 #include <icu/include/unicode/unistr.h>
#endif

#if LEM_DEBUGGING==1 && defined LEM_MSC
#include <crtdbg.h>
#endif

#undef min
#undef max

namespace lem
{
  extern int lem_strlen( const char* );
  extern int lem_strlen( const wchar_t* );

  extern wchar_t* to_lower( wchar_t *s );
  extern wchar_t* to_upper( wchar_t *s );

  extern int to_int( const wchar_t *s );
  extern bool to_bool( const wchar_t *s );

  class Stream;

 class UFString
 {
  friend void swap( UFString &x, UFString &y );

  public:
   // Types - ����������� � STL::basic_string
   typedef std::char_traits<wchar_t> traits_type;
   typedef wchar_t                   value_type;
   typedef size_t                    size_type;

   typedef wchar_t*                  pointer;
   typedef const wchar_t*            const_pointer;
   typedef wchar_t*                  iterator;
   typedef const wchar_t*            const_iterator;

   typedef unsigned char             hash_type;

   // ��������� - ������������ ����� ������. ������� ��� �������������
   // � ������� BaseCString, ��� ������������ ����������� ������������
   // �� ������ ����������.
   enum { max_len = INT_MAX };//boost::integer_traits<size_type>::const_max-1 };

  private:
   #if LEM_DEBUGGING==1
   Guardian guard1;
   #endif

   wchar_t *str; // ��������� �� ���� � ������������ ������.

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

   static wchar_t static_zero;

   inline void SetContens( wchar_t *s )
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
   // ****************************************************************
   #if defined LEM_STRPOOL
   void UnRef(void);
   #endif

   void Init( const wchar_t *s );

   #if defined LEM_QT
   void Init( const QString & s );
   #endif

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

   //! ��������� ����� ������ ��������, ����������� � ������������ ����� ������� UFString
   // ���������� ������ ����� ��� ����������� ����� �� �������� ������������� UFString(wchar_t*,bool)
   static wchar_t* Alloc( size_type total_length )
   { 
    return (wchar_t*)malloc( sizeof(wchar_t)*total_length );
   }

   static wchar_t* Realloc( wchar_t *Ptr, int total_length )
   { 
    return (wchar_t*)realloc( Ptr, sizeof(wchar_t)*total_length );
   }

   static void Free( wchar_t *ptr ) { free(ptr); }

  public:
   UFString( void );
   explicit UFString( const char *astr );
   UFString( const wchar_t *ustr );


   // ********************************************************************
   // ����� ������������, �� �������� ��� ����������� �����������:
   // ���� ������, �� ������� ��������� ��������, ����� ����������������
   // ��� �������� ����� ������, ��� ��� �� ����������� ���������
   // ������ ����� ������������ ����. �������� get_control ���������� ��
   // ������������, � ����� ������ ��� ��������������� ��������� �������
   // ������������.
   // ********************************************************************
   UFString( wchar_t *str, bool get_control );

   // ************************************************************
   // �������� ������, ��������� �� ������ ��������� ������� ch.
   // ************************************************************
   explicit UFString( wchar_t Ch );

   // ***************************************************
   // ��������� ������, ��������� �� nTime �������� ch.
   // ***************************************************
   UFString( size_type nTime, wchar_t ch );

   // *************************************************************
   // ��������� ������ �� �������� �� beg �� end-1,
   // ������������� ���� ����������� � ���������� �������������.
   // *************************************************************
   UFString( const wchar_t *beg, const wchar_t *end );

   UFString( const UFString& s );

   UFString( const std::wstring &str );

   // ������������ ������������
   UFString( const UFString& s1, const UFString& s2 );
   UFString( const UFString& s1, const UFString& s2, const UFString& s3 );

   #if defined LEM_DOT_NET
   explicit UFString( System::String *s );
   #endif

   #if defined LEM_VCL
//   explicit UFString( const WideString &s );
   #endif

   #if defined LEM_QT && defined LEM_UNICODE
   explicit UFString( const QString &x );
   #endif
  
   #if defined LEM_WXWIDGETS && defined LEM_UNICODE
   explicit UFString( const wxString &s );
   #endif

   #if defined LEM_MFC
   explicit UFString( const CStringW &s );
   #endif

   #if defined LEM_ICU
   explicit UFString( const UnicodeString &s );
   #endif

   ~UFString(void);

   UFString& operator=( const char *s );
   UFString& operator=( const wchar_t *s );
   UFString& operator=( const UFString& s );
   UFString& operator=( const std::wstring& s );
   UFString& operator=( wchar_t ch );

   #if defined LEM_QT
   UFString& operator=( const QString & ustr );
   #endif

   #if defined LEM_DOT_NET
   UFString& operator=( System::String *s );
   #endif

   #if defined LEM_VCL
//   UFString& operator=( const WideString &s );
   #endif

  
   #if defined LEM_WXWIDGETS && defined LEM_UNICODE
   UFString& operator=( const wxString &s );
   #endif

   #if defined LEM_MFC
   UFString& operator=( const CStringW &s );
   #endif

   #if defined LEM_ICU 
   UFString& operator=( const UnicodeString &s );
   #endif

   void copy( const wchar_t *beg, const wchar_t *end );

   // **************************
   // Accessing the C string.
   // **************************

   // Do NOT use it: for internal usage only!
   inline wchar_t* ptr(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    #if defined LEM_STRPOOL
    UnShare();
    #endif
    return str;
   }

   inline const wchar_t* c_str(void) const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif

    return !(str) ? (const wchar_t*)L"\0" : (const wchar_t*)str;
   }


   inline wchar_t front() const
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    return str ? *str : 0;
   }

   inline wchar_t back() const
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
   void calc_hash(void);

   // ���������� ���-���� ������ - ����� �� �����������
   void calc_hash_only(void);

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
   inline wchar_t operator[]( int i ) const
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
   wchar_t last_char( int i=0 ) const;

   // Returns the index of the rightmost character that matches any
   // character in the delimiters string.
   int LastDelimiter( const wchar_t *delimiters ) const;


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

   void set( int i, wchar_t ch );

   // ������� ������ - ������ �� �������������, � �������� � ������� ��
   // ���������� ������. ����� ������ ����������.
   void clear(void);

   void set_dir( int i, wchar_t ch );

   UFString& reduce( int i );
   void insert( int pos, wchar_t ch );
   void remove( int pos );

   // Reduce string length to new_len.
   void ShrinkTo( int new_len );

   inline void Insert( int pos, wchar_t ch ) { insert(pos,ch); }
   inline void Remove( int pos ) { remove(pos); }

   UFString& operator+=( const UFString &s );
   UFString& operator+=( const char *s    );
   UFString& operator+=( const wchar_t *s );
   UFString& operator+=( wchar_t ch );
   UFString& operator+=( const std::wstring &s );

   #if defined LEM_DOT_NET
   UFString& operator+=( System::String *s );
   #endif

   #if defined LEM_VCL
//   UFString& operator+=( const WideString &s );
   #endif

   #if defined LEM_MFC
   UFString& operator+=( const CStringW &s );
   #endif

   #if defined LEM_QT && defined LEM_UNICODE
   UFString& operator+=( const QString &x );
   #endif
  
   #if defined LEM_WXWIDGETS && defined LEM_UNICODE
   UFString& operator+=( const wxString &s );
   #endif

   #if defined LEM_ICU 
   UFString& operator+=( const UnicodeString &s );
   #endif

   UFString& Add_Dirty( const UFString &s );
   UFString& Add_Dirty( const char *s );
   UFString& Add_Dirty( const wchar_t *s );
   UFString& Add_Dirty( wchar_t ch );
   UFString& Add_Dirty_Chars( const wchar_t *s, size_t count );

   int count( wchar_t ch ) const;
   int find( wchar_t ch ) const;
   int find_last_of( wchar_t ch ) const;
   int rfind( wchar_t ch ) const { return find_last_of(ch); }

   int search( wchar_t to_find, int nentry=1 ) const;
   int search( const UFString &to_find, int nentry=1 ) const;
   int search( const char *to_find, int nentry=1 ) const;
   int search( const wchar_t *to_find, int nentry=1 ) const;

   // ����� ��������� ��� ����� ��������
   int searchi( const UFString &to_find, int nentry=1 ) const;

   int search_from( wchar_t to_find, int start_pos ) const;
   int search_from( const UFString &to_find, int start_pos ) const;
   int search_from( const char *to_find, int start_pos ) const;
   int search_from( const wchar_t *to_find, int start_pos ) const;

   int searchi_from( const UFString &to_find, int start_pos ) const;

   // ��������� �� ������ ������ � ��������� ���������. ������� 'i' - ��� ����� ��������
   bool eq_beg( const UFString &to_find ) const;
   bool eq_begi( const UFString &to_find ) const;
   bool eq_beg( const wchar_t* to_find ) const;
   bool eq_begi( const wchar_t* to_find ) const;
   bool eq_beg( const char* to_find ) const;

   // ��������� �� ����� ������ � ��������� ���������
   bool eq_end( const wchar_t* to_find ) const;
   bool eq_endi( const wchar_t* to_find ) const;
   bool eq_end( const UFString & to_find ) const;
   bool eq_endi( const UFString & to_find ) const;

   // ***********************************************
   // ������ ��������� ��� ����� ��������?
   // ***********************************************
   bool eqi( const UFString &x ) const;
   bool eqi( const wchar_t *x ) const;

   // ********************************************
   // ������ ��������� ������ �� ������ ������
   // ********************************************
   UFString& subst(
                   const UFString &mask,
                   const UFString &text,
                   int nentry=1
                  );

   // �������� ��� ��������� ������ mask �� ������ text.
   UFString& subst_all( const UFString &mask, const UFString &text, bool case_sensitive=true );
   UFString& subst_all( const std::vector< std::pair<UFString,UFString> > &macros );
   UFString& subst_all( wchar_t old_ch, wchar_t new_ch );
   UFString& subst_all(
                       const std::vector< std::pair<UFString,UFString> > &macros,
                       const std::set<wchar_t> &first_chars 
                      );

   // ���������� � �������� ��������
   UFString& to_upper(void);

   // ���������� � ������� ��������
   UFString& to_lower(void);

   // ������� ������������� ������
   UFString& normalize_diaktrics(void);


   UFString& to_Aa(void);

   // ***********************************************************************
   // ����������� ������� ��������, ����������� ������. ���� �� ������ ������
   // ��������� �� ���������, �� ������ �� ��������.
   // ***********************************************************************
   UFString& strip( wchar_t Bound );
   UFString& strip_quotes(void);
   UFString& strip_apostrophes(void);

   UFString& dress( wchar_t Bound );
   UFString& dress_quotes(void);
   UFString& dress_apostrophes(void);
   UFString& dress_spaces(void);

   UFString& cut_final_dot(void);
   UFString& cut_final_commas(void);
   UFString& trim(void);

   UFString& add_sp(void);
   UFString& add_nl(void);
   UFString& add_spaces( int n );
   UFString& expand_to( int n );

   UFString& cut( int from, int upto );

   // *********************************************************
   // ������� ������ �� ����� ����� new_len. ���� ������ ������,
   // ��� new_len, �� ������ �� ����������.
   // *********************************************************
   UFString& trancate_to( int new_len );


   // *********************************************************
   // ������������� ����� ����� ��� �������, ��� ��� �����
   // ����������������� ������������ ���������� new_cap.
   // ���� new_cap ������ �������� �������� �������, �� ������
   // �� ����������.
   // *********************************************************
   UFString& reserve( UFString::size_type new_cap );

   // *****************************************************************
   // ���� ���������� ������ ������ � ��������� ��-�� ����������� 
   // ����� NULL, �� �������� ������ � ������������ �������� '\0'.
   // ��� ���������� ��� ��������� C'���� �������, ������� � ��������
   // ��������� �������� c-������ � ������� �� NULL.
   // *****************************************************************
   void re_clear(void);

   int    to_int(void)  const;
   bool   to_bool(void) const;

   friend bool operator==( const UFString &s1, const UFString &s2 );
   friend bool operator!=( const UFString &s1, const UFString &s2 );

   #if defined LEM_DOT_NET
   bool operator==( System::String *s ) const;
   bool operator!=( System::String *s ) const;
   #endif

   #if defined LEM_ICU
   bool operator==( const UnicodeString &s ) const;
   bool operator!=( const UnicodeString &s ) const;
   #endif

   // ��������� �������� - ������ � ���������� ������
   void SaveBin( Stream &bin ) const;
   void LoadBin( Stream &bin );

   int ToInt(void) const;
   bool ToBool(void) const;


   #if defined LEM_QT
   QString to_qt(void) const;
   #endif
  };


 // *******************************************************
 // ����������� ��� ���������� ������� ������ ������.
 // �� ����� ���� ���������� ��������� ����� NULL, ��� ���
 // ��������� � ���������� ���� �� �����.
 // *******************************************************

 inline UFString::UFString(void)
 {
  str=NULL;
  hash=cap=len=0;
  #if defined LEM_STRPOOL
  ref_count=NULL;
  #endif
  return;
 }




 inline UFString::UFString( const UFString& s )
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
    wcscpy( str, s.str );
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



 inline UFString::UFString( const wchar_t *beg, const wchar_t *end )
 {
  if( end < beg )
   throw std::bad_alloc();

  const UFString::size_type l = end-beg;
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

 inline UFString::UFString( wchar_t *Str, bool /*get_control*/ )
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


 inline UFString::UFString( const wchar_t *uStr )
 {
  if( !uStr || !*uStr )
   {
    str=NULL;
    #if defined LEM_STRPOOL
    ref_count=NULL;
    #endif
    cap=len=hash='\0';
    return;
   }

  cap=len=(int)wcslen(uStr);
  str=Alloc(len+1);

  #if LEM_DEBUGGING==1
  if(!str)
   throw std::bad_alloc();
  #endif

  #if defined LEM_STRPOOL
  ref_count = new int(1);
  #endif

  wcscpy( str, uStr );
  calc_hash();

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }

 
 // *********************************************
 // ��������� ������ �� ������ �������.
 // *********************************************

 inline UFString::UFString( wchar_t c )
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
  len=cap=1;
  return;
 }

 

 inline UFString::~UFString(void)
 {
  #if defined LEM_STRPOOL
  UnRef();
  #else
  Free(str); str=NULL; // �� ������ ������ �������� ��������� �� ���� ������.
  #endif
 }


// ***********************************************************
// ����� ������� ������ ������ ���������� ���������� �����,
// ������� ����� ��������� ��������.
// ***********************************************************
#if defined LEM_STRPOOL
inline void UFString::UnShare(void)
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
     const wchar_t *old=str;
     str=Alloc( len + 1 );
     wcscpy( str, old );
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
inline void UFString::UnRef(void)
{
 if( ref_count )
  {
   CheckHeapPtr(ref_count);
   LEM_CHECKIT_Z(*ref_count>0);

   if( !--*ref_count )
    {
     delete ref_count;
     Free(str);
    }

   ref_count=NULL;
  }
 else
  {
   LEM_CHECKIT_Z(str==NULL);
   LEM_CHECKIT_Z(len==0);
   LEM_CHECKIT_Z(cap==0);
   str = NULL;
  }

 str = NULL;
 len=cap=0;
 return;
}
#endif


inline UFString& UFString::operator=( const UFString &s )
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
   hash=cap=0;
   // ���� str � ref_count ��� �������� � //UnRef()
   return *this;
  }

 cap = s.cap;
 str = s.str;
 hash = s.hash;
 ref_count = s.ref_count;
 ++*ref_count;
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

 wcscpy( str, s.str );
 hash = s.hash;
 #endif


 #if LEM_DEBUGGING==1
 s.Assert();
 Assert();
 #endif

 return *this;
}


 inline UFString& UFString::operator=( wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif

  #if defined LEM_STRPOOL
  if( !ref_count || *ref_count==1 )
   {
    // ����� ������������ ��������� ������ ��� ���������� �������?
 
    if( !str )
     {
      str = Alloc( 2 );
      ref_count = new int(1);
      cap = 1;
     }
    else
     {
      if( !cap )
       {
        // � ������ ����� �� ���������, �������� ����� ������.
        str = Realloc( str, 2 );

        if(!str)
         throw std::bad_alloc();

        cap=1;
       }
      }

    *str=ch;
    str[1]='\0';
    calc_hash();
   }
  else
   {
    UnRef();
    
    str = Alloc( 2 );
    ref_count = new int(1);

    if(!str)
     throw std::bad_alloc();

    cap=1;
    
    *str=ch;
    str[1]='\0';
    calc_hash();
   }
  #else
  if( !cap )
   {
    // � ������ ����� �� ���������, �������� ����� ������.
    str = Realloc( str, 2 );

    #if LEM_DEBUGGING==1
    if(!str)
     throw std::bad_alloc();
    #endif

    cap=1;
   }

  *str=ch;
  str[1]='\0';
  calc_hash();
  #endif

  return *this;
 }




 inline void UFString::set( int i, wchar_t ch )
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

 inline void UFString::set_dir( int i, wchar_t ch )
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

 inline wchar_t UFString::last_char( int i ) const
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

 inline int UFString::find( wchar_t ch ) const
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

 inline int UFString::search( wchar_t ch, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, ch, nentry );
 }


 inline int UFString::count( wchar_t ch ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  int n=0;
  for( const wchar_t *p=str; p!=str+len; p++ )
   if( *p==ch )
    n++;

  return n;
 }

 /***************************************************************************
  ���������� ��������� nentry-�� ��������� ��������� [f] � ������ [s].
  ���������� ������ ������� ���������� �������. ���� ��������� ��
  ����������, ��� ����� �� ��������� � ������ ����� nentry, �� ���������� -1.
 ****************************************************************************/

 inline int UFString::search( const UFString &f, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, f.c_str(), nentry );
 }

 inline int UFString::searchi( const UFString &f, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_findi( str, f.c_str(), nentry );
 }

 inline int UFString::search( const char *to_find, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, to_find, nentry );
 }


 inline int UFString::search( const wchar_t *to_find, int nentry ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find( str, to_find, nentry );
 }



 inline int UFString::search_from( const UFString &to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find.c_str(), start_pos );
 }


 inline int UFString::searchi_from( const UFString &to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_findi_from( str, to_find.c_str(), start_pos );
 }


 inline int UFString::search_from( const char *to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 inline int UFString::search_from( const wchar_t *to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 inline int UFString::search_from( wchar_t to_find, int start_pos ) const
 {
  #if LEM_DEBUGGING==1
  Assert();
  #endif
  return lem_find_from( str, to_find, start_pos );
 }


 extern const UFString add_sp( const UFString& s );
 extern const UFString add_nl( const UFString& s );
 extern const UFString add_spaces( const UFString& s, int n );
 extern const UFString trim( const UFString &s );
 extern const UFString expand_to( const UFString &s, int n );


 /***************************************************************
                   ��������� ���������
 ****************************************************************/


 inline bool operator==( const UFString &s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  return s1.hash==s2.hash && s1.len==s2.len && lem_eq( s1.c_str(), s2.c_str() );
 }

 inline bool operator==( const UFString &s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_eq( s1.c_str(), s2 );
 }


 inline bool operator==( const UFString &s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_eq( s1.c_str(), s2 );
 }


 inline bool operator==( const char *s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_eq( s2.c_str(), s1 );
 }


 inline bool operator==( const wchar_t *s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_eq( s2.c_str(), s1 );
 }


 inline bool operator==( const UFString &s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch=='\0';

  return s.front()==ch && s[1]=='\0';
 }


 inline bool operator==( wchar_t ch, const UFString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch=='\0';

  return s[0]==ch && s[1]=='\0';
 }

 // ************************************************************************


 inline bool operator!=( const UFString &s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif

  return s1.hash!=s2.hash ||
         s1.len!=s2.len ||
         lem_neq( s1.c_str(), s2.c_str() );
 }


 inline bool operator!=( const UFString &s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_neq( s1.c_str(), s2 );
 }


 inline bool operator!=( const UFString &s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_neq( s1.c_str(), s2 );
 }


 inline bool operator!=( const char *s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_neq( s1, s2.c_str() );
 }


 inline bool operator!=( const wchar_t *s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_neq( s1, s2.c_str() );
 }


 inline bool operator!=( const UFString &s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch!='\0';

  return s[0]!=ch || s[1]!='\0';
 }


 inline bool operator!=( wchar_t ch, const UFString &s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  if( s.empty() )
   return ch!='\0';

  return s[0]!=ch || s[1]!='\0';
 }

#if defined LEM_VCL
//extern bool operator==( const UFString &s1, const WideString &s );
//extern bool operator!=( const UFString &s1, const WideString &s );
#endif

#if defined LEM_QT && defined LEM_UNICODE
extern bool operator==( const UFString &s1, const QString &x );
extern bool operator!=( const UFString &s1, const QString &x );
#endif
  
#if defined LEM_WXWIDGETS && defined LEM_UNICODE
extern bool operator==( const UFString &s1, const wxString &s );
extern bool operator!=( const UFString &s1, const wxString &s );
#endif

#if defined LEM_MFC
extern bool operator==( const UFString &s1, const CStringW &s );
extern bool operator!=( const UFString &s1, const CStringW &s );
#endif

// ****************************************************************


 inline bool operator>( const UFString& s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_gt( s1.c_str(), s2.c_str() );
 }


 inline bool operator>( const UFString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_gt( s1.c_str(), s2 );
 }


 inline bool operator>( const UFString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_gt( s1.c_str(), s2 );
 }


 inline bool operator>( const char *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_gt( s2.c_str(), s1 );
 }


 inline bool operator>( const wchar_t *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_gt( s2.c_str(), s1 );
 }


 inline bool operator>( const UFString& s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  wchar_t s2[2]={ ch, '\0' };
  return lem_gt( s.c_str(), s2 );
 }


 inline bool operator>( wchar_t ch, const UFString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  wchar_t s2[2]={ ch, '\0' };
  return lem_gt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator>=( const UFString& s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_ge( s1.c_str(), s2.c_str() );
 }


 inline bool operator>=( const UFString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_ge( s1.c_str(), s2 );
 }


 inline bool operator>=( const UFString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_ge( s1.c_str(), s2 );
 }


 inline bool operator>=( const char *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_ge( s2.c_str(), s1 );
 }


 inline bool operator>=( const wchar_t *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_ge( s2.c_str(), s1 );
 }


 inline bool operator>=( const UFString& s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  wchar_t s2[2]={ ch, '\0' };
  return lem_ge( s.c_str(), s2 );
 }


 inline bool operator>=( wchar_t ch, const UFString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif

  wchar_t s2[2]={ ch, '\0' };
  return lem_ge( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator<( const UFString& s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_lt( s1.c_str(), s2.c_str() );
 }


 inline bool operator<( const UFString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_lt( s1.c_str(), s2 );
 }


 inline bool operator<( const UFString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_lt( s1.c_str(), s2 );
 }


 inline bool operator<( const char *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_lt( s2.c_str(), s1 );
 }


 inline bool operator<( const wchar_t *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_lt( s2.c_str(), s1 );
 }


 inline bool operator<( const UFString& s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  wchar_t s2[2]={ ch, '\0' };
  return lem_lt( s.c_str(), s2 );
 }


 inline bool operator<( wchar_t ch, const UFString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  wchar_t s2[2]={ ch, '\0' };
  return lem_lt( s2, s.c_str() );
 }

 // ****************************************************************


 inline bool operator<=( const UFString& s1, const UFString &s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  s2.Assert();
  #endif
  return lem_le( s1.c_str(), s2.c_str() );
 }


 inline bool operator<=( const UFString& s1, const char *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_le( s1.c_str(), s2 );
 }


 inline bool operator<=( const UFString& s1, const wchar_t *s2 )
 {
  #if LEM_DEBUGGING==1
  s1.Assert();
  #endif
  return lem_le( s1.c_str(), s2 );
 }


 inline bool operator<=( const char *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_le( s2.c_str(), s1 );
 }


 inline bool operator<=( const wchar_t *s1, const UFString& s2 )
 {
  #if LEM_DEBUGGING==1
  s2.Assert();
  #endif
  return lem_le( s2.c_str(), s1 );
 }


 inline bool operator<=( const UFString& s, wchar_t ch )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  wchar_t s2[2]={ ch, '\0' };
  return lem_le( s.c_str(), s2 );
 }


 inline bool operator<=( wchar_t ch, const UFString& s )
 {
  #if LEM_DEBUGGING==1
  s.Assert();
  #endif
  wchar_t s2[2]={ ch, '\0' };
  return lem_le( s2, s.c_str() );
 }


 inline UFString& UFString::to_upper(void)
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


 inline UFString& UFString::to_lower(void)
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


   // ***************************************
   // Recalculating the hash after changes.
   // ***************************************
   inline void UFString::calc_hash(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    hash=lem_calc_string_hash_len(str,&len);
   }

   // **************************************************
   // ���������� ���-���� ������ - ����� �� �����������
   // **************************************************
   inline void UFString::calc_hash_only(void)
   {
    #if LEM_DEBUGGING==1
    Assert();
    #endif
    hash=lem_calc_string_hash(str);
   }

 inline bool find_char_in_string( wchar_t c, const wchar_t *str )
 { return !!wcschr( str, c ); }

 inline bool in_quotes( const UFString &s )
 { return s.length()>1 && s.front()=='"' && s.back()=='"'; }

 extern const UFString to_lower( const UFString &s );
 extern const UFString to_upper( const UFString &s );
 extern const UFString subst(
                        const UFString &s,
                        const UFString &mask,
                        const UFString &text,
                        int nentry
                       );


 extern const UFString cut_final_commas( const UFString &s );
 extern const UFString to_Aa( const UFString &s );

 extern const UFString remove_chars( const UFString &str, const UFString &chs );
 extern const UFString remove_char( const UFString &str, wchar_t chs );
 extern const UFString strip( const UFString &fs, wchar_t Bound );
 extern const UFString strip_quotes( const UFString &str );
 extern const UFString strip_apostrophes( const UFString &str );
 extern const UFString dress( const UFString &s, wchar_t Bound );
 extern const UFString dress_quotes( const UFString &s );
 extern const UFString dress_apostrophes( const UFString &s );
 extern const UFString dress_spaces( const UFString &s );

 extern const UFString operator+( const UFString& s1, const UFString& s2 );
 extern const UFString operator+( const UFString& s1, const char *s2 );
 extern const UFString operator+( const UFString& s1, const wchar_t *s2 );
 extern const UFString operator+( const char *s1, const UFString &s2 );
 extern const UFString operator+( const UFString& s1, wchar_t s2 );
 extern const UFString operator+( wchar_t ch, const UFString& s );

 extern const UFString mid( const UFString &s, int I0, int nch );
 extern const UFString left( const UFString &s, int NCH );
 extern const UFString right( const UFString &s,  int NCH );

 extern const UFString remove_chars( const UFString &str, const wchar_t *chs );
 extern const UFString get_lead_chars( const UFString &s, wchar_t ch );
 extern int LastDelimiter( const UFString &s, const wchar_t *delimiters );
 extern const UFString unpack_c( const wchar_t *Sent );

 extern const UFString encode_chars_to_html( const UFString &str );
 extern const UFString encode_html_to_chars( const UFString &str );
 extern const UFString encode_chars_to_xml( const UFString &str );

 extern const UFString encode_str_to_sql( const UFString &str );

 // ������ wildcards �� ���������� �������.
 // �� ��������� (�������� supress_front_asterix) ������ ������ '*' �����������
 // �� ��������.
 extern UFString wildcards_to_regex( const UFString &str, bool supress_front_asterix=true );

 // ������ sprintf, ������ ���������� ��������� ����� UFString
 extern UFString format_str( const wchar_t *fmt, ... );

 extern const UFString to_NULL( const UFString &s );

  // ��������� ���� ����� ����� ������������ ������������ � ��������� ���������
  // ������������ ���������, 1.0 - ��������� ���������, 0.0 - ���������
  // �����������.
  extern float eq_soundex( const UFString &a, const UFString &b );

  // ��� ���������� ������ � ������� ������� ����� �������� �������
  // ����� �� 2 �����: 1) ���������� ��������, 2) ��������� ��������������� ��������
  // � ������ �� �����.
  typedef lem::UFString SoundexPattern;
  extern lem::SoundexPattern eq_soundex1( const lem::UFString &pattern );
  extern float eq_soundex2( const UFString &a, const lem::SoundexPattern &pattern );

  #if defined LEM_UNICODE
  typedef UFString String;
  #endif

  extern void swap( UFString &x, UFString &y );

 } // end of namespace 'lem'

 namespace std
 {
  #if defined LEM_BORLAND
  inline void swap( lem::UFString &x, lem::UFString &y )
  { lem::swap(x,y); }
  #else
  template<>
  inline void swap( lem::UFString &x, lem::UFString &y )
  { lem::swap(x,y); }
  #endif
 }

#endif
