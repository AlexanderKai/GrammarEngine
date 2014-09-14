// LC->16.04.2010

#include <lem/streams.h>
#include <lem/conversions.h>
#include <lem/afstring.h>

using namespace lem;


static int my_eqi( const char *s1, const char *s2 )
{
 while( *s1 && *s2 )
  if( tolower(*s1)!=tolower(*s2) )
   {
    return -1;
   }
  else
   { s1++; s2++; }          

 return *s1-*s2;
}


FString::FString( const std::string& s )
{
 cap = len = CastSizeToInt(s.length());

 if( len )
  {
   str=Alloc(len+1);
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   strcpy( str, s.c_str() );
   calc_hash();
  }
 else
  {
   // ���� �������� = NULL, �� ��������������� ������ ������.
   str=NULL;

   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif

   hash=0;
  }

 return;
}



// ************************************************************
// ����������� ����������� - ������ ���������� �� ���� �����
// ************************************************************
FString::FString( const FString& s1, const FString& s2 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 s2.Assert();
 #endif

 cap = len = s1.len + s2.len;

 if( len )
  {
   str=Alloc( len+1 );
   *str=0;

   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif

   if( !s1.empty() )
    strcpy( str, s1.str );

   if( !s2.empty() )
    strcat( str, s2.str );

   calc_hash_only();
  }
 else
  {
   str=NULL;
   hash=0;
   #if defined LEM_STRPOOL
   ref_count = NULL;
   #endif
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}


// ************************************************************
// ����������� ����������� - ������ ���������� �� ���� �����
// ************************************************************
FString::FString( const FString& s1, const FString& s2, const FString& s3 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 s2.Assert();
 s3.Assert();
 #endif

 cap = len = s1.len + s2.len + s3.len;

 if( len )
  {
   str=Alloc( len+1 );
   *str=0; 

   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif

   if( !s1.empty() )
    strcpy( str, s1.str );

   if( !s2.empty() )
    strcat( str, s2.str );

   if( !s3.empty() )
    strcat( str, s3.str );

   calc_hash_only();
  }
 else
  {
   str=NULL;
   hash=0;
   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return;
}



 FString::FString( const wchar_t *uStr )
 {
  if( !uStr || !*uStr )
   {
    str=NULL;
    #if defined LEM_STRPOOL
    ref_count=NULL;
    #endif
    hash=cap=len=0;
    return;
   }

  len=CastSizeToInt(wcslen(uStr));
  str=Alloc( len+1 );

  #if LEM_DEBUGGING==1
  if(!str)
   throw std::bad_alloc();
  #endif

  #if defined LEM_STRPOOL
  ref_count = new int(1);
  #endif

  cap=len;
  lem_strcpy( str, uStr );
  calc_hash();

  #if LEM_DEBUGGING==1
  Assert();
  #endif

  return;
 }



// ******************************************************
// ������� ������ ������ nch � ��������� ��������� ch.
// ******************************************************
FString::FString( size_type nTime, char c )
{
 if( nTime<=0 )
  {
   str=NULL;
   #if defined LEM_STRPOOL
   ref_count = NULL;
   #endif
   hash=len=cap=0;
  }
 else
  {
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   str = Alloc( nTime+1 );
   #if LEM_DEBUGGING==1
   if(!str)
    throw std::bad_alloc();
   #endif
   for( size_type i=0; i<nTime; i++ )
    str[i] = c;

   str[nTime]='\0';
   cap=len=CastSizeToInt(nTime);
   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}

/*
#if defined LEM_VCL
FString::FString( const AnsiString &s )
{
 Init(s.c_str());
 return;
}
#endif
*/

#if defined LEM_QT && !defined LEM_UNICODE
FString::FString( const QString &x )
{
 Init(s.c_str());
 return;
}
#endif
  
#if defined LEM_WXWIDGETS && !defined LEM_UNICODE
FString::FString( const wxString &s )
{
 Init(s.c_str());
 return;
}
#endif


#if defined LEM_MFC
FString::FString( const CStringA &s )
{ Init((const char*)s); }
#endif


// Reduce string length to new_len.
void FString::ShrinkTo( int new_len )
{
 LEM_CHECKIT_Z(new_len>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif
 if( new_len<len && len )
  {
   str[new_len]=0;
   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


FString& FString::operator=( const char *s )
{
 #if defined LEM_STRPOOL
 if( !s || !*s )
  {
   hash='\0';
   len=0;
   if( str )
    {
     UnShare();
     *str=0;
    }

   return *this;
  }

 UnShare();

 if( !ref_count )
  ref_count = new int(1);

 len=lem_strlen(s);
 if( cap<len )
  {
   // ������ ���� ������ ������� ���, ����� ���������� ����� ������.
   str=Realloc( str, len+1 );
   cap=len;
  }

 lem_strcpy( str, s );
 calc_hash_only();
 #else

 if( !s || !*s )
  {
//    free_z(str); // �� ������ ������ �������� ��������� �� ���� ������.
   hash='\0';
   len=0;

   if( str )
    *str=0;

   return *this;
  }

 len=CastSizeToInt(strlen(s));
 if( cap<len )
  {
   // ������ ���� ������ ������� ���, ����� ���������� ����� ������.
   str=Realloc( str, len+1 );
   cap=len;
  }

 strcpy( str, s );
 calc_hash_only();
 #endif

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}



FString& FString::operator=( char ch )
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
    
   str = Alloc( sizeof(char)*2 );
   ref_count = new int(1);

   if(!str)
    throw std::bad_alloc();
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
  }
 #endif

 cap=1;
 *str=ch;
 str[1]='\0';
 calc_hash();

 return *this;
}


#if defined LEM_VCL
//FString& FString::operator=( const AnsiString &s )
//{ return operator=(s.c_str()); }
#endif

#if defined LEM_QT && !defined LEM_UNICODE
FString& FString::operator=( const QString &x )
{ return operator=(s.c_str()); }
#endif
  
#if defined LEM_WXWIDGETS && !defined LEM_UNICODE
FString& FString::operator=( const wxString &s )
{ return operator=(s.c_str()); }
#endif

#if defined LEM_MFC
FString& FString::operator=( const CStringA &s )
{ return operator=((const char*)s); }
#endif


// ***********************************************************
 // ���� ������ s �� ������, �� ��������� � �� ����� ������.
 // ���� �� ����� ������ ��� ���� �����, �� �� �� �����������.
 // ***********************************************************

FString& FString::add_sp(void)
{ 
 if( length() && last_char()!=' ' )
  operator+=(' ');

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


const FString lem::add_sp( const FString& s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res=s;
 res.add_sp();
 return res;
}



FString& FString::add_nl(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( length() && last_char()!='\n' )
  operator+=('\n');

 return *this;
}



const FString lem::add_nl( const FString& s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res(s);
 res.add_nl();
 return res;
}


const FString lem::add_spaces( const FString& s, int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif
  
 FString res(s);
 res.add_spaces(n);
 return res;
}





// ******************************************************************
// ������ ��� ������ ������ ����� �� �������� ������, � �����������
// ���� str �������� NULL. � ��������� ������� ��� ������������, �
// ����� ������� ������ ���������� �������� ������ � �������� ����
// ������ ������� �����.
// ******************************************************************

void FString::re_clear(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( !str )
  {
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   str=Alloc( 1 );
   *str = 0;
   calc_hash();
   cap=0;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return;
}


FString& FString::trim(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem_trim(str);
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif
 
 return *this;
}


const FString lem::trim( const FString &s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res(s);
 res.trim();

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 return res;
}


// *********************************************************
// ��������� ������� ����� ����� ������ ����� n.
// *********************************************************
FString& FString::expand_to( int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l = length();
 if( n>l )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   for( int i=n-l-1; i>=0; i-- )
    Add_Dirty(' ');

   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return *this;
}


const FString lem::expand_to( const FString &s, int n )
{
 LEM_CHECKIT_Z(n>0);

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res(s);
 res.expand_to( n );

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 return res;
}


const FString lem::remove_chars( const FString &str, const FString &chs )
{
 #if LEM_DEBUGGING==1
 str.Assert();
 chs.Assert();
 #endif

 FString res=str;
 lem_remove_chars( res.ptr(), chs.c_str() );
 res.calc_hash();

 #if LEM_DEBUGGING==1
 str.Assert();
 chs.Assert();
 #endif

 return res;
}

const FString lem::remove_char( const FString &str, char chs )
{
 #if LEM_DEBUGGING==1
 str.Assert();
 #endif

 FString res=str;
 lem_remove_char( res.ptr(), chs );
 res.calc_hash();

 #if LEM_DEBUGGING==1
 str.Assert();
 #endif
 return res;
}


FString& FString::strip( char Bound )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( len>=2 && str && *str==Bound && str[len-1]==Bound )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif
   memmove( str, str+1, len-2 );
   str[len-2]='\0';
   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::strip_quotes(void)
{ return strip( (char)'"' ); }


FString& FString::strip_apostrophes(void)
{ return strip( (char)'\'' ); }


const FString lem::strip( const FString &fs, char Bound )
{
 FString res=fs;
 res.strip(Bound);
 return res;
}


const FString lem::strip_quotes( const FString &str )
{ return strip( str, (char)'"' ); }


const FString lem::strip_apostrophes( const FString &str )
{ return strip( str, (char)'\'' ); }


FString& FString::dress( char Bound )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 FString m = *this;
 (*this) = FString(Bound) + m + FString(Bound);

 #if LEM_DEBUGGING==1
 Assert();
 #endif
  
 return *this;
}


FString& FString::dress_quotes(void)
{ return dress( '"' ); }


FString& FString::dress_apostrophes(void)
{ return dress( '\'' ); }


FString& FString::dress_spaces(void)
{ return dress( ' ' ); }



const FString lem::dress( const FString &s, char Bound )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif
 
 return FString(Bound) + s + FString(Bound);
}


const FString lem::dress_quotes( const FString &s )
{ return dress( s, char('"') ); }


const FString lem::dress_apostrophes( const FString &s )
{ return dress( s, char('\'') ); }


const FString lem::dress_spaces( const FString &s )
{ return dress( s, char(' ') ); }


const FString lem::cut_final_commas( const FString &s )
{
 FString res=s;
 res.cut_final_commas();
 return res;
}


const FString lem::to_Aa( const FString &s )
{
 FString res=s;
 res.to_Aa();
 return res;
}


FString& FString::dos_to_win(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::dos_to_win( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::dos_to_koi8(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::dos_to_koi8( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}



FString& FString::win_to_dos(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::win_to_dos( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif
 
 return *this;
}


FString& FString::koi8_to_dos(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::koi8_to_dos( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::koi8_to_win(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::koi8_to_win( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::win_to_koi8(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 lem::win_to_koi8( str );
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}



const FString lem::win_to_dos( const FString &s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res = s;
 res.win_to_dos();
 return res;
}


const FString lem::dos_to_win( const FString &s )
{
 FString res = s;
 res.dos_to_win();
 return res;
}


const FString lem::koi8_to_dos( const FString &s )
{
 FString res = s;
 res.koi8_to_dos();
 return res;
}


const FString lem::dos_to_koi8( const FString &s )
{
 FString res = s;
 res.dos_to_koi8();
 return res;
}


const FString lem::koi8_to_win( const FString &s )
{
 FString res = s;
 res.koi8_to_win();
 return res;
}


const FString lem::win_to_koi8( const FString &s )
{
 FString res = s;
 res.win_to_koi8();
 return res;
}



FString& FString::operator=( const wchar_t *s )
{
 if( !s || !*s )
  {
   hash='\0';
   len=0;
   if( str )
    {
     #if defined LEM_STRPOOL
     UnShare();
     #endif

     *str=0;
    }
   return *this;
  }

 #if defined LEM_STRPOOL
 UnShare();
 if( !ref_count )
  ref_count = new int(1);
 #endif 

 len=CastSizeToInt(wcslen(s));
 if( cap<len )
  {
   // ������ ���� ������ ������� ���, ����� ���������� ����� ������.
   str=Realloc( str, len+1 );
   cap=len;
  }

 lem_strcpy( str, s );
 calc_hash_only();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}

 /***************************************************************

                  ��������� ������������

 ****************************************************************/

const FString operator+( const FString& s1, const FString& s2 )
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
  lem_strcpy( sum, s1.c_str() );

 if( s2.c_str() )
  lem_strcat( sum, s2.c_str() );

 FString res(sum,true);

 #if LEM_DEBUGGING==1
 res.Assert();
 s1.Assert();
 s2.Assert();
 #endif

 return res;
}



const FString operator+( const FString& s1, const char *s2 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 #endif

 const int l1 = s1.length();
 if( !l1 ) return FString(s2);

 const int l2 = strlen(s2);

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



const FString operator+( const FString& s1, const wchar_t *s2 )
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



const FString operator+( const char *s1, const FString &s2 )
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
  lem_strcpy( sum, s1 );

 if( s2.c_str() )
  lem_strcat( sum, s2.c_str() );

 #if LEM_DEBUGGING==1
 s2.Assert();
 #endif
 return FString(sum,true);
}


const FString operator+( const FString& s1, char s2 )
{
 #if LEM_DEBUGGING==1
 s1.Assert();
 #endif

 const int l1=s1.length();
 char *sum = lem::FString::Alloc( l1+2 );
 sum[0]='\0';

 if( s1.c_str() )
  lem_strcpy( sum, s1.c_str() );

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


const FString operator+( char ch, const FString& s )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 const int l2=s.length();
 char *sum = lem::FString::Alloc( l2+2 );

 sum[0]=ch;
 sum[1]='\0';

 if( !!(s.c_str()) )
  strcpy( sum, s.c_str() );

 return FString(sum,true);
}


// ***********************************************************************

FString& FString::operator+=( const FString& s )
{
 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif

 if( s.empty() )
  return *this;

 const int l=length(), sl=s.length();

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    *str='\0';
  }

 strcat( str, s.str );

 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif

 return *this;
}



FString& FString::Add_Dirty( const FString& s )
{
 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif

 if( s.empty() )
  return *this;

 const int l=length(), sl=s.length();
 #if defined LEM_STRPOOL
 UnShare();
 #endif 

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 lem_strcat( str, s.str );
 len += s.len;

 #if LEM_DEBUGGING==1
 Assert();
 s.Assert();
 #endif
  
 return *this;
}


FString& FString::operator+=( const char *s )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l=length(), sl = lem_strlen(s);

 if( !sl )
  return *this;


 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 lem_strcat( str, s );

 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::Add_Dirty( const char *s )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l=length();
 const int sl = lem_strlen(s);
 if( !sl ) return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif
 
 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 lem_strcat( str, s );
 len += sl;

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::operator+=( const wchar_t *s )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l=length();
 const int sl = lem_strlen(s);
 if( !sl ) return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif 

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 lem_strcat( str, s );
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 calc_hash();
 return *this;
}


FString& FString::Add_Dirty( const wchar_t *s )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l=length();
 const int sl = lem_strlen(s);
 if( !sl ) return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < (l+sl) )
  {
   cap = 2*(l+sl+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }

   if( !l )
    str[0]='\0';
  }

 lem_strcat( str, s );
 len += sl;

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


FString& FString::operator+=( char ch )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( !ch )
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < len+1 )
  {
   cap += (len+8);
   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }
  }

 str[len]=ch;
 str[len+1]='\0';

 #if LEM_DEBUGGING==1
 Assert();
 #endif
 calc_hash();

 return *this;
}



FString& FString::Add_Dirty( char ch )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( ch=='\0' )
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( cap < len+1 )
  {
   cap += (len+8);

   if( !str )
    {
     str = Alloc( cap+1 );
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     str = Realloc( str, cap+1 );
    }
  }

 str[len]=ch;
 str[len+1]='\0';
 len++;

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}

 /**************************************************************

                   ��������� �������

 **************************************************************/

 /****************************************************************
   � ��������� ������� ����������� ������, ������ ������������.
   ���� ������� ����� �� �������� [0,�����_������), �� ������ ��
   ���������� (��� �� ���, � ����).
 ****************************************************************/

void FString::insert( int pos, char ch )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( pos<=len )
  {
   #if defined LEM_STRPOOL
   UnShare();

   if( ref_count==NULL )
    ref_count = new int(1);
   #endif

   // ������ ����������� ������ ������.
   // ���� ��� ����� � ����� ������?
   if( cap < len+1 )
    {
     // ��� - ���������.
     cap += (len+8);
     str=Realloc( str, cap+1 );
     if( !len )
      *str=0;
    }

   // �������� ����� ������ ������ �� ������� �������.
   if( len )
    {
     memmove( str+pos+1, str+pos, len-pos+1 );
     str[pos]=ch;
    }
   else
    {
     *str=ch;
     str[1]=0;
    } 

   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return;
}

/*********************************************************************
 �������� ������� �� ��������� �������, ������ ����������.
 ���� ������� ��� ��������� [0,�����_������), �� ������ �� ����������.
**********************************************************************/
void FString::remove( int pos )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif 
 
 if( pos == len-1 )
  str[pos]=0;
 else if( pos<len )
  lem_strcpy( str+pos, str+pos+1 );

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 calc_hash();
 return;
}

/******************************************************************
  ������� ������ �� i ��������, ����� reduce(0) �� ������ ������.
  ��� ������ �� ������� ������ ������ �� ����������.
******************************************************************/
FString& FString::reduce( int i )
{
 LEM_CHECKIT_Z(i>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 int l=length();
 int term_pos=l-i;

 if( term_pos>l )
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 str[term_pos]='\0';
 calc_hash();

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 return *this;
}


/************************************************************************
  ��������� ����� ������, ��������� �� �������� ������-��������� s
  � i0-�� � ���������� nch. ���� i0<0, �� ��������������� i0=0. ����
  (i0+nch) ������, ��� ����� ������ s, ��� � ������������ ������ �����
  �������� �������������� ������ ��������.
************************************************************************/
const FString lem::mid( const FString &s, int I0, int nch )
{
 LEM_CHECKIT_Z(nch>=0);

 if( nch<=0 || I0<0 || I0>=s.length() )
  return lem::FString();

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res(nch,0);
 if( nch>=0 )
  {
   const int i0 = I0<0 ? 0 : I0;
   const int l=s.length();

   if( i0>=l )
    return res;

   for( int i=0; i<nch && (i+i0)<l; i++ )
    {
     res.ptr()[i] = s[i+i0];
     res.ptr()[i+1] = '\0';
    }
  }

 res.calc_hash();
 return res;
}


/**************************************************************************
  ������������ ������, ��������� �� �������� ������-��������� s, ������
  � ������� (������ 0) ������ nch. ���� ����� �������� ������ ������������,
  �� ��������� ����� ��������� �������������� ������� ���������� ��������.
***************************************************************************/
const FString lem::left( const FString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 if( NCH<=0 )
  return lem::FString();

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res(NCH,'\0');

 if( NCH>0 )
  {
   const int l=s.length();
   const int nch = NCH>l ? l : NCH;

   for( int i=nch-1; i>=0; i-- )
    res.ptr()[i] = s[i];

   res.ptr()[nch] = '\0';
  }

 res.calc_hash();
 return res;
}


/*****************************************************************************
  ������������ ������, ��������� �� ��������� nch �������� ������-��������� s.
  ���� ����� �������� ������ ������������, �� ��������� ����� ���������
  �������������� ������� ���������� ��������.
******************************************************************************/
const FString lem::right( const FString &s, int NCH )
{
 LEM_CHECKIT_Z(NCH>=0);

 if( NCH<=0 )
  return lem::FString();

 #if LEM_DEBUGGING==1
 s.Assert();
 #endif
 FString res(NCH,'\0');
 if( NCH>0 )
  {
   const int l=s.length();
   const int nch = NCH>l ? l : NCH;

   int i0=l-nch;
   for( int i=0; i<nch; i++ )
    res.ptr()[i] = s[i+i0];

   res.ptr()[nch] = '\0';
  }

 res.calc_hash();
 return res;
}


// ********************************************************************
// ����� ������ ������������� �� n �� ���� ���������� � ����� ������
// ��������.
// ********************************************************************
FString& FString::add_spaces( int n )
{
 LEM_CHECKIT_Z(n>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int l = length();
 const int nn = n - l;

 // ���� ��� ��������?
 if( nn>0 )
  {
   for( int i=0; i<nn; i++ )
    Add_Dirty( static_cast<char>(' ') );

   calc_hash();
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif
 return *this;
}



 // *************************************************
 // �������� mask � ������ s �������� �� text.
 // nentry - ����� ��������� ����� � �������� �����.
 // *************************************************

FString& FString::subst(
                        const FString &mask,
                        const FString &text,
                        int nentry
                       )
{
 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 const int istart = search( mask, nentry );

 if( istart==UNKNOWN )
  return *this;

 // ����� ����� ������ istart
 const FString left = lem::left( *this, istart );

 // ����� ������
 const FString right = lem::right( *this, length()-mask.length()-istart );

 // ��������� �������� �� 3� ������.
 (*this) = FString(left,text,right);
 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 return *this;
}


// ***************************************************
// ������ ������� ��������� ������ mask �� text.
// ***************************************************
FString& FString::subst_all( const FString &mask, const FString &text )
{
 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 if( !str || !*str || !mask.str || !*mask.str )
  // ��� ������ ������ ������ �� ������.
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 if( mask.length()>=text.length() )
  {
   // ��� ��� ��� ������ ����� ������ �� �������������, �� ����� ���������
   // ����������� ����� ������� ���������...
   int icur=0;
   char first = *mask.str;
   int mask_l = mask.length();
   int text_l = text.length();

   while( str[icur] )
    if( str[icur]== first )
     {
      // �����, ��� ��������� ������ ������. ��������� ������� ����� ���������?
      bool match=true;
      for( int i=1; i<mask_l; i++ )
       {
        if( !str[icur+i] || str[icur+i]!=mask.str[i] )
         {
          match=false;
          break; 
         }
       }

      if( match )
       {
        // ����� ������ ����������. ��������� ����� ������...
        for( int i=0; i<text_l; i++ )
         str[icur++] = text.str[i];
         
        // �������� ���������, ���� ����� ������ ������ �����������. 
        if( mask_l>text_l )
         {
          int i_src = icur+mask_l-text_l;
          int i_dst = icur; 
          while( str[i_src] )
           {
            str[i_dst++] = str[i_src++];
           }
          str[i_dst]=0; 
         }
       }
      else
       icur++;   
     }
    else
     icur++;
   calc_hash();
  }
 else
  { 
   int istart=0;
   while( length() )
    {
     istart = search_from( mask, istart );
   
     if( istart==UNKNOWN )
      return *this;

     // ����� ����� ������ istart
//      const FString left = lem::left( *this, istart );

     // ����� ������
     const FString right = lem::right( *this, length()-mask.length()-istart );

      // ��������� �������� �� 3� ������.
//      (*this) = left + text + right;
     reserve( istart+text.length()+right.length()+2 );

//      (*this) = left;
     trancate_to(istart);

     Add_Dirty(text);
     Add_Dirty(right);
     calc_hash();
  
     istart += text.length();
    }
  }

 #if LEM_DEBUGGING==1
 Assert();
 mask.Assert();
 text.Assert();
 #endif

 return *this;
}


FString& FString::subst_all( char old_ch, char new_ch )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 int l=length();
 for( int i=0; i<l; i++ )
  if( str[i]==old_ch )
   str[i] = new_ch;

 calc_hash();
 return *this;
}


// *********************************************************************************
// ������ ���� �������� �� ������ (������ ������� ���� - ��� ������� - ��� ������;
// ������ ������� - �� ��� ������).
// *********************************************************************************

FString& FString::subst_all( const std::vector< std::pair<FString,FString> > &macros )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( macros.empty() ) return *this;

 int istart=0;
 while( istart < length() )
  {
   bool found=false;

   // ���� ������, ������� � ������� istart, �������� ������� ������ � istart
   int istart_min=length();
   int i_mask=UNKNOWN;
   for( Container::size_type i=0; i<macros.size(); i++ )
    {
     int istart0 = search_from( macros[i].first.c_str(), istart );
  
     if( istart0!=UNKNOWN )
      {
       found=true;

       if( istart0 < istart_min )
        {
         istart_min=istart0;
         i_mask = CastSizeToInt(i); 
        }
      }
    }
  
   if( !found )
    return *this;
    
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   const FString& a = macros[i_mask].first;
   const FString& b = macros[i_mask].second;

   #if LEM_DEBUGGING==1
   a.Assert();
   b.Assert();
   #endif

   // ����� ����� ������ istart
//    const FString left = lem::left( *this, istart );

   // ��������� �������� �� 3� ������.
   if( macros[i_mask].second.length() <= macros[i_mask].first.length() )
    {
     // ����� ����������� ����� ������ ���������� - ����� ���������
     // ����� ������� ������.
     memcpy( str+istart_min, b.c_str(), b.length() );
     memmove(
             str+istart_min+b.length(),
             str+istart_min+a.length(),
             len-istart_min-a.length()+1
            );
     len -= (a.length()-b.length());
    }
   else
    {
     // ����� ������
     const FString right = lem::right( *this, length()-a.length()-istart_min );

//    (*this) = left + macros[i_mask].second + right;

     reserve( istart_min+b.length()+right.length()+1 );
     trancate_to(istart_min);
//    (*this) = left;
     Add_Dirty(b);
     Add_Dirty(right);
    }

   istart = istart_min;
  }

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 calc_hash_only();

 return *this;
}

// *********************************************************************************
// ���������� ���������� ��������� - ������� ����������� ������ �������� � �������
// ������ ������ ��������. � �������, ����� ������� ����� ����� ����, �������� $aaa,
// �� ���� ������ ������ ��������, ����� ����������� �������� ����� ����������
// ������� � ������.
// *********************************************************************************
FString& FString::subst_all(
                            const std::vector< std::pair<FString,FString> > &macros,
                            const std::set<char> &first_chars 
                           )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 int istart=0;
 while( istart < length() )
  {
   bool found=false;
   int istart_min=length();

   // ���� ������� ����� �������, � ������� ����������� �������.
   typedef std::set<char>::const_iterator IT;
   for( IT ic=first_chars.begin(); ic!=first_chars.end(); ic++ )
    {
     int is = search_from( *ic, istart );

     if( is!=UNKNOWN )
      {
       istart_min = std::min( istart_min, is );
       found=true;
      }
    }

   if( !found )
    // �������� �� �������
    return *this;

   #if defined LEM_STRPOOL
   UnShare();
   #endif

   istart = istart_min;

   // ���� ����� ������, ������� � ������� istart. ���������, ��� ������ ������   
   // ������� ��� ���������, ��� ��� ���� �� ������� ������� (� ������� istart+1).
   found=false;
   int i_mask=UNKNOWN;
   for( Container::size_type i=0; i<macros.size(); i++ )
    {
//      const char *S1 = str+istart;
//      const char *S2 = macros[i].first.c_str();
     if( !memcmp( str+istart+1, macros[i].first.c_str()+1, macros[i].first.length()-1 ) )
      {
       i_mask = CastSizeToInt(i);
       found = true;
      }  
    }
   
   if( found )
    {
     const FString& a = macros[i_mask].first;
     const FString& b = macros[i_mask].second;
     #if LEM_DEBUGGING==1
     a.Assert();
     b.Assert(); 
     #endif

     // ��������� �������� �� 3� ������.
/*
      if( macros[i_mask].second.length() <= macros[i_mask].first.length() )
       {
        // ����� ����������� ����� ������ ���������� - ����� ���������
        // ����� ������� ������.
        memcpy( str+istart_min, b.c_str(), b.length()*sizeof(char) );
        memmove(
                str+istart_min+b.length(),
                str+istart_min+a.length(),
                sizeof(char)*(len-istart_min-b.length()+1)
               );
        len -= (a.length()-b.length());
       }
      else
*/
      {
       // ����� ������
       const FString right = lem::right( *this, length()-a.length()-istart_min );
  
       reserve( istart_min+b.length()+right.length()+1 );
       trancate_to(istart_min);
       Add_Dirty(b);
       Add_Dirty(right);
      }

     istart += b.length();
    }  
   else
    {
     istart++;
    } 
  }

 calc_hash_only();

 return *this;
}

FString& FString::cut_final_commas(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 // ������� ������� �� ����� ������?
 int n_comma=0;

 for( int i=length()-1; i>=0; i-- )
  if( str[i]!=',' )
   break;
  else
   n_comma++;

 // ������ ������� ������ �� n_comma ��������.
 if( n_comma )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   reduce( n_comma );
  }

 return *this;
}


void FString::LoadBin( Stream &bin )
{
 #if defined LEM_STRPOOL
 UnShare();
 #endif

 bin.rd( this );
 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


void FString::SaveBin( Stream &bin ) const
{
 bin.wr( this );
 #if LEM_DEBUGGING==1
 Assert();
 #endif
}


// *********************************************************************
// �������� � ������� � ���� 'Aaaaa', �� ���� ������ ����� - ���������,
// ��� ��������� - ���������.
// *********************************************************************
FString& FString::to_Aa(void)
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( !length() )
  return *this;

 #if defined LEM_STRPOOL
 UnShare();
 #endif

 to_lower();

 char buf[2]= { str[0], '\0' };
 lem::to_upper(buf);

 str[0] = buf[0];
 calc_hash();

 return *this;
}

const FString lem::remove_chars( const FString &str, const char *chs )
{
 #if LEM_DEBUGGING==1
 str.Assert();
 #endif

 FString res;
 res.reserve( str.length() );

 if( !str.empty() )
  {
   int i=0;
   while( str[i]!='\0' )
    {
     if( !find_char_in_string( str[i], chs ) )
      res.Add_Dirty( str[i] );
     i++;
    }

   res.calc_hash();
  }

 return res;
}


// *************************************************************
// ���������� ������, ��������� �� �������� ch, ������� ���������
// � ������ ������ s.
// *************************************************************
const FString lem::get_lead_chars( const FString &s, char ch )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 FString res;

 const int l=s.length();
 for( int i=0; i<l; i++ )
  if( s[i]!=ch )
   break;
  else
   res += ch;
 return res;
}



int lem::LastDelimiter( const FString &s, const char *delimiters )
{
 #if LEM_DEBUGGING==1
 s.Assert();
 #endif

 // From end char...
 for( int i=s.length()-1; i>=0; i-- )
  // Is it delimiter?
  if( lem_find( delimiters, s[i] )!=UNKNOWN )
   // Yes - return index of char.
   return i;

 // Nothing matches.
 return UNKNOWN;
}



// ***************************************************************
// ������� '\n' � ������ ����������� � �������������� ���������,
// ������� ������ ���������� C++ ����������� � '\n' � ��.
// ***************************************************************
const FString lem::unpack_c( const char *Sent )
{
 FString res;

 if( !(Sent) )
  return res;

 int i=0;
 while( Sent[i]!=0 )
  {
   switch(Sent[i])
   {
    case '\n':  res+='\\'; res+='n'; break;
    case '\t':  res+='\\'; res+='t'; break;
    case '\r':   res+='\\'; res+='r'; break;
    case '\f': res+='\\'; res+='f'; break;
    case '\b': res+='\\'; res+='b'; break;
    default: res+=Sent[i]; break;
   }

   i++;
  }

 return res;
}


// ********************************************************
// ������ ��������� �� new_len �������� (���� ��� ��������)
// ********************************************************
FString& FString::trancate_to( int new_len )
{
 LEM_CHECKIT_Z(new_len>=0);

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( new_len>=0 && new_len<len )
  {
   len=new_len;
   str[len]=0;
   calc_hash();
  }

 return *this;
}

// ******************************************************************
// �� ������ ���������� � ������������ ������� ������� � ������� from
// �� (�������) ������� upto. ������������ ������ �� ���� ��.
// ��� ����, ����� �������� ������ [from,upto], ��������� mid(...)
// ******************************************************************
FString& FString::cut( int from, int upto )
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( from>=0 && upto<len && from<upto )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   memmove( str+from, str+upto, len-upto+1 );
   calc_hash();
  }

 return *this;
}


