// -----------------------------------------------------------------------------
// File LA_PhoneticCondictor.CPP
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
// LEM C++ library  http://www.solarix.ru
// ����� LA_PhoneticCondictor - �������� ����� ������� ������������ ��������� ���
// ������������� ����-��������. ���������� �� ��������� �������� ��������� ���
// ������������ ���������, ������� ������ �������� ��������� ������������ ������
// ������� ��������.
// -----------------------------------------------------------------------------
//
// CD->26.02.1997
// LC->28.05.2011
// --------------

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbols.h>
#include <lem/solarix/Symbol.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LA_PhoneticRule.h>

using namespace lem;
using namespace Solarix;


LA_PhoneticCondictor::LA_PhoneticCondictor(void) { loc=UNLOCATED; }

LA_PhoneticCondictor::LA_PhoneticCondictor( const UCString &str, bool IsPrefix, bool IsAffix )
 : context(str)
{
 if( IsPrefix) loc=PREFIX;
 else if( IsAffix ) loc=AFFIX;
 else loc=UNLOCATED;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
LA_PhoneticCondictor::LA_PhoneticCondictor( Macro_Parser &txtfile, GraphGram &gram )
{ LoadTxt(txtfile,gram); }
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_PhoneticCondictor::LoadTxt( Macro_Parser &txtfile, GraphGram &gram )
{
 txtfile.read_it(B_CONTEXT);
 const BethToken t = txtfile.read();

 context = t.string();

 context.strip_quotes();

 // ������ ������ �� ������ ������ ���� �������� ��� ����� - �� ����
 // ���� ��������� ����� �������. ����������� ����� �����������
 // ���������� ������ '*'.
 //
 // � ���� ������� ����������� ���������� ������� $ - ��� ���������� ��
 // ���������� ��������: "$aaa" - ���������, "aaa$" - ������.

 if( context.front()==L'$' )
  {
   loc = PREFIX;
   context.Remove(0);
  }
 else if( context.back()==L'$' )
  {
   loc = AFFIX;
   context.Remove( context.length()-1 );
  }
 else
  loc = UNLOCATED; 


 const int cl=context.length();
 for( int i=0; i<cl; i++ )
  {
   const wchar_t ch = context[i];

   if( ch==L'*' )
    continue;

   const Word_Coord wc = gram.FindSymbol(ch);
   if( wc.GetEntry()==UNKNOWN )
    {
     lem::Iridium::Print_Error( t, txtfile );
     gram.GetIO().merr().printf(
                            "Condictor [%us] contains unknown symbol (neither "
                            "char nor quantor '*')\n"
                            , context.c_str()
                           );
     throw E_ParserError();
    }

   context.set( i, gram.entries()[wc.GetEntry()].GetName() );
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool LA_PhoneticCondictor::operator==( const LA_PhoneticCondictor& x ) const
{ return context==x.context && loc==x.loc; }
#endif


#if defined SOL_CAA
bool LA_PhoneticCondictor::DoesMatch( const wchar_t *example ) const
{
 // ����� �� ����������, ��� ��� �������� ������������ ��������
 // �������������� ��������� ��� ������� �� ������ � ������ �����������
 // ������� ����� � ��������� ������� �� �������.

 const wchar_t *Condition = context.c_str();
 while( *Condition )
  {
   if( *Condition=='*' )
    {
     Condition++;
     example++;
     continue; // ������� ����������� � ����� ���������.
    }

   if( *example != *Condition )
    return false;

   example++;
   Condition++;
  }

 return true;
}
#endif

#if defined SOL_CAA
bool LA_PhoneticCondictor::Can_Subst( const UCString &lex ) const
{
 if( context.length() > lex.length() )
  return false;

 switch( loc )
 {
  case PREFIX:
   // ������ ����� lex ������ ��������� condictor
   return !memcmp(
                  lex.c_str(),
                  context.c_str(),
                  context.length()*sizeof(*lex.c_str())
                 );

  case AFFIX:
   // ����� ����� lex ������ ��������� condictor
   return !memcmp(
                  lex.c_str()+lex.length()-context.length(),
                  context.c_str(),
                  context.length()*sizeof(*lex.c_str())
                 );

  case UNLOCATED: LEM_STOPIT;
 }

 return false;
}
#endif

