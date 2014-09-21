// -----------------------------------------------------------------------------
// File NULL_CONSOLE.CPP
//
// (c) Koziev Elijah
//
// Content:
// ���������� ���������� �������� ������ �� ������� - mout � merr. ������
// ������ ������������ ��� �������� �������� - ������� mout � merr ���������
// �� NUL.
//
// 22.02.2010 - ��� �������� ���������� ������� ��������� � lem_startup.cpp
// -----------------------------------------------------------------------------
//
// CD->07.01.2005
// LC->22.02.2010
// --------------

#include <lem/streams.h>
#include <lem/console_streams.h>

using namespace lem;

#if defined LEM_WINDOWS
OFormatter *lem::mout = NULL;
OFormatter *lem::merr = NULL;
#else
OFormatter *lem::mout = NULL;
OFormatter *lem::merr = NULL;
#endif