FString& FString::reserve( lem::FString::size_type new_cap )
{
 #if defined LEM_64
 LEM_CHECKIT_Z( new_cap!=lem::uint64_max );
 #elif defined LEM_32
 LEM_CHECKIT_Z( new_cap!=lem::uint32_max );
 #else 
  #error Unknown platform
 #endif

 #if LEM_DEBUGGING==1
 Assert();
 #endif

 if( cap < CastSizeToInt(new_cap) )
  {
   #if defined LEM_STRPOOL
   UnShare();
   #endif

   if( !cap )
    {
     // ���� ������ ������...
     str = Alloc( CastSizeToInt(new_cap)+1 );
     *str=0;
     #if defined LEM_STRPOOL
     ref_count = new int(1);
     #endif
    }
   else
    {
     // Increase the capacity of memory allocated for string, so it will be
     // able to store up to new_cap chars.
     str = Realloc( str, CastSizeToInt(new_cap)+1 );
    }

   cap=new_cap;
  }

 return *this; 
}

// ************************************************
// ����� ������� ������ ������.
// @retval ������ ���������� �������
// @retval UNKNOWN ���� ������ �� ������
// ************************************************
int FString::find_last_of( char ch ) const
{
 if( empty() )
  return UNKNOWN;

 int pos=len-1; 
 for( int i=pos; i>=0; i-- )
  if( str[i]==ch )
   return i;

 return UNKNOWN;
}


