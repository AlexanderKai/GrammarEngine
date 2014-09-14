// -----------------------------------------------------------------------------
// File COORD_EX.CPP
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
// SOLARIX Grammar engine
// ����� GramCoordEx - ���������� ������������� ���������� ���������� ���
// ������� ����� ������������ ����� ����-�������.
// -----------------------------------------------------------------------------
//
// CD->24.06.1996
// LC->05.09.2010
// --------------

#include <lem/solarix/coord_pair.h>

using namespace lem;
using namespace Solarix;

/******************************************************************
  ������������� ����� ������������� ������� � ������.

  � ������ ������ �������� ����� � ������ ����� ����� �� ������,
  ��� � ca. ���� ��� �� �������, �������� ����� ��������� � ������
  ����� icoord, �� �������� �������� �� ����� ��������.
*******************************************************************/
int CPE_Array::FindTwice( const GramCoordAdr& ca ) const
{
 const int ires = FindOnce(ca);
 if(ires!=UNKNOWN)
  return ires;

 for( Container::size_type i=0; i<size(); i++ )
  if( operator[](i).GetCoord().GetIndex()==ca.GetIndex() )
   return CastSizeToInt(i);

 return UNKNOWN;
}

int CPE_Array::FindOnce( const GramCoordAdr& ca ) const
{
 // ������ ������ ���������.
 for( Container::size_type i=0; i<size(); i++ )
  if( operator[](i).GetCoord()==ca )
   return CastSizeToInt(i);

 return UNKNOWN;
}

/*******************************************************
 ���������� �������������� ������������ ���� � ������.
 ���� ����� ��������, ���������� UNKNOWN.
*******************************************************/
int CPE_Array::FindOnce( const GramCoordPair& pair ) const
{
 for( Container::size_type i=0; i<size(); i++ )
  if(
     operator[](i).GetCoord()==pair.GetCoord() &&
     operator[](i).GetState()==pair.GetState()
    )
   return CastSizeToInt(i);

 return UNKNOWN;
}
