// -----------------------------------------------------------------------------
// File LA_PROJ_LIST.CPP
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
// ����� LA_ProjList - ������ �������� �������� ��� ����, ������������ � ����� �
// ��� �� �����. �������� ��������� ���� �������� �������� ���� ��� ������������
// ��������.
// -----------------------------------------------------------------------------
//
// CD->20.08.1997
// LC->09.06.2011
// --------------

#if defined SOL_REPORT
#include <lem/oformatter.h>
#include <lem/solarix/sg_autom.h>
#endif

#include <lem/solarix/LA_WordProjectionBuffer.h>

using namespace lem;
using namespace Solarix;


LA_ProjList::LA_ProjList(void):Collect<LA_WordProjection>()
{ Char=0; }

LA_ProjList::LA_ProjList( wchar_t ch ):Collect<LA_WordProjection>()
{ Char=ch; }

LA_ProjList::LA_ProjList( const LA_ProjList &l ):Collect<LA_WordProjection>(l)
{ Char=l.Char; }

void LA_ProjList::operator=( const LA_ProjList &l )
{
 Collect<LA_WordProjection>::operator=(l);
 Char=l.Char;
 return;
}


#if defined SOL_LOADBIN 
void LA_ProjList::LoadBin( lem::Stream &bin )
{
 bin.read(&Char,sizeof(Char));
 Collect<LA_WordProjection>::LoadBin(bin);
 return;
}
#endif

#if defined SOL_SAVEBIN
void LA_ProjList::SaveBin( lem::Stream &bin ) const
{
 bin.write(&Char,sizeof(Char));
 Collect<LA_WordProjection>::SaveBin(bin);
 return;
}
#endif


/*******************************************************************
   �������������� ��������� � ������ � ������� �������� ������� ��
 �������������, ��� ��� ���� ������������ �������� ������������ �
 ������ ������. ������� ��� ������ ������� ��������������� ��������
 ����� ������������, ��� ������� �������� �������������.

   ������� ��������, ��� ������� ����������� �������� �����������
 ������ ����� ���� ����� ������: �������� ������� ����� ������ ��
 ����� ����������.
********************************************************************/
void LA_ProjList::ReSort(void)
{
 // ������� ����������� �������� ����� ��������� ������, � �����
 // ���������� ��� ������. ��� ���������� ������������ �����.
 IntCollect index(size());
 const int N=CastSizeToInt(size());

 for( Container::size_type i=0; i<size(); i++ )
  index[i]=CastSizeToInt(i);

 // ������� ���������� �����.
 for( int gap=N/2; gap>0; gap/=2 )
  for( int i=gap; i<N; i++ )
   for( int j=i-gap; j>=0; j-=gap )
    {
     if( get( index[j+gap] ) < get( index[j] ) )
      break;

     const int dummy = index[j];
     index[j]        = index[j+gap];
     index[j+gap]    = dummy;
    }

 // �� ������������� ������ ��������� ������. ������ �����������
 // �������� ������ ���������.
 Collect<LA_WordProjection> adjust(size());
 for( Container::size_type i2=0; i2<size(); i2++ )
  adjust[i2] = get( index[i2] );

 Collect<LA_WordProjection>::operator=(adjust);
 return;
}


#if defined SOL_REPORT
void LA_ProjList::PrintInfo(
                            OFormatter &txtfile,
                            SynGram &gram
                           ) const
{
 if( empty() )
  // ����� �� �������� �������, ���������� ������ ������...
  return;

 txtfile.printf(
                "\nList of cached projections beginning with symbol [%uc]:\n"
                , Char
               );

 for( Container::size_type i=0; i<size(); i++ )
  get(CastSizeToInt(i)).PrintInfo(txtfile,gram);

 return;
}
#endif
