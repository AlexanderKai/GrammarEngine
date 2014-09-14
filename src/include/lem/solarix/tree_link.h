// -----------------------------------------------------------------------------
// File TREE_LINK.H
//
// (c) by Koziev Elijah
//
// Content:
// Tree_Link class - ��������� ��������� ������ ����� ������ � ��������������
// ��������.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->10.11.2010
// --------------

#ifndef SOL_LINK__H
#define SOL_LINK__H
#pragma once

 #include <lem/quantors.h>

 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
  class OFormatter;
 }

 namespace Solarix
 {
  class SynGram;


 /*************************************************************************
  ����� ��� ����������� ������������� ������ � ��������-beth. ������
  ������ ��������� ������������ �������� ���������� � �������� ���������,
  �������������� �������� � ����� icoord � istate.
 **************************************************************************/
 class Tree_Link
 {
  private:
   int icoord;
   int istate;

  public:
   Tree_Link(void) { icoord=UNKNOWN; istate=UNKNOWN; }
   Tree_Link( int is );
   Tree_Link( int is, int ic ) { istate=is; icoord=ic; }

   #if defined SOL_LOADTXT
   Tree_Link( lem::Iridium::Macro_Parser &txtfile, const SynGram &gram );
   #endif

   inline int GetCoord(void) const { return icoord; }
   inline int GetState(void) const { return istate; }

   inline bool Is_Undefined(void) const
   { return istate==UNKNOWN || istate==ANY_STATE; }

   inline bool operator!=( const Tree_Link bl ) const { return !operator==(bl); }

   inline bool operator==( const Tree_Link& bl ) const
   {
    if( icoord==UNKNOWN || istate==UNKNOWN )
     return false; // ���� ����� ������ �� ����������.

    if( icoord==ANY_STATE || bl.icoord==ANY_STATE )
     return true;

    if( icoord==UNKNOWN_STATE )
     return bl.icoord==UNKNOWN_STATE;

    return icoord==bl.icoord && istate==bl.istate;
   }

   inline bool operator<( const Tree_Link& bl ) const
   {
    if( icoord<bl.icoord )
     return true;

    if( icoord==bl.icoord )
     return istate<bl.istate;

    return false;
   }

   #if defined SOL_LOADTXT
   bool LoadTxt( lem::Iridium::Macro_Parser &txtfile, const SynGram &gram );
   #endif

   void Print( lem::OFormatter &txtfile, const SynGram &gram ) const;

   #if defined SOL_SAVETXT
   void SaveTxt( lem::OFormatter &txtfile, const SynGram &gram ) const;
   #endif
 };

 } // namespace 'Solarix'

#endif
