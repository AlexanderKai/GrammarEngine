#ifndef IDX_MYSQL_BACKEND__H
#define IDX_MYSQL_BACKEND__H
#pragma once

 #if defined FAIND_IDBLIST_MYSQL || defined FAIND_INDEXER_MYSQL

 #include <lem/solarix/se_indexer.h>
 #include <lem/mysql/mysql.h> 

 namespace Solarix
 {

  namespace Search_Engine
  { 

   class DocumentIteratorMySQL : public DocumentIterator
   {
    private:
     std::auto_ptr<Assoc_Files> files;

    public:
     DocumentIteratorMySQL( Assoc_Files *_files ) : files(_files) {}
     virtual ~DocumentIteratorMySQL(void) {}

     virtual int Size(void) const;
     virtual int GetDocId( int i ) const;
   };


   struct MySqlBackend
   {
    static int nrows_per_insert; // max number of record per single bulk insert

    static int SelectInt( MYSQL *db, const char *Select );
    static void ProcessError( MYSQL *mysql, const char *SqlCommand );
    static void ProcessError( MYSQL *mysql, const lem::FString &SqlCommand );
   };

   #define MYSQL_ERR lem::to_unicode(mysql_error(mysql)).c_str()


   #if defined FAIND_IDBLIST_MYSQL
   // ***************************************************************
   // ������������� �������������� ��� �������� � ����������� ����.
   // ***************************************************************
   class Idb_List_MySQL : public Idb_List
   {  
    private:
     boost::posix_time::ptime list_timestamp; // ������� ������� ������������ ������,
                                              // ������������ ��� ������������� �������
                                              // � ���������� � ������ � ��. 

     lem::Path list_filename; // "idb_filename" ��� ����� �� (������ ��� SQLite)

     // ������ ���� � ��������� ����� �� ������� ��������
     const lem::Path GetListFileName(void) const;

     // � ������� CHANGELOG ������������ ������� ����� ��� �����
     // ���������� ���������� ������� � IDB_LIST
     void UpdateChangelog(void);

     // ������� ����������� ������� � ������ ��.
     void CreateScheme(void);

     void BeginTransaction(void);
     void CommitTransaction(void);
     void RollbackTransaction(void);
     int SelectInt( const char *Select );
     void PurgeDomain_Internal( int id_zone );
     void UpdateSQL( const Domain_Info &domain, FString &update ) const;
     void InsertSQL( const Domain_Info &domain, FString &update ) const;

    public:
     Idb_List_MySQL( const Indexer_Options *Flags );
     virtual ~Idb_List_MySQL(void);

     // ������ �������� � ���������� ���������.
     // ��� StorageInfo=true ����� ���������� ���������� � ��������� 
     // ��������� ������.
     virtual void PrintVersion(
                               OFormatter &out,
                               const lem::UI::Resource_List &resx,
                               bool StorageInfo=false
                              ) const;

     virtual int CreateDomain(
                              const UFString &Domain_Name,
                              const lem::Path &index_db_folder,
                              Domain_Info::ContentMode Mode,
                              bool ReadOnly,
                              const UFString &Cmd,
                              Domain_Info::ChangesMonitorType Refresh=Domain_Info/*::Changes_Monitor*/::Manual,
                              Domain_Info::EngineType engine_type=Domain_Info::FaindEngine ,
                              bool shared=false,
                              bool allows_word_wheeled_search=false
                             );

     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd );

     // ����������, ��� ��� ���������� ���� ����������� �������. ���������
     // ������������ � ���������.
     virtual void SetNeedsDictionary( const UFString &Domain_Name, bool Flag );

     // �������� ������ ��� �� ����� (��� ��) � ����������� ������
     virtual void Load(void);

     virtual void ReloadDomain( int id );

     // ������ ����������� ������ �������� � �������� ����, ���������
     // �������� (���� ������� �������, ���� � ��������� ��������� ������
     // ������).
     virtual void Save(void);

     // �������� �������� ���� � ���������� ��������� � ���������.
     virtual void DeleteDomain( int id_zone );

     // ������� ���� - ���� �������� ��������.
     virtual void PurgeDomain( int id_zone );

     // �������������� ���� � ���������� ��������� � ���������
     virtual void Rename( int iZone, const UFString &new_name );

     // ��������� �������� ������� � ���������� ��������� � ���������
     virtual void SetComment( int iZone, const UFString &Comment );

     virtual void Share( int id_zone, bool shared );

     // ��� ���������� ������� ����������� ������ ����
     // "��������� � ������������������".
     virtual void SaveNeedsRefreshFlag( int id_zone );

     virtual void DeleteAllIndexes(void);

     // � ���� ��� �� ������������� ��������������?
     virtual bool IsEmptyDomain( int id_zone );

     // ���������� �������� ������� � ��������� ��������.
     virtual void BackupDomainsList( const lem::Path &dest_folder );

     // �������������� �������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomainsList( const lem::Path &dest_folder );

     // ���������� ������� � ��������� ��������.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // �������������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // �������� ������������� ��������� ������, ���������� true � ������ ������.
     virtual bool LockByReader( int id_index );
     virtual bool LockByWriter( int id_index );

     // ��������� ������� ����������. ��� �� ������ ����������� ���������
     // �������, ��� ��� ����� �������� �������� ���������� ����� ����������.
     virtual bool IsLockedByReader( int id_index );
     virtual bool IsLockedByWriter( int id_index );

     // �������� ������������� ��������� ������, ���������� true � ������ ������.
     virtual void UnlockByReader( int id_index );
     virtual void UnlockByWriter( int id_index );

     // �������������� ������ ���� ����������.
     virtual void UnlockAll(void);
   };
   #endif



   #if defined FAIND_INDEXER_MYSQL 
   class IndexReaderMySql : public Indexer
   {
    private:
     lem::Ptr<SQLConnection> connection;

     virtual void LoadDocuments(void);

     virtual int FindKeywordSlow( const UCString &Word, Morphology morph ) const;
     virtual void FindKeywordsSlow(
                                   const UCString &Word,
                                   Fuzzy_Comparator *equator,
                                   std::set<int> &result
                                  ) const;


    public:
     IndexReaderMySql(
                      IndexManager *Manager,
                      const Domain_Info &Domain_info,
                      Solarix::Dictionary *ptrDict,
                      const LD_Seeker *seeker,
                      const Echo_Options *Echo,
                      const General_Options *Generals,
                      const lem::Ptr<SQLConnection> &Connection
                     );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexReaderMySql(void);

     virtual Zone_Statistics GetZoneStat(void);

     // ���������� ���������� � ��������� �������� �������.
     virtual void PrintInfo( OFormatter &out, bool detailed=false );

     virtual Assoc_Files* GetAssocFiles( int super_index, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles(
                                        int super_index1,
                                        int super_index2,
                                        const Pattern &pattern
                                       );
     virtual Assoc_Files* GetAllFiles(void);

     virtual bool LoadDocumentIndex( File_Entry *file_entry );

     virtual void PreparePrefetchingKeywords(void);
     virtual void FinishPrefetchingKeywords(void);
     virtual void PrefetchKeyword( const UCString &Word );

     virtual Document_Index* CreateDocIndex(void) const;

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     virtual bool FindIndex(
                            const File_Location &loc,
                            File_Entry **entry,
                            bool &broken,
                            bool do_load=true
                           );

     virtual bool GetTagForFile(
                                const lem::UFString &filename,
                                File_Location::LocType loctype,
                                const lem::UFString &fileloc, 
                                const lem::UFString &tag,
                                lem::UFString &value
                               );


     virtual bool DoesSupportMorphology(void) const;

     virtual bool SupportMetainfo(void) const;


     virtual FString GetEngineName(void) const;

     // ������ ������� ����� ���������� ������������������ ���������� (�������
     // ���������� ��� ������������ ��� ���������).
     virtual int CountDocuments(void);

     // ������������ ��������� �� ������������������ ��������. � �����������
     // �� ���������� ������������ ������ ����� ���� ������ ������ ��� �������
     // ������, ��� ��������� � ����� ����������� ������.
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int idoc );
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );

     virtual int CountKeywords(void);
   };

   class IndexWriterMySql : public Indexer
   {
    private:
     // ��� ������������ ������ KEYWORD � �� � � ��������� ������
     std::map< int, int > local_2_db;
     int kwd_id_seq;

     void CreateScheme(void);

    public:
     IndexWriterMySql(
                      IndexManager *Manager,
                      const Domain_Info &Domain_info,
                      Solarix::Dictionary *ptrDict,
                      const LD_Seeker *seeker,
                      const Echo_Options *Echo,
                      const General_Options *Generals
                     );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexWriterMySql(void);

     virtual void AddDocument(
                              const File_Location &filename,
                              Base_File_Reader *reader
                             );

     virtual void SetTagForFile(
                                const lem::UFString &path,
                                File_Location::LocType loctype,
                                const lem::UFString &loc, 
                                const lem::UFString &tag,
                                const lem::UFString &value
                               );

     virtual bool DoesSupportMorphology(void) const;
   };


   class IndexUpdaterMySql : public Indexer
   {
    private:
     // ��� ������������ ������ KEYWORD � �� � � ��������� ������
     std::map< int, int > local_2_db;
     int kwd_id_seq;

    public:
     IndexUpdaterMySql(
                       IndexManager *Manager,
                       const Domain_Info &Domain_info,
                       Solarix::Dictionary *ptrDict,
                       const LD_Seeker *seeker,
                       const Echo_Options *Echo,
                       const General_Options *Generals
                      );

     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );

     virtual void Commit(void);

     virtual ~IndexUpdaterMySql(void);

     virtual bool DoesSupportMorphology(void) const;

     virtual bool IsFileChanged( const File_Location &filename );

     virtual void AddDocument(
                              const File_Location &filename,
                              Base_File_Reader *reader
                             );
   };
  #endif


   extern void encode_mysql_path( UFString &str );
   extern void decode_mysql_path( UFString &str );

  }
 
}

  
#endif

#endif
