// -----------------------------------------------------------------------------
// File AUTOMATON.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
//
// ����� Automaton - ������� ��� �������� ��������� (� ��� ����� ���������)
// �������.
// -----------------------------------------------------------------------------
//
// CD->29.05.1997
// LC->04.01.2011
// --------------

#include <lem/macro_parser.h>
#include <lem/logfile.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/some_strings.h>
#include <lem/solarix/automaton.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

/****************************************************************************
   ������� - �������� ����������� ������� ������� �������. ������ �������
 �������� ������������� ���������� �����������, ���������� �����������
 ���������� ���������� (��������������� ��) � ��������������� �����
 ������������ ������� ��� ������� � �������� ������ � ����������. �
 ��������� ������� �������� ��������� ��������� ���� � ����� ������
 ��������� ������� ������ ���������� ������. �������� �������� ����������
 (��. ���� sol_gram.cpp). ������ �������� ���������� �� ����� �� ������ �
 ����� ������� ���������� ������ � ������� ������������ ������, ��������
 ������������� ������� � ��������� (��. ������ SolSynRule � ProcedureBeth).

   ����� Automaton �� ������������ ��� �� ����, �� ������ ������� �������
 ��� ������ ������� ���������. �� ���������� ����� ������� ���� �����
 ��������� ������ ����������� ���������� (������� ������ Criterion),
 ������������ ����� �������� ���������� ����������� ������� �����������
 ��������� ������������� ������ ����������� ������� ���������.
*****************************************************************************/
Automaton::Automaton( int Index )
{
 // ��� ��� �� ����, ��� ����� �� ��������...
 dict = NULL;
 param = NULL;

 // ������� ����.
 was_loaded = false;

 index = Index;

 return;
}

Automaton::~Automaton(void)
{
 delete param;
 return;
}


/***************************************************************************
 ���������� ����� � ����� ������� ��������. ��������� ���������� �� �������
 ��������� �������� ��������� � ������ ��������� � ������������ �� ��������.
****************************************************************************/
void Automaton::SetDictPtr( Dictionary *d )
{ dict=d; }

#if defined SOL_LOADTXT && defined SOL_COMPILER
/********************************************************************
 ����� ������� Dictionary ��������� � ��������� ����� ������ ��������
 �������� � ������ ��� ��������� �� ���� (����� ��� ������� ��).
 ����� ������� ������ �������� �������� ���������� ����� PreLoad, �
 ����� ���������� ��������� ������ ���������� PostRead.
*********************************************************************/
void Automaton::LoadTxt(
                        Macro_Parser &txtfile,
                        const Binarization_Options &options
                       )
{
 try
  {
   if( !was_loaded )
    PreLoad(txtfile,options);

   was_loaded=true;
   txtfile.read_it(B_OFIGPAREN);
   load(txtfile,options);
   PostRead(txtfile,options);
  }
 catch( E_ParserError &x )
  {
   GetIO().merr().printf(
                         "Syntax error in automaton [%us] section\n%us\n"
                         , GetName().c_str()
                         , x.what()
                        );

   was_loaded = false;
   throw(x);
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool Automaton::ProcessLexem2(
                              const BethToken &t,
                              Macro_Parser &txtfile,
                              const Binarization_Options &options
                             )
{
 return false;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
 ����������, �������� ����������� ���� ������ ��������. ���� ���������
 ����������� ������� ��������� ������������ � ��������� ���� �����������
 ��������� ������ ����� ����, ��� ���������� � ��������� ��� �����,
 ���������� ����������� ����� ProcessLexem.
*************************************************************************/
void Automaton::load(
                     Macro_Parser &txtfile,
                     const Binarization_Options &options
                    )
{
 bool looping=true;
 while( looping )
  {
   if( txtfile.eof() )
    {
     Print_Error(txtfile);
     GetIO().merr().printf(
                           "End of file has been reached before Automaton [%us] section completely loaded\n"
                           , GetName().c_str()
                          );
     throw E_ParserError();
    }

   const BethToken t=txtfile.read();

   if( !ProcessLexem(t,txtfile,options) )
    {
     switch(t.GetToken())
      {
       case B_CRITERION:
        if( param!=NULL )
         param->LoadTxt( GetIO(), txtfile );
        break;

       case B_CFIGPAREN:
        looping=false;
        break;

       default:
        {
         const BSourceState back=txtfile.tellp();

         if( param!=NULL )
          {
           if( txtfile.read().GetToken()==B_EQUAL )
            {
             txtfile.seekp( t.GetBegin() );
             param->LoadTxt(GetIO(),txtfile);
             break;
            }
          }
         else
          {
           LEM_STOPIT;
          }

         txtfile.seekp(back);

         // �������������� �������.
         GetIO().merr().printf( "\nIncorrect lexem [%us]\n", t.string().c_str() );
         Print_Error(t,txtfile);
         throw E_ParserError();
        }
      }
    }
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/**********************************************************************
 ���� ����� ������������ ��� ���������� ����������� ������� ��������
 ����� ��������� ������������� ������ �� ����� ������. ���� ����������
 true, �� ���� ������, ������������ ������� t, ��������� � ��������.
***********************************************************************/
bool Automaton::ProcessLexem(
                              const BethToken &/*t*/,
                              Macro_Parser& /*txt*/,
                              const Binarization_Options& /*options*/
                             )
{ return false; }
#endif


void Automaton::PrintMap( OFormatter &txtfile )
{}


#if defined SOL_LOADBIN
/********************************************************************************
 ����� ��������� ���������� � ���������� �������� �� ���������� ��������� ������
 (�����). � ����������� ������ ����� �����������, �� ��� ������� ����� ������
 ���� ������ ��� �������� ������� ���������� param.
*********************************************************************************/
void Automaton::LoadBin( lem::Stream &bin, const Load_Options &opt )
{
 if( bin.read_bool() && param!=NULL )
  param->LoadBin(bin);

 return;
}
#endif

#if defined SOL_SAVEBIN
/****************************************************************************
 ����� ��������� ���������� � ����������� �������� � �������� ������ (�����).
 ����������� ������ ����������� �����, �� ������ � ����� ������ ������� ���
 ������� ��� ���������� ���������� ������� ����������.
*****************************************************************************/
void Automaton::SaveBin( lem::Stream &bin ) const
{
 bin.write_bool( param!=NULL );
 if( param!=NULL )
  param->SaveBin(bin);

 return;
}
#endif

/*
#if defined SOL_CAA && !defined SOL_NO_AA
PhrasoBlock* Automaton::Process( PhrasoBlock *block )
{
 if( GetDebugLevel()>3 && lem::LogFile::IsOpen() )
  lem::LogFile::logfile->printf(
                                "OVERDEBUGGING: automaton [%us] ::Process(...) phrasoblock key=%d\n",
                                GetName().c_str(),
                                block!=NULL ? block->GetKey() : UNKNOWN
                               );

 return block;
}
#endif
*/

#if defined SOL_REPORT
/********************************************************************
 ����� ���������� ������ ��� ������ � ������� �������� � ����������
 ��������� ������, ����� ����������� �������� � ��� �����.
*********************************************************************/
void Automaton::Report( OFormatter &mrep )
{
 mrep.printf(
             "Automaton [%us]:\n"
             , GetName().c_str()
            );

 return;
}
#endif


// ****************************************************
// ��� ��������� ������� � ��������� �����-������...
// ****************************************************
const Sol_IO& Automaton::GetIO(void) const
{ return dict->GetIO(); }
