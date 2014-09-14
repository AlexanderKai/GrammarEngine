// -----------------------------------------------------------------------------
// File SE_INDEXER.H
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// Search engine FAIND. Indexer classes.
// ��������� ������ FAIND. ��������� ���� ������.
//
// 14.02.2006 - � �������� ���� ������ ����� �������� ������� 'CD/DVD',
//              ����� ��� ������������ ������ ������ ������ ������������ - 
//              �������� ������ ���� � ������.
//
// 20.02.2006 - � �������� ���� ������ �������� "������ ��������������� �������",
//              ����� � ������� ������� ��������� ���������� ���������� �������
//              (� ������� - �������� ����������).
//
// 12.03.2006 - ������ ����� ��� ���� "noindex" - ��� ����������� ����������.
//
// 04.07.2006 - ��������� � ������� �������� ������� �������� (��� �����������
//              ����� ����������������� �������������� �������) � �������� �����.
//
// 04.07.2006 - ������ ������ �� �������� ����������� ��������� � ������������
//              �����.
//
// 25.10.2006 - ����������� ���� �������, ���������� �� � ������� ���������.
//
// 06.11.2006 - ��������� ������ ��������� �� > 2Gb
//
// 24.02.2007 - ��� ������ Pro � �������� ���������� ��������� �������� �������
//              ����� �������������� ���� SQLite
// 
// 11.06.2007 - ��� std::auto_ptr �������� �� boost::shared_ptr, ��� ���
//              ���������� std::auto_ptr �� MSVC 6.0 ������ ::reset() 
//
// 27.06.2007 - �������� ��� ��� ������� ��������� CLucene.
// -----------------------------------------------------------------------------
//
// CD->19.03.2005
// LC->19.04.2010
// --------------

