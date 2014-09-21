// -----------------------------------------------------------------------------
// File INTERPOL.CPP
//
// (c) by koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ��������� ������� ��������� ������������ � �������������.
// -----------------------------------------------------------------------------
//
// CD->06.03.1995
// LC->19.04.2007
// --------------


#include <lem/math/real_functions.h>
#include <lem/math/approxim.h>

using namespace lem;
using namespace lem::Math;

// --------------------------------------------------------------------
// Square Interpolation by three nodes. ��� �������� ���� ����� (����
// ����� <x0,y0>, <x1,y1>, <x2,y2>) ���� �������� �������� � ����� X
// ����� ���������� ���������������� ��������.
// --------------------------------------------------------------------
REAL lem::Math::SquareInterpol(
                               REAL x0, REAL y0,
                               REAL x1, REAL y1,
                               REAL x2, REAL y2,
                               REAL X
                              )
{
 const REAL B = (y1-y0)/(x1-x0);
 return y0 + ( B+( ((y2-y0)-B*(x2-x0))*(X-x1)/((x2-x1)*(x2-x0)) ) )* (X-x0);
}

// -------------------------------------------------------------------------
// One-dimentional interpolation by N nodes using Lagrange polynome.
//
//         N       N
//        ---    +---+
//        \      |   |  ( X - Xk )
// Ln(X) = >  Yi*|   | -------------
//        /      |   |  ( Xi - Xk )
//        ---    -   -
//        i=i0    k=i0
//                k!=i
//
// ������� xi � yi ������ ���������� ����������������� �����. ��������
// X - �������� �����, ��� ���������� ����� �������� �����������������
// ���������.
// -----------------------------------------------------------------------
REAL lem::Math::LagrangeInterpol(
                                 const RArray& xi,
                                 const RArray& yi,
                                 REAL X
                                )
{
 const int i0 = xi.GetFrom();
 const int in = xi.GetTo();

 LEM_CHECKIT_Z( in==yi.GetTo() );
 LEM_CHECKIT_Z( i0==yi.GetFrom() );

 if(i0==in)
  return yi(i0);

 REAL P,Xi,S=TOREAL(0.0);
 const REAL ONE=TOREAL(1.0);

 for( int i=i0; i<=in; i++ )
  {
   P=ONE;
   Xi=xi(i);

   for( int k=i0; k<=in; k++ )
    if( k != i )
     P *= (X-xi(k))/(Xi-xi(k));

   S += P*yi(i);
  }

 return S;
}

/************************************************************************
  ����� ���� ������������ �������� ����� ������� ������� ���������.


  ������� ���������:

   xi - ������ ��������� �����.
   X - �����, ������� ���������� ��������.


  ������������ ��������:

   ������ ��������, ������� ��������� ����� �� ����� X, ��� ����
   ������ ������������ ����� ��������� ��� +1. ��������� �������������
   ��������� ����� ������ �� ������� ����� � xi, ��� ��� ����� ��������
   ��������� 1 � ������������� �������� �������.

  ���������:

            1. �������������� ��� ��������, ��� �������� � xi ����������
               �� i=i0.

****************************************************************************/

int lem::Math::FindLeftPoint( const RArray& xi, REAL X )
{
 const int i0 = xi.GetFrom();
 const int in = xi.GetTo();

 // ���� ��� �����, ������� ����� � ������ �� ����������
 // ��������.
 const REAL xa=xi(i0), xb=xi(in);

 int LeftNode = i0 + int((X-xa)/(xb-xa));
 int irange   = (in-i0)/2+(in-i0)%2;

 if( X<=xa || X>=xb )
  {
   // ����� ��� ��� �������� �������� �������.
   if( X<=xa )
    LeftNode=i0;
   else
    LeftNode=in-1;
  }
 else
  FOREVER
   {
    if( xi(LeftNode)<=X && xi(LeftNode+1)>=X )
     break;

    if( xi.get(LeftNode)>=X )
     {
      // ���� � ����� ������������.
      if( (irange/=2) < 1 )
       irange=1;

      LeftNode -= irange;

      if( LeftNode<i0 )
       LeftNode=i0;
     }
    else
     {
      // ���� � ������ ������������.
      if( (irange/=2) < 1 )
       irange=1;

      LeftNode += irange;

      if( LeftNode>in-1 )
       LeftNode=in-1;
     }
   }

 return LeftNode;
}

