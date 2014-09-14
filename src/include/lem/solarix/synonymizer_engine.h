#ifndef SYNONYMIZER_ENGINE__H
#define SYNONYMIZER_ENGINE__H
#pragma once

// -----------------------------------------------------------------------------
// File synonymize_engine.h
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
// SOLARIX Grammar engine and Search Engine API functions (DLL/SO)
// API ��� ������� � ��������������� ������ � ���������� � ���� ������� DLL/SO.
//
// 09.10.2006 - �����������, � ������ �������� API ������ ������������� �����
//              �������� "sol_"
//
// 09.10.2006 - ������ ���������� ����������� ���������� ��������� (RegexEx)
//
// 12.10.2006 - ������� ��������� sol_TranslateToBase - ����� ����������� �
//              ������� �����. 
//
// 15.10.2006 - ���������� ��������������� � ���������� ������ ����������.
//
// 21.11.2006 - � ��������� sol_TranslateToBase �������� ����� ��������.
//
// 05.05.2007 - changing API to implement a new multithreading features of
//              the search engine.
//
// 08.09.2007 - API ������ PRO � LITE ������� ��������� �����������,
//              ���������������� � LITE ��������� �������� ����������.
//
// 27.09.2007 - ��������� sol_GetResultW ��� ��������� ������ ����������� � wchar_t
// 13.11.2008 - ��������� sol_CreatePortableSearcher � sol_AttachPortableIndex
// 15.11.2008 - ��������� ������ ��������� �������� ����
// 03.02.2009 - �������� ���� FG_OMIT_FREQ1 ��� ������������� � ��������������
//              N-����� � ��������� ��������.
// 13.02.2009 - �������� API ������ SentenceBroker
// 24.02.2009 - ������� sol_EnumInClass ���������� 3 ��� �����
// 25.02.2009 - ��������� sol_PreloadNGramsCaches
// 02.03.2009 - ��� sol_Tokenize � sol_CreateSentenceBroker ��������� ��������
//              �����.
// 08.04.2009 - ������ sol_PreloadNGramsCaches
// 10.04.2009 - ��������� API �������������� (sol_Paraphrase)
// 20.07.2009 - ����������� API ������� � ���� N-�����: ������ sol_SeekNGrams,
//              ��������� sol_Seek2Grams, sol_Seek3Grams, sol_Seek4Grams,
//              sol_Seek5Grams
// 03.11.2009 - ��������� ��������� sol_MorphologyAnalysis ��� ����������
//              ���������������� ������� � ������ ���������.
// 22.03.2010 - ��������� ��������� FG_RANDOMIZE ��� ��������� ������ ��������
//              ������������� ������ - ������������.
// 21.07.2010 - ��������� ������� sol_SetTagsXXX ��� ���������� ��������� ��
//              ��������� ����. 
// 10.09.2010 - ����� ������� sol_BuildKnowledgeBase2 ��� ��������� ����������
//              ������ ����� ������������� �������.   
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->10.09.2010
// --------------

#if defined DLL_EXPORTS || defined FAIND_IENGINES
 #define FAIND_EXPORTS
#else
 #define FAIND_IMPORTS
#endif

#undef DLL_ENTRY

#if defined FAIND_IMPORTS
 #if defined LEM_WINDOWS || defined WIN32
  #define FAIND_API(RetType) extern RetType __stdcall
 #else
  #define FAIND_API(RetType) extern "C" RetType
 #endif
#elif defined GREN_EXPORTS || defined FAIND_EXPORTS
 #if defined LEM_WINDOWS || defined WIN32
  #define FAIND_API(RetType) __declspec(dllexport) RetType __stdcall
 #else
  #define FAIND_API(RetType) extern "C" RetType __attribute__((visibility("default")))
 #endif
#else
 #error
#endif



#if !defined FAIND_INTERNAL_TYPES

 typedef void* HFAIND;
 typedef void* HSOL_INDEXER;
 typedef void* HFAINDCMD;
 typedef void* HFAINDXML;
 typedef void* HREGEXEX;
 typedef void* HFAINDPARAMS;

 typedef void* HGREN_STR;
 typedef void* HGREN_INTARRAY;
 typedef void* HGREN_WCOORD;
 typedef void* HGREN_RESPACK;
 typedef const void* HGREN_TREENODE;
 typedef void* HGREN_PHRASOMAT;
 typedef void* HGREN_FGTEMPLATE;
 typedef void* HGREN_SBROKER;

#endif // !defined DLL_EXPORTS


// ������������� ������ � �������������� ������.
// ������� � ������ ������� ���������� ���� �� �����������.
FAIND_API(HFAIND) sol_CreateSearchEngine(void);
FAIND_API(HFAIND) sol_CreatePortableSearcher( int flags );

// ������������� � ������ ��������������� ������, ��������� ������� �� ���������� �����
FAIND_API(HFAIND) sol_CreateGrammarEngineW( const wchar_t *DictionaryXml );
FAIND_API(HFAIND) sol_CreateGrammarEngineA( const char *DictionaryXml );
#if defined UNICODE || defined _UNICODE 
#define sol_CreateGrammarEngine sol_CreateGrammarEngineW
#else
#define sol_CreateGrammarEngine sol_CreateGrammarEngineA
#endif

FAIND_API(int) sol_LoadGrammarEngine( HFAIND hEngine );

