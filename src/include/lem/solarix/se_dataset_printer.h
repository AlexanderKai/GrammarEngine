#ifndef SE_DATASET_PRINTER__H
#define SE_DATASET_PRINTER__H
#pragma once

 #include <lem/ustreams.h>
 #include <lem/tuple.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/se_hit_statistics.h>
 #include <lem/solarix/se_general_options.h>
 
 namespace Solarix
 {
  namespace Search_Engine
  { 
   using lem::OFormatter;
   using lem::CodeConverter;
   using lem::FString;
   using lem::UFString;
   using Solarix::Search_Engine::File_Location;
   using lem::CodeConverter;
   using lem::Collect;
   using lem::MCollect;


   class Fix_Context;
   struct Pattern;
   struct Query;

  // ************************************************
  // Virtual class of result saver - descendants are
  // responsible for storing results in different
  // formats (TXT, XML, etc).
  //
  // ������� ����� ��� ������ � ��������� �����  
  // ************************************************ 
  class Base_DataSet_Printer
  {
   protected:	   
    const lem::UI::Resource_List &resx; // �������������� �������
    lem::Ptr<OFormatter> stream; // ����� ��� ������ ������ �����������
    const Solarix::Search_Engine::General_Options *generals;
	
    void PrepareStream(
                       const lem::UFString &name,
                       lem::Char_Stream::WideStreamType type,
                       const CodeConverter *encoding, 
                       const lem::Collect<lem::FString> &tunes
                      );

   public:
    Base_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources,
                         const UFString& filename, // ��� �����
                         lem::Char_Stream::WideStreamType type, // ����� ������ ������ ���� � ������
                         const CodeConverter *encoding, 
                         const Collect<lem::FString> &tunes // tuning options
                        );

    Base_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources,
                         lem::OFormatter *stream,
                         const lem::Collect<lem::FString> &tunes
                        );

    Base_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources
                        );

	virtual ~Base_DataSet_Printer(void);

    // ��������� ���������� ����� ������������ ���������������
    // ����������� ����������� - ������� ������ ���������
    // ������ ��������� ������, � ����� ��� ������� �����
    // �������� ��������� �������������� ����������.
    virtual bool CanShowRawFiles(void) const;

    // �������� ����� ������ ����������� ������ � �����������������
    // �����, � ������� - �� �������. ��� ����������� ������ ������
    // ����� ��������� ��� ��������, ���������� �� ����������
    // ���������� �������� ����������.
	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      )=0;

    // ��������������� ����� ����������� ������, ��������������
    // ������ ���������� ������������, �������� ��� ������ � 
    // �������� �����.
	virtual void PrintRaw(
                          const wchar_t *Zone_Name,
                          const File_Location &where
                         );

    // ���� ����� ���������� ��� ��������������� ������ �����������
    // ������ - �� �� ����������. �� �� ��������� ����, � ������ ����
    // ���������� ������ ��� ������ � ������� �������� ������, �����
    // �������� ��� ��������, ��������� ���������� � ������� ������ ������.
	virtual void PrintUnsorted(
                               const wchar_t *Zone_Name,
                               const File_Location &where,
                               const Fix_Context &ctx
                              ) {}

    // ������ ����� ������ (��� � ����� ������ - �������������� ������������������
    // � ��������������� � ����� �� �������� ������). ��� ����� ���� � ���� ������
    // � plain text (�������� ��������� ������� � ������������), � ����� �������� HTML.
    virtual void PrintSimple( const wchar_t *Text, const wchar_t *Format ) {}


    // ������ true, ���� � ���������� ���������� ����� Clear_Output
    virtual bool CanClearOutput(void) const { return false; }

    // ���������� ��� ������ ������ ������ ���� ������ - ����� ������ 
    // ��������������� ������.
    virtual void ClearOutput(void) {}

    // ���������� � ������ ������
    virtual void Print( const MCollect<Pattern*> &qlist )=0;
    virtual void Print( const Query &q )=0;

    // ���������� � ����� ������
    virtual void Print( const Hit_Statistics &hits, const Query &q )=0;
  };	    


	 

  class Xml_DataSet_Printer : public Base_DataSet_Printer
  {
   private:
    void WriteHeader(void);

   public:	   
	Xml_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        const UFString &filename,
                        const Collect<FString> &tunes
                       );

    Xml_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        OFormatter *stream,
                        const Collect<FString> &tunes
                       );

	virtual ~Xml_DataSet_Printer(void);

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );

    virtual void Print( const Hit_Statistics &hits, const Query &q );
    virtual void Print( const MCollect<Pattern*> &qlist );
    virtual void Print( const Query &q );
  };	   

  class Sql_DataSet_Printer : public Base_DataSet_Printer
  {
   private:
    void WriteHeader(void);

    bool oracle_varchar2; // ��������� ����������� �� ����� ������ VARCHAR2 � Oracle
    bool sqlplus; // ��� ��������� ������� � SQL*Plus ������� & ������������ \,
                      // ����� ��� ������������ ��� ��������� �������.

    void TuneUp( const Collect<FString> &tunes );

   public:	   
	Sql_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        const UFString &filename,
                        const Collect<FString> &tunes
                       );

    Sql_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        OFormatter *stream,
                        const Collect<FString> &tunes
                       );

    Sql_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        const Collect<FString> &tunes
                       );

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );

    virtual void Print( const Hit_Statistics &hits, const Query &q );
    virtual void Print( const MCollect<Pattern*> &qlist );
    virtual void Print( const Query &q );
  };	   

  
  #if defined FAIND_ODBC
  class Odbc_DataSet_Printer : public Sql_DataSet_Printer
  {
   private:
    lem::Database::SQL_ODBC *db; // ���������� � ��������.
    lem::DB_Stream *writer; // ����� ��� ������ SQL-������.

   public:	   
	Odbc_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources,
                         const UFString &connection,
                         const Collect<FString> &tunes
                        );

    virtual ~Odbc_DataSet_Printer(void);

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );
//    virtual void Print( const Hit_Statistics &hits );
//    virtual void Print( const MCollect<Pattern*> &qlist );
//    virtual void Print( const Query &q );
  };	   
  #endif


  class Html_DataSet_Printer : public Base_DataSet_Printer
  {
   private:
    FString encode;
    bool tabular;
    bool table_started;
    bool html_header_footer;
    bool print_query;

    void HandleTunes( const Collect<FString> &tunes );
    void PrintBanners(void);
    void WriteHeader(void);
    void WriteFooter(void);

   public:	   
	Html_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources,
                         const UFString &filename,
                         const Collect<FString> &tunes
                        );


    Html_DataSet_Printer(
                         const Solarix::Search_Engine::General_Options *opts,
                         const lem::UI::Resource_List &resources,
                         OFormatter *stream,
                         const Collect<FString> &tunes
                        );


	virtual ~Html_DataSet_Printer(void);

    inline void SetTabularFormat(void) { tabular=true; }
    inline void SetListingFormat(void) { tabular=false; }

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );
    virtual void Print( const Hit_Statistics &hits, const Query &q );
    virtual void Print( const MCollect<Pattern*> &qlist ) {}
    virtual void Print( const Query &q );
  };	   

  class Txt_DataSet_Printer : public Base_DataSet_Printer
  {
   private:
    bool rich; // ��������� ����������

   public:	   
	Txt_DataSet_Printer(
                        const Solarix::Search_Engine::General_Options *opts,
                        const lem::UI::Resource_List &resources,
                        const UFString &filename,
                        const Collect<FString> &tunes
                       );

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );

    virtual void Print( const Hit_Statistics &hits, const Query &q ) {}
    virtual void Print( const MCollect<Pattern*> &qlist ) {}
    virtual void Print( const Query &q ) {}
  };	   

  class Raw_DataSet_Printer : public Base_DataSet_Printer
  {
   public:
//	lem::MCollect< boost::tuple<lem::UFString*,Solarix::Search_Engine::File_Location*,Solarix::Search_Engine::Fix_Context*> > list;
    lem::MCollect< lem::triple<UFString*,File_Location*,Fix_Context*> > list;

   public:	   
	Raw_DataSet_Printer( const lem::UI::Resource_List &resources );

	virtual ~Raw_DataSet_Printer(void);

	virtual void Print(
                       const wchar_t *Zone_Name,
                       const File_Location &where,
                       const Fix_Context &ctx
                      );

    virtual void Print( const Hit_Statistics &hits, const Query &q );
    virtual void Print( const MCollect<Pattern*> &qlist ) {}
    virtual void Print( const Query &q );
  };	   

  }
 }

#endif
