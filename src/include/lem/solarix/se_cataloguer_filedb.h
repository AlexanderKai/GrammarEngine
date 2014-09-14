// -----------------------------------------------------------------------------
// File SE_CATALOGUER_FILEDB.H
//
// (c) 2008 by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// 06.10.2008 - ���������� ������ Idb_List_File �������� �� se_indexer.h �
//              ������ ���� � ���� ������������ �������. 
// -----------------------------------------------------------------------------
//
// CD->06.10.2008
// LC->13.11.2008
// --------------

#if !defined SE_CATALOGUER_FILEDB__H && defined FAIND_IDBLIST_FILEDB
 #define SE_CATALOGUER_FILEDB__H
#pragma once

 #include <lem/solarix/se_indexer.h>
 
 namespace Solarix
 {
  namespace Search_Engine
  { 

   // ***************************************************************
   // ������������� �������������� ��� �������� � �������� �����.
   // ***************************************************************
   class Idb_List_File : public Idb_List
   {  
    private:
     boost::posix_time::ptime list_timestamp; // ������� ������� ������������ ������,
                                              // ������������ ��� ������������� �������
                                              // � ���������� � ������ �� �����. 

     lem::Path list_filename; // "idb_filename" ��� ����� �� ������� ���������� ��������
     lem::Path todel_filename; // ��� ����� �� ������� ����� ��� ��������

     // ������ ���� � ��������� ����� �� ������� ��������
     const lem::Path GetListFileName(void) const;

     // ������ ���� � ������ ������/����� ��� ��������
     const lem::Path GetToDelFileName(void) const;

     virtual void SaveScheduledFiles(void);

    public:
     Idb_List_File( const Indexer_Options *Flags );
     virtual ~Idb_List_File(void);

     // ������ �������� � ���������� ���������.
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
                              Domain_Info::EngineType engine_type=Domain_Info::FaindEngine,
                              bool shared=false,
                              bool allows_word_wheeled_search=false
                             );

     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd );

     // ����������, ��� ��� ���������� ���� ����������� �������. ���������
     // ������������ � ���������.
     virtual void SetNeedsDictionary( const UFString &Domain_Name, bool Flag );

     // �������� ������ ��� �� ����� (��� ��) � ����������� ������
     virtual void Load(void);

     // ������ ����������� ������ �������� � �������� ����, ���������
     // �������� (���� ������� �������, ���� � ��������� ��������� ������
     // ������).
     virtual void Save(void);

     // �������� �������� ���� � ���������� ��������� � ���������.
     virtual void DeleteDomain( int id_zone );

     virtual void ReloadDomain( int id_zone );

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


  } // namespace Search_Engine
 } // namespace Solarix

#endif
