// -----------------------------------------------------------------------------
// File IR_VAR_TABLE.CPP
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
// ����� IR_Var_Table - ������� ���������� ��� ������ �������.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->22.01.2009
// --------------

#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;


IR_Var_Table::IR_Var_Table( const IR_Var_Table *Prev )
{ prev = Prev; }


IR_Var_Table::~IR_Var_Table(void)
{ ZAP_A(*this); }


/*********************************************************************
 ����� ���������� � �������� ������. � ������ ������ ������������
 ������ ����������, ����� UNKNOWN.
**********************************************************************/
int IR_Var_Table::Find( const UCString& name ) const
{
 if( name.empty() )
  return UNKNOWN;

 for( Container::size_type i=0; i<size(); i++ )
  if( at(i)->GetName()==name )
   return i;

 // ���� ���� �������� �� ���������� ������� � �������, �� ���������
 // ����� � ���.
 return prev==NULL ? UNKNOWN : prev->Find(name);
}



const IR_Parser_Variable* IR_Var_Table::Seek( const UCString& name ) const
{
 if( name.empty() )
  return NULL;

 for( Container::size_type i=0; i<size(); i++ )
  if( at(i)->GetName()==name )
   return at(i);

 return prev==NULL ? NULL : prev->Seek(name);
}



/*******************************************************************
 �������� ���������� � �������� ������ �� �������.
 ��������������� ������ ���� ������, ��������� ������� ��
 ���������������.
********************************************************************/
void IR_Var_Table::Remove( const UCString &name )
{
 for( Container::size_type i=0; i<size(); i++ )
  if( at(i)->GetName()==name )
   {
    delete operator[](i);
    MCollect<IR_Parser_Variable*>::Remove( i );
    return;
   }

 return;
}

// ---------------------- End Of File [IR_VAR_TABLE.CPP] -----------------------