// �������� ���������� ������, ������������ ���� ��������.
FAIND_API(int) sol_DeleteSearchEngine( HFAIND hEngine );
FAIND_API(int) sol_DeleteGrammarEngine( HFAIND hEngine );

// ��� ������������� ���������� (sol_CreatePortableSearcher) - ���������� ������ �
// ��������� ����� ��� ������������ ������.
FAIND_API(int) sol_AttachPortableIndex( HFAIND hEngine, const wchar_t *IndexFolder );

// ���������� ������������� ���������� ������ - �������� ����������
// �� ���������� ����������������� �����.
FAIND_API(int) sol_ReadIniW( HFAIND hEngine, const wchar_t *ini_filename );
FAIND_API(int) sol_ReadIniA( HFAIND hEngine, const char *ini_filename );
#if defined UNICODE || defined _UNICODE 
#define sol_ReadIni sol_ReadIniW
#else
#define sol_ReadIni sol_ReadIniA
#endif


// ��������� ����������� ���������� ���������� ������ � ��������� ����.
// ������������: 0 - ����������� ��������, -1 ������ �������� ����� �������
FAIND_API(int) sol_OpenLogFileA( HFAIND hEngine, const char *logfilename );
FAIND_API(int) sol_OpenLogFileW( HFAIND hEngine, const wchar_t *logfilename );
#if defined UNICODE || defined _UNICODE 
#define sol_OpenLogFile sol_OpenLogFileW
#else
#define sol_OpenLogFile sol_OpenLogFileA
#endif


// ���������� ����������� � ������, ���� ������� �����������.
FAIND_API(void) sol_CloseLogFile( HFAIND hEngine );

// Load the dictionary (morphology and syntax analyzer + thesaurus)
// Return: 2 - already loaded, 1 - ok, 0 - error has occured.
FAIND_API(int) sol_LoadDictionaryA( HFAIND hEngine, const char *Filename );
FAIND_API(int) sol_LoadDictionaryW( HFAIND hEngine, const wchar_t *Filename );
#if defined UNICODE || defined _UNICODE 
#define sol_LoadDictionary sol_LoadDictionaryW
#else
#define sol_LoadDictionary sol_LoadDictionaryA
#endif


// ������������ ���������� ������ ��� HTML ��������, � �� XML �� ���������.
FAIND_API(void) sol_GenerateHtml( HFAIND hEngine );

// Generate XML results (this is default behaviour of the engine).
FAIND_API(void) sol_GenerateXml( HFAIND hEngine );

// Result page is not needed.
FAIND_API(void) sol_NoResults( HFAIND hEngine );


// � HTML ����������� �� ��������� ���������
// (���� <html><title>...</title><body> � ����������� </body></html>).
FAIND_API(void) sol_StripHtml( HFAIND hEngine );


// ��������� ����� ������� � ��������� ��������� ������. ����������
// 0, ���� ������ �� ����, 1 ���� ����. ��������� �� ����� ����� ���� NULL,
// ����� ������ ������������ ������� ������� ������.
FAIND_API(int) sol_GetError( HFAIND hEngine, wchar_t *buffer, int buffer_len );


// ������� ���������� ������� ������
FAIND_API(void) sol_ClearError( HFAIND hEngine );


// FAIND_API(int)  sol_SearchText( HFAIND hEngine, const wchar_t *query, const wchar_t *text );

// ��������� ��� ������ � ������� ���������� ��� ����������� � ��������.
FAIND_API(HFAINDPARAMS) sol_CreateParams( HFAIND hEngine );
FAIND_API(int) sol_DeleteParams( HFAINDPARAMS hParams );
FAIND_API(int) sol_AddParam( HFAINDPARAMS hParams, const wchar_t *ParamName, const wchar_t *ParamValue );

// Parse the query and return the executor handle.
FAIND_API(HFAINDCMD) sol_ParseQuery( HFAIND hEngine, const wchar_t *query );
FAIND_API(HFAINDCMD) sol_ParseSqlQuery( HFAIND hEngine, const wchar_t *query );
FAIND_API(HFAINDCMD) sol_ParseQueryWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );
FAIND_API(HFAINDCMD) sol_ParseSqlQueryWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );

// Run the executor which executes the query.
FAIND_API(int) sol_ExecuteQuery( HFAIND hEngine, HFAINDCMD hCmd );

// Delete the executor after all.
FAIND_API(void) sol_DeleteQuery( HFAINDCMD hCmd );

// Do sol_ParseQuery, sol_ExecuteQuery, sol_DeleteQuery
FAIND_API(int) sol_Execute( HFAIND hEngine, const wchar_t *query );
FAIND_API(int) sol_ExecuteSql( HFAIND hEngine, const wchar_t *query );
FAIND_API(int) sol_ExecuteWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );
FAIND_API(int) sol_ExecuteSqlWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );


// ���������� ����� (� �������� char) ������ ����������.
FAIND_API(int) sol_GetResultLen( HFAINDCMD hCmd );

// �������� ���������� ������ � ��������� �����, ������� ������ ����� �����������
// ����� (��. sol_GetResultLen).
FAIND_API(void) sol_GetResult( HFAINDCMD hCmd, char *buffer );
FAIND_API(void) sol_GetResultW( HFAINDCMD hCmd, wchar_t *buffer );