// ***********************************************
// ������ ��������� ��� ����� ��������?
// ***********************************************
bool FString::eqi( const FString &x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 x.Assert();
 #endif

 if( x.len!=len )
  return false;

 if( empty() )
  return true;

 #if defined LEM_LINUX
 return !strcasecmp( str, x.str );
 #elif defined LEM_WINDOWS
 return !stricmp( str, x.str );
 #else
 return !my_eqi( str, x.str );
 #endif
}


bool FString::eqi( const char *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif
 
 if( !x || !*x )
  return !len;

 #if defined LEM_LINUX
 return !strcasecmp( str, x );
 #elif defined LEM_WINDOWS
 return !stricmp( str, x );
 #else
 return !my_eqi( str, x );
 #endif
}


void FString::Init( const char *s )
{
 cap = len = lem_strlen(s);

 if( len )
  {
   str=Alloc( len+1 );
   #if defined LEM_STRPOOL
   ref_count = new int(1);
   #endif
   strcpy( str, s );
   calc_hash();
  }
 else
  {
   // ���� �������� = NULL, �� ��������������� ������ ������.
   str=NULL;

   #if defined LEM_STRPOOL
   ref_count=NULL;
   #endif

   hash=0;
  }

 return;
}

FString& FString::operator+=( const std::string &s )
{ return operator+=(FString(s)); }


