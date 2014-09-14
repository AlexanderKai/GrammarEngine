#ifndef FAIND__H
#define FAIND__H
#pragma once

// -----------------------------------------------------------------------------
// File FAIND.H
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
// SOLARIX Grammar engine and Search Engine API functions (Win32 DLL)
// API ��� ������� � ��������������� ������ � ���������� � ���� ������� Win32 DLL.
//
// ���� �������������� ��������� (������� �������, ���������, ��������� � �.�.)
// ��������� � ���� ������������� �������� � ����� _sg_api.h, �������
// ������������ ������������ YGRES.
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
// 22.12.2009 - API ��������������� ������ � �������������� �������� ���������
//              ������ 
// 13.04.2010 - �� ���� ������� bool ������� �� int ��� ����������� ��������
//              � ������� �������. 
// 09.05.2011 - ��������� ������� sol_LoadPlugins[W,A,8] ��� ��������
//              �������� �� ��������� ��������
// 10.05.2011 - ��������� ������� sol_LoadOCR[W,A,8] ��� �������� OCR ������
// -----------------------------------------------------------------------------
//
// CD->20.06.2005
// LC->10.05.2011
// --------------

#if defined WIN32
 #if defined LEM_MFC || defined MFC_VER
  #include <afxwin.h>
 #else 
  #include <windows.h>
 #endif
 #define FAIND_CALLBACK CALLBACK
#else
 #define FAIND_CALLBACK
 #define CALLBACK
#endif

typedef void (FAIND_CALLBACK *EngineCallbackProc_StartFile)( const wchar_t *Filename );
typedef void (FAIND_CALLBACK *EngineCallbackProc_StartFolder)( const wchar_t *Folder );
typedef void (FAIND_CALLBACK *EngineCallbackProc_Success)(
                                                          const wchar_t *filename,
                                                          const wchar_t *location,
                                                          const wchar_t *tmp
                                                         );


typedef const wchar_t* (CALLBACK *sol_DocumentProvider)( const wchar_t *Docname );

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
 typedef void* HGREN_LONGSTRING;

#endif // !defined DLL_EXPORTS


// ������������� ������ � �������������� ������.
// ������� � ������ ������� ���������� ���� �� �����������.
FAIND_API(HFAIND) sol_CreateSearchEngine(void);
FAIND_API(HFAIND) sol_CreatePortableSearcher( int flags );

// Load the dictionary (morphology and syntax analyzer + thesaurus)
// Return: 2 - already loaded, 1 - ok, 0 - error has occured.
FAIND_API(int) sol_LoadDictionaryA( HFAIND hEngine, const char *Filename );
FAIND_API(int) sol_LoadDictionaryW( HFAIND hEngine, const wchar_t *Filename );
#if defined UNICODE || defined _UNICODE 
#define sol_LoadDictionary sol_LoadDictionaryW
#else
#define sol_LoadDictionary sol_LoadDictionaryA
#endif

// �������� ���������� ������, ������������ ���� ��������.
FAIND_API(int) sol_DeleteSearchEngine( HFAIND hEngine );

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

// ������������ ���������� ������ ��� HTML ��������, � �� XML �� ���������.
FAIND_API(void) sol_GenerateHtml( HFAIND hEngine );

// Generate XML results (this is default behaviour of the engine).
FAIND_API(void) sol_GenerateXml( HFAIND hEngine );

// Result page is not needed.
FAIND_API(void) sol_NoResults( HFAIND hEngine );


// � HTML ����������� �� ��������� ���������
// (���� <html><title>...</title><body> � ����������� </body></html>).
FAIND_API(void) sol_StripHtml( HFAIND hEngine );

// returns the length of text buffer for error text (including terminating '\0')
FAIND_API(int) sol_GetErrorLen( HFAIND hEngine );
FAIND_API(int) sol_GetErrorLen8( HFAIND hEngine );

// ��������� ����� ������� � ��������� ��������� ������. ����������
// 0, ���� ������ �� ����, 1 ���� ����. ��������� �� ����� ����� ���� NULL,
// ����� ������ ������������ ������� ������� ������.
FAIND_API(int) sol_GetError( HFAIND hEngine, wchar_t *buffer, int buffer_len );
FAIND_API(int) sol_GetError8( HFAIND hEngine, char *BufferUtf8, int buffer_len );