// Returns the size (in wchar_t's + 1) of the buffer needed for storing the list of
// index names. The list can be retrieved via sol_GetDomainsList call.
FAIND_API(int) sol_GetDomainsListSize( HFAIND hEngine );

// Returns the number of indexes whose names are listed in 'Buffer'.
// Each index name is followed  by 'Delimiter' char
FAIND_API(int) sol_GetDomainsList( HFAIND hEngine, wchar_t Delimiter, wchar_t *Buffer );
FAIND_API(HFAINDXML) sol_GetDomainsListXml( HFAIND hEngine );

FAIND_API(int) sol_XmlTextLen( HFAINDXML xml );
FAIND_API(int) sol_GetXmlText( HFAINDXML xml, char *Buffer, int BufferSize );
FAIND_API(void) sol_DeleteXml( HFAINDXML xml );

// ���������� ���������� ���������� ��������
FAIND_API(int) sol_CountDomains( HFAIND hEngine );

// ���������� ��������� (��� NULL) �� ������ ���������� � �������.
FAIND_API(const wchar_t*) sol_GetDomainComment( HFAIND hEngine, const wchar_t *Domain_Name );

// ����� ����������� ������� � �������� ������, ������������ id ������� ���� -1, ����
// ����� ����������.
FAIND_API(int) sol_FindDomain( HFAIND hEngine, const wchar_t *Domain_Name );



// ***************************************************************************
// ������ �������� ��� ������ � ������������ ����������� ����������� (RegexEx)
// ***************************************************************************

// ����������� � ����������
FAIND_API(HREGEXEX) sol_CreateRx( HFAIND hEngine, const wchar_t *Pattern );
FAIND_API(void) sol_DeleteRx( HREGEXEX hRegex );

// ��������� ����������
FAIND_API(void) sol_SetMorphologyRx( HREGEXEX hRegex, int Mode );
FAIND_API(void) sol_SetSyntaxRx( HREGEXEX hRegex, int Mode );
FAIND_API(void) sol_SetSameSentenceRx( HREGEXEX hRegex );
FAIND_API(void) sol_SetDistanceRx( HREGEXEX hRegex, int Distance );
FAIND_API(void) sol_SetOrderedRx( HREGEXEX hRegex, int Ordered );
FAIND_API(void) sol_EnableThesaurusRx( 
                                     HFAIND hEngine, 
                                     HREGEXEX hRegex,
                                     int Jumps,
                                     int Synonyms,
                                     int Grammar,
                                     int Semantics,
                                     int Translations
                                    );
FAIND_API(void) sol_SetSoundexRx( HREGEXEX hRegex, int Enable );
FAIND_API(void) sol_AllowPartialMatchingRx( HREGEXEX hRegex, int Allow );
FAIND_API(void) sol_SetStripAccentsRx( HREGEXEX hRegex, int Strip );
FAIND_API(void) sol_SetOnlyOneMatchRx( HREGEXEX hRegex, int OnlyOne );

// ����� � ������ �����������
FAIND_API(int) sol_SearchRx( HREGEXEX hRegex, const wchar_t *Begin, const wchar_t *End );
FAIND_API(int) sol_CountMatchesRx( HREGEXEX hRegex );
FAIND_API(int) sol_GetMatchTextLenRx( HREGEXEX hRegex, int Index );
FAIND_API(void) sol_GetMatchTextRx( HREGEXEX hRegex, int Index, wchar_t *Buffer, int BufferSize );
FAIND_API(double) sol_GetMatchRankRx( HREGEXEX hRegex, int Index );

FAIND_API(int) sol_FindTaggedDocument( HFAIND hEngine, const wchar_t *Filename, const wchar_t *Location );
FAIND_API(int) sol_GetDocumentTag( HFAIND hEngine, int Id_doc, const wchar_t *Tag, wchar_t **Value );
FAIND_API(int) sol_AddTaggedDocument( HFAIND hEngine, const wchar_t *Filename, const wchar_t *Location );
FAIND_API(int) sol_SetDocumentTag( HFAIND hEngine, int Id_doc, const wchar_t *Tag, const wchar_t *Value );




const int FG_LOGICS                    = 0x00000001;
const int FG_GERUND1                   = 0x00000002;
const int FG_GERUND2                   = 0x00000004;
const int FG_QUEST                     = 0x00000008; // ������������ ��������������
const int FG_EXCLAM                    = 0x00000010; // ������������ ���������������
const int FG_INTRO                     = 0x00000020;
const int FG_COMPLEX                   = 0x00000040;
const int FG_MULTISENT                 = 0x00000080;
const int FG_SUBSTWORDS                = 0x00000100;
const int FG_COMSENT                   = 0x00000200; // ������������ ����������������� �����������

const int FG_USE_LEX_WHEN_EXHAUSTED    = 0x00000400; // ���� ������������� ����� �����������, 
                                                     // �� ������������ ������ ��������, � ��
                                                     // �������� ������������� ������
const int FG_EXTRACT_FIRST             = 0x00000800; // �������� �� �������� �� ��������������
                                                     // ������, � ���� �� �����

const int FG_DONT_REMOVE_USED          = 0x00001000; // �� ������� �� �������������� ������ ��������������. 
const int FG_GENERATOR_USES_NGRAMS     = 0x00002000; // ��������� ������ ���������� ���� N-�����
const int FG_GENERATOR_USES_CHAINS     = 0x00004000; // ��������� ������ �� ������ �������������� ��������


// ����� ��� sol_Paraphrase
const int FG_TOKENIZE                  = 0x00000001; // ����������� (��� ��������)
const int FG_TRANSFORM                 = 0x00000002; // ���������������� - ������� ��-�������������� ������
const int FG_SYNONYMIZE                = 0x00000004; // ��������� �������������
const int FG_SYNONYMIZER_MULTIWORD     = 0x00000008; // ������������ ������� (������������) ��������
const int FG_PARAFRASE_REORDER         = 0x00000010; // ���������������� - �������� ������� ����
const int FG_PARAFRASE_CONSERVATIVE    = 0x00000020; // ���������������� - ������������� ���������� � ������������� �������, �������� � ��������� ������ � �.�.
const int FG_RANDOMIZE                 = 0x00000040; // ������������ ������ - ����������� ��������� ��� �������� ���� � ����������� �������������� �����

// ����� ������������ - ��������� � FG_RANDOMIZE
const int FG_RND_NOUN                  = 0x00001000; // �������� � ����������������
const int FG_RND_ADJ                   = 0x00002000; // �������� � ���������������
const int FG_RND_VERB                  = 0x00004000; // �������� � ���������
const int FG_RND_ADVERB                = 0x00008000; // �������� � ���������


// ����� ���������� N-��������
const int FG_NO_NGRAMS                 = 0x00000000; // �� ������������ N-������ 
const int FG_SYNONYMIZER_USES_NGRAMS   = 0x00000001; // ��������� ����������� ������������� �� ������� N-�����
const int FG_PEDANTIC_NGRAMS           = 0x00000002; // ���������� � ���������� ����� ���������
const int FG_OMIT_FREQ1                = 0x00000010; // ������������ N-������ � �������� 1
const int FG_2GRAMS                    = 0x00000020; // ����������� �� 2�������
const int FG_23GRAMS                   = 0x00000040; // ����������� �� 2�������, 3������ ��� ���������� �������
const int FG_3GRAMS                    = 0x00000100; // ����������� �� 2 � 3�������
const int FG_4GRAMS                    = 0x00000200; // ����������� �� 2, 3 � 4�������
const int FG_5GRAMS                    = 0x00000400; // ����������� �� 2, 3, 4 � 5�������
const int FG_2345GRAMS                 = 0x00000800; // ����������� �� 2�������, 3, 4 � 5 ������ ��� ���������� �������
const int FG_SYNONYMIZER_USES_1GRAMS   = 0x00001000; // ������������ ��������� ��� ������ ��������� � ������������ ������������ �� ��������� ����������


// Results format
const int FG_YIELD_PLAIN_TEXT          = 0x00000000;
const int FG_YIELD_XML                 = 0x00000001;
const int FG_YIELD_ALL_SYNS            = 0x00000002; // �������� � XML ����������� ��� ��������� �������� ��� ������� ��������� �����

// Debug options
const int FG_NO_DEBUG                  = 0x00000000;
const int FG_DEBUG                     = 0x00000001; // ��������� ���������� ����������� �������������
const int FG_DEBUG_HTML                = 0x00000002; // ��������� ���������� ����������� ������������� � ������� HTML

// Syntax analyzer flags
const int FG_SIMPLE_ANALYSIS           = 0x00000001; // ����������, ������� ������
const int FG_PEDANTIC_ANALYSIS         = 0x00000002; // ������������ ���������, �� ����� ������ �������������� ������


// ������� ���� - ���������� ��������� �����
const int FG_FORCE_LI   = 0x01000000; // ��������� ������� �� � ������� 
const int FG_FORCE_TO   = 0x02000000; // ��������� ������� �� � ����������������-��������

FAIND_API(HGREN_PHRASOMAT) sol_CreatePhraseGenerator( HFAIND hEngine, int ilang );
FAIND_API(int) sol_StopSynonyms( HGREN_PHRASOMAT hBuilder, int n, const int *words_ie, int use_thesaurus );
FAIND_API(int) sol_SetWordsForPhrase( HGREN_PHRASOMAT hBuilder, int n, const int *words_ie, int use_thesaurus );
FAIND_API(int) sol_Set2GramsForPhrase( HGREN_PHRASOMAT hBuilder, int npairs, const int *words_ie );
FAIND_API(wchar_t*) sol_GeneratePhrase( HGREN_PHRASOMAT hBuilder, int PhraseType, int DebugFlags );
FAIND_API(int) sol_GeneratePhrase2( HGREN_PHRASOMAT hBuilder, int PhraseType, int DebugFlags, wchar_t *Buffer, int maxlen );
FAIND_API(int) sol_DeleteGeneratedPhrase( wchar_t *Phrase );
FAIND_API(int) sol_DeletePhraseGenerator( HGREN_PHRASOMAT hBuilder );
FAIND_API(void) sol_RandomizePhraseGenerator( HGREN_PHRASOMAT hBuilder );

FAIND_API(int) sol_BuildKnowledgeBase(
                                      HFAIND hEngine,
                                      const wchar_t *DocumentsFolder,
                                      const wchar_t *DestinationFolder,
                                      int LanguageId,
                                      int Flags
                                     );

FAIND_API(int) sol_LoadKnowledgeBase( HGREN_PHRASOMAT hBuilder, const wchar_t *FolderPath );