#if defined LEM_VCL
//FString& FString::operator+=( const AnsiString &s )
//{ return operator+=(s.c_str()); }
#endif

#if defined LEM_QT && !defined LEM_UNICODE
FString& FString::operator+=( const QString &x )
{ return operator+=(s.c_str()); }
#endif
  
#if defined LEM_WXWIDGETS && !defined LEM_UNICODE
FString& FString::operator+=( const wxString &s )
{ return operator+=(s.c_str()); }
#endif

#if defined LEM_MFC
FString& FString::operator+=( const CStringA &s )
{ return operator+=( (const char*)s ); }
#endif


#if defined LEM_VCL
//bool lem::operator==( const lem::FString &s1, const AnsiString &s )
//{ return s1.length()==s.Length() && lem::operator==(s1,s.c_str()); }

//bool lem::operator!=( const lem::FString &s1, const AnsiString &s )
//{ return s1.length()!=s.Length() || !lem::operator==(s1,s.c_str()); }
#endif

#if defined LEM_QT && !defined LEM_UNICODE
bool lem::operator==( const lem::FString &s1, const QString &x )
{ return s1.length()==s.length() && lem::operator==(s1,s.c_str()); }

bool lem::operator!=( const lem::FString &s1, const QString &x )
{ return s1.length()!=s.length() || !lem::operator==(s1,s.c_str()); }
#endif
  
