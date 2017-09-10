// -----------------------------------------------------------------------------
// File WORDS_STATISTICS.CPP
//
// (c) Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project
// CHARS program
//
// Words processor - part of CHARS code.
// ���樠����஢���� ����� - ����������� � ��ࠡ��뢠�� ����⨪� ���
// 楫�� ᫮�.
//
// ������� ��� ����� ⥪�⮢� 䠩�� '*.dat' � ���ᠭ��� ������᪨�
// १���⮢, �ਣ���� ��� ����㧪� � �ணࠬ�� ���㠫���樨, ⠪ � ��
// ������������� 䠩��� '*.sol', ����� �࠭᫨������ ���㫥� YGRES �
// ᮤ�ঠ� ������ ���� �� �㪢��, ᫮���, ᫮���.
// -----------------------------------------------------------------------------
//
// CD->04.09.2002
// LC->20.08.2009
// --------------

#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>

#include "empir.h"


WordStatProcessor::WordStatProcessor(void)
{
 words_count=0;
 return;
}

// ******************************************************
// ��ࠡ�⪠ ��।���� ᫮�� ustr � ���⮩ word_freq
// ******************************************************
void WordStatProcessor::Add(
                            const UCString &ustr,
                            lem::int64_t word_freq
                           )
{
 // ����� ������ ⮫쪮 ॠ�쭮 ࠧ��� ᫮�, � �� 䠪�,
 // �� ������ ᫮�� ����砥��� � ��ࠡ�⠭��� ⥪��� word_freq
 // ࠧ, ������㥬.
 words_count++;

 // Get the numerical estimations <p> for word.
 const GraphGram &gg = sol_id->GetGraphGram();

 Nfreq.push_back( word_freq );

 return;
}


void WordStatProcessor::Post_Process(void)
{
 mout->printf( "Postprocessing word statistics (%vfE%d%vn records): ", Nfreq.size() );
 mout->flush();

 tot_freq=0;
 for( lem::Container::size_type j=0; j<Nfreq.size(); j++ )
  tot_freq += Nfreq[j];


 mout->printf( "%vfAOK%vn\n" );

 return;
}


// *******************************************************
// �����⮢�� � ��࠭���� १���⮢ ��ࠡ�⪨.
// *******************************************************
void WordStatProcessor::Report( OFormatter &rep ) const
{
 mout->printf( "Writing the calibration tables for GG..." ); mout->flush();
 rep.printf(
            "\nStatistics for words\n"
            " Number of different words processed: %qd\n\n"
            , words_count
           );

 try
  {
   Report_Chars(rep);
   Report_Syllabs(rep);
   mout->printf( "%vfAOK%vn\n" );
  }
 catch(...)
  {
   mout->printf( "%vfCError%vn\n" );
  }

 return;
}


void WordStatProcessor::Report_Chars( OFormatter &rep ) const
{
 return;
}


void WordStatProcessor::Report_Syllabs( OFormatter &rep ) const
{
 return;
}

lem::Path WordStatProcessor::GetOutPath( const wchar_t *filename ) const
{
 LEM_CHECKIT_Z( filename!=NULL );
 lem::Path p(outdir);
 p.ConcateLeaf(filename);
 return p;
}