FAIND_API(int) sol_BuildKnowledgeBase2(
                                       HGREN_PHRASOMAT hEngine,
                                       const wchar_t *EtalonFile,
                                       int Order,    
                                       int Flags
                                      );

FAIND_API(int) sol_Paraphrase(
                              HGREN_PHRASOMAT hBuilder,
                              int PhraseTypeFlags,
                              int SyntaxAnalysisFlags,
                              int NGramFlags,
                              int ThesaurusFlags,
                              int DebugFlags,
                              int ResultsFormat,
                              int MaxSubst,
                              const wchar_t *OrgPhrase,
                              wchar_t *NewPhrase,
                              int maxlen,
                              int max_elapsed_msec
                             );

FAIND_API(int) sol_Paraphrase8(
                               HGREN_PHRASOMAT hBuilder,
                               int PhraseTypeFlags,
                               int SyntaxAnalysisFlags,
                               int NGramFlags,
                               int ThesaurusFlags,
                               int DebugFlags,
                               int ResultsFormat,
                               int MaxSubst,
                               const char *OrgPhrase8,
                               char *NewPhrase8,
                               int maxlen,
                               int max_elapsed_msec
                              );


#if !defined FAIND_IENGINES

#if defined SOLARIX_GRAMMAR_ENGINE || defined GREN_IMPORTS
// Load the dictionary (morphology and syntax analyzer + thesaurus)
// Return: 2 - already loaded, 1 - ok, 0 - error has occured.
FAIND_API(int) sol_LoadDictionaryA( HFAIND hEngine, const char *Filename );
FAIND_API(int) sol_LoadDictionaryW( HFAIND hEngine, const wchar_t *Filename );
#if defined UNICODE || defined _UNICODE 
#define sol_LoadDictionary sol_LoadDictionaryW
#else
#define sol_LoadDictionary sol_LoadDictionaryA
#endif
#endif

#endif // #if !defined FAIND_IENGINES



// Return the Solarix project version info.
// ���� ��������� Major, Minor, Build �� ����� NULL, �� ����� ���
// ������������ ��������������� ����� ������ ������ ����������.
//
// ���������� 0 ��� LITE, 1 ��� PRO, 2 ��� PREMIUM
FAIND_API(int) sol_GetVersion( HFAIND hEngine, int *Major, int *Minor, int *Build );

// ���������� ����� ������ ������������ �������.
FAIND_API(int) sol_DictionaryVersion( HFAIND hEngine );


// ***********************************************************************
// Count the total number of entries in dictionary.
// ������� ��������� ������ � �������.
// ***********************************************************************
FAIND_API(int) sol_CountEntries( HFAIND hEngine );

// ***********************************************************************
// Count the total number of wordforms in dictionary.
// ������� ��������� (���� ������������) � �������
// ***********************************************************************
FAIND_API(int) sol_CountForms( HFAIND hEngine );


FAIND_API(int) sol_LemmatizeWord( HFAIND h, wchar_t *word, bool Allow_Dynforms );

// *****************************************************
// ���������� ���������: ������� ������� �����.
// ����� ����� ������ � ������ Pro, ��� ��� ������ Free
// ����� ��������� ������� ��� ���������.
// *****************************************************
FAIND_API(int) sol_CountLinks( HFAIND hEngine );

// ***********************************************************************
// Returns the max lexem length
// ���������� ������������ ����� �������
// ***********************************************************************
FAIND_API(int) sol_MaxLexemLen( HFAIND hEngine );


// *******************************************
// Set the default language ID.
// ������������� ���� �� ���������. ������������� ��� �����
// ����� ������� � ����� _sg_api.h
// *******************************************
FAIND_API(int) sol_SetLanguage( HFAIND hEngine, int Language );



// ***************************************************************************
// Find the entry index.
// Other API functions use this index to perform operations on words without
// repeated search in dictionary.
//
// ����� ������� ��������� ������ �� ���������� ������. ������ �������
// �������������� ������ ����� ��������� �������� �� ������� � ��������������
// ����� ������� (����� �� ��������� ����� � �������).
// ***************************************************************************
FAIND_API(int) sol_FindEntry(
                            HFAIND hEngine,
                            const wchar_t *Word, // Entry name
                            int Class,           // Required grammatical class 
                            int Language         // Language ID (if ambiguos)
                            );


FAIND_API(int) sol_FindClass( HFAIND hEngine, const wchar_t *ClassName );
FAIND_API(int) sol_FindEnum( HFAIND hEngine, const wchar_t *EnumName );
FAIND_API(int) sol_FindEnumState( HFAIND hEngine, int Enum, const wchar_t *StateName );

// ���������, ����� ���� ������ ������� Enum ��� ������ Class: 0 - �� ����� ���������,
// 1 - ������� (����� ��� ���� ��������� ������), 2 - ��������� (�������� ����������),
// 3 - ���
FAIND_API(int) sol_EnumInClass( HFAIND hEngine, int Class, int Enum );

#define sol_FindStrings( hEngine, Word ) sol_FindStringsEx(hEngine,Word,false,false,false,false,false,0)


// ����� ���� ��������� ��� ���������� �����, � ��������� ������ ���������
// �� ���������. ������������ ������ �� ������� �����.
FAIND_API(HGREN_STR) sol_FindStringsEx(
                                      HFAIND hEngine,
                                      const wchar_t *Word,
                                      bool Allow_Dynforms,
                                      bool Synonyms,
                                      bool Grammar_Links,
                                      bool Translations,
                                      bool Semantics,
                                      int nJumps
                                     );