/****************************************************************************
 �������� ������������ �� �������� �������� ������� (������� ������, �?).

 ��������� ���� ��������� � �������� ����� ����. ����������� �������
 ����� ��� ������������� ��������� ����� - ��������� ����� ���������.
*****************************************************************************/
REAL lem::Math::LinearInterpol(
                               const RArray& xi,
                               const RArray& yi,
                               REAL X
                              )
{
 const int i0 = xi.GetFrom();
 const int in = xi.GetTo();

 LEM_CHECKIT_Z( xi.size()>0 );
 LEM_CHECKIT_Z( in==yi.GetTo() );
 LEM_CHECKIT_Z( i0==yi.GetFrom() );

 if(i0==in)
  return yi(i0);

 const int LeftNode = FindLeftPoint( xi, X );
 const int RightNode = LeftNode+1;

 // ����� ������� ���� �����.
 const REAL xl = xi(LeftNode),  yl = yi(LeftNode);
 const REAL xr = xi(RightNode), yr = yi(RightNode);

 return yl + (X-xl)/(xr-xl)*(yr-yl);
}

/**********************************************************
 �������������� ������������ �� �������� �������� �������.
***********************************************************/
REAL lem::Math::SquareInterpol(
                               const RArray& xi,
                               const RArray& yi,
                               REAL X
                              )
{
 const int i0 = xi.GetFrom();
 const int in = xi.GetTo();

 LEM_CHECKIT_Z( xi.size()>0 );
 LEM_CHECKIT_Z( in==yi.GetTo() );
 LEM_CHECKIT_Z( i0==yi.GetFrom() );

 if(i0==in)
  return yi(i0);

 if( xi.size()==2 )
  return yi(i0) + (yi(in)-yi(i0))/(xi(in)-xi(i0)) * (X-xi(i0));

 int LeftNode = FindLeftPoint( xi, X );
 int RightNode = LeftNode+1;

 if( RightNode==in )
  {
   LeftNode--;
   RightNode--;
  }

 const int ThirdNode = RightNode+1;

 // ����� ������� ���� �����.
 const REAL x0 = xi(LeftNode),  y0 = yi(LeftNode);
 const REAL x1 = xi(RightNode), y1 = yi(RightNode);
 const REAL x2 = xi(ThirdNode), y2 = yi(ThirdNode);

 return SquareInterpol(
                        x0, y0,
                        x1, y1,
                        x2, y2,
                        X
                       );
}

/*****************************************************************************
  ������������ � ������������� ��������� �������� �������� �������.

  ��������� ������������� ������� ��������� � X ���� �� xi, � ��������� �
  ���������� ������ ������������� ��������� ��������.

  ������� ���������:

   xi - ���������� ������� �����.

   yi - �������� ������� � �������� xi ������.

   X - �����, � ������� ������������ �������� �������.

   AP - ������� ���������������� ��������.


  ������������ ��������:

   ��������� ������������/�������������.
************************************************************************/

REAL lem::Math::LagrangeInterpol(
                                 const RArray& xi,
                                 const RArray& yi,
                                 REAL X,
                                 int AP
                                )
{
 const int NL = AP+1;
 const int i0 = xi.GetFrom();
 const int in = xi.GetTo();

 LEM_CHECKIT_Z( xi.size()>0 );
 LEM_CHECKIT_Z( in==yi.GetTo() );
 LEM_CHECKIT_Z( i0==yi.GetFrom() );
 LEM_CHECKIT_Z( NL<=CastSizeToInt(xi.size()) );

 if(i0==in)
  return yi(i0);

 int LeftNode = FindLeftPoint( xi, X );

 // ����� ��������������� ��������� �������� �� AP ������.
 // ��� ��� ����� ����� � ������ ��������� ����� ��������.

 int LI = LeftNode-NL/2;

 if( LI<i0 )
  LI=i0;

 int RI = LI+NL;

 if( RI>in )
  {
   RI=in;
   LI=in-NL+1;
  }

 const REAL ONE=TOREAL(1.);
 REAL P,Xi,S=TOREAL(0.);

 for( int i=LI; i<=RI; i++ )
  {
   P=ONE;
   Xi=xi(i);

   for( int k=LI; k<=RI; k++ )
    if( k != i )
     P *= (X-xi(k))/(Xi-xi(k));

   S += P*yi(i);
  }

 return S;
}

// ------------------------- End Of File [INTERPOL.CPP] ------------------------
