#pragma once

// -----------------------------------------------------------------------------
// File REAL.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2006
//
// Content:
// REAL NUMBERS TYPE SUPPORT.
// ��������� ���� REAL, ��������� ����������� �� ���������� ��������
// �������������.
//
// 31.08.2006 - ���������� �������������� ��������-������� ��� ������� ��������
//              � ��������� ���� ��� ���������� ����������.
//
// 23.04.2008 - ��������� ��������� min_float, max_float, min_double, max_double
// -----------------------------------------------------------------------------
//
// CD->18.01.1996
// LC->23.04.2008
// --------------

#if !defined(LEM_REAL__H) && !defined(LEM_NOREAL)
 #define LEM_REAL__H

 #include <lem/config.h>

 //#if defined DEFREAL4
  #include <lem/math/fp4.h>
 //#elif defined DEFREAL10
  #include <lem/math/fp10.h>
 //#else
  #include <lem/math/fp8.h>
 //#endif

 namespace lem
 {
  namespace Math
  {
   #if defined DEFREAL4
   typedef float REAL;
   #elif defined DEFREAL10
   typedef long double REAL;
   #else
   // �� ��������� ���������� REAL ��� REAL8.
   typedef double REAL;
   #endif
  }

  const float float_min = lem::Math::MINREAL4;
  const float float_max = lem::Math::MAXREAL4;

  const double double_min = lem::Math::MINREAL8;
  const double double_max = lem::Math::MAXREAL8;
 }

#endif