#if defined LEM_WXWIDGETS && !defined LEM_UNICODE
bool lem::operator==( const lem::FString &s1, const wxString &s )
{ return s1.length()==s.length() && lem::operator==(s1,s.c_str()); }

bool lem::operator!=( const lem::FString &s1, const wxString &s )
{ return s1.length()!=s.length() || !lem::operator==(s1,s.c_str()); }
#endif

#if defined LEM_MFC
bool lem::operator==( const lem::FString &s1, const CStringA &s )
{ return s1.length()==s.GetLength() && lem::operator==(s1,(const char*)s); }

bool lem::operator!=( const lem::FString &s1, const CStringA &s )
{ return s1.length()!=s.GetLength() || !lem::operator==(s1,(const char*)s); }
#endif



 // ************************************************************
 // ������ text �������� ��������� x, ������ x ������ ����
 // � ������ ������ ������ text.
 //
 // ��������:
 //
 //       text =     ABCDEFG
 //       x    =     ABC
 //
 // ************************************************************

bool FString::eq_beg( const FString &x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 x.Assert(); 
 #endif

 if( x.len>len )
  return false;

 if( x.len==len )
  return operator==(*this,x);

 const int lx = x.len;
 for( int i=0; i<lx; i++ )
  if( x.str[i]!=str[i] )
   return false;

 return true;
}



