// -----------------------------------------------------------------------------
// File INTEGRAL.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ��������� �������� ���������� �������������� - � �������� ������� ��������
// ���������.
// -----------------------------------------------------------------------------
//
// CD->06.01.96
// LC->16.10.04
// ------------

#ifndef LEM_INTEGRAL__H
#define LEM_INTEGRAL__H
#pragma once

 #include <lem/qarray.h>

 namespace lem
 {
  namespace Math
  {
  // �������, ��������� �� ������� ����������
  // � ������������ ���������� ����������.

  typedef REAL(*lem_int_func)( REAL x );
  typedef REAL(*lem_int_func_2d)( REAL x1, REAL x2 );
  typedef REAL(*lem_int_func_3d)( REAL x1, REAL x2, REAL x3 );
 
  // ������ ������� �������� n-� ����������� (PRIME_ORDER=n) � ��������� �����.
  typedef REAL(*lem_int_func_primes)( REAL x, int PRIME_ORDER );

  // ����� ���������������
  extern REAL Squares( lem_int_func F, REAL a, REAL b, long n );
 
  // 2-� ������ ������� ������ ���������������
  extern REAL Squares2d(
                        lem_int_func_2d F,
                        REAL a1, REAL a2,
                        REAL b1, REAL b2,
                        int n1,  int n2
                       );

  // ------------------------------------------------
  // ����� �������� ��� �������� �������� �������.
  //
  // ������� � ��������������� ������.
  //
  // Computes integral for a given equidistant table
  // of function by trap-s method.
  extern REAL TrapTable(
                        const RArray& F, // ������� �� n �������� �������, ������� ����� ���������.
                        REAL a,   // �������
                        REAL b    // ��������������.
                       );

  extern REAL TrapTable(
                        const REAL *F, // ������� �� n �������� �������, ������� ����� ���������.
                        const REAL *X, // ������ ��������� X ����� �����.
                        REAL a,  // �������
                        REAL b,  // ��������������.
                        REAL n   // ����� �������� ������� � �������.
                       );

  // A subroutine for integrations by the trapezoidal rule.
  extern REAL Trap( lem_int_func F, REAL a, REAL b, long n );

  // Another integration routine now by Simpson's rule.
  extern REAL Simpson(
                      lem_int_func F,
                      REAL a, REAL b,
                      long n,
                      int dir=1
                     );

  extern REAL Simpson(
                      const RArray &Y,
                      REAL h,
                      int dir=1
                     );

  extern REAL SimpsonRunge(
                           lem_int_func F,
                           REAL a,
                           REAL b,
                           long n=1,
                           long decr=2,
                           REAL EPS=0.0,
                           int dir=1
                          );

  extern REAL Simpson2d(
                        lem_int_func_2d F,
                        REAL a1,
                        REAL a2,
                        REAL b1,
                        REAL b2,
                        int n1,
                        int n2
                       );


  // ������������� ��������� ��� �������������� ������� ������ �� �������
  // ��������� ������� (�� 96-��).
  extern REAL Gauss(
                    lem_int_func F, // ��������������� �������
                    REAL a,         // ������� ��������� - ��
                    REAL b,         // ��
                    long n,         // ����� �������������� ��������� ���������
                    int Order,      // ������� �������
                    int dir=1       // ����������� ������������ - �� ���������
                                    // ����� �������, 0 - ������ ������.
                   );

  // ����� ���������� ��������� ��� �������������� ������� ������. ��� ���
  // ��� ������� ������� �������� � ������������ � ������ �����, �� �����
  // ������������ ���������� ��������� ��� ����������� ������� ������� ���
  // ���������� ��������.
  extern REAL Gauss(
                    lem_int_func F,
                    REAL a,
                    REAL b,
                    long n,
                    int Order,
                    const REAL *T,
                    const REAL *A,
                    int dir
                   );

  extern REAL Gauss2(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss3(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss4(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss5(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss6(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss7(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss8(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss9(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss10( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss11( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss12( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss16( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss20( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss24( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss32( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss40( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss48( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss64( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Gauss96( lem_int_func F, REAL a, REAL b, long n, int dir=1 );

  extern REAL GaussLn(
                      lem_int_func F,
                      REAL a,
                      REAL b,
                      long n,
                      int Order,
                      int dir=1
                     );

  extern REAL GaussLn(
                      lem_int_func F,
                      REAL a,
                      REAL b,
                      long n,
                      int Order,
                      const REAL *T,
                      const REAL *A,
                      int dir
                     );

  extern REAL GaussLn2( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn3( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn4( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn5( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn6( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn7( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL GaussLn8( lem_int_func F, REAL a, REAL b, long n, int dir=1 );
 
  // ������������� ��������� � ������� ������ �������� � ����������� �������.
  // �������� ��������, ��� � ��������� ���������� �� ���� ���������������
  // �������, � �������� �� exp(-x), ��� ��� ��� ��������������� ������� exp(-x)
  // ������� F ������ ���������� 1.
  extern REAL GaussLagger( lem_int_func F, int Order );

  // ������������� ��������� � ������������ ������� � ������ ���������.
  // � ��������� ���������� ��������������� �������, �������� �� exp(-x^2),
  // ����� ������� ���� ���������� ���������������� ������� exp(-x^2), ��
  // ���������� �������, ������������ 1.
  extern REAL GaussHermit( lem_int_func F, int Order );

  // --------------------------------------------------------------------
  // �������������� ������� �������� �� ������� ��������� �������.
  extern REAL ChebyshevN(
                         lem_int_func F,
                         REAL a,
                         REAL b,
                         long n,
                         int Order
                        );

  extern REAL Chebyshev2( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev3( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev4( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev5( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev6( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev7( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev9( lem_int_func F, REAL a, REAL b, long n );
  extern REAL Chebyshev(
                        lem_int_func F,
                        REAL a,
                        REAL b,
                        long n,
                        int ORDER,
                        const REAL T[]
                       );

  // �������������� ������� �������-������ �� ������� ��������� �������.
  extern REAL NewtonCotesN(
                           lem_int_func F,
                           REAL a,
                           REAL b,
                           long n,
                           int order,
                           int dir=1
                          );

  extern REAL NewtonCotes(
                          lem_int_func F,
                          REAL a,
                          REAL b,
                          long n,
                          const RArray& A
                         );

  extern REAL NewtonCotes(
                          lem_int_func F,
                          REAL a,
                          REAL b,
                          long n,
                          int dir,
                          int ORDER,
                          const REAL A[],
                          REAL A0,
                          REAL FACTOR
                         );

  extern REAL NewtonCotes(
                          const RArray& F,
                          REAL a,
                          REAL b,
                          const RArray& A
                         );

  extern REAL NewtonCotes(
                          lem_int_func F,
                          REAL a,
                          REAL b,
			  int n,
                          const RArray& A
                         );

  extern REAL NewtonCotes(
                          lem_int_func F,
                          REAL a,
                          REAL b,
	 		  int n,
                          int ORDER
                         );

  extern REAL Cotes3(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes4(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes5(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes6(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes7(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes8(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes9(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Cotes10( lem_int_func F, REAL a, REAL b, long n, int dir=1 );

  // �������������� ������� ������ n=6
  extern REAL Oueddle6( lem_int_func F, REAL a, REAL b, long n );

  extern const RArray BuildNewtonCotes( int n );

  extern REAL LobattoN(
                       lem_int_func F,
                       REAL a,
                       REAL b,
                       long n,
                       int ORDER,
                       int dir=1
                      );

  extern REAL Lobatto3(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto4(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto5(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto6(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto7(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto8(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto9(  lem_int_func F, REAL a, REAL b, long n, int dir=1 );
  extern REAL Lobatto10( lem_int_func F, REAL a, REAL b, long n, int dir=1 );

  extern REAL Lobatto(
                      lem_int_func F,
                      REAL a,
                      REAL b,
                      long n,
                      int ORDER,
                      const REAL A[],
                      const REAL W[],
                      int dir
                     );


  // ����� �����-����� (��������� ����)

  typedef bool(*lem_volume_fun_2d)( REAL x1, REAL x2 );
  typedef bool(*lem_volume_fun_3d)( REAL x1, REAL x2, REAL x3 );
 
  extern REAL MMK_Quadrature(
                             lem_int_func F,
                             REAL a,
                             REAL b,
                             int ntrials
                            );


  extern REAL MMK_Quadrature(
                             lem_int_func_2d F,
                             lem_volume_fun_2d V,
                             REAL a1,
                             REAL a2,
                             REAL b1,
                             REAL b2,
                             int ntrials
                            );

  extern REAL MMK_Quadrature(
                             lem_int_func_3d F,
                             lem_volume_fun_3d V,
                             REAL a1,
                             REAL a2,
                             REAL b1,
                             REAL b2,
                             REAL c1,
                             REAL c2,
                             int ntrials
                            );


  extern REAL EulerIntegral(
                            lem_int_func_primes F,
                            REAL a,
                            REAL b,
                            long n,
                            int ORDER
                           );
  } // namespace Math

 } // namespace lem

#endif
// ------------------------- End Of File [INTEGRAL.H] --------------------------
