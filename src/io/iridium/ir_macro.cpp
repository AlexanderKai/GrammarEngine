// -----------------------------------------------------------------------------
// File IR_MACRO.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// ����� IR_Macro - ��������� ��� ����������� ������ �������.
// -----------------------------------------------------------------------------
//
// CD->30.07.1997
// LC->17.02.2010
// --------------

#include <lem/conversions.h>
#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro::IR_Macro( Sol_IO &io, UTextParser &txtfile )
{
 LoadTxt(io,txtfile);
 return;
}

// *****************************************************************
// �������� ������� - � ������ Flag_name � ���������� Flag_Content
// *****************************************************************
IR_Macro::IR_Macro( const UCString &Flag_Name, const UCString &Flag_Content )
{
 head = Flag_Name;
 body = new IR_Macro_Text(Flag_Content);
 return;
}

/********************************************************************
 �������� ����������� ������� �� ���������� ������. ������ �����
 ������ ������ �� ����� �������, �� ���� ����� define ��� ��������.
*********************************************************************/
void IR_Macro::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 /*
 // ��������, �� ��������� ������
 //
 //              #define MACRO \
 //              #begin
 //              ...
 //              #end
 //
 // ����� ������ ����������� '\' ����� ����� ������� ������ ���� ������ �
 // ��������, ��� �� ������ ��������� ������������ ����������� ������
 // �������� �������.
 */

 head.LoadTxt(io,txtfile);

 const SourceState back = txtfile.tellp();
 if( txtfile.read() != Macro_Parser::t_Backslash )
  txtfile.seekp(back);
 else
  // ����������� ������ �������� ������
  txtfile.read();

 body = IR_Operator::LoadOperatorTxt(io,txtfile);
 return;
}

/*********************************************************************
 ���� ����������� ������� ����� ��� #define name xxx, �� ������ �����
 ������� ���������� ��� ���������������� ������������. ���� xxx ����
 ����� �����, �� ����������� ���������� ����� �������������, �����
 ����� ���������. ���� �� ������ ��� ��������� ��-�������, ��
 ���������� NULL.
**********************************************************************/
IR_Parser_Variable* IR_Macro::GetVariable( Sol_IO &io ) const
{
 if( !body )
  return NULL;

 IR_Parser_Variable *res=NULL;

 Collect<UFString>     ll;
 Collect<IR_Macro_Subst> subst;

 IR_Var_Table table(NULL);
 IR_Macro_Table mt;
 body->Perform( io, ll, subst, table, mt );

 if( !is_name(head.GetName().c_str()) || head.GetnArg() || ll.size()>1 )
  return NULL;

 const UFString content = !ll.empty() ? ll.front() : UFString(L"");
 int dummy;
 if( to_int(content.c_str(),&dummy) )
  res = new IR_Parser_Variable( head.GetName(), dummy, content.c_str() );
 else
  res = new IR_Parser_Variable( head.GetName(), content.c_str() );

 return res;
}

