#ifndef SE_INDEX_OPTIONS__H
#define SE_INDEX_OPTIONS__H
#pragma once

 // ��������� Indexer_Options - ����� ��������� �����������, 
 // ����� ��� ���� ����������� ������������ � ������ �������
 // ������.
 
 #include <boost/utility.hpp>
 #include <lem/zeroed.h>
 #include <boost/logic/tribool.hpp>
 #include <lem/fstring.h>
 #include <lem/noncopyable.h>
 #include <lem/ufstring.h>
 #include <lem/solarix/se_morphology.h>
 #include <lem/solarix/se_domain_info.h>

 #if defined FAIND_IDBLIST_MYSQL || defined FAIND_INDEXER_MYSQL
  #define FAIND_MYSQL
 #endif

 #if defined FAIND_MYSQL
  #include <lem/mysql/mysql.h>
 #endif

 namespace Solarix
 {
  namespace Search_Engine
  { 
   using boost::logic::tribool;

   // **************************************************
   // ��������� � ����������� ����������� � SQL backend
   // **************************************************
   struct SQLConnection : boost::noncopyable
   {
    lem::FString login;
    lem::FString psw;
    lem::FString db;   // ��� ���� ��� MySQL, ����� ��� Oracle, ��� DSN ��� ODBC
    lem::FString host; // ����� ����� (�����������, ���� SQL ������� �������).

    #if defined FAIND_MYSQL
    MYSQL* mysql;
    #endif
   
    SQLConnection(void);
    ~SQLConnection(void);

    // ������������ � ����
    void Connect(void);

    void Disconnect(void);

    // �������� ����������
    void Begin(void);

    // ��������� ����������
    void Commit(void);

    // ���������� ����������
    void Rollback(void);

    #if defined FAIND_MYSQL
    inline MYSQL* GetHandle(void) { return mysql; }
    #endif

    bool Connected(void) const;
   };


   #if defined FAIND_INDEXER
   // *****************************************
   // ����� ��� ���������� ������� ������������
   // *****************************************
   struct Indexer_Options
   {
    bool use; // ������������ �� ���������� ��� ������
    lem::Path storage; // ������� � ������� ����������� (���� �������� ���������)
    SQLConnection *connection; // ��������� ����������� � ��

    lem::zbool allow_clucene_wr; // ��������� ������������� ������ ������ ��������
                                 // � ��������� ��������� ��� ����������� CLucene

    lem::zbool allow_mysql_wr; // ��������� ������������� ������ ������ ��������
                               // � ��������� ��������� ��� ����������� MySQL
 
    lem::zbool ram_cataloguer; // ������ ���� �������������� ���� Idb_List_File_Ram ��� ������ � CD
    lem::Path preload_index_db; // ���� (����������, � ���������� ���������) ��� �������� � ����� ������� ��� ��������
    lem::UFString preload_index_name; // ��� ����� �������
    lem::zbool subst_cddrive; // ������������� �������� ��� ����� �� CDROM ��� ����� � ��������� ������

    Indexer_Options(void);

    Indexer_Options( const Indexer_Options &x );

    void operator=( const Indexer_Options &x );

    inline void Disable(void) 
    { use = false; }

    bool CheckSQLConnection(void) const;
   };
   #endif
 
   #if defined FAIND_INDEXER
   struct Create_Command : lem::NonCopyable
   {
    lem::UFString Name;
    lem::Path LocationFolder;
    lem::zbool ReadOnly;
    lem::zbool shared;
    lem::zbool word_wheeled_search;
    Solarix::Search_Engine::Domain_Info::ContentMode Mode;
    Solarix::Search_Engine::Domain_Info::ChangesMonitorType Refresh;
    Solarix::Search_Engine::Domain_Info::EngineType engine_type;

    Create_Command(void)
    {
     Mode = Solarix::Search_Engine::Domain_Info::/*ContentMode::*/Static;
     Refresh = Solarix::Search_Engine::Domain_Info::/*ChangesMonitorType::*/Manual;
     engine_type = Solarix::Search_Engine::Domain_Info::/*EngineType::*/FaindEngine;
    }
   };
   #endif



   // **************************************************
   // ��������� ������������ ��� ������������� �������,
   // ������� DDL ��� ������� ��� ���� ��������.
   // **************************************************
   struct Indexer_Operation
   {
    #if defined FAIND_INDEXER
    static lem::UFString ALL_ZONES_NAME; // ���������� ��� ��� ����������� '��� ����' ��� ������
    static lem::UFString ALL_SHARED_ZONES_NAME; // ���������� ��� ����������� ��������

    lem::zbool use; // ������������ ����������
    lem::UFString domain_name; // ��� ������� ������
    int id_domain; // ���� ������ ��������, �� - ��� id.

    lem::Collect<lem::UFString> domains; // ������ ���� ��� - ���� ����� �� ���������� ����� 

    lem::UFString command; // ��������� ������������� �������
    lem::UFString arg, arg2; // �������������� ��������� �������
    lem::zbool ddl; // ��� ������ ���� -index purge
    Create_Command create; // �������������� ��������� ��� ������� -index create_domain ...

    lem::zbool searching;     // ������������ ����������: ����� �� ����
    lem::zbool indexing;      // ������������ ����������: �������������� ����
    lem::zbool updating;      // ������������ ����������: ���������� �������
    lem::zbool optimize;      // �������������� � ������� ���� ��� commit'� (���� ���������� ������������)
    lem::zbool add_files;     // � ������ ����������� �����
    
    lem::zbool touch_files;   // ��� ������ ������ �� ������� - ������ ��������� � ������
    lem::zbool touch_servers; // ��������� ����������� FTP ��������
    lem::zbool show_metainfo; // ���������� �������������� � ��������� ��������� (����)   

    Solarix::Search_Engine::Morphology morphology; // ������������ ���������� � ������� ������ ��� ����������
                           // ����������� ��� ��������� ������������ ���������� 

    tribool allow_reindex; // ��������� �� � ���� ������ ����������������� ����������
                           // ���������.

    lem::zbool recreate_whole_assoc; // ������ ������������ ������ ������� �� ����������� ��������
    lem::zbool store_docindex; // ��������� ������������� ������
    lem::zbool store_docmatrix; // ��� ���������� ��������� ���. ����������

    lem::zbool store_doc_prox; // ��������� ������������� ������� ��������
    lem::zbool store_zone_prox; // ������� � ��������� ����������� ������� �����������
   
    // ��� ���� ��������� ������� ��������� � �� ����� ������������ ��� ������
    lem::zbool can_read_zone_prox;

    lem::zbool create_proximity; // ��� ���������� ��������� ������� �������� ����
    lem::zbool create_frequency; // ��� ���������� ����������� ���������� ������ ����
    lem::zbool knowledge_mine;   // ��������� ������ � ��������� ���������� � �������

    lem::zbool create_topic; // �������� � ��������� ���� ���������� � ������ ������������
    lem::zbool store_tags; // ���������� � ������������� ������� ���� ���������� (��������,
                     // ���������� <title> � HTML ��� ���� ��� MP3)
    lem::zbool store_contents; // ���������� ���������� ��������� � ���� ��� offline ������ �� ������� ���������

    enum Ranking { No_Rank, Freq_Rank, Rel_Freq_Rank };
    Ranking ranking; // ��� ������ ��������� ��� ��������� (���� �� ����������)

    lem::zbool load_all_keywords;

    lem::zbool control_modif; // �������������� ������������ ������� � ������ � ���� �
                        // �������� ������
 
    lem::zbool force_reindex; // ���������� ��������� ������������ ���� ��� ������������������ 

    lem::zbool allow_rooting;   // �������� �� ��������� � ����� ������������� ��� ������

    void Init( const Indexer_Operation &x );

    Indexer_Operation(void); 
    Indexer_Operation( const Indexer_Operation &x );

    void operator=( const Indexer_Operation &x );

    inline void Disable(void) 
    {
     load_all_keywords=false;
    }

    inline bool AllDomains(void) const { return domain_name==ALL_ZONES_NAME; }
    inline bool AllSharedDomains(void) const { return domain_name==ALL_SHARED_ZONES_NAME; }
    #endif
   };

  }
 } 
 
#endif