FAIND_API(int) sol_CountStrings( HGREN_STR h );
FAIND_API(int) sol_GetStrings( HGREN_STR h, wchar_t **Res );
FAIND_API(int) sol_GetString( HGREN_STR h, int i, wchar_t *Res );
FAIND_API(int) sol_DeleteStrings( HGREN_STR h );


// ������� - ���������� ����� �������� � �����, ������� ���������� 
// "������", ���������� ��� ���� ���� ����� �����. � ������ �������������
// �������� ������, ������ 0. 
// ������ � ������ PRO 
FAIND_API(int) sol_Stemmer( HFAIND hEngine, const wchar_t *Word );


// ���������� "���" ��������� ������ - ������ ��� ������� �����,
// �� ����� ���� ������ ������ (��������, ������ ���� - ������
// � ���� - �������). ������ 0 � ������ ������, -1 ������.
FAIND_API(int) sol_GetEntryName(
                               HFAIND hEngine,
                               int EntryIndex,
                               wchar_t *Result
                              );

FAIND_API(int) sol_GetEntryCoordState(
                                      HFAIND hEngine,
                                      int EntryIndex,
                                      int coord
                                     );


// ���������� ������ ��������������� ������, � �������� ���������
// ��������� ������.
FAIND_API(int) sol_GetEntryClass( HFAIND hEngine, int EntryIndex );


// ���������� ��� ��������������� ������ �� ��� �������
FAIND_API(int) sol_GetClassName(
                               HFAIND hEngine,
                               int ClassIndex,
                               wchar_t *Result
                              );

// ���������� ��� ���������� �� �������
FAIND_API(int) sol_GetCoordName(
                                HFAIND hEngine,
                                int index,
                                wchar_t *Result
                               );

// ���������� ��� ��������� ���������� �� �������
FAIND_API(int) sol_GetCoordStateName(
                                     HFAIND hEngine,
                                     int coord,
                                     int state,
                                     wchar_t *Result
                                    );

// *************************************************************
// Returns the gender of noun (unapplayable for English) 
//
// ���������� ��� ���������������� (����������� ��� �����������)
// *************************************************************
FAIND_API(int) sol_GetNounGender( HFAIND hEngine, int EntryIndex );

// ��������� ���������������� - ���������� � ������ ����� ��������� ����� 
// EntryIndex ��������� ������ � �������� ������ Number � � ������ ������ Case.
FAIND_API(int) sol_GetNounForm(
                               HFAIND hEngine,   
                               int EntryIndex,
                               int Number,
                               int Case,
                               wchar_t *Result
                              );


// **************************************************************************
// ��������� ������� - ������������ ����� � ������ ����� Number, ���� Gender,
// ������� Tense � ���� Person.
// **************************************************************************
FAIND_API(int) sol_GetVerbForm(
                               HFAIND hEngine,  
                               int EntryIndex,
                               int Number,
                               int Gender,
                               int Tense,
                               int Person, 
                               wchar_t *Result
                               );


// *************************************************************************
// ��������� ��������������� � ������ ����� Number, ��� Gender, ����� Case,
// ����� �������������� Anim, �������-������ ����� Shortness, �����
// ��������� Compar_Form.
// *************************************************************************
FAIND_API(int) sol_GetAdjectiveForm(
                                   HFAIND hEngine,
                                   int EntryIndex,
                                   int Number,
                                   int Gender,
                                   int Case,
                                   int Anim,
                                   int Shortness,
                                   int Compar_Form, 
                                   wchar_t *Result
                                  );

// ***********************************************************************
// ������������ ���������������� � �������������. �������� �������� �����
// � (�����������) - ��������������/����������������.
// ***********************************************************************
FAIND_API(int) sol_CorrNounNumber(
                                 HFAIND hEngine, 
                                 int EntryIndex,   // id_entry
                                 int Value,        // � ����� ������ �����������
                                 int Case,         // NOMINATIVE_CASE_ru
                                 int Anim,         // INANIMATIVE_FORM_ru
                                 wchar_t *Result      // ����� ��� ����������
                                 );

FAIND_API(int) sol_CorrVerbNumber(
                                 HFAIND hEngine, 
                                 int EntryIndex,
                                 int Value,
                                 int Gender, 
                                 int Tense,
                                 wchar_t *Result
                                 );

FAIND_API(int) sol_CorrAdjNumber(
                                HFAIND hEngine, 
                                int EntryIndex,
                                int Value,
                                int Case, 
                                int Gender,
                                int Anim,  
                                wchar_t *Result
                               );

// ����� ��������� ������ � ���������� � ���, ��� ������� ����������� ����������
// ����� ������������� �������� ������ Word. ���������� ������ ������ EntryIndex,
// ������ ����� Form, � ������ ��������������� ������ � ��������� ������.
FAIND_API(int) sol_FindWord(
                            HFAIND hEngine, 
                            const wchar_t *Word,
                            int *EntryIndex,
                            int *Form,
                            int *Class 
                           );

FAIND_API(int) sol_GenerateWordform(
                                    HFAIND hEngine, 
                                    int ie,
                                    int npairs,
                                    const int *pairs,
                                    wchar_t *Result
                                   );