bool FString::eq_beg( const char *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>length() )
  return false;

 if( lx==length() )
  return operator==(*this,x);
 for( int i=0; i<lx; i++ )
  if( x[i]!=str[i] )
   return false;

 return true;
}


bool FString::eq_begi( const char *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>length() )
  return false;

 for( int i=0; i<lx; i++ )
  if( lem::to_lower(x[i] )!=lem::to_lower( str[i] ) )
   return false;

 return true;
}


bool FString::eq_beg( const wchar_t *x ) const
{
 #if LEM_DEBUGGING==1
 Assert();
 #endif

 const int lx = lem_strlen(x);
 if( lx>len )
  return false;

 if( lx==len )
  return operator==(*this,x);

 for( int i=0; i<lx; i++ )
  if( char(x[i])!=str[i] )
   return false;

 return true;
}


void lem::swap( lem::FString &x, lem::FString &y )
{
 std::swap( x.str, y.str );

 #if defined LEM_STRPOOL
 std::swap( x.ref_count, y.ref_count );
 #endif

 std::swap( x.len, y.len );
 std::swap( x.cap, y.cap );
 std::swap( x.hash, y.hash );
 
 return;
}

int lem::FString::ToInt(void) const
{ return lem::to_int(c_str()); }

bool lem::FString::ToBool(void) const
{ return lem::to_bool(c_str()); }
