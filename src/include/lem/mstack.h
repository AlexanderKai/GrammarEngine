// -----------------------------------------------------------------------------
// File MSTACK.H
//
// (c) Koziev Elijah
//
// Content:
// ������ MStack - ��������� ���� '����' ��� ���������� ��� ��� ���������,
// ������� ����� ���� ��������� ����������� ������� ������� memcpy, �� ���� ��
// ���������� ����� � ������������ ���������� ������.
// -----------------------------------------------------------------------------
//
// CD->06.10.1994
// LC->11.02.2006
// --------------

#ifndef LEM_M_STACK__H
#define LEM_M_STACK__H
#pragma once

 #include <lem/containers.h>

 namespace lem
 {

 template<class ITEM> class MStack : public MCollect<ITEM>
 {
  public:
   MStack(void):MCollect<ITEM>() {}

   inline const ITEM pop(void)
   {
    LEM_CHECKIT_Z(!empty());
    const ITEM x = back();
    ReduceBy(1);
    return x;
   }

   // ***********************************************
   // ����� ������� ND ��������� ��������� �� �����.
   // ***********************************************
   inline void drop( int ND )
   {
    LEM_CHECKIT_Z(ND>=0);
    ReduceBy(ND);
    return;
   }

   // ***********************************************
   // ���������� �������� �� ������� �����.
   // ***********************************************
   inline void push( const ITEM& item )
   {
    push_back(item);
    return;
   }

   //***********************************************************
   // ���������� ������ �� �������, ��������� �� depth �������
   // �� ��������. ���� depth=0, �� - ������ �� ��������.
   //***********************************************************
   inline ITEM& top( int depth=0 )
   {
    LEM_CHECKIT_Z(n-1-depth>=0);
    return container[n-1-depth];
   }

   inline const ITEM& top( int depth=0 ) const
   {
    LEM_CHECKIT_Z( n-1-depth>=0 );
    return container[n-1-depth];
   }
 };

 } // end of namespace 'lem'

#endif
