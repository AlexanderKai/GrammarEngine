// -----------------------------------------------------------------------------
// File PHYSCONS.H
//
// (c) by Koziev Elijah, Obninsk, Russia, 1995-2004
//
// ����� ���������� ��������. Physical constans (from MATHCAD PLUS)
// -----------------------------------------------------------------------------
//
// CD->11.07.95
// LC->16.10.04
// ------------

#ifndef LEM_PHYSICAL_CONST__H
#define LEM_PHYSICAL_CONST__H
#pragma once

 #include <lem/real.h>
 #include <lem/math_constants.h>

 const REAL PHYS_c  = 299792458;      // �������� �����, �/�. Velocity of light in a vacuum, [m/sec].
 const REAL PHYS_G  = 6.67259e-11;    // �������������� ����������. Gravitational constant, [m^3/(kg*s^2)].
 const REAL PHYS_NA = 6.0221367e23;   // ���������� ��������. Avogadro's number, [1/mole].
 const REAL PHYS_Mp = 1.6726231e-27;  // ����� ����� �������, ��. Proton rest mass, [kg].
 const REAL PHYS_Mn = 1.6749286e-27;  // ����� ����� ��������, ��. Neutron rest mass, [kg].
 const REAL PHYS_Me = 9.1093897e-31;  // ����� ����� ���������, ��. Electron rest mass, [kg].
 const REAL PHYS_e  = 1.60217733e-19; // ����� ���������, �� Electron charge, [coul].
 const REAL PHYS_h  = 6.6260755e-34;  // ���������� ������, ��*���. Planck's constant, [joule*sec].
 const REAL PHYS_ma = 1.6605402e-27;  // Atomic mass unit, [kg]


 const REAL PHYS_E0 = 1.e-7/(4.*PI*PHYS_C*PHYS_C); // ������. ����, �/�.
 const REAL PHYS_M0 = 4.*PI*1e-7;  // ��������� ����������, ��/�.

 const REAL PHYS_VM  = 0.00224138;  // �������� ����� ��. ���� ��� �.�., �^3/����
 const REAL PHYS_R   = 8.314;       // �����. ���. ����., ��/(�*����)
 const REAL PHYS_F   = 96485;       // ����. �������, ��/����
 const REAL PHYS_k   = 1.38066e-23; // ����. ���������, ��/�
 const REAL PHYS_e0  = 1.e-7/(4.*PI*PHYS_C*PHYS_C); // Permittivity of vacuum, [farad/m].
 const REAL PHYS_mu0 = 4.e-7*PI;    // Permeability of vacuum, [newton/amp^2].
 const REAL PHYS_ncw = 1,31959110e-15; // Neutron Compton wavelengh, [m].
 const REAL PHYS_mrm = 1.8835327e-28; // Muon rest mass, [kg].
 const REAL PHYS_cer = 2.81794092e-15; // Classical electron radius, [m].
 const REAL PHYS_qc  = 3.63694807e-4; // Quantum of circulation, [m^2/s].
 const REAL PHYS_mvg = 22.41410; // Molar volume of ideal gas at STP, [liter/mole].
 const REAL PHYS_fc  = 96485.309; // Faraday constant, [coul/mole].
 const REAL PHYS_sbc = 5.67051e-8; // Stefan-Boltzmann constant, [watt/(m^2*K^4)]
 const REAL PHYS_rc  = 10973731.534; // Rydberg constant, [1/m]
 const REAL PHYS_br  = 0.529177249e-10; // Bohr radius, [m].
 const REAL PHYS_emm = 928.47701e-26; // Electron magnetic moment, [joule/tesla].
 const REAL PHYS_pmm = 1.41060761e-26; // Proton magnetic moment, [joule/tesla].
 const REAL PHYS_bm  = 9.2740154e-24; // Bohr magneton, [joule/tesla].
 const REAL PHYS_nm  = 5.0507866e-27; // Nuclear magneton, [joule/tesla].
 const REAL PHYS_fsc = 7.29735308e-3; // Fine structure constant.
 const REAL PHYS_ecw = 2.42631058e-12; // Electron Compton wavelength, [m].
 const REAL PHYS_pcw = 1.32141002e-15; // Proton Compton wavelength, [m].
 const REAL PHYS_mgc = 8.314510; // Molar gas constant, [joule/(mole*K)].
 const REAL PHYS_k   = 1.380658e-23; // Boltzmann's constant, [joule/K].
 const REAL PHYS_frc = 3.7417749e-16; // First radiation constant, [watt*m^2].
 const REAL PHYS_src = 0.01438769; // Second radiation constant, [m*K].


 /*************************************************************************
  MATHCAD Physical Constants are from:

  CRC Handbook of Chemistry and Physics, 72nd edition, edited by
  David R. Lide, CRC Press, 1991.
 *************************************************************************/
 
/*
      ***  ������������� ������� ���������  ***

                1 �������� = 1e-10 �
                1 ����     = 2.54e-2 �
                1 �����    = 1e-15 �
                1 ����     = 1e-28 �^2
                1 �.�.     = 1.49e11 �
                1 ��. ���  = 9.46e15 �
                1 ��.-�.   = 9.81 �
                1 ���      = 1e-7 ��
                1 �������  = 4.19 ��
                1 ��       = 1.60e-19 ��
                1 �.�.     = 736 ��
                1 ��.      = 9.81e4 ��
                1 ��.��.�. = 133 ��
                1 ���.     = 1.01e5 ��
                1 ����     = 3.7e10 ��
                1 ���      = 1e-2 ��
                1 �������  = 2.58e-4 ��/��
*/

/*
                   ������

  ������� ������ ����� = 6.37e6 �
  ������� ��������� ����� = 5500 ��/�^3
  ����� ����� = 5.96e24 ��
  ������ ������ = 6.95e30 �
  ������ ���� = 1.74e6 �
  ����� ������ = 1.97e30 ��
  ����� ���� = 7.3e22 �� 
  ������� ��������� ������ = 1400 ��/�^3
*/

#endif
// ------------------------- End Of File [PHYSCONS.H] --------------------------