#if !defined SE_DOCUMENT_INDEX__H && defined FAIND_INDEXER
#define SE_DOCUMENT_INDEX__H
#pragma once

 #include <lem/config.h>

 #if !defined FAIND_NO_BOOST_REGEX
 #include <boost/regex.hpp>
 #endif

 #include <boost/date_time/posix_time/posix_time.hpp>

 #if defined FAIND_SIGNALS
 #include <boost/signal.hpp>
 #endif

 #include <lem/ilist.h> 
 #include <lem/streams.h> 
 #include <lem/containers.h> 
 #include <lem/math/random.h>
 #include <lem/math/fp1.h> 
 //#include <lem/solarix/text_processor.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/se_general_options.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/se_lexer_options.h>
 #include <lem/solarix/se_index_options.h>
 #include <lem/solarix/se_word_searcher.h>
 #include <lem/solarix/idx_folder_monitor.h>
 
 #undef assert

 namespace lem
 {
  namespace File_Factory
  {
   struct Scan_Options;
  }
 }

 namespace Solarix
 {
  class LD_Seeker;

  namespace Search_Engine
  { 
   struct Pattern;
   class Base_File_Reader;

   using lem::IList;
   using lem::BinaryFile;
   using lem::Stream;
   using lem::FString;
   using lem::UFString;
   using lem::UCString;
   using lem::OFormatter;
   using lem::Collect;
   using Solarix::Search_Engine::File_Location;
   using Solarix::Search_Engine::Morphology;
   using Solarix::LD_Seeker;
   using Solarix::Search_Engine::Pattern;

   struct Search_Options;

   #if defined FAIND_DATAMINE
   class Doc_Topic; 
   #endif

   class Fuzzy_Comparator;

   #if defined FAIND_4G_DOCS
   // ��������� 2^32 ��������� � ����� �������. ��� ���� �������� ���������
   // ������� ����������� ������.
   typedef lem::uint32_t DocIndex;
   const int DocIndex_MAX=lem::uint32_max;
   #else
   typedef lem::uint16_t DocIndex;
   const int DocIndex_MAX=lem::uint16_max;
   #endif

   // ************************************************************************
   // ����� ��� ���������� ������� ����������� �������� ������ (�������������).
   // ������� ��������� �������� ����� �������� �� ����������� ������� �
   // ����������� ������ ��� ��������� �������.
   // ************************************************************************
   class Idb_List : public lem::IList<Domain_Info>, lem::NonCopyable
   {  
    protected:
     virtual const Domain_Info& Get( size_type idx ) const;
     virtual       Domain_Info& Get( size_type idx );

    protected:
     friend class IndexManager;

     const Indexer_Options *flags; // ��������� ������ ������������
     lem::zbool loaded; // ������ ��� ��������?
     lem::PtrCollect<Domain_Info> list; // ������ ���������� ��������

     lem::Collect<lem::Path> to_del; // ����������� ������ ������ � ��������� ��� �������� � ���� ������������
     lem::zbool to_del_dirty; // ������ to_del ��� ������� ����� ��������

     #if defined LEM_THREADS
     lem::Process::CriticalSection cs; // ��� ������������� ��������� � ������ ��������
     #endif

     // �������� ������ � ����� �� ������ to_del
     virtual void PurgeScheduledFiles(void);
     virtual void SaveScheduledFiles(void); 

    public:
     Idb_List( const Indexer_Options *Flags );

     virtual ~Idb_List(void);

     void EnterCS(void);
     void LeaveCS(void);

     // ������ �������� � ���������� ���������.
     virtual void PrintVersion( OFormatter &out, const lem::UI::Resource_List &resx, bool StorageInfo=false ) const=0;

     // ������� ����� ������ � ���������� �� id.
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
                             ) { LEM_STOPIT; LEM_NO_RET(0); }

     // ���������� ��� ������� ����������� ������� ������
     virtual void StoreDomainCommands( int id_zone, const UFString &Cmd )
     { LEM_STOPIT; }

     // ����������, ��� ��� ���������� ���� ����������� �������. ���������
     // ������������ � ���������.
     virtual void SetNeedsDictionary( int id_zone, bool Flag ) 
     { LEM_STOPIT; }

     // �������� ������ ��� �� ����� (��� ��) � ����������� ������
     virtual void Load(void) { LEM_STOPIT; }

     // ���� �� �����, ��� ������ ������� ������� � ���� �������� ��� �������� � ����������� ������.
     virtual void ReloadDomain( int id ) { LEM_STOPIT; }

     // ������ ����������� ������ �������� � �������� ����, ���������
     // �������� (���� ������� �������, ���� � ��������� ��������� ������
     // ������).
     virtual void Save(void) { LEM_STOPIT; }

     // �������� �������� ���� � ���������� ��������� � ���������.
     virtual void DeleteDomain( int id_zone ) { LEM_STOPIT; }

     // ������� ���� - ���� �������� ��������.
     virtual void PurgeDomain( int id_zone ) { LEM_STOPIT; }

     // �������������� ���� � ���������� ��������� � ���������
     virtual void Rename( int id_zone, const UFString &new_name ) { LEM_STOPIT; }

     // ��������� �������� ������� � ���������� ��������� � ���������
     virtual void SetComment( int id_zone, const UFString &Comment )  { LEM_STOPIT; }

     // ��������� ������ ������ �������
     virtual void Share( int id_zone, bool shared ) { LEM_STOPIT; }

     // ��� ���������� ������� ����������� ������ ����
     // "��������� � ������������������".
     virtual void SaveNeedsRefreshFlag( int id_zone ) { LEM_STOPIT; }

     // ����� ������� ��� ���������� ����� s/n CD
     virtual int FindCdrom( lem::uint32_t SericalNumber ) const;

     // IList<>
     virtual bool IsFixedSize(void) const { return false; }
     virtual bool IsReadOnly(void) const { return false; }

     // ������� ����������� ������ (� ��������� ��������� ���).
     virtual void Clear(void);

     virtual bool Empty(void) { return list.empty(); }

     // ����� ���������� �������, ������� ������������
     virtual IList<Domain_Info>::size_type Count(void) const { return list.size(); }

     // IList<>
     virtual void SetCur( IList<Domain_Info>::size_type i ) { LEM_STOPIT; }
     virtual IList<Domain_Info>::size_type GetCur(void) { LEM_STOPIT; LEM_NO_RET(0); }
 
     // IList<>
     virtual void Add( const Domain_Info &x )  { LEM_STOPIT; }
     virtual bool Contains( const Domain_Info& x ) const  { LEM_STOPIT; LEM_NO_RET(false); }
     virtual Idb_List::size_type IndexOf( const Domain_Info& x ) const  { LEM_STOPIT; LEM_NO_RET(0); }
     virtual void Insert( size_type i, const Domain_Info& x )  { LEM_STOPIT; }
     virtual void RemoveAt( Idb_List::size_type i )  { LEM_STOPIT; }
     virtual void Remove( const Domain_Info& x )  { LEM_STOPIT; }

     virtual const Domain_Info& GetUnsafe( size_type idx ) const { return *list[idx]; }
     virtual       Domain_Info& GetUnsafe( size_type idx )       { return *list[idx]; }
     const Domain_Info& GetUnsafe( const UFString &Domain_Name );

     // ��� ��������-����������� ��������� ����� �������� ����.
     virtual void GetSafe( int id, Domain_Info &res );

     // ������-���������� ����� ����������� ����� ��� ����
     virtual lem::UFString GetDomainName( int id_zone );

     // ������-���������� ����� ����������� ���������� ��� ����
     virtual lem::UFString GetDomainComment( int id_zone );

     virtual bool GetNeedsDictionary( int id_zone );
     virtual bool IsShared( int iDomain ); 
     virtual bool IsActual( int iDomain ); 
     virtual bool IsStatic( int iDomain ); 
     virtual bool IsDynamic( int iDomain ); 
     virtual bool IsNoIndex( int iDomain );
     virtual bool IsReadOnly( int iDomain );
     virtual bool IsMonitored( int iDomain ); 
     virtual void GetDomainCmd( int iDomain, lem::UFString &cmd );
     virtual bool DoesNeedRefresh( int iDomain ); 
     virtual bool IsRemote( int iDomain ); 
     virtual Solarix::Search_Engine::Domain_Info::EngineType GetIndexEngine( int iDomain );
     virtual bool DoesNeedIdleRefresh( int iDomain ); 
     virtual bool AllowsWordWheeledSearch( int iDomain ); 
     boost::posix_time::ptime GetDomainModifTimestamp( int iDomain );

     // ����� ������� ��������� ���� �� �� �����
     virtual int Find( const UFString &Domain_Name );
 
     // ����� ������� ��������� ���� �� id
     virtual int FindById( int id );

     // ����� ���������� �������� (�� ���� ��������� ������������)
     virtual int CountActual(void);

     virtual void DeleteAllIndexes(void)=0;

     virtual bool IsEmptyDomain( int id_zone )=0;

     // ���������� ������� ���������� �� ����������� �����.
     virtual void PrintList( OFormatter &out, const lem::UI::Resource_List &resx, bool xml=false, bool shared_only=false );

     // ���������� �������� ������� � ��������� ��������.
     virtual void BackupDomainsList( const lem::Path &dest_folder ) { LEM_STOPIT; }

     // �������������� �������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomainsList( const lem::Path &dest_folder ) { LEM_STOPIT; }

     // ���������� ������� � ��������� ��������.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder ) { LEM_STOPIT; }

     // �������������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder ) { LEM_STOPIT; }

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

     virtual const Domain_Info& ImportDomain( const Domain_Info &d, const Remote_Zone& r );

     // ��������� ���� ��� ����� ������ ���� ������ � �������.
     virtual void AddToDel( const lem::Path &p );

     // ������������ ��� ��� ������ ������������ �������.
     virtual lem::Path GetNewDomainFolder(void) const;

   };



   #if defined FAIND_IDBLIST_SQLITE || defined FAIND_IDBLIST_MYSQL
    #define FAIND_IDBLIST_SQL
   #endif
  



   class Indexer;

   class Proximity_Catalog : public lem::MCollect< std::pair<int /*super_index*/, lem::Stream::pos64_type /*beginning*/> >
    , boost::noncopyable
   {
    public:
     Proximity_Catalog(void) {}
   };


   class Assoc_Files;


   const int N_PAIR_HASH  = 4096;
   const int N_HASH_GROUP = 16; 
   inline unsigned CALC_PAIR_HASH( int first, int second )
   { return (first>>16 ^ first ^ second>>16 ^ second) & 0x00000fffu; }


   // ���� �������� ����
   struct Entry_Pair : public std::pair<int,int>
   {
    Entry_Pair(void) {}
    Entry_Pair( int i, int j ) { first=i; second=j; }

    inline bool operator==( const Entry_Pair &x ) const
    { return first==x.first && second==x.second; }

    inline bool operator!=( const Entry_Pair &x ) const
    { return first!=x.first || second!=x.second; }

    inline bool operator>( const Entry_Pair &x ) const
    {
     return first > x.first ?
             true  :
            ( first==x.first ? second>x.second : false );
    }   

/*
    inline lem::uint8_t hash(void) const
    {
     return  ( first>>24 ^ first>>16 ^ first >>8 ^ first ) ^ 
             ( second>>24 ^ second>>16 ^ second >>8 ^ second );
    }
*/

    enum { NHASH=N_PAIR_HASH };

    inline unsigned hash(void) const { return CALC_PAIR_HASH(first,second); }
   };


   inline unsigned calc_pair_hash( int first, int second )
   { return (first>>16 ^ first ^ second>>16 ^ second) & 0x00000fffu; }




   struct Context2 : public Entry_Pair
   {
    bool more_than_1;
    union {
           DocIndex idoc;
           lem::MCollect<DocIndex> *v;
          };  
    
    Context2(void) { v=NULL; more_than_1=false; }
    
    Context2( int I1, int I2, DocIndex iDoc )
     : Entry_Pair(I1,I2), more_than_1(false), idoc(iDoc) {}

    inline bool operator==( const Entry_Pair &x ) const
    { return first==x.first && second==x.second; }

    inline void Add( DocIndex iDoc )
    {
     if( more_than_1 )
      v->push_back(iDoc);
     else
      {
       const DocIndex iDoc0 = idoc;
       v = new lem::MCollect<DocIndex>();
       v->push_back( iDoc0 );
       v->push_back( iDoc );
      }

     more_than_1 = true; 
    }

    inline void Free(void) { if(more_than_1) lem_rub_off(v); }
 
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
   };


   // ***************************************
   // ����� ������� �������� ��� ���� ����.
   // ***************************************
   class Zone_Proximity : boost::noncopyable
   {
    private:
     typedef lem::MCollect<Context2> CtxSublist;
     CtxSublist* sublist[ Entry_Pair::NHASH ]; // ���� ��������� ��� ������� �������� ���-����
     typedef std::map<Entry_Pair,int> Accel;
     Accel* accels[ Entry_Pair::NHASH ]; // ���������� ���������� sublists

     lem::Stream::pos64_type beg; // ���� ������������ ��� ���������� ������� �� ����
     lem::Stream::pos64_type cat[ Entry_Pair::NHASH ]; // ������� - ������� ������ ���������� � �����

     void Clear_Sublist( CtxSublist &l ) const;
     void SaveBin( const CtxSublist &l, lem::Stream &bin ) const;
     void LoadBin( CtxSublist &l, lem::Stream &bin );

    public:
     Zone_Proximity(void);
     ~Zone_Proximity(void);

     // ������� ����� ��������������� ����� ����
     void Clear(void);

     void Prepare_Range( int i0, int iN );

     void Add_Pair( int sublist, int si1, int si2, DocIndex idoc );

     // ���������� ������� ��������
     void SaveBin_Head( lem::Stream &bin );
     void SaveBin_Body( lem::Stream &bin, int i0, int iN );
     void SaveBin_Tail( lem::Stream &bin ) const;

     // ������������ ������ ������������ ����������, ���������� ����
     // ���� (��������� �� �������� � ����������� �������� ����).
     Assoc_Files* Get_Assoc_Files( lem::Stream &bin, int super_index1, int super_index2 );
   }; 



   // ********************************************
   // ������ ��� ������ ������������� ���������
   // ********************************************
   class Document_Index : lem::NonCopyable
   {
    public:
     lem::MCollect<Index_Entry> word_list; // ������ ���� ��� ����-����.
     lem::MCollect<int> freq_list; // ������ ������ ����

    private:
     #if defined LEM_DEBUGGING==1
     lem::Guardian guard1;
     #endif

     lem::Stream::pos64_type words_beg; // ������� � ����� ������ ������ ����.
     lem::Stream::pos64_type freq_beg; // ������� � ����� ������ ������ ������.
     lem::Stream::pos64_type prox_beg; // ������� � ����� ������ ������� ��������.
     lem::Stream::pos64_type topic_beg; // ������� � ����� ������ ��������� ����.
     lem::Stream::pos64_type index_end; // ������ ���� ����� ������ �������

     Proximity_Catalog prox_cat; // ����������� �� ����� ������� ��� ������� �������� � ���������
     lem::MCollect< std::pair<Index_Entry,int> > freqs_loaded; // ����������� �� ����� ��������� �������

     std::vector<int> prox; // ������� ���� � ����� ����������� (������� ������)
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* > LINKS;
     LINKS links;
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* >::iterator ITER1;
     typedef std::map< int /*ientry1*/, std::map< int /*ientry2*/, int /*freq*/ >* >::const_iterator CITER1;

     typedef std::map< int /*ientry2*/, int /*freq*/ >::iterator ITER2;
     typedef std::map< int /*ientry2*/, int /*freq*/ >::const_iterator CITER2;

     // �������� ����� � ������� �������
//     std::multimap< int, int /*keywords[*]*/  > keywords_map;
     std::map< int, int > keywords_map;

     #if defined LEM_DEBUGGING==1
     lem::Guardian guard2;
     #endif

     Document_Index( const Document_Index& );
     void operator=( const Document_Index& );

    public:
     const Indexer_Operation *operation;
     bool good; // ����� �� ������������ ������
     DocIndex idoc; // ������ ��������� � ����� ������ ����
     boost::posix_time::ptime build; // ����� ������ ������

     #if defined FAIND_DATAMINE
     Solarix::Search_Engine::Doc_Topic *topic; // ��������� ��� ����������� ���� ���������
     #endif

     #if defined LEM_DEBUGGING==1
     inline void Assert(void) const
     {
      guard1.Assert();
      guard2.Assert();
     }
     #endif

    public:
     Document_Index( const Indexer_Operation *Operation, DocIndex iDoc );

     ~Document_Index(void);

//     inline void set_Minbound( Real1 v ) { minbound=v; }
//     inline Real1 get_Minbound(void) const { return minbound; }

     // ���������� ��������� �������� ����� (��� ������
     // � ����� ������� �������� ���� ������� �������� �
     // ������ Indexer).
     inline void RegisterWord( int catalog_index )
     {
      IFDEBUG(Assert());
      if( keywords_map.find( catalog_index )==keywords_map.end() )
       {
        keywords_map.insert( std::make_pair( catalog_index, CastSizeToInt(word_list.size()) ) );
        word_list.push_back(catalog_index);
       }
      IFDEBUG(Assert());
     }

     // ������������ ������ Register_Word - �������������
     // ����������� ���������� �� �������� ����.
     inline void RegisterFrequency( int catalog_index )
     {
      IFDEBUG(Assert());
      std::map< int, int >::const_iterator i = keywords_map.find( catalog_index );
      if( i==keywords_map.end() )
       {
        keywords_map.insert( std::make_pair( catalog_index, CastSizeToInt(word_list.size()) ) );
        word_list.push_back(catalog_index);
        freq_list.push_back(1);
       }
      else
       freq_list[ i->second ]++;
      IFDEBUG(Assert());
     } 

     inline void RegisterProximity( int catalog_index )
     { prox.push_back(catalog_index); } 


     // ��������� ������ � ����������� ������ ���������� �����������
     void SentenceFinished(void);
     void SentenceFinished( Zone_Proximity &zone_prox );

     // ���������� ��������� ���������, ����� ��������� ��������� ��������
     void Completed(void);
  
     void Build( Indexer *Catalog, Solarix::Dictionary *dict );

     // ��� ��������� ��������� ������� �������� ����?
     inline bool HasProxMatrix(void) const
     {
      return lem::fpos64_not_zero(prox_beg);
     }

     void SaveBin( lem::Stream& bin ) const;
     void LoadBin( lem::Stream& bin );

     // ������� �������� ���� � ���������
     inline int Size(void) const
     {
      IFDEBUG(Assert());
      return CastSizeToInt(word_list.size());
     }

     inline const lem::MCollect<Index_Entry>& GetKeywords(void) const
     {
      IFDEBUG(Assert());
      return word_list;
     }

     inline const lem::MCollect<int>& GetFreqs(void) const
     {
      IFDEBUG(Assert());
      return freq_list;
     }
  

     inline const LINKS& GetLinks(void) const
     {
      IFDEBUG(Assert());
      return links;
     }

     // ����� ������� ������������ (��� ��������) �����
     // ����� �������� ���� ���������.
     bool Find( const Indexer &Catalog, const UCString &Word ) const;

     // ��� �����, ������� ������� � ����� ����������� �������� ����,
     // ����������� �������� ��� ����������� � ���������.
     inline bool Find( int catalog_index ) const
//     { return keywords_map.find( catalog_index )!=keywords_map.end(); }
     {
      IFDEBUG(Assert());
      return std::find( word_list.begin(), word_list.end(), catalog_index )!=word_list.end();
      // ��� ��� ������ word_list ��� ������������ ����� ���������� ���������,
      // �� ��� ������ ����� ��������� ������� ����� ����������. 
//      return std::binary_search( word_list.begin(), word_list.end(), catalog_index );
/*
      for( int i=0; i<word_list.size(); i++ )
       if( word_list[i] == catalog_index )
        return true;

      return false; 
*/
     }


    int FindProxCatIndex( int super_index ) const;
    int FindLocalKeywordIndex( int super_index ) const;

    bool TestProximity( lem::Stream &bin, int icat1, int ibit2, int ikey2 ) const;

    void SaveTmpProx( lem::Stream &bin );

    int GetWordFreq( int super_index ) const;
   };


   struct File_Entry;
   class ProximityMatrixProber : boost::noncopyable
   {
    private:
     friend class IndexReaderFaind;
     const File_Entry *file_entry;
     lem::Ptr<lem::BinaryFile> bin;
     
    public:
     ProximityMatrixProber(void); 
     
     bool TestProximity( int icat1, int ibit2, int ikey2 ) const;
   };

   // ***********************************
   // ���� ������ � �������� ��������.
   // ***********************************
   struct File_Entry
   {
    public:
     enum Status {
                  Unknown, Created, Updated, Deleted,
                  Untouched /* �������� ������ ���� �������� �� ��������� - ������������ ����� �������
                               �������������� ������������ ���� */
                 };

     Document_Index *idx; // ��� ������ ���������
     File_Location name;  // ��� ��������� � ������ ���-�� (����� ��������, ����������, ������)

     lem::uint16_t i_file; // ������ ����� ����� (stor_files � Indexer),
                           // ��� �������� ������ ���������.

     DocIndex i_indexed_file; // ������ ��������� ��������� � �������� ������ indexed_files    

     lem::Stream::pos64_type offset; // ���������� ������� � �����


    private:
     lem::uint8_t status;

    public:
     File_Entry(void)
     {
      idx=NULL;
      i_file=(lem::uint16_t)UNKNOWN;
      i_indexed_file=(DocIndex)UNKNOWN;
      lem::fpos64_clear(offset);
      status=/*Status::*/Created;
     }


     #if LEM_DEBUGGING==1
     inline void Assert(void) const 
     {
      #if LEM_DEBUGGING==1 && defined LEM_MSC
      LEM_CHECKIT_Z( !idx || _CrtIsValidHeapPointer(idx) == TRUE );
      #endif
     }
     #endif

     void SaveBin( lem::Stream& bin ) const;
     void LoadBin( lem::Stream& bin );

     // ������� ������ ��������� - �� �������� �� ����� �
     // �� ������ ��������� ������ � ������.
     inline void Purge(void)
     {
      IFDEBUG(Assert());
      lem_rub_off(idx);
     }

     inline bool IsAvailable(void) const
     {
      IFDEBUG(Assert());
      return i_file != static_cast<lem::uint16_t>(UNKNOWN);
     }

     // ���� �������� ��� (����)������������
     inline bool IsChanged(void) const
     { return status==/*Status::*/Created ||
              status==/*Status::*/Updated ||
              status==/*Status::*/Deleted ||
              status==/*Status::*/Untouched;
     }

     inline void SetDeleted(void)
     {
      status=/*Status::*/Deleted;
      name.clear();
     }

     inline void SetUpdated(void)
     {
      status=/*Status::*/Updated;
     }

     inline void SetUnchanged(void)
     {
      status=/*Status::*/Unknown;
     }

     inline void SetUntouched(void)
     {
      status=/*Status::*/Untouched;
     }

     inline bool IsDeleted(void) const
     { return status==/*Status::*/Deleted; }

     void RebasePath( const lem::UFString &old_prefix, const lem::UFString &new_prefix );
   };



   // ********************************************************
   // �������� �������������� ����� ��������������� ������
   // ********************************************************
   struct Assoc_Handle
   {
    int super_index; // keyword ID
    lem::uint16_t i_stor_file; // database filename
    lem::Stream::pos64_type offset; // Start position of data in the file

    Assoc_Handle(void)
    {
     super_index=UNKNOWN;
     i_stor_file=(lem::uint16_t)UNKNOWN;
     lem::fpos64_clear(offset);
    }
   };


   struct Assoc_Hash_Array
   {   
    enum { N_RANGE=256 }; // �� ������� ������������� ������ ���� ��������.    
    enum { RANGE_MASK=N_RANGE-1 };

    lem::uint16_t i_stor_file[N_RANGE];  // ������ ����� ����� ��, ��� �������� ������ ������ (������
                                         // ������ �� - ���� stop_files � Indexer). ��� ������� 
                                         // �������� ���-���� ����� ���� ��������� ����.

    lem::Stream::pos64_type offset[N_RANGE]; // �������� � ������ ��� ������ ������ - �� ������� ����
    bool dirty;                             // ���� �� ��������� (����� ���������� � ����)

    Assoc_Hash_Array(void);

    void SaveBin( lem::Stream &bin );
    void LoadBin( lem::Stream &bin );

    void Clear(void);
   };

   // *****************************************************************
   // Keyword ID (or super index) is translated to hash code
   // *****************************************************************
   inline int Superindex_2_Hash( int Index )
   {
    return Assoc_Hash_Array::RANGE_MASK & Index;
/*
    return 0x000000ffU & ((Index >> 24) ^
                          (Index >> 16) ^
                          (Index >> 8));
*/
   }



   // **************************************************
   // ������ ������, ��������������� � �������� ������.
   // ������ ����� ���� ����� ���� ����� id ����������
   // ����������, ���� ����� ������ �������� �����.
   // **************************************************
   class Assoc_Files : public lem::MCollect<DocIndex> // ������� ���������� �����������������
                                                 // ������ (��. ���� data_files � Indexer)
   {
    private:
     bool All; // ������� "���" ��� ������ �� ����-�������.

     friend class IndexWriterFaind;

     lem::PtrCollect<lem::Path> paths; 

     std::map<int,int> i_files; // ��� �������� ������ � �������� ������� ������� �����

     void Build(void);

     Assoc_Handle handle; // ��������� ���������� ��������� ��� �����������
                          // ���������� ����������� ������. 

//     inline void clear(void) { lem::MCollect<DocIndex>::clear(); }

    public:
     Assoc_Files(void) { All=false; }
     Assoc_Files( Assoc_Handle &Handle ) : handle(Handle) { All=false; }

     void SaveBin( lem::Stream &bin );
     void LoadBin( lem::Stream &bin );

     static void SaveBin( lem::Stream &bin, lem::MCollect<DocIndex> &v );

     void Clear(void);
  
     // ���������� (� ��������� ������������) ��������.
     inline bool Add( int iFile )
     {
      if( i_files.find( iFile )==i_files.end() )
       {
        /*lem::MCollect<DocIndex>::*/push_back(iFile);
        i_files.insert( std::make_pair( iFile, iFile ) );
        return true;
       }

      return false;
     }

     // ���������� (��� �������� ������������) ��������.
     inline void AddDirect( int iFile )
     {
      /*lem::MCollect<DocIndex>::*/push_back(iFile);
      i_files.insert( std::make_pair( iFile, iFile ) );
     }

     void AddDirect( lem::Path *path );

     inline bool Find( int iFile ) const
     { return i_files.find( iFile )!=i_files.end(); }

     inline bool Find( const lem::Path &p ) const;

     // ���������� ��� ����������� �������� ������. ������������ �� �����
     // ��������� �������� � ����������� ���������.
     void Or( const Assoc_Files &b, int limit=lem::int_max );
     void Minus( const Assoc_Files &b );  
     void And( const Assoc_Files &b );

     inline void SetAllFlag(void) { All=true; }
     inline bool IsAll(void) const { return All; }

     // ������������ ����� ��������� � ������ ���������� ��
     // ��������� ��������.
     void LimitTo( int maxhitcount );

     int CountIds(void) const { return CastSizeToInt(size()); }
     int CountPaths(void) const { return CastSizeToInt(paths.size()); }
     bool empty(void) const; 

     const lem::Path& GetPath( int i ) const { return *paths[i]; }
   };

   struct Echo_Options;


   // **************************************************
   // This structure stores the statistics for one zone
   // **************************************************
   struct Zone_Statistics
   {
    int index_count;     // number of zones
    int stor_files;      // number of database files

    lem::uint64_t occupied;  // disk space occupied

    int docs;            // number of indexed documents
    lem::uint64_t docs_size; // total size of indexed docs
    int keywords;        // number of keywords

    Zone_Statistics(void) { index_count=stor_files=docs=keywords=0; occupied=docs_size=0; }

    void operator += ( const Zone_Statistics &x )
    {
     index_count++;
     stor_files += x.stor_files;;
     occupied   += x.occupied;
     docs       += x.docs;
     keywords   += x.keywords;
     docs_size  += x.docs_size;
    }
   };

  
   #if defined FAIND_INDEXER
   // **************************************************
   // ����� ������, � ������� �������� ����� �������
   // **************************************************
   struct Storage : lem::NonCopyable
   {
    lem::Path folder;            // �������, ��� ����������� ��� ����� �� ������� (���� ���� - ���� �������)

    lem::Path kwd_path;          // ���� � ����� "keywords" �� (�������� �����)

    lem::Path docs_path;         // ���� � ����� "documents" �� (������������������ ���������)
    lem::Path docspos_path;      // ���� � ����� � ��������� �������� ���������� � docs_path

    lem::Path files_path;        // ���� � ����� "dbfiles" �� (����� ��) 
    lem::Path assoc_hashes_path; // ���� � ����� "assoc_hashes" �� 
    lem::Path prox_path;         // ���� � ����� "prox_matrix" �� - ������� �������� ��� ���� � ������ ����������� ����������
    lem::Path status_path;       // ���� � ������� � ������� ���� (������� ������������� �������)
    lem::Collect<UFString> stor_files; // �����, � ������� �������� �������

    lem::Math::RandU rnd_file; // ��� ��������� ���������� ����� �����

    lem::zeroed<bool> dirty;     // ���� - ������ ����� �������� �� ����

    Storage(void) {}

    void SetFolder( const lem::Path &Folder, lem::int32_t trans_id=-1 );

    // ������� ����� ��������� ��� ��� ����� ������ � ��.
    void CreateNewFilename( lem::Path &new_filename, int &i_new );

    inline void AddStorFile( const UFString &FileName )
    {
     LEM_CHECKIT_Z( !FileName.empty() );
     dirty = true;
     stor_files.push_back(FileName);
    }

    void LoadPath( lem::Path &path, lem::Stream &bin );

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin );

    // ������� ����� ������ � ��������� ����� �������
    int Count(void) const;

    void Clear(void);
   };
   #endif
 
   #if defined FAIND_INDEXER
   // **************************************************
   // ��������� �������.
   // **************************************************
   struct Zone_Status
   {
    enum { BadStatus=-1, EmptyStatus=0, CompleteStatus=1000 }; // ������� ���������� ����

    int version;
    boost::posix_time::ptime finished; // �����, ����� ���� ��������� ���������� ����
    int status; 

    Zone_Status(void)
    { clear(); }

    void clear(void)
    {
     version=0;
     status=BadStatus;
     finished=boost::date_time::not_a_date_time;
    }

    inline bool ok(void) const { return status==CompleteStatus; }

    // ������������� ���������� ���������� ������
    inline void SetOk(void) { status=CompleteStatus; }

    inline void Failed(void) { status=BadStatus; }

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin ) const;
   };
   #endif

   // *********************************************
   // ������ ������������������ ����������.
   // *********************************************
   struct DocumentsList : lem::NonCopyable
   {
    typedef std::multimap< lem::UFString::hash_type, File_Entry* >::const_iterator C_ITER;
    typedef std::multimap< lem::UFString::hash_type, File_Entry* >::iterator V_ITER;

    std::vector<File_Entry*> indexed_files;
    std::multimap< lem::UFString::hash_type, File_Entry* > files;
    lem::zeroed<bool> dirty; // ������ ��� ������� � ����� ��������� ���

    DocumentsList(void) {}
    ~DocumentsList(void);

    inline void AddIndexedFile( File_Entry *entry )
    {
     files.insert( std::make_pair( entry->name.GetName().GetHash(), entry ) );
     entry->i_indexed_file = CastSizeToInt(indexed_files.size());
     indexed_files.push_back(entry);
     dirty = true;
    }

    inline int Count(void) const { return CastSizeToInt(indexed_files.size()); }

    inline bool Loaded(void) const { return indexed_files.empty()==false; }

    inline const File_Entry& Get( int i ) const { return *indexed_files[i]; }
    inline       File_Entry& Get( int i )       { return *indexed_files[i]; }

    void Clear(void);

    void LoadBin( lem::Stream &bin );
    void SaveBin( lem::Stream &bin );

    #if LEM_DEBUGGING==1
    void Assert(void) const;
    #endif

    void RebasePaths( const lem::UFString &old_prefix, const lem::UFString &new_prefix );
   };


   class DocumentIterator;
   class IndexManager;
   class Crawler_Operation;
   class Topic_Finder;
   struct Hit_Statistics;


   // *************************************
   // ����������
   // *************************************
   class Indexer : lem::NonCopyable
   {
    public:
     Domain_Info domain_info;        // �������� �������. ������ �����, � �� ������,
                                     // ������� ������ ������������ � �������� ���������������. 
     Indexer_Operation operation;    // ����������� ���������
     Zone_Status zone_status;        // ������ ����������� ����
     Word_Searcher keywords;         // ����� ������ �������� ����


     // ������������ ������������ �������������� ������, ������������
     // � ����������� ��������� �������.
     lem::CPtr<Solarix::Dictionary> sol_id;
     lem::CPtr<Solarix::Search_Engine::Fuzzy_Comparator> fuzzy_eq;
     lem::CPtr<const Solarix::Search_Engine::Lexer_Options> lexer_options;
     #if defined FAIND_DATAMINE
     lem::CPtr<Solarix::Search_Engine::Topic_Finder> topic_finder;
     #endif 
     lem::CPtr<const Solarix::Search_Engine::Search_Options> searching;
     #if !defined SOL_NO_AA
     //lem::CPtr<Solarix::Text_Processor> tpu;
     #endif

     static wchar_t Command_Delimiter_Char;

    protected:
     boost::shared_ptr<DocumentIterator> document_iterator; // �������� ��������� ������� � ������ ����������
     const Echo_Options* echo;
     const General_Options* generals;
     IndexManager* manager;
     Solarix::Dictionary *dictionary;
     const Solarix::LD_Seeker *seeker;

     // ������ ������� ��� ������ �����������.
     virtual FString GetEngineName(void) const;

     int GetRealDomainId(void) const;
     virtual void RebaseDocumentPath( File_Entry &entry );

    public:
     Indexer(
             IndexManager *Manager,
             const Domain_Info &Domain_info,
             Solarix::Dictionary *ptrDict,
             const LD_Seeker *seeker,
             const Echo_Options *Echo,
             const General_Options *Generals
            );

     virtual ~Indexer(void);

     // �������� ������� � ������ ��� ���������, ���������� ������� � 
     // ������� ��� ���������.
     virtual void Mount(
                        const Indexer_Operation &Operation,
                        const Crawler_Operation &engine_command
                       );


     // ��� �����������: ���� �� ����������������� ��������
     virtual bool IsFileChanged( const File_Location &filename );

     // ���������� ������� ��������� - ���������� ��� ����������� ���������,
     // ��������� ���������� �������.
     virtual void Commit(void);

     // ����������� �������� ����� � ������������ ��� ������ � ����� ������.
     inline int AddKeyword( const UCString &Word, Morphology m )
     { return keywords.AddKeyword(Word,m); }

     inline const Word_Searcher& GetSearcher(void) const { return keywords; }

     // ����� ����������� �������� ���� �������� ����� ������ Word. ���� �������,
     // ������������ ���������� ���������� ���� ����� (��. ���
     // ������� ������� Get_Keyword). ���� �� ������� - ������ UNKNOWN.
     inline int FindKeyword( const UCString &Word, Morphology morph ) const
     { return keywords.Find(Word,morph); }

     inline void FindKeywords(
                              const UCString &Word,
                              Fuzzy_Comparator *equator,
                              std::set<int> &result
                             ) const
     { keywords.FindKeywords(Word,equator,result); }

     inline void FindKeywordsRoots(
                                   const UCString &Word,
                                   std::set<int> &result
                                  ) const
     { keywords.FindKeywordsRoots(Word,result); }


     #if !defined FAIND_NO_BOOST_REGEX
     void FindKeywordsRegex(
                            const boost::wregex &Word,
                            std::set<int> &ind_list,
                            lem::MCollect<UCString> &str_list
                           ) const
     { keywords.FindKeywordsRegex(Word,ind_list, str_list); }
     #endif 

     virtual int FindKeywordSlow( const UCString &Word, Morphology morph ) const;
     virtual void FindKeywordsSlow(
                                   const UCString &Word,
                                   Fuzzy_Comparator *equator,
                                   std::set<int> &result
                                  ) const;


     inline bool IsSolarixKeyword( int superindex ) const
     { return keywords.IsSolarixKeyword(superindex); }

     inline const UCString& GetKeyword( int super_index ) const
     { return keywords.GetKeyword(super_index); }

//     void Load( File_Entry* pfile );

     // Returns the list of file indeces that associated with keyword.
     virtual Assoc_Files* GetAssocFiles( int super_index, const Pattern &pattern );
     virtual Assoc_Files* GetAssocFiles( int super_index1, int super_index2, const Pattern &pattern );
     virtual Assoc_Files* GetAllFiles(void);
     virtual Assoc_Files* GetAssocFiles( const Pattern &pattern );

     // ��������� ��� ����������� �������������� �������������� ��� �����
     virtual void SetTagForFile(
                                const lem::UFString &path,
                                File_Location::LocType loctype,
                                const lem::UFString &loc, 
                                const lem::UFString &tag,
                                const lem::UFString &value
                               );

     // ��������� �������� ���� ��� ���������� ���������.
     virtual bool GetTagForFile(
                                const lem::UFString &filename,
                                File_Location::LocType loctype,
                                const lem::UFString &fileloc, 
                                const lem::UFString &tag,
                                lem::UFString &value
                               );


     // ��������� ��� ������ ����������� �������������, ������� ��
     // ������������ ���������� � ����� ���������� ������.

     // ����� �� ������ �����, ���� prefix=true, �� ����������� ����� �� ���������� ������ ����� � word
     virtual Assoc_Files* GetAssocFiles( const UCString &word, bool Prefix, int maxhitcount, const Pattern &pattern );
 
     // ����� �� �������������� ������ (OR)
     virtual Assoc_Files* GetAssocFiles( const MCollect<UCString> &words, int maxhitcount, const Pattern &pattern );

     virtual void PreparePrefetchingKeywords(void);
     virtual void FinishPrefetchingKeywords(void);
     virtual void PrefetchKeyword( const UCString &Word );

//     virtual Document_Index* CreateDocIndex(void) const;

     #if defined FAIND_DATAMINE
     virtual boost::shared_ptr<Doc_Topic> LoadDocumentTopic( int i_file );
     #endif

     // ���������� ������������������ ������ � ��������� �������
     virtual void DumpFiles( const lem::Path &filename, const wchar_t *format );

     // ���������� ���������� � ��������� �������� �������.
     virtual void PrintInfo( OFormatter &out, bool detailed=false );

     // �������������� ���������� �� ����������� �������.
     virtual Zone_Statistics GetZoneStat(void);

     static void PackDomainCommands( UFString &cmd, const Collect<UFString> & args );
     static void UnpackDomainCommands( const UFString &cmd, Collect<UFString> & args );

     virtual void AddDocument( const File_Location &filename, Base_File_Reader *reader );

     virtual bool LoadDocumentIndex( File_Entry *file_entry );

     // ������ ���� ����������� � ��������: ������������ ��
     // ���������� ����������.
     virtual bool DoesSupportMorphology(void) const;

     // ������ ���� ����������� � ��������: ������������ ��
     // ���������� �������� �� ����������� �������� ���� �
     // �����������.
     virtual bool SupportSolarixKeywordsDictionary(void) const;

     virtual int GetDocumentId( int i );

     // ������������ ��������� �� ������������������ �������� �� ��� ID.
     // � ����������� �� ���������� ������������ ������ ����� ���� ������
     // ������ ��� ������� ������, ��� ��������� � ����� ����������� ������.
     virtual boost::shared_ptr<File_Entry> GetDocumentById( int id_doc );

     // ���������� ID ���������� �� ��������� �������-������������� ���������.
     virtual boost::shared_ptr<File_Entry> GetDocumentByIndex( int id_doc );

     // ������ ������� ����� ���������� ������������������ ����������.
     virtual int CountDocuments(void);

     // ������ ������� ���������� �������� ���� � �����������.
     virtual int CountKeywords(void);

     virtual void DumpHTML( const lem::Path &filename );
     virtual void DumpCSV( const lem::Path &filename );
     virtual void DumpTXT( const lem::Path &filename );
     
     virtual ProximityMatrixProber* GetProximityMatrixProber( const File_Entry *file_entry );

     virtual bool IsActiveSearcher( const Pattern &pattern ) const;

     // ���������� ��� ��������� �������� ������� ��������������.
     virtual bool IsActiveWriter(void) const;

     // ���������� �� ����� ��� ��������� �������� ����� � ���������
     // � ������ ��������.
     virtual bool NeedsExternalFilesearch(void) const;

     // ����� ���������� ��� �������� ������������ - ������� ���� ���������
     // �������� ������� ��������������. ����� �������� stat ������������ 
     // ���������� - ���-�� ������������ ������.
     virtual void Run( Solarix::Search_Engine::Hit_Statistics &stat );


     // ��������� ����������� � �������� �� ������������ �������������� �����,
     // �������� locate.
     virtual bool SupportFulltextSearch(void) const;

     // ���� ���������� ����� ���������� � �������� ���� ��� ������
     virtual bool SupportMetainfo(void) const;

     // ��� ������������� ��������� ������ � ������� ���� �� �����
     virtual void ReopenIfNeeded(void) {}


     // ������� ������������� ���������� ������������ � ����. 0-��� �����������.
     virtual void SetMaxPoolSize( int n );
   };

 
   // *********************************************
   // ����� ���������� �������������.
   // *********************************************
   class IndexManager : lem::NonCopyable
   {
    private:
     Solarix::Dictionary* dictionary; // �������������� ������
     const Solarix::LD_Seeker* seeker;
     lem::Ptr<Idb_List> idb_list; // �������������
  
     #if defined FAIND_FILEMON
     Folder_Monitor folder_monitor;
     #endif

     #if defined LEM_THREADS   
     lem::Process::CriticalSection cs;
     #endif

     int MaxPoolSize; // ������������ ���������� �������������� � ���� ��������
     lem::Collect< boost::shared_ptr<Indexer> > index_pool; // ��� ����������� ��������

     // ������� �� ���� �������� ������ ��� ��������� ����
     bool PurgeIndexPool( int id_index );

     // ��� ���������� � SQL ���������.
     lem::Collect< std::pair< Remote_Zone, lem::Ptr<SQLConnection> > > connections;

     lem::Ptr<SQLConnection> FindConnection( const Remote_Zone &server );

    public:
     enum { Version=12 }; // ��� ������� ������ �������� ��

     static int count_writer, count_reader, count_updater; // ��� ����� �������� ������������

     const Echo_Options *echo;
     const General_Options *generals;
     const Indexer_Options *options;

    public:
     IndexManager(
                  Solarix::Dictionary *ptrDict,
                  const Solarix::LD_Seeker* Seeker,
                  const Indexer_Options *Options,
                  const Echo_Options *Echo,
                  const General_Options *Generals
                 );

     virtual ~IndexManager(void);

     // ������ �������� � ���������� ���������.
     virtual void PrintVersion( OFormatter &out, const lem::UI::Resource_List &resx ) const;

     inline       Idb_List& GetDomains(void)       { return *idb_list; }
     inline const Idb_List& GetDomains(void) const { return *idb_list; }

     #if defined FAIND_FILEMON
     void StartMonitoring( Change_Event_Func func );
     void StopMonitoring(void);
     inline const Folder_Monitor& GetFolderMonitor(void) const { return folder_monitor; }
     void MonitorDynamicZone( int id_zone );
     int FindIndexToRefresh(void);
     #endif

     // �������� ���� ��������
     void DeleteAllIndexes(void);

     // ���������� ������ ��������
     virtual void ListDomains( OFormatter &out, const lem::UI::Resource_List &resx );
     virtual void ListSharedDomains( OFormatter &out, const lem::UI::Resource_List &resx );

     // ����� ����� ���������� �� ��������.
     virtual void ShowTotals( OFormatter &out, const lem::UI::Resource_List &resx );

     // ������ ������� �������, ��� ���������� �������� � ������.
     virtual void PurgeDomain( const UFString &domain_name );

     // ������� ������ ���������� ��� �������
     virtual void SetDomainComment( const UFString &domain_name, const UFString &text );

     // �������� ������� �� ������, ������� �����
     virtual void DeleteDomain( const UFString &domain_name );

     // �������������� �������
     virtual void RenameDomain( const UFString &domain_name, const UFString &new_name );

     // ���������� �������� ������� � ��������� ��������.
     virtual void BackupDomainsList( const lem::Path &dest_folder );

     // �������������� �������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomainsList( const lem::Path &dest_folder );

     // ���������� ������� � ��������� ��������.
     virtual void BackupDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // �������������� ������� �� ��������� ����� � ��������� ��������.
     virtual void RestoreDomain( const UFString &domain_name, const lem::Path &dest_folder );

     // ��������� ������ ������ ������� ��� �������
     virtual void ShareDomain( const UFString &domain_name, bool shared );
     virtual void ShareDomain( int id_zone, bool shared );

     // �������������� ���������� �� ���� ����������� �����
     // �������� - ��� ��������� ��������� ��� ��������� ��������
     // ���������� ��������� ���.
     virtual Zone_Statistics GetTotalZonesStat(
                                               OFormatter &out 
                                               #if defined FAIND_SIGNALS
                                               , boost::signal2< void, lem::OFormatter&, const wchar_t* > &progress
                                               #endif 
                                              );


     // ������� ���������� �� ���������� �������
     virtual void PrintDomainInfo( const UFString &domain_name, OFormatter &out, bool detailed=false );

    // ��� ���������� ������� ���������� ������ ������������������ ����������.
    virtual void DumpFiles(
                           const UFString &domain_name,
                           const lem::Path &filename,
                           const wchar_t *format
                          );

    virtual bool IndexNeedsPurgedBeforeUpdate( int id_zone );

    virtual boost::shared_ptr<Indexer> GetReader( const Indexer_Operation &operation, const Crawler_Operation &engine_command );
    virtual boost::shared_ptr<Indexer> GetWriter( const Indexer_Operation &operation, const Crawler_Operation &engine_command );
    virtual boost::shared_ptr<Indexer> GetUpdater( const Indexer_Operation &operation, const Crawler_Operation &engine_command );

    boost::shared_ptr<Indexer> GetReader( const UFString &zone_name );

    virtual void ZoneNeedsReindexing( int id_zone, lem::Collect< lem::Path* > &changed_files );
    virtual void ZoneNeedsReindexing( int id_zone );

    // �������� ������������� ��������� ������, ���������� true � ������ ������.
    virtual bool LockByReader( int id_index );
    virtual bool LockByWriter( int id_index );

    virtual bool IsLockedByReader( int id_index );
    virtual bool IsLockedByWriter( int id_index );

    // �������� ������������� ��������� ������, ���������� true � ������ ������.
    virtual void UnlockByReader( int id_index );
    virtual void UnlockByWriter( int id_index );

    virtual void UnlockAll(void);
    virtual void Unlock( const UFString &domain_name );

    inline SQLConnection& GetConnection(void) { return *(options->connection); }

    virtual void PrintSessions( OFormatter &out, const lem::UI::Resource_List &resx ) const;

    // ������ �������� �������� � ���������� �������
    virtual void ImportDomains( SQLConnection &c );

    // ��������� �� ��� �������, �� ���� �� �������� �� ��� ����������� ��������
    bool VerifyNameChars( const lem::UFString &zone_name ) const;

    void SetMaxPoolSize( int n ) { MaxPoolSize=n; }
   };



   class DocumentIterator
   {
    public:
     DocumentIterator(void) {}
     virtual ~DocumentIterator(void) {}

     virtual int Size(void) const=0;
     virtual int GetDocId( int i ) const=0;
   };




  } // namespace Search_Engine
 } // namespace Solarix

#endif
