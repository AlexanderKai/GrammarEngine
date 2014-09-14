// -----------------------------------------------------------------------------
// File GG_FORM.CPP
//
// (c) Koziev Elijah
//
// Content:
// ����� GG_EntryForm - ������� ������������ ������� (����������) - ������
// ���������� ���������. ��� ���������� �����. �� ��������� ����������
// ��������� �����������, �� ���� ������� GG_EntryForm �������� � ������
// GG_Entry.
// -----------------------------------------------------------------------------
//
// CD->10.08.1996
// LC->02.01.2011
// --------------

#include <lem/solarix/Symbol.h>

using namespace std;
using namespace lem;
using namespace Solarix;

/********************************************************************
 ��� �������� ���������� ���������, � ������ ��� ����� ��������������
 ���� ������ ������������ ���-��������� (Dim) � ��� ����� (Name).
*********************************************************************/
GG_EntryForm::GG_EntryForm( const CP_Array& Dim, lem::uint32_t Name )
{
 name = Name;
 copy( Dim.begin(), Dim.end(), back_inserter(dim) );
 return;
}



lem::CString GG_EntryForm::GetNameUtf8(void) const
{
 return Solarix::EncodeChar32ToUtf8(name);
}

lem::UCString GG_EntryForm::GetNameWide(void) const
{
 return Solarix::EncodeChar32ToWide(name);
}