// ****************************************************************
// �����, �������� ������������� ���������� value, ����������� �
// ��������� ������������� (������������ �����)
// ****************************************************************
FAIND_API(int)sol_Value2Text(
                             HFAIND hEngine, 
                             wchar_t *Result,
                             int Value,
                             int Gender
                            );

// ������� ����� �����. ������������ ����� �������� ���, ���������� ��� ����
// ��������� � ������ ����� ��������� ������, ���� -1 ���� ����� �� ������.
FAIND_API(int) sol_SeekWord( HFAIND hEngine, const wchar_t *word, int Allow_Dynforms );


// ��������� ������ ���������� � ������������ ��������������
// ����������������, �������� "������->�����". ��� ������ ���������
// �������� (���������� � ���������� ������� �������)!
// ������� �������� EntryIndex - ��������� ����������� ������ sol_FindEntry.
// ������������ ������ ��������� ������ (���������������) ��� �������������,
// ��������, � sol_GetNounForm, ���� -1 ���� �������� � ����������������
// �� �������������� ���������.
FAIND_API(int) sol_TranslateToNoun( HFAIND hEngine, int EntryIndex );


// ���������� ��������� ������ � ������������ ��� ������������� ���������
// �������������� ����� ������� (����������).
FAIND_API(int) sol_TranslateToInfinitive( HFAIND hEngine, int EntryIndex );


// ���������� � ������� �����.
// ������ 1, ���� �������������� ����� �����, 0 ���� ����� �� ������� � �������.
// ��������� ������������ � Word, ������� �������� �����.
// ���� ����� ��������� ��������� �������������� ������� ����, �� �����
// ����������� �����-�� (�������������) ����.
FAIND_API(int) sol_TranslateToBase( HFAIND hEngine, wchar_t *Word, int AllowDynforms ); 


// ���������� ������ ������� ���� ��� �����. 
FAIND_API(HGREN_STR) sol_TranslateToBases( HFAIND hEngine, const wchar_t *Word, int AllowDynforms );


// ���������� ���� �������� ���������� ����� � ������ � ���������� �������.
// Find all possible mappings of the word to the lexicon and return tha handle of the list. 
FAIND_API(HGREN_WCOORD) sol_ProjectWord( HFAIND hEngine, const wchar_t *Word, int Allow_Dynforms );
FAIND_API(HGREN_WCOORD) sol_ProjectMisspelledWord( HFAIND hEngine, const wchar_t *Word, int Allow_Dynforms, int nmaxmiss );

// Count the number of mappings in the list. 
FAIND_API(int) sol_CountProjections( HGREN_WCOORD hList );

// The the list.
FAIND_API(void) sol_DeleteProjections( HGREN_WCOORD hList );

// Return the entry id (primary key). The entry properties can be accessed 
// via id, see sol_GetEntryName for example.
// ������������ id (primary key) ��������� ������ ����� ��������
FAIND_API(int) sol_GetIEntry( HGREN_WCOORD hList, int Index );

// ������������ ��������� ��������������� �������� Coord � �������� Index
FAIND_API(int) sol_GetProjCoordState(
                                     HFAIND hEngine,
                                     HGREN_WCOORD hList,
                                     int Index,
                                     int Coord
                                    );




// **************************************************************************
// ���������� ��������������� ������� - �� ����� �����, �� ������ ����������
// ������, �������� �������������� �������� ���������� ��������������� �����.
// ��� ������� �������� � ���� ��������, �������� ������������� ����������.
// **************************************************************************
FAIND_API(HGREN_RESPACK) sol_SyntaxAnalysis(
                                            HFAIND hEngine,
                                            const wchar_t *Sentence,
                                            bool Allow_Dynforms,
                                            bool Allow_Unknown,
                                            int max_msec,
                                            int Language
                                           );
FAIND_API(HGREN_RESPACK) sol_MorphologyAnalysis(
                                                HFAIND hEngine,
                                                const wchar_t *Sentence,
                                                bool Allow_Dynforms,
                                                bool Allow_Unknown,
                                                int max_msec,
                                                int Language
                                               );

// �������� ����������� ������� 
FAIND_API(void) sol_DeleteResPack( HGREN_RESPACK hPack );

// ������� �������������� ��������� ������� �����?  
FAIND_API(int) sol_CountGrafs( HGREN_RESPACK hPack ); 

// ������� �������� (����� �������� ������) � �������� �����?
FAIND_API(int) sol_CountRoots( HGREN_RESPACK hPack, int iGraf );

// ��������� ��������� �� �������� ���� �������� ������ 
FAIND_API(HGREN_TREENODE) sol_GetRoot( HGREN_RESPACK hPack, int iGraf, int iRoot );

// ���������� ������������� � ������� ���� �����
FAIND_API(int) sol_CountLeafs( HGREN_TREENODE hNode );

// ���������� ��������� �� �������� �����
FAIND_API(HGREN_TREENODE) sol_GetLeaf( HGREN_TREENODE hNode, int iLeaf );

// ���������� ������ ��������� ������ � ����
FAIND_API(int) sol_GetNodeIEntry( HFAIND hEngine, HGREN_TREENODE hNode );
FAIND_API(int) sol_GetNodeVerIEntry( HFAIND hEngine, HGREN_TREENODE hNode, int iver );

// ��������� ���������� ����
FAIND_API(void) sol_GetNodeContents( HGREN_TREENODE hNode, wchar_t *Buffer );

