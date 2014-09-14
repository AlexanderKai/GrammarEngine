// -----------------------------------------------------------------------------
// File IR_MACRO_TEXT.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// ����� IR_Macro_Text - ��������������� ������������� �����.
// -----------------------------------------------------------------------------
//
// CD->24.04.1998
// LC->17.02.2010
// -------------

#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Text::IR_Macro_Text( const UCString &x )
{
 push_back(x);
 return;
}

/***********************************************************************
 ��������� ����������� ���� ������� �� ���������� �����. ����� ��������,
 ��� ���������� ���� ������� �� �������������� ������-����
 ������������������, �� ���� ����������� ������ ������������ as is.
************************************************************************/
void IR_Macro_Text::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 // ��������� ������� �� ����� ������. ������� '\' - ������� �����������
 // �� ��������� ������.

 bool on_next_line=false;
 while( !txtfile.eof() )
  {
   const UToken t = txtfile.read();
   if( t.eol() )
    {
     if( on_next_line )
      {
       on_next_line=false;
       continue;
      }
     else
      break;
    }

   if( t==Macro_Parser::t_Backslash )
    {
     // ����������� ������������� ����� ������� ����� ���������� ��
     // ��������� ������.
     on_next_line=true;
     const UToken t=txtfile.read();
     if( t.GetToken() != LEM_SOURCE_EOL )
      {
       Print_Error( io, t, txtfile );
       io.merr().printf( "����� ������� \\ � �������� ������� ������ ���� �� ������\n" );
       throw E_ParserError();
      }

     continue;
    }

   if( !t.empty() )
    push_back( t.string() );

   on_next_line = false;
  }

 return;
}

/*****************************************************************
 ������� ����������� ���� ������� - ��������� ��� ��������������.
 ��������� - ����������� ������� � ������ list, ������� ��������
 subst ����� ��������� � ������� ������� ������������ ������.
******************************************************************/
void IR_Macro_Text::Perform(
                            Sol_IO &io,
                            Collect<UFString> &list,
                            const Collect<IR_Macro_Subst> &subst,
                            const IR_Var_Table &/*table*/,
                            const IR_Macro_Table &/*mt*/
                           ) const
{
 const int nput = size();
 for( int iput=0; iput<nput; iput++ )
  {
   const UCString &put = at(iput);

   bool found=false;
   int isubst;
   for( isubst=CastSizeToInt(subst.size())-1; isubst>=0; isubst-- )
    if( (found = (subst[isubst].GetName() == put)) )
     break;

   if( found )
    {
     const IR_Macro_Subst &z = subst[isubst];
     const int ns=z.size();
     for( int iadd=0; iadd<ns; iadd++ )
      list.push_back( z[iadd].c_str() );
    }
   else
    list.push_back(put.c_str());
  }

 return;
}
