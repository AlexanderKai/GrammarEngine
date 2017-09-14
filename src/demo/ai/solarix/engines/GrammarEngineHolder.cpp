// -----------------------------------------------------------------------------
// File GrammarEngineHolder.cpp
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project   http://www.solarix.ru
// SEARCH ENGINE Core
//
// Win32 DLL ��������� � ��������� ������.
// Old-fashioned Win32 DLL interface to the search engine.
//
// 24.01.2006 - API ���������, ������ ����� ��� ������������ ������� ��
//
// 24.01.2006 - API fuctions use wchar_t strings.
//
// 29.05.2006 - � ������� API ������ �������� 'HFAIND' - ����� ����������
//              ���������� ������.
//
// 06.08.2006 - ������� API - callback ������� "������ ��������� ��������" �
//              �������� ��������� �������� UNICODE ��� ��������
//
// 20.08.2006 - ��������� sol_Translate_To_Noun ��� ���������� ���� � �����
//              ���������������.
//
// 25.08.2006 - ��������� ��������� sol_Project_Word ��� ��������� ����
//              �������� ����� �� ��������, � ����� ������ �������� ��� ������
//              � ������������ ������� ��������� ��������. 
//
// 30.08.2006 - ��������� ��������� ��� ��������������� ������� � ������ � 
//              ������������ ������ �������. 
//
// 08.10.2006 - � ������ Pro ��������� ��������� API ��� ������ � RegexEx -
//              ������������ ����������� �����������.
//
// 15.10.2006 - ������ �������������� API ��� ������ � ������������.
//
// 21.11.2006 - ��������� ������� ��� ������������.
//
// 25.11.2006 - �������� sol_GetError - ���������� wchar_t ������ ��������
//              ������. 
//
// 28.11.2006 - ������� sol_UnloadDictionary.
//
// 27.09.2011 - �������� ����� ������� �������� ���������.
// 05.03.2012 - ���� ������ ::Load(...) � ��������� ��������������� ���� � ������� �������,
//              �� � ���� ������ ����������� �������� ��������, � �� ������ ������������ ���� "������ ��� ��������"
//
// 13.09.2017 - �����������, ����������� �� ������ ���������� ������
// -----------------------------------------------------------------------------
//
// CD->01.03.2005
// LC->13.09.2017
// --------------

#include <lem/config.h>

#if defined DLL_EXPORTS

#include <lem/conversions.h>
#include <lem/ustreams.h>
#include <lem/unicode.h>
#include <lem/solarix/version.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include "GrammarEngineHolder.h"

using namespace lem;
using namespace lem::Char_Stream;
using namespace Solarix;

GrammarEngineHolder::GrammarEngineHolder(void)
{
 sg = NULL;
 n_lexicon_reserve = 0;

 if( lem::UI::get_UI().IsRussian() )
  DefaultLanguage = RUSSIAN_LANGUAGE;
 else if( lem::UI::get_UI().IsFrench() )
  DefaultLanguage = FRENCH_LANGUAGE;
 else if( lem::UI::get_UI().IsSpanish() )
  DefaultLanguage = SPANISH_LANGUAGE;
 else
  DefaultLanguage = ENGLISH_LANGUAGE;

 // ��������� ����� ��������� �� �������
 nul_tty = new OFormatter( Path(NULL_DEVICE) );

 ok = true;

 return;
}

    
void GrammarEngineHolder::PostINI(void)
{}

GrammarEngineHolder::~GrammarEngineHolder(void)
{
 delete nul_tty;
 return;
}


void GrammarEngineHolder::SetError( const lem::UFString & error_text )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker locker(&cs_error);
 #endif

 error = error_text;
 return;
}



bool GrammarEngineHolder::Load( const wchar_t *DictionaryXml, bool LazyLexicon )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker guard(&cs);
 #endif
 
 lem::zbool loaded_ok;

 Solarix::Dictionary_Config cfg;

 if( n_lexicon_reserve!=0 )
  cfg.ldsize = n_lexicon_reserve;
 
 dict = new Solarix::Dictionary(NULL,NULL,cfg);

 lem::Path p(DictionaryXml);

 if( p.DoesExist() )
  {
   Load_Options opt;

   opt.affix_table     = true;
   opt.seeker          = true;
   opt.load_semnet     = true;
   opt.ngrams          = true;
   opt.lexicon         = !LazyLexicon;

   loaded_ok = dict->LoadModules( p, opt ) ? 1 : 0;

   seeker = dict->seeker;
   sg = &dict->GetSynGram();

   if( !!dict->affix_table )
    { 
     fuzzy = new Solarix::Search_Engine::Fuzzy_Comparator();
     fuzzy->ApplyDictionary( *dict );
    }

   lem::MCollect<int> langs;
   DefaultLanguage = dict->GetLanguages(langs);
  }
 else
  {
   lem::MemFormatter mem;
   mem.printf( "File [%us] does not exist", DictionaryXml );
   SetError(mem.string());
  }

 return loaded_ok;
}

#endif
