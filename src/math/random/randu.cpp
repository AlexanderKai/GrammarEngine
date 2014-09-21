// -----------------------------------------------------------------------------
// File RANDU.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ���������� ��������� ��������������� ���������� �������������� ����� �
// �������������� ���������� �� ���������.
// -----------------------------------------------------------------------------
//
// CD->18.01.1996
// LC->16.08.2007
// --------------

#if !defined LEM_NOREAL

#include <lem/math/random.h>
#include <lem/math/math.h>

using namespace boost;
using namespace lem;
using namespace lem::Math;

int RandU::Number=0;

//lem::Math::RandU::result_type lem::Math::RandU::min_value=0;
//lem::Math::RandU::result_type lem::Math::RandU::max_value=0xffffffffUL;

/*
  ���� ������������� ��� � ������ ��������� ����� ����� �
  ���������:

   ��.�������, �.���������, �.������ "�������� ������ ��������������
   ����������", -�.:"���", 1980, ���.260 � �����.

*/

static REAL ABRAM[]=
                    {
                     TOREAL(5347981115.),
                     TOREAL(9803612217.),
                     TOREAL(5952640238.),
                     TOREAL(4057739351.),
                     TOREAL(4321169255.),
                     TOREAL(9734470328.),
                     TOREAL(5811691964.),
                     TOREAL(2624044643.),
                     TOREAL(8328797391.),
                     TOREAL(9282377578.),
                     TOREAL(6602338277.),
                     TOREAL(7452371118.),
                     TOREAL(8489213956.),
                     TOREAL(9889992315.),
                     TOREAL(6578359640.)
                    };

RandU::RandU( int n )
{
// min_value=0;
 //max_value=0xffffffffUL;

 if( n>=0 ) Number=n-1;

 // ���� �� ������������� ������ ����� ���������
 // ����������� �����������, �� ���������� ��� �������
 // ������ ������������ ������� �������������� ���������
 // �������. ��� ����������� �������� ����� ����������� �
 // ������� ������������ ���� ������.
 Number++;

 // �������� ��������� ����������.

 HALFM = uint32_max/2;

 // ��������� ��������� � ���������� ��������� �������������
 // ������.

 IA  = 8*Droundl( PI/8.0*HALFM) + 5;
 IC  = 2*Droundl( ( 0.5-qsqrt(3.0)/6.0 ) * HALFM) + 1;

 // �������������� ��������� ��� ��� �������������� � ����� � ��������� ������.
 S = TOREAL(0.5)/HALFM;

 // ����� ������� ������������ ��������� ��������
 // ������ ������ �� �������� ���������� �����������.
// LASTY = 314159257UL*(Number);

 LASTY = qroundl( ABRAM[ Number%DIM_A(ABRAM) ] + TOREAL(314159257.)*Number );
 return;
}

void RandU::Generate( int NR, REAL *dest )
{
 for( int i=0; i<NR; i++ )
  dest[i] = aget();

 return;
}

void RandU::SaveBin( lem::Stream& bin ) const
{
 const int s=sizeof(RandU);
 bin.write( &s,     sizeof(s)     );
 bin.write( &HALFM, sizeof(HALFM) );
 bin.write( &IA,    sizeof(IA)    );
 bin.write( &IC,    sizeof(IC)    );
 bin.write( &S,     sizeof(S)     );
 bin.write( &LASTY, sizeof(LASTY) );
 return;
}

void RandU::LoadBin( lem::Stream& bin )
{
 int s;
 bin.read( &s,     sizeof(s)     );
 LEM_CHECKIT_Z(s==sizeof(RandU));

 bin.read( &HALFM, sizeof(HALFM) );
 bin.read( &IA,    sizeof(IA)    );
 bin.read( &IC,    sizeof(IC)    );
 bin.read( &S,     sizeof(S)     );
 bin.read( &LASTY, sizeof(LASTY) );
 return;
}

#endif

