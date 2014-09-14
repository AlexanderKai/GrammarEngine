#ifndef SE_CMD_EXECUTORS__H
#define SE_CMD_EXECUTORS__H
#pragma once

 #include <lem/solarix/search_engine.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 

  #if defined FAIND_HELP_COMMAND
  // *************************************************************
  // Printing the help pages into the formatting lem::Stream.
  // ������ ���������� ���������� �� ������ � ��������� ���������.
  // *************************************************************
  class CmdHelp : public CmdExecutor
  {
   private:
    int div; // ����� ������ ������� ��������

    void Help_Basic( lem::OFormatter &out );
    void Help_Search_Domain( lem::OFormatter &out );
    void Help_Query( lem::OFormatter &out );
    void Help_Results( lem::OFormatter &out );
    void Help_Samples( lem::OFormatter &out );
    void Help_Formats( lem::OFormatter &out );
    void Help_Dictionary( lem::OFormatter &out );
    void Help_Tunes( lem::OFormatter &out );
    void Help_Caches( lem::OFormatter &out );
    void Help_Encodings( lem::OFormatter &out );
    void Help_Locales( lem::OFormatter &out );
    void Help_Plugins( lem::OFormatter &out );
    void Show_Version( lem::OFormatter &out );
    void Help_Contacts( lem::OFormatter &out );
  
   public:
    CmdHelp( lem::Ptr<Crawler> ptr, int Div );

    // does nothing, always returns 'true'
    virtual bool Do(void);

    // prints the help
    virtual void PrintResults( lem::OFormatter &out );
  };
  #endif

  // ************************************
  // ������� ������ (�������� �� �������)
  // ************************************
  class CmdSearch : public CmdExecutor
  {
   public:
    CmdSearch( lem::Ptr<Crawler> ptr ) : CmdExecutor(ptr) {}

    virtual bool Do(void);
    virtual void PrintResults( lem::OFormatter &out );
  };
   
 
  // ***************************************************
  // ��������� ����� ��� ����������� (������������),
  // �������� - �������� ������ ������� �������
  // ***************************************************
  class CmdIndexDDL : public CmdExecutor
  {
   public:
    CmdIndexDDL( lem::Ptr<Crawler> ptr );

    virtual bool Do(void);
  };



  // ***************************************************
  // �������������� ����������
  // ***************************************************
  class CmdIndexing : public CmdExecutor
  {
   public:
    CmdIndexing(lem::Ptr<Crawler> ptr );

    virtual bool Do(void);
    virtual void PrintResults( lem::OFormatter &out );
  };


  // **********************************************
  // �������� � ����� ��������� ����������
  // **********************************************
  class CmdDCache : public CmdExecutor
  {
   public:
    CmdDCache( lem::Ptr<Crawler> ptr );

    virtual bool Do(void);
  };

  #if defined FAIND_DATAMINE
  // **********************************************
  // �������� � ����������������
  // **********************************************
  class CmdTopicDB : public CmdExecutor
  {
   public:
    CmdTopicDB( lem::Ptr<Crawler> ptr );

    virtual bool Do(void);
  };
  #endif  


  #if defined SOLARIX_PRO
  // ***************************************************
  // ���������� ���-��������.
  // ***************************************************
  class CmdHttpd : public CmdExecutor
  {
   public:
    CmdHttpd( lem::Ptr<Crawler> ptr );

    void ParseArgs( const lem::Collect<UFString> &args, int ifrom );

    virtual bool Do(void);
  };
 #endif

  #if defined SOLARIX_PRO
  // ***************************************************
  // ���������� ����� �����
  // ***************************************************
  class CmdTagsDB : public CmdExecutor
  {
   public:
    CmdTagsDB( lem::Ptr<Crawler> ptr );

    void ParseArgs( const lem::Collect<UFString> &args, int ifrom );

    virtual bool Do(void);
  };
 #endif

  #if defined FAIND_PROBE_FEATURE
  class CmdProbeFeature : public CmdExecutor
  {
   public:
    CmdProbeFeature( lem::Ptr<Crawler> ptr );

    void ParseArgs( const lem::Collect<UFString> &args, int ifrom );

    virtual bool Do(void);
  };
  #endif

 }
}

#endif
