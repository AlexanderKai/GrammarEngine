// -----------------------------------------------------------------------------
// File IO_AUDII.CPP
//
// Copyright:    Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2000
//
//
// Content:
// ��⮪ ������ ����묨 � ����㠫�� ��㪮�� ���ன�⢮�.
// ***
// �����প� ��㪮���� ����� � ���⥬� (SOUND INLET).
// -----------------------------------------------------------------------------
//
// CD->28.01.99
// LC->03.12.00
// ------------

#include <lem/config.h>

#if defined SOL_CAA

#if defined SOL_DOS
#include <dos.h>
#include <conio.h>
#endif

#include "lem_dir.h"
#include "lem_bstr.h"

Lem_AUI_Stream::Lem_AUI_Stream(void)
{
 record = NULL;
 return;
}

Lem_AUI_Stream::~Lem_AUI_Stream(void)
{
 lem_rub_off(record);
 lem_remove(snd_tmp_fname);
 return;
}

// *****************************************************************
// ����७��� ��楤�� ��� �����⮢�� ࠡ��� � 䠩��� ��㪮������.
// �� ���뢠�� ��⮪ ��� ���뢠���.
// *****************************************************************
void Lem_AUI_Stream::Open(void)
{
 LEM_CHECKIT_Z(record==NULL);
 lem_check_ptr( record = new LemBinaryFile(snd_tmp_fname,true,false) );
 return;
}

// ************************************************************************
// ��⠥� ����� ������ �� 䠩�� � ��㪮����묨. �᫨ ��⮪ �� ��
// �����, � ��⠥��� �� ᤥ����. ��������! �᫨ 䠩� ��㪮������ �����
// �� ������� �� ��᪥, � �㤥� ᣥ���஢��� �᪫��⥫쭠� �����.
// ************************************************************************
void Lem_AUI_Stream::read( void *ptr, const size_t size )
{
 if( record==NULL )
  Open();

 LEM_CHECKIT_Z( record!=NULL );
 record->read( ptr, size );

 return;
}

// ******************************************************************
// ������ � ��㪮������� �� ��᪥ �����稫�, ����� ᯮ����� 㤠����
// �६���� 䠩� � ����뢠�� ��⮪.
// ******************************************************************
void Lem_AUI_Stream::flush(void)
{
 lem_rub_off(record);
 lem_remove(snd_tmp_fname);
 return;
}

const bool Lem_AUI_Stream::isready(void) const
{
 return lem_does_exist(snd_tmp_fname);
}

const bool Lem_AUI_Stream::eof(void) const
{
 LEM_CHECKIT_Z(record!=NULL);
 return record->eof();
}

void Lem_AUI_Stream::fclose(void)
{
 lem_rub_off(record);
 return;
}

const long Lem_AUI_Stream::fsize(void) const
{
 LEM_CHECKIT_Z(record!=NULL);
 return record->fsize();
}

// ********************************************************************
// ����᪠�� �ࠩ��� ��㪮���� �����. ��� �ࠩ��� ��ନ��� ��᪮��
// �६���� 䠩�, ����� ��⥬ ����� ���� ����㦥� ���⥬�� ���
// �������.
// ********************************************************************
#if defined SOL_DOS
REGISTER_STATIC_STRING(SOL_RECORDER,"dos_rec.exe ");
REGISTER_STATIC_STRING(SOL_WAV_EXT,"wav");
#endif

#if defined(SOL_WINDOWS) && defined(SOL_TUI_PLAIN)
REGISTER_STATIC_STRING(SOL_RECORDER,"dos_rec.exe ");
REGISTER_STATIC_STRING(SOL_WAV_EXT,"wav");
#endif

void Lem_AUI_Stream::DoRecord(void)
{
 #if defined SOL_DOS
 snd_tmp_fname = sol_get_tmp_name(SOL_WAV_EXT);
 const SolFString x=SolFString(SOL_RECORDER)+SolFString(snd_tmp_fname);
 sol_system( x.string() );
 #elif defined(SOL_WINDOWS) && defined(SOL_GUI)
  // ...
 #elif defined(SOL_WINDOWS) && defined(SOL_TUI_PLAIN)
 snd_tmp_fname = sol_get_tmp_name(SOL_WAV_EXT);
 const SolFString x=SolFString(SOL_RECORDER)+SolFString(snd_tmp_fname);
 sol_system( x.string() );
 #else
  // ...
 #endif

 return;
}

void Lem_AUI_Stream::Record_If_Needed( const bool forced )
{
 if(forced)
  DoRecord();

 if( isready() && record==NULL )
  Open();

 return;
}

void Lem_AUI_Stream::write( const void* /*src*/, const size_t /*size*/ )
{
 LEM_STOPIT;
}

void Lem_AUI_Stream::put( const int /*ch*/ )
{
 LEM_STOPIT;
}

#endif // defined SOL_CAA
// --------------------------- End Of File [IO_AUDII.CPP] ----------------------
