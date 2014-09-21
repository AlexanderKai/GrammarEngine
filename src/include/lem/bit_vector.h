// -----------------------------------------------------------------------------
// File BIT_VECTOR.H
//
// (c) Koziev Elijah
//
// Content:
// ����� BitVector - ������� ���������. �������� �� ������ �������������
// ������ MCollect. ��������� ���� ������������ � ����� �� 32 ����� �
// ������������ ��� uint32_t �����. ������ ������ MCollect �������������� �
// ���, ����� �������� ����� �����, � �� ����� ����������� ������� ������, ��
// ������� ������������ ��� ����.
//
// ���� ��������� ����� ������� ������������ ����� �����. ���������� ������
// ���������, ������� ������ �������� 32 ����, �� �������� ������� ������� -
// ��. ����� BitArray32 � ����� lem_bita.h
// -----------------------------------------------------------------------------
//
// CD->14.06.1996
// LC->15.10.2009
// --------------

#ifndef LEM_BITVECTOR__H
#define LEM_BITVECTOR__H
#pragma once

 #include <lem/containers.h>
 #include <lem/streams.h>

 namespace lem
 {
  using lem::uint32_t;
  
 // ***************************************************************
 // ���������� ����� ����� ����� (�� 4 �����), ������, �����������
 // ��� �������� n �����. ��� 0 ����� ��������� - 0 ������, ���
 // 1...8 ����� - 1 ����, � ��� �����.
 // ***************************************************************
 inline lem::Container::size_type lbv_nblock( lem::Container::size_type n )
 {
  return n<32 ? (n ? 1 : 0) : ( n%32 ? n/32+1 : n/32 );
 }

 class BitVector;

 // ********************************************************************
 // ����� ��� ����������� ������������� - ������ �� ��������� ���, ���
 // ����������� ������ �������������� ��������� [] ������ BitVector.
 // ********************************************************************
 class BitReference
 {
  private:
   const lem::Container::size_type ibit;
   BitVector *v;

  public:
   BitReference(void):ibit(0),v(NULL) {};
   BitReference( lem::Container::size_type iBit, BitVector *V )
   :ibit(iBit),v(V) {};

   void operator=( bool Bit );
 };

 class BitVector : public MCollect<uint32_t>
 {
  private:
   size_type nbit; // ����� ���������� ����� (������ ������, ��� ����� ����������
                   // ������� ������.

   inline lem::Container::size_type Blocks32(void) const { return MCollect<uint32_t>::size(); }

   void SaveBin_Compressed( lem::Stream &bin, int Depth ) const;

  public:
   BitVector( lem::Container::size_type n0=0 )
   :MCollect<uint32_t>( lbv_nblock(n0) )
   {
    nbit = n0;
    Nullify();
    return;
   }

   BitVector( const BitVector& bv ) : MCollect<uint32_t>(bv)
   { nbit=bv.nbit; }

   inline BitVector& operator=( const BitVector& bv )
   {
    if( this==&bv )
     return *this;

    MCollect<uint32_t>::operator=(bv);
    nbit=bv.nbit;
    return *this;
   }

//   inline void AddAll( int nBit )
//   {
//    MCollect<uint32_t>::AddAll( lbv_nblock(nbit=nBit) );
//    return;
//   }

   inline void reserve( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::reserve( lbv_nblock(nbit=nBit) );
    return;
   }

   inline void resize( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::resize( lbv_nblock(nbit=nBit) );
    return;
   }

   inline void ReshapeBy( lem::Container::size_type nBit )
   {
    MCollect<uint32_t>::ReshapeBy( lbv_nblock(nBit) );
    nbit += nBit;
    return;
   }

   inline BitReference operator[]( lem::Container::size_type ibit )
   { return BitReference(ibit,this); }

   // ************************************************
   // ������������� i-�� ��� � ��������� bit.
   // ************************************************
   inline void set( size_type i, bool bit )
   {
    LEM_CHECKIT_Z( i<nbit );
    const size_type iblock = i/32;
    const uint32_t  maska  = uint32_t( 0x80000000u ) >> (i%32);

    if(bit)
     get_Container()[iblock] |= maska;
    else
     get_Container()[iblock] &= ~maska;

    return;
   }

   // ********************************************
   // ���������� ��������� i-�� ����.
   // ********************************************
   inline bool get( size_type ibit ) const
   {
    LEM_CHECKIT_Z( ibit<nbit );
    const size_type iblock   = ibit/32;
    const uint32_t maska = uint32_t( 0x80000000u ) >> (ibit%32);
    return ( MCollect<uint32_t>::get(iblock)&maska)!=0;
   }

   // ****************************************************
   // ���������� ����� �������� �����.
   // ****************************************************
   inline size_type size(void) const { return nbit; }

   void Add( long nbit, bool bit );

   // *************************************************
   // ����������� ��� ���� ��� � �������� ���������.
   // *************************************************
   inline void push_back( bool Bit )
   {
    if( capacity()*32 <= nbit )
     MCollect<uint32_t>::push_back(0);

    size_type ibit=nbit;
    nbit++;

    set( ibit, Bit );
    return;
   }

   int find( int len ) const;

   inline void SetAll( bool Bit )
   {
    if(Bit)
     SetBits( 0xff );
    else
     Nullify();

    return;
   }

   bool IsThere_1(void) const;
   bool IsThere_0(void) const;

   inline void SetAll_1(void) { SetBits(0xff); }
   inline void SetAll_0(void) { SetBits(0);    }

   void LoadBin( lem::Stream &bin );

   void SaveBin( lem::Stream &bin ) const;

   // ��������� ���������� ������� �� �������, ��������� ����
   // ����������� ������� ����� �������� ����������� ������ ����� 
   // �� �����.
   void SaveBin_RLE( lem::Stream &bin, bool Compress ) const;
   void LoadBin_RLE( lem::Stream &bin );
 };

 inline void BitReference::operator=( bool Bit )
 { v->set(ibit,Bit); }

 } // namespace 'lem'

#endif
