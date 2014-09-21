// -----------------------------------------------------------------------------
// File LEM_CYCS.H
//
// (c) Koziev Elijah
//
// Content:
// ������ CyclicStack - ��������� ���� '����' ��� ���������� ��� ���
// ���������. ���������� �� ������������� ������ lem::Stack ���, ��� ��� ����
// ��������� ����������� ������ �����. ��� ������ ����� ����������� ���������
// ��������� ��� �������, ����� �������� ������������� ����������� ��������
// �� ������ ��� ��������� � ������ �����. ��� �������� ����������� ���
// ������������ ����������� ��������� � ���������� �� ���� ����, ��� ������
// ������� �������� � ������ ����������� ����������, �� ���� ������� �������
// �������, ���������� ����������, � ���������� ����������.
// -----------------------------------------------------------------------------
//
// CD->02.04.1999
// LC->12.10.2005
// --------------

#ifndef LEM_CYCLICSTACK__H
#define LEM_CYCLICSTACK__H
#pragma once

 #include <lem/stack.h>

 namespace lem
 {
  template<class ITEM> class CyclicStack : public Stack<ITEM>
  {
   private:
    int maxn; // ������������ ���������� ����� �������� ���������.
    int i0;   // ���������� ������ �������� � ������� �������� '0'.

    // ��� �������� �������������.
    const ITEM pop(void);
    void drop( int ND );
    void push_back( const ITEM &x );

   public:
    #if defined __MINGW__ || defined LEM_GNUC
    typedef typename Stack<ITEM>::size_type size_type;
    
    inline size_type size(void) const { return Stack<ITEM>::size(); }  
    #endif    

   public:
    CyclicStack():Stack<ITEM>()
    { maxn=1; i0=0; }

    inline void SetMax( int nItems ) { maxn=nItems; }


    // #####################################################################
    // �������� ����� ���������� ������ ���� ����������� � �������� ������,
    // ��� ��� �� ����� ���������� ����������.
    // #####################################################################
    inline ITEM& operator[]( int i )
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& operator[]( int i ) const
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& get( int i ) const
    { LEM_CHECKIT_Z(i>=0 && i<size()); return Stack<ITEM>::operator[]((i+i0)%size()); }

    inline const ITEM& back(void) const
    { LEM_CHECKIT_Z(size()>0); return Stack<ITEM>::operator[]((size()-1+i0)%size()); }

    inline       ITEM& back(void)
    { LEM_CHECKIT_Z(size()>0); return Stack<ITEM>::operator[]((size()-1+i0)%size()); }

    // ***********************************************
    // ���������� �������� �� ������� �����.
    // ***********************************************
    inline void push( const ITEM& item )
    {
     if( size() >= maxn )
      {
       // --------------------------------------------------------------------
       // ���� ������� �� ������ ����� ������ � �������� �������� � �����.
       // ������ ������ ����������� �� ������ �������, ��� ������� � �������
       // ������� �������� ������ ������������ �� 1 ��� � ������:
       //
       //  ��������� 555:
       //
       //  ����:
       //       000 111 222 333 444
       //        |               |
       //        ������� ������� ������� �������
       //
       //       555 111 222 333 444
       //        |   |
       //        |   ����� �������
       //        |
       //        ������� �������
       //
       // --------------------------------------------------------------------
       Stack<ITEM>::operator[](i0++) = item;
      }
     else
      Stack<ITEM>::push_back(item);

     return;
    }

    //***********************************************************
    // ���������� ������ �� �������, ��������� �� depth �������
    // �� ��������. ���� depth=0, �� - ������ �� ��������.
    //***********************************************************
    inline ITEM& top( int depth=0 )
    {
     LEM_CHECKIT_Z(size()-1-depth>=0);
     return Stack<ITEM>::get( (size()-1-depth+i0)%size() );
    }

    inline const ITEM& top( int depth=0 ) const
    {
     LEM_CHECKIT_Z(size()-1-depth>=0);
     return Stack<ITEM>::get( (size()-1-depth+i0)%size() );
    }
  };

 } // end of namespace 'lem'

#endif
// -------------------------- End Of File [LEM_CYCS.H] -------------------------