// ������� ���������� ������� ������
FAIND_API(void) sol_ClearError( HFAIND hEngine );


FAIND_API(int) sol_SearchText( HFAIND hEngine, const wchar_t *query, const wchar_t *text );

// ��������� ��� ������ � ������� ���������� ��� ����������� � ��������.
FAIND_API(HFAINDPARAMS) sol_CreateParams( HFAIND hEngine );
FAIND_API(int) sol_DeleteParams( HFAINDPARAMS hParams );
FAIND_API(int) sol_AddParam( HFAINDPARAMS hParams, const wchar_t *ParamName, const wchar_t *ParamValue );

// Parse the query and return the executor handle.
FAIND_API(HFAINDCMD) sol_ParseQuery( HFAIND hEngine, const wchar_t *WideQuery );
FAIND_API(HFAINDCMD) sol_ParseQueryA( HFAIND hEngine, const char *AsciiQuery );
FAIND_API(HFAINDCMD) sol_ParseQuery8( HFAIND hEngine, const char *Utf8Query );

FAIND_API(HFAINDCMD) sol_ParseSqlQuery( HFAIND hEngine, const wchar_t *query );
FAIND_API(HFAINDCMD) sol_ParseQueryWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );
FAIND_API(HFAINDCMD) sol_ParseSqlQueryWithParams( HFAIND hEngine, const wchar_t *query, HFAINDPARAMS hParams );
FAIND_API(HFAINDCMD) sol_ParseQueryForText( HFAIND hEngine, const wchar_t *query, const wchar_t *text );

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


// ��������� ���������������� callback-�������� ��� ����������� �������� ������������
// ������ ��� ������ ��� ��������������.
//
// Return value:
//              0  - callback function is installed
//              -1 - an error has occured
FAIND_API(int) sol_SetCallback_StartFile( HFAIND hEngine, EngineCallbackProc_StartFile ptrFunction );
FAIND_API(int) sol_SetCallback_StartFolder( HFAIND hEngine, EngineCallbackProc_StartFolder ptrFunction );
FAIND_API(int) sol_SetCallback_Success( HFAIND hEngine, EngineCallbackProc_Success ptrFunction );

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
                                     int AllowSynonyms,
                                     int AllowGrammar,
                                     int AllowSemantics,
                                     int AllowTranslations
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

FAIND_API(int) sol_EnableTextCache( HFAIND hEngine, int Enable );

FAIND_API(int) sol_FindTaggedDocument( HFAIND hEngine, const wchar_t *Filename, const wchar_t *Location );
FAIND_API(int) sol_GetDocumentTag( HFAIND hEngine, int Id_doc, const wchar_t *Tag, wchar_t **Value );
FAIND_API(int) sol_AddTaggedDocument( HFAIND hEngine, const wchar_t *Filename, const wchar_t *Location );
FAIND_API(int) sol_SetDocumentTag( HFAIND hEngine, int Id_doc, const wchar_t *Tag, const wchar_t *Value );

FAIND_API(int) sol_CountStrings( HGREN_STR h );
FAIND_API(int) sol_GetStrings( HGREN_STR h, wchar_t **Res );
FAIND_API(int) sol_GetString( HGREN_STR h, int i, wchar_t *Res );
FAIND_API(int) sol_DeleteStrings( HGREN_STR h );

FAIND_API(int) sol_Free( HFAIND hEngine, void *Ptr );

FAIND_API(int) sol_LoadPluginsW( HFAIND hEngine, const wchar_t *Folder, int Flags );
FAIND_API(int) sol_LoadPluginsA( HFAIND hEngine, const char *Folder, int Flags );
FAIND_API(int) sol_LoadPlugins8( HFAIND hEngine, const char *FolderUtf8, int Flags );
#define sol_LoadPlugins(hEngine,Folder,Flags) sol_LoadPluginsW(hEngine,Folder,Flags)

FAIND_API(int) sol_LoadOCRW( HFAIND hEngine, const wchar_t *EngineFilename, int Flags );
FAIND_API(int) sol_LoadOCRA( HFAIND hEngine, const char *EngineFilename, int Flags );
FAIND_API(int) sol_LoadOCR8( HFAIND hEngine, const char *EngineFilenameUtf8, int Flags );
#define sol_LoadOCR(hEngine,EngineFilename,Flags) sol_LoadOCRW(hEngine,EngineFilename,Flags)


#endif
