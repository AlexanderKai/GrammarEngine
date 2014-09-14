#if !defined IDX_CATALOGUER_SQLITE__H
 #define IDX_CATALOGUER_SQLITE__H
#pragma once

 #if defined FAIND_IDBLIST_SQLITE

 #include <lem/sqlite/sqlite3.h> 
 #include <lem/solarix/se_indexer.h>

 namespace Solarix
 {

  namespace Search_Engine
  { 

   // ***************************************************************
   // ������������� �������������� ��� �������� � ����������� ����.
   // ***************************************************************
   class Idb_List_SQLite : public Idb_List
   {  
    private:
     boost::posix_time::ptime list_timestamp; // ������� ������� ������������ ������,
                                              // ������������ ��� ������������� �������
                                              // � ���������� � ������ � ��. 

     lem::Path list_filename; // "idb_filename" ��� ����� �� (������ ��� SQLite)

     struct sqlite3* hdb; // ���������� ��

     // ������ ���� � ��������� ����� �� ������� ��������
     const lem::Path GetListFileName(void) const;

     // � ������� CHANGELOG ������������ ������� ����� ��� �����
     // ���������� ���������� ������� � IDB_LIST
     void UpdateChangelog(void);

     // ������� ����������� ������� � ������ ��.
     void CreateScheme(void);
     void CreateAdditionalTables(void);

     void BeginTransaction(void);
     void CommitTransaction(void);
     void RollbackTransaction(void);
     int SelectInt( const char *Select );
     void UpdateSQL( const Domain_Info &domain, FString &update ) const;
     void UpdateSQL_NeedsRefresh( const Domain_Info &domain, FString &update ) const;
     void InsertSQL( const Domain_Info &domain, FString &update ) const;
     void InsertSQL_Remoting( const Domain_Info &domain, FString &update ) const;
     void DeleteSQL_Remoting( const Domain_Info &domain, FString &sql ) const;

     void SaveChangedFiles( const Domain_Info &domain ) const;

     virtual void SaveScheduledFiles(void);

     const Domain_Info& ImportDomain( const Domain_Info &d, const Remote_Zone& r );

     void OpenDatabase(void);
     void CloseDatabase(void);

    public:
     Idb_List_SQLite( const Indexer_Options *Flags );
     virtual ~Idb_List_SQLite(void);

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

     // ������������ �������� ������ �������
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

  }
  
}

#endif
 
#endif
