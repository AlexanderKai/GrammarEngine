// -----------------------------------------------------------------------------
// File IR_MACRO_TABLE.CPP
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
// ����� IR_Macro_Table - ������� �������� ��� �������������.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->22.01.2009
// --------------

#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Macro_Table::IR_Macro_Table(void)
{}

IR_Macro_Table::~IR_Macro_Table(void)
{ ZAP_A(*this); }


/****************************************************
 ���������� ������� � ������. ���� ������ � ����� ��
 ������ ��� ���������, �� �������� ��� ���� �� �����.
*****************************************************/
void IR_Macro_Table::Add( IR_Macro *to_add )
{
 // ���� ����� ���������� ��� ����, ������ ������������������ ��.
 for( Container::size_type i=0; i<size(); i++ )
  if( at(i)->GetHead().GetName()==to_add->GetHead().GetName() )
   {
    delete operator[](i);
    operator[](i)=to_add;
    return;
   }

 // ��������� ������...
 push_back(to_add);
 return;
}

/*******************************************************************
 �������� ����� � ������� ������ � ������ name, ���������� ������
 �������� ������� � ������ �����, ���� UNKNOWN ��� ��������� ������.
********************************************************************/
int IR_Macro_Table::Find( const UCString& name ) const
{
 if( name.empty() )
  return UNKNOWN;

 for( Container::size_type i=0; i<size(); i++ )
  if( (*this)[i]->GetHead().GetName()==name )
   return i;

 return UNKNOWN;
}

// ------------------- End Of File [IR_MACRO_TABLE.CPP] ------------------------
