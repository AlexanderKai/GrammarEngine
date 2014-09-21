// -----------------------------------------------------------------------------
// File LEM_COAP.CPP
//
// (c) 2005 by Elijah Koziev     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
//
// �������� ���������� ���������� mout � merr - ��� ������� ����������� ������
// �� ��������� �������. ��� ���������� ���������� ��������� �� ������� OS, �
// ��������� - ������������ ����������� ��������� ���������� �������� (�������,
// ����� ���������� ncurses).
//
// ������������� ��������� ������� ��� ������� ����.
// ��������� ������� ������ �� ��������� ������� ��� Win32.
//
// 03.10.2005 - ������������� ������� ������� ���������� � ������
//              cp_code_pages.cpp, ��� ��� ��� ��������� ������� ����� ���������
//              ������� ��������.  
// -----------------------------------------------------------------------------
//
// CD->23.10.2000
// LC->26.05.2008
// --------------

#include <lem/config.h>
#include <lem/oformatter.h>
#include <lem/keyboard.h>
#include <lem/console_application.h>

// Standard console streams for common output and for error messages.
lem::OFormatter* lem::mout = NULL;
lem::OFormatter* lem::merr = NULL;

// ****************************************
// ��������� ��� ����� ������ � ����������
// ****************************************
lem::IKbdFormatter* lem::mkey = NULL;
