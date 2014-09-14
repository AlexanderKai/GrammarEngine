// -----------------------------------------------------------------------------
// File SOL_IO.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2003
//
// Content:
// ����� �����-������: �������� ������� ��� �����-������ ���������� �����������
// �����������.
// -----------------------------------------------------------------------------
//
// CD->14.10.02
// LC->13.04.07
// ------------

#include <lem/oformatter.h>
#include <lem/sol_io.h>

using namespace lem;

void Sol_IO::Flush(void)
{
 if( echo ) echo->flush();
 if( err  )  err->flush();
}

// -------------------------- End Of File [SOL_IO.CPP] -------------------------