// ��������� ���������� ��� ����
FAIND_API(int) sol_GetNodeCoordState( HGREN_TREENODE hNode, int icoord );

// ���������� �������������� ������ ����������, ������� ��������.
FAIND_API(int) sol_GetNodeVersionCount( HFAIND hEngine, HGREN_TREENODE hNode );

// ��������� ������� ������������ ���� � ����
FAIND_API(int) sol_GetNodeCoordPair( HGREN_TREENODE hNode, int icoord, int istate );
FAIND_API(int) sol_GetNodeVerCoordPair( HGREN_TREENODE hNode, int iver, int icoord, int istate );

// ����� ��������� ������������ ��� � ����
FAIND_API(int) sol_GetNodePairsCount( HGREN_TREENODE hNode );
FAIND_API(int) sol_GetNodeVerPairsCount( HGREN_TREENODE hNode, int iver );

FAIND_API(int) sol_GetNodePairCoord( HGREN_TREENODE hNode, int ipair );
FAIND_API(int) sol_GetNodeVerPairCoord( HGREN_TREENODE hNode, int iver, int ipair );
FAIND_API(int) sol_GetNodePairState( HGREN_TREENODE hNode, int ipair );
FAIND_API(int) sol_GetNodeVerPairState( HGREN_TREENODE hNode, int iver, int ipair );


// ����� ������ � ���������
FAIND_API(HGREN_INTARRAY) sol_SeekThesaurus(
                                            HFAIND hEngine,
                                            int iEntry,
                                            int Synonyms,
                                            int Grammar_Links,
                                            int Translations,
                                            int Semantics,
                                            int nJumps
                                           );
FAIND_API(HGREN_INTARRAY) sol_Thesaurus(
                                        HFAIND hEngine,
                                        int iEntry,
                                        int Link
                                       );

FAIND_API(HGREN_SBROKER) sol_CreateSentenceBroker( HFAIND hEngine, const wchar_t *Filename, const wchar_t *DefaultCodepage, int language );
FAIND_API(HGREN_SBROKER) sol_CreateSentenceBrokerMem( HFAIND hEngine, const wchar_t *Text, int language );
FAIND_API(int) sol_FetchSentence( HGREN_SBROKER hBroker );
FAIND_API(int) sol_GetFetchedSentence( HGREN_SBROKER hBroker, wchar_t *Buffer );
FAIND_API(void) sol_DeleteSentenceBroker( HGREN_SBROKER hBroker );

FAIND_API(HGREN_STR) sol_Tokenize( HFAIND hEngine, const wchar_t *Sentence, int language );

// ����� �� ���� N-�����
FAIND_API(int) sol_Seek1Grams( HFAIND hEngine, int type, const wchar_t *word1 );
FAIND_API(int) sol_Seek2Grams( HFAIND hEngine, int type, const wchar_t *word1, const wchar_t *word2 );
FAIND_API(int) sol_Seek3Grams( HFAIND hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3 );
FAIND_API(int) sol_Seek4Grams( HFAIND hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3, const wchar_t *word4 );
FAIND_API(int) sol_Seek5Grams( HFAIND hEngine, int type, const wchar_t *word1, const wchar_t *word2, const wchar_t *word3, const wchar_t *word4, const wchar_t *word5 );
FAIND_API(int) sol_CountNGrams( HFAIND hEngine, int type, int Order, unsigned int *Hi, unsigned int *Lo );

FAIND_API(int) sol_CountInts( HGREN_INTARRAY h );
FAIND_API(int) sol_GetInt( HGREN_INTARRAY h, int i );
FAIND_API(void) sol_DeleteInts( HGREN_INTARRAY h );

FAIND_API(int) sol_IsLanguagePhrase( HFAIND hEngine, const wchar_t *Phrase, int Language );
FAIND_API(int) sol_GuessPhraseLanguage( HFAIND hEngine, const wchar_t *Phrase );
FAIND_API(int) sol_TranslatePhrase( HFAIND hEngine, const wchar_t *Phrase, int FromLanguage, int ToLanguage, wchar_t *ResPhrase, int maxlen );

FAIND_API(int) sol_Free( HFAIND hEngine, void *Ptr );

FAIND_API(int) sol_MatchNGrams( HFAIND hEngine, const wchar_t *Text, int * unmatched_2_ngrams, int *n2, int *n3 );
FAIND_API(int) sol_Syllabs( HFAIND hEngine, const wchar_t *OrgWord, wchar_t SyllabDelimiter, wchar_t *Result );

// Find the internal language index by its name (usually English name)
// Returns -1 if no language is found.
FAIND_API(int) sol_FindLanguage( HFAIND hEngine, const wchar_t *LanguageName );

// Probe the lexicon for language entries.
// Returns 1 if language is present in lexicon, 0 if not,
FAIND_API(int) sol_HasLanguage( HFAIND hEngine, int ilanguage );

// Set thesaurus tags. Empty string clears the previously installed tag.
FAIND_API(int) sol_SetTagsW( HGREN_PHRASOMAT hBuilder, const wchar_t *Tags, int Flags );
FAIND_API(int) sol_SetTagsA( HGREN_PHRASOMAT hBuilder, const char *Tags, int Flags );
FAIND_API(int) sol_SetTags8( HGREN_PHRASOMAT hBuilder, const char *Tags, int Flags );


#endif
