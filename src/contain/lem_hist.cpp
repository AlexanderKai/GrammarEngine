// -----------------------------------------------------------------------------
// File LEM_HIST.CPP
//
// (c) Koziev Elijah
//
// Content:
// �����������.
// ��������� ��� ������ � ���������� ���������. ������������ �������� ��
// ���������� ���������� � ���������� �������������� ����������.
// -----------------------------------------------------------------------------
//
// CD->05.05.1996
// LC->10.09.2017
// --------------

#include <lem/oformatter.h>
//#include <lem/math/math.h>
//#include <lem/math/differ.h>
#include <lem/math/histogram.h>
#include <limits>

#undef max

using namespace lem;
//using namespace lem::Math;

/*******************************************************************************
  ��� �������������� ������������� ������� �����-����� ������� ���������
  ������� �������� � ���������� �� ������ �������� �������� ������������
  ����������, �� � ����������� ����������� ����� ������������� ���� ����������.
  ������ ������������ ��������� �������. ������ ����� ��������������
  ���������� ��������� ������, �������� �������� ��������.

  ����, ����� ��������� ������.

  ����� �������� ��������� ��������� y=[HISTO_A,HISTO_B]. �� ������ �� HISTO_N
  ����������. ����� � ���������� ���������� ������������� �����-����� ����������
  �������� Y, ��������� ���������� � ������ ::Add(Y). ���� ����� ���������, �
  ����� �������� �������� �������� Y �� ������������� �����, � �����������
  �������� ����� ������� ��� ����� ��������� �� 1. � ����� ������� �� ��������
  ��������������� ������������� ����������� (���������������� �������� �������).
  ��� ��������� �������������� ���������� ������������ ������������� ����������
  ����� ::report, ������� ���������� �������, ��������� � ��� ����� �
  ����������� ����� OFormater.

    ����������������� ����������� ��������� ������� ���������� ��� ������ ������
  ::picture.

    ��� ��� ��� �������� ������� ������ ������������ ��������� RArray, ��
  �� ���� ��������, ��������� � ������������ �� ����� ���������� HISTO_N,
  �������������� ������, ������� ���������� � ������ LEM_ARRA.H � LEM_ARRA.CPP.
*******************************************************************************/

Histogramma::Histogramma(void)
{
 HISTO_A=HISTO_B=dhisto=0.;
 HISTO_N=0;
 return;
}

// ************************************************
// �������� �������� ��������� � "����� ��������"
// ************************************************
Histogramma::Histogramma( double a, double b, int n )
{
 HISTO_A = a;
 HISTO_B = b;
 dhisto = ((HISTO_B=b)-(HISTO_A=a))/(HISTO_N=n);
 histo = RArray(0,n-1);
 return;
}

Histogramma::Histogramma( const Histogramma& h )
{
 HISTO_A = h.HISTO_A;
 HISTO_B = h.HISTO_B;
 HISTO_N = h.HISTO_N;
 dhisto  = h.dhisto;
 histo   = h.histo;
 return;
}

Histogramma& Histogramma::operator=( const Histogramma& h )
{
 HISTO_A = h.HISTO_A;
 HISTO_B = h.HISTO_B;
 HISTO_N = h.HISTO_N;
 dhisto  = h.dhisto;
 histo   = h.histo;

 return *this;
}

// !!! �����! ����������� ����������!!!
void Histogramma::Set( double x, double v )
{
 const int id = int( (x-HISTO_A)/dhisto+0.5 );
 if( id>=0 && id<HISTO_N )
  histo[id]=v;

 return;
}

// ����������� �� �������������...
//void Histogramma::prime( int prime_order, int nnode )
//{ Differ(histo,prime_order,nnode,dhisto); }

/*
void Histogramma::SaveBin( LemBinaryFile& bin ) const
{
 bin.write( &HISTO_A, sizeof(HISTO_A) );
 bin.write( &HISTO_B, sizeof(HISTO_B) );
 bin.write( &HISTO_N, sizeof(HISTO_N) );
 bin.write( &dhisto,  sizeof(dhisto) );

 histo.SaveBin(bin);
 return;
}
*/

/*
void Histogramma::LoadBin( LemBinaryFile& bin )
{
 bin.read( &HISTO_A, sizeof(HISTO_A) );
 bin.read( &HISTO_B, sizeof(HISTO_B) );
 bin.read( &HISTO_N, sizeof(HISTO_N) );
 bin.read( &dhisto,  sizeof(dhisto) );

 histo.LoadBin(bin);
 return;
}
*/


int Histogramma::GetIndex( double x ) const
{
 return int( (x-HISTO_A)/dhisto + 0.5 );
}

// **************************************************
// �������� - ���������� ������� ���������������.
// **************************************************
double Histogramma::integral(void) const
{ return sum_y()*dhisto; }

double Histogramma::sum_y(void) const
{
 double s=0.;
 for( int i=0; i<HISTO_N; i++ )
  s += histo[i];

 return s;
}

void Histogramma::Normalize(void)
{
 double normer = 0;
 for( lem::Container::size_type i=0; i<histo.size(); i++ ) 
  {
   const double pi = histo[i];
   normer = std::max( normer,  abs(pi) );
  }

 if( normer!=0 )
  {
   for( lem::Container::size_type i=0; i<histo.size(); i++ ) 
    {
     histo[i] = histo[i] / normer;
    }
  }

 return;
}


