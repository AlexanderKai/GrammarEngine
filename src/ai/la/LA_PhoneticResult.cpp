// -----------------------------------------------------------------------------
// File LA_RULE_RESULT.CPP
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
// LEM C++ library  http://www.solarix.ru
// ����� LA_PhoneticResult - ������������ ����� ������� ������������ ��������� ���
// ������������� ����-��������. ��������� ��������� ����������� ��������� �
// ������ �������� �������� ������������ �������� ����� ������������� �������
// � �������� ���������.
// -----------------------------------------------------------------------------
//
// CD->26.02.1997
// LC->30.05.2011
// --------------

#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/LA_PhoneticRule.h>

using namespace lem;
using namespace Solarix;

#if defined SOL_LOADTXT && defined SOL_COMPILER
LA_PhoneticResult::LA_PhoneticResult( Macro_Parser &txtfile, GraphGram &gram )
{ LoadTxt(txtfile,gram); }
#endif


LA_PhoneticResult::LA_PhoneticResult( const UCString &str ) : context(str)
{}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void LA_PhoneticResult::LoadTxt( Macro_Parser &txtfile, GraphGram &gram )
{
 txtfile.read_it(B_CONTEXT);
 const BethToken t = txtfile.read();
 UCString Context = t.string();

 // ��������, ��������� �� ������ ������ ������������� ���������.
 // ������ �����, ��� ������ ���� � ������� ��������.
 if( !in_quotes(Context) )
  {
   lem::Iridium::Print_Error( t, txtfile );
   gram.GetIO().merr().printf(
                              "������ ������������� ��������� [%us] � ������������ ������� ������ "
                              "���� � ������� ��������\n"
                              , Context.c_str()
                             );
   LEM_STOPIT;
  }

 Context.strip_quotes();
 context = Context;

 context.Translate(gram);
 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
bool LA_PhoneticResult::operator==( const LA_PhoneticResult& x ) const
{ return context==x.context; }
#endif
