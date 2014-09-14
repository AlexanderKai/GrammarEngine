// -----------------------------------------------------------------------------
// File STRING_SET.CPP
//
// (c) Koziev Elijah
//
// Content:
// ����� UCStringSet - ��������� ��� ���������� �����. ������������ �����, ���
// ��������� ������������� �������� � ���������� ����� ��� � ����� �����.
// ������� �� ������ � ���������������!
//
// 28.09.2006 - ������� ������� ���� ��������� ����������, ����� ���������
//              � ��������� ������ ������������ ������.
// -----------------------------------------------------------------------------
//
// CD->11.12.1995
// LC->18.12.2009
// --------------

#include <lem/ucstring_functions.h>
#include <lem/oformatter.h>
#include <lem/sol_io.h>
#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/string_set.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

UCStringSet::UCStringSet(void):MCollect<UCString>()
{}

#if defined SOL_LOADTXT
UCStringSet::UCStringSet( const Sol_IO &io, Macro_Parser& txtfile )
{ LoadTxt(io,txtfile); }
#endif


UCStringSet::UCStringSet( const UCString &s )
{
 push_back( s );
 return;
}

#if defined SOL_LOADTXT
/****************************************************************************
 ��������� �� ���������� ����� ��������� ���������� �����. ���� �����
 ������ ����, �� ��� ����� ���� ���������������. ���� ���������� ����������
 ��������� ����, �� ��� ����������� � �������� ��������.
 �������:
         1. �������
         2. { ������� ������� ... ������� }

 ������ ������ ���������� ����� � ������, ���� � �������� ��������� �������
 ������ ���� �������. ������ �������� � ����� ������� ��������!
*****************************************************************************/
void UCStringSet::LoadTxt( const Sol_IO &io, Macro_Parser &txtfile )
{
 BethToken t = txtfile.read();

 if( t.GetToken()!=B_OFIGPAREN )
  {
   // ������ ������.
   push_back(t.c_str());
  }
 else
  {
   // ������ ������.
   while( !txtfile.eof() )
    {
     if( txtfile.eof() )
      {
       Print_Error(t,txtfile);
       io.merr().printf(
                        "End of file has been reached before "
                        "set of lexems completely loaded\n"
                       );
       LEM_STOPIT;
      }

     t = txtfile.read();

     if( t.GetToken()==B_CFIGPAREN )
      break;

     push_back(t.string());
     weight.push_back(1);
    }
  }

 return;
}
#endif



#if defined SOL_SAVETXT
void UCStringSet::SaveTxt( OFormatter &txtfile ) const
{
 if( size()!=1 )
  txtfile << sol_get_token(B_OFIGPAREN);

 Print(txtfile);

 if( size()!=1 )
  txtfile << sol_get_token(B_CFIGPAREN);

 return;
}
#endif


/*********************************************************************
 ��������� ������ ����������� ���������. ������ ���������� ��� ������
 ���� ��������� ������ �� ����� ���������� � ������������.
**********************************************************************/
void UCStringSet::Print( OFormatter &s ) const
{
 s.printf( "%vfE" );

 const int n=CastSizeToInt(size());
 for( int i=0; i<n; i++ )
  {
   s << get(i);

   if( i<n-1 )
    s << " "; // ��������� ����� ��������� ��������.
  }

 s.printf( "%vn" );
 return;
}

/********************************************************************
 ����� ������ � ����������� ���������. ���� ������� �������, ��
 ���������� �� ���������� ������=(0,...), ����� ������������ UNKNOWN.
*********************************************************************/
int UCStringSet::Find( const UCString& name ) const
{
 for( lem::Container::size_type i=0; i<size(); i++ )
  if( get(i)==name )
   return CastSizeToInt(i);

 return UNKNOWN;
}


int UCStringSet::FindNoCase( const UCString& name ) const
{
 for( lem::Container::size_type i=0; i<size(); i++ )
  if( get(i).eqi(name) )
   return CastSizeToInt(i);

 return UNKNOWN;
}


/***************************************************************************
 ������������ ���� �������� ������ (������������ ������ ����� � ����������
 �������������� ���������, ����� ������ ��������� ���������� �����������).
****************************************************************************/
void UCStringSet::AddList( const UCStringSet& ss )
{
 const int nss=CastSizeToInt(ss.size());
 // ��������� ����� �������� ���� ������ �� ��������� ����������
 // ��������� ������� nss.
 ReshapeBy(nss);
 for( int i=0; i<nss; i++ )
  {
   push_back(ss[i]);
   weight.push_back( ss.weight[i]);
  }

 return;
}

void UCStringSet::Add( const UCString &lexem, int w )
{
 push_back( lexem );
 weight.push_back(1);
 return;
}

/********************************************************************
 ��� ������-�������� ���������� � ���� ����������� ������, ���������
 ������� ��������� ���������.
*********************************************************************/
const UFString UCStringSet::string(void) const
{
 UFString res;
 for( lem::Container::size_type i=0; i<size(); i++ )
  {
   if(i) res += ' ';
   res += get(i).c_str();
  }

 return res;
}


bool UCStringSet::operator==( const UCStringSet &x ) const
{
 if( size()!=x.size() )
  return false;

 for( lem::Container::size_type i=0; i<size(); i++ )
  if( get(i) != x[i] )
   return false;

 return true;
}


bool UCStringSet::operator!=( const UCStringSet &x ) const
{
 if( size()!=x.size() )
  return true;

 for( lem::Container::size_type i=0; i<size(); i++ )
  if( get(i) != x[i] )
   return true;

 return false;
}


void UCStringSet::Save_Packed( lem::Stream &bin ) const
{
 uint8_t N = size();

 LEM_CHECKIT_Z( N<128 );

 bin.write( &N, 1 );
 for( const_iterator i=begin(); i!=end(); i++ )
  lem::Save_Packed( *i, bin );

 return; 
}

void UCStringSet::Load_Packed( lem::Stream &bin )
{
 uint8_t N = 0;
 bin.read( &N, 1 );
 resize( N );

 for( int i=0; i<N; i++ )
  lem::Load_Packed( &(operator[](i)), bin );

 return;
}