double Histogramma::GetM1(void) const
{
 double M1=0;

 double normer = 0;
 for( lem::Container::size_type i=0; i<histo.size(); i++ ) 
  {
   const double pi = histo[i];
   normer += pi;
   const double x = GetX(i);
   M1 += pi*x;
  }

 if(abs(normer)>std::numeric_limits< double >::min())
  M1 /= normer;

 return M1;
}

// *******************************************************************
// ��������� � ���������� � rep �������������� ��������� �����������.
// *******************************************************************
void lem::report( const Histogramma &hist, OFormatter& rep )
{
 // ���������� �������� � ������������ ������������.
 int imax=0;
 double pmax=0., pmin= std::numeric_limits< double >::max();

 int i;
 for( i=0; i<hist.size(); i++ )
  {
   if( hist[i]>pmax )
    pmax=hist[imax=i];

   pmin = std::min( pmin, hist[i] );
  }

 rep.printf( "/* Min frequency */ %40tMIN_FREQ=%55t%Re\n", pmin );
 rep.printf( "/* Max frequency */ %40tMAX_FREQ=%55t%Re\n", pmax );
 rep.printf( "/* Begin frequency */ %40tFREQ_START=%55t%Re\n", hist[0] );
 rep.printf( "/* End frequency */ %40tFREQ_END=%55t%Re\n", hist.back() );

 const double tmaxp = hist.GetX(imax);
 rep.printf( "/* Max frequency position (X) */ %40tMAX_P_X=%55t%Re\n", tmaxp );

 // �������� �������� �� ������...
 const double s=hist.integral();
 rep.printf( "/* Integral */ %40tINTEGRAL=%55t%Re\n", s );

 double normer=0;
 for( i=0; i<hist.size(); i++ )
  normer += hist[i];

 if( normer<std::numeric_limits< double >::min() )
  return;

 // ������������ ������ ����������� ������ (������� ��������������).
 double M1=hist.GetM1();

 rep.printf( "/* Average */ %40tM1=%55t%Re\n", M1 );

 // ������ ����������� ������, ������ ���������. ����� ������
 // ����������� ������, ��������� ���������� ����������.
 double M2=0.,M3=0.;
 if( abs(normer)>std::numeric_limits< double >::min())
  for( i=0; i<hist.size(); i++ )
   {
    const double pi = hist[i]/normer;
    const double x = hist.GetX(i);
    M2 += pi*pow(x-M1, 2);
    M3 += pi*pow(x-M1, 3);
   }

 rep.printf( "/* Dispersy */ %40tM2=%55t%Re\n", M2 );

 double sigma=0., kv= std::numeric_limits< double >::min();
 if(M2>=0.)
  sigma = sqrt(M2);

 rep.printf( "/* Square root of dispersy */ %40tSIGMA=%55t%Re\n", sigma );

 if(abs(M1)>std::numeric_limits< double >::min())
  {
   kv = sigma/M1;
   rep.printf( "/* Coefficient of variation sqrt(M2)/M1 */ %40tKV=%55t%Re\n", kv );
  }

 if( M2>std::numeric_limits< double >::min())
  {
   const double Ka = M3/pow(double(M2),double(3./2.));
   rep.printf( "/* 3rd central moment */ %40tM3=%55t%Re\n", M3 );
   rep.printf( "/* Coefficient of assimetry */ %40tKa=%55t%Re\n", Ka );
  }

 return;
}

// ************************************************************************
// ����������� ����������� ���������� ������������� � ��������� ������ rep.
// AMPLITUDE - ����� ���������� ������� ��� ������ �������� �������.
// NTIMEMARKS - ����� ���������� �� ��� X
// ************************************************************************
void lem::picture(
                  const Histogramma &hist,
                  OFormatter& rep,
                  int AMPLITUDE,
                  int NTIMEMARKS
                 )
{
 rep.printf( "Histogram step: dhisto %40t= %re\n\n", hist.GetDX() );

 print(
       hist.array(),
       hist.GetFromX(),
       hist.GetToX(),
       AMPLITUDE,
       NTIMEMARKS,
       rep
      );
 return;
}


// *********************************************************
// ��������� ������ � ��������� ������� ��� �������������
// � ��������� ������������ ����������� ������. ������ CSV.
// *********************************************************
void lem::save_data( const Histogramma &hist, OFormatter& rep )
{
 for( int i=0; i<hist.size(); i++ )
  rep.printf( "%g;%g\n", hist.GetX(i), hist[i] );

 return;
}

void lem::print(
                const RArray& GISTO,
                double GISTO_A,
                double GISTO_B,
                int AMPLITUDE,
                int NTIMEMARKS,
                OFormatter& rep
               )
{
 const int NGISTO = GISTO.size();
 const int i0 = GISTO.GetFrom();

 const int NTPAC = NGISTO/NTIMEMARKS;
 double MAXG = max(GISTO);

 if( MAXG==0 )
  return;

 double dx = (GISTO_B-GISTO_A)/NGISTO;
 double x;
 int ng;

 for( int i=0; i<NGISTO; i++ )
  {
   x = GISTO_A + double(i)*dx;              // �������� ���������� ���������
   ng = int( GISTO(i+i0)*AMPLITUDE/MAXG ); // ������ �������� � ��������

   if( !(i%NTPAC) )
    rep.printf( "%1.5W12re-+%H#%H-+\n", x, ng, AMPLITUDE-ng );
   else
    rep.printf( "%13h |%H#%H.|\n", ng, AMPLITUDE-ng );
  }

 rep.printf( "%1.5W12re-+%H-+\n", GISTO_B, AMPLITUDE );
 return;
}
