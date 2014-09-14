// -----------------------------------------------------------------------------
// File COORD_PAIR.H
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
// ������ GramCoordAdr, GramCoordPair - ������������ ����.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->27.04.2010
// --------------

#ifndef SOL_COORD_PAIRS__H
#define SOL_COORD_PAIRS__H
#pragma once

 #include <lem/quantors.h>
 #include <lem/containers.h>
 #include <lem/smart_pointers.h>

 #include <lem/solarix/sol_prdf.h>

 namespace lem
 {
  class OFormatter;
  namespace Iridium { class Macro_Parser; }
 }

 namespace Solarix
 {
  using lem::OFormatter;
  using lem::Iridium::Macro_Parser;
  using lem::MCollect;

  /***************************************************************
   ������������� ���������� � ������ ����������.
   ����������� ������������� ����� ������������ �� ��� �������,
   ��� �� ��������� ������������� � ��������� ����-���������.
  ****************************************************************/
  class GramCoordAdr
  {
   private:
    int icoord; // ������� ������ ��������� � ������ ����������.
    int ivar;   // ������ ������ �����-��������. 0 - ������ �� ������� ���.

   public:
    GramCoordAdr(void)
    { icoord=UNKNOWN; ivar=UNKNOWN; }

    GramCoordAdr( int iCoord )
    { icoord=iCoord; ivar=0; }

    GramCoordAdr( int iCoord, int iVariant )
    { icoord=iCoord; ivar=iVariant; }

    inline int GetIndex(void) const { return icoord; }
    inline int GetVar(void)   const { return ivar;   }

    inline bool operator==( const GramCoordAdr ca ) const
    { return icoord==ca.icoord && ivar==ca.ivar; }

    inline bool operator!=( const GramCoordAdr ca ) const
    { return icoord!=ca.icoord || ivar!=ca.ivar; }

    inline bool operator<( const GramCoordAdr & x ) const
    { return icoord<x.icoord; }

    inline bool operator>( const GramCoordAdr & x ) const
    { return icoord>x.icoord; }

    inline bool IsAny(void) const
    { return icoord==ANY_STATE; }

    inline bool IsDefined(void) const
    { return icoord!=UNKNOWN || ivar!=UNKNOWN; }
  };

  class Grammar;

  /***********************************************************************
   �������� ������������ ����, �� ���� ���������� ������� ���������� �
   ������� ���������. ������ ���������� - ��� ������� ����,
   ��. GramCoordAdr.
  ***********************************************************************/
  class GramCoordPair
  {
   private:
    GramCoordAdr icoord; // ������ ����������
    int istate;          // ������ ���������

   public:
    GramCoordPair(void)
    { istate=UNKNOWN; }

    GramCoordPair( const GramCoordAdr iCoord, int is ):icoord(iCoord)
    { istate=is; }

    #if defined SOL_LOADTXT
    GramCoordPair( Macro_Parser &txtfile, const Grammar &gram )
    { LoadTxt(txtfile,gram); }
    #endif

    #if defined SOL_LOADTXT
    void LoadTxt( Macro_Parser &txtfile, const Grammar &gram );
    #endif

    void SaveTxt( OFormatter &txtfile, const Grammar &gram ) const;

    inline const GramCoordAdr& GetCoord(void) const { return icoord; }
    inline int GetState(void) const { return istate; }
    inline void SetState( int iState ) { istate=iState; }

    inline bool operator==( const GramCoordPair &c ) const
    { return icoord==c.icoord && istate==c.istate; }

    inline bool operator!=( const GramCoordPair &c ) const
    { return icoord!=c.icoord || istate!=c.istate; }

    inline bool operator<( const GramCoordPair & x ) const
    {
     if( icoord<x.icoord ) return true;
     if( icoord>x.icoord ) return false;
     return istate<x.istate;
    }


    inline bool DoesContainReference(void) const
    { return istate<0; }
  };

  /****************************************************************
   ��������� ��� ����������� ������������� ���������� ����������
   ��� ������� ����� ��������� � ����������� ���� context.
  ****************************************************************/
  class GramCoordEx : public GramCoordPair
  {
   private:
    bool affirm; // ���� =0, �� �������������, ����� ����� ����� "�����, �����"

   public:
    GramCoordEx(void):GramCoordPair() { affirm=false; }

    GramCoordEx( const GramCoordAdr icoord, int istate, bool af )
    :GramCoordPair(icoord,istate) { affirm = af; }

    GramCoordEx( const GramCoordPair cp )
    :GramCoordPair(cp) { affirm=true; }

    inline bool GetAffirm(void) const { return affirm; }

    inline bool operator<( const GramCoordEx & x ) const
    {
     if( affirm < x.affirm ) return true;
     if( affirm > x.affirm ) return false;
     return GramCoordPair::operator<(x);
    }
  };

  class CA_Array : public MCollect<GramCoordAdr>
  {
   public:
    CA_Array( int n0=0 )
    :MCollect<GramCoordAdr>(n0) {}

    int FindTwice( const GramCoordAdr ca ) const;

    inline bool operator==( const CA_Array &x ) const
    {
     if( size()!=x.size() )
      return false;

     for( size_type i=0; i<size(); i++ )
      if( get(i)!=x.get(i) )
       return false;

     return true;
    }

    inline bool operator!=( const CA_Array &x ) const
    {
     if( size()!=x.size() )
      return true;

     for( size_type i=0; i<size(); i++ )
      if( get(i)!=x.get(i) )
       return true;

     return false;
    }


   /****************************************************************************
    ������� �������� strict ����������, ������ �� ����� �����, ��� x,
    ����������, ���� ����������� ������������ aliases - �������������� �����
    ����������.
   ****************************************************************************/
   inline int find_fuzzy(
                         const GramCoordAdr& x,
                         bool strict
                        ) const
   { return strict ? find(x) : FindTwice(x); }

  };



  class CPE_Array : public MCollect<GramCoordEx>
  {
   public:
    CPE_Array(void):MCollect<GramCoordEx>() {}

    int FindOnce( const GramCoordAdr& ca ) const;
    int FindTwice( const GramCoordAdr& ca ) const;
    int FindOnce( const GramCoordPair& ca ) const;
  };


  class CP_Array : public MCollect<GramCoordPair>
  {
   public:
    CP_Array( int n0=0 );
    CP_Array( const CPE_Array &x );
    CP_Array( const MCollect<GramCoordPair> &x ):MCollect<GramCoordPair>(x) {}

    int FindOnce( const GramCoordAdr& ca ) const;
    int FindTwice( const GramCoordAdr& ca ) const;
    int FindOnce( const GramCoordPair& cp ) const { return find(cp); }
  
    void RemoveStates( const GramCoordAdr& ca );

    inline int GetState( const GramCoordAdr &ca ) const
    {
     int i = FindOnce(ca);
     return i==UNKNOWN ? i : get(i).GetState();
    }

    // ******************************************************
    // Highly optimized comparison...
    // ******************************************************
    inline bool operator==( const CP_Array &x ) const
    {
     if( empty() && x.empty() )
      return true;

     if(
        size()  != x.size()  ||
        front() != x.front()     // it is checked that n>0
       )
      return false;

     for( size_type i=1; i<size(); i++ )
      if( get(i) != x.get(i) )
       return false;

     return true;
    }

    #if defined SOL_LOADTXT
    void LoadTxt( lem::Iridium::Macro_Parser &txtfile, const Solarix::Grammar &gram );
    #endif

    void SaveTxt( OFormatter &txtfile, const Grammar &gram ) const;

    void Parse( const lem::UFString &str );
  };


  typedef boost::shared_array< CP_Array >  RC_CP_Array;


  extern bool sol_do_them_match( const CPE_Array &A, const CPE_Array &B );

 } // namespace 'Solarix'

#endif
