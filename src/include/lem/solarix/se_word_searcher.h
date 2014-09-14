// LC->21.11.2011

#ifndef SE_WORD_SEARCHER__H
#define SE_WORD_SEARCHER__H
#pragma once

  #if !defined FAIND_NO_BOOST_REGEX
   #include <boost/regex.hpp>
  #endif

  #include <lem/solarix/se_morphology.h>
  #include <lem/solarix/WordEntry.h>
  #include <lem/solarix/sg_autom.h> 
  #include <lem/solarix/LD_Seeker.h>
  #include <lem/solarix/dictionary.h>

  #undef assert

  namespace Solarix
  {
   namespace Search_Engine
   { 
    class Fuzzy_Comparator;

     // ��������� ��� �������� ������ ����.
     class Word_Searcher
     { 
      public:
       const LD_Seeker *ld_seeker;
       enum { N_SUBLIST=65536 };

      private:
       friend class Indexer;
       friend class IndexWriterFaind;
       friend class IndexUpdaterFaind;
    
       Solarix::Dictionary *sol_id;
  
       // ����� ������ �������� ���� - ������ �� N_SUBLIST ����������
       // (�� ����� ������ �������� ���-���� �����) ��� ���������
       // ������ ����������� - ��� ����� ������� ����� ������
       // ������������� ����������� ������ ���������� �������
       // ���������.

       struct KwdSublist
       {
        lem::MCollect<UCString> keywords;
        UCString::hash_type hmin, hmax;

        lem::MCollect< lem::int16_t > idx; // ��� �������������� ������ � keywords �� hash8

        KwdSublist(void) { hmin=0xff; hmax=0; }
    
        int Find( const UCString &Word ) const;
        int Add( const UCString &Word );

        void SaveBin( lem::Stream& bin ) const;
        void LoadBin( lem::Stream& bin );

        inline int Size(void) const { return CastSizeToInt(keywords.size()); }
        inline const UCString& operator[]( int i ) const { return keywords[idx[i]]; }
        inline void Clear(void) { keywords.clear(); idx.clear(); hmin=0xff; hmax=0; }
        inline void Reserve( int n ) { keywords.reserve(n); idx.reserve(n); }
       };

       KwdSublist keywords[ N_SUBLIST ];

       Stream::pos64_type offsets[N_SUBLIST];
       bool loaded[N_SUBLIST];
       lem::zeroed<bool> dirty; // ���� "������ ����� ���������"

       // �� ����������� ������� �������� ����� ���������.   
       inline int GetSublist( int super_index ) const
       { return 0x0000ffff & super_index; }

       inline int GetSubIndex( int super_index ) const
       { return (0x7f000000 & super_index)>>16; }

      public:
       Word_Searcher( Solarix::Dictionary *ptrDict, const LD_Seeker *Seeker );   

       virtual ~Word_Searcher(void);

       // �� ������ ��������� i_sublist � ������� � ���� ��������� j
       // ��������� ���������� ������ �����.
       // ������� ��� ������ �������� 0 - ������� ����, ��� ����� �� � ���������.
       inline int SuperIndex( int i_sublist, int j ) const
       { return (j << 16) | i_sublist; }

       // ������ ��������� ������ � ��������� ����������� � ��������
       // ���� ����� - ���������� ������� ���.
       inline int IEntryToIndex( int iEntry ) const
       {
        IFDEBUG(assert());
        return iEntry | 0x80000000UL;
       }

       // ����� ���� ������������� �� ��������
       inline bool IsSolarixKeyword( int superindex ) const 
       { return (superindex & 0x80000000UL) == 0x80000000UL; }


       // ����������� ���������������� �� �������� ����� ����������� �
       // ���������� ������ � ���������
       inline int IndexToIEntry( int Super_Index ) const
       {
        IFDEBUG(assert());
        return Super_Index & 0x7fffffffUL;
       }

       // �������������� ������ � ����������� �������� ������ ���������� ���
       // ��������������. ��� ���� ������������� ������� �� ����������, ���
       // ��� ��� ������������� �������� ����� �� �������������.
       void Reserve(void);

       // ����������� �����, ������������ ��� ���������� ������
       // � ������.
       int AddKeyword( const UCString &Word, Morphology m );

       // ����� ����� - ������������ ��� ���������� ������.
       // ���� ������ ������� �� ������ ��������� (������ ������� ����)
       // � ������� � ��������� (��������� 24 ����).
       // ���� ����� �� �������, �� ������������ UNKNOWN.
       int Find( const UCString &Word, Morphology m ) const;

       // �������� ����� �������� ����
       void FindKeywords(
                         const UCString &Word,
                         Fuzzy_Comparator *equator,
                         std::set<int> &result
                        ) const;

       void FindKeywordsRoots(
                              const UCString &Word,
                              std::set<int> &result
                             ) const;

       #if !defined FAIND_NO_BOOST_REGEX
       void FindKeywordsRegex(
                              const boost::wregex &Word,
                              std::set<int> &ind_list,
                              lem::MCollect<UCString> &str_list
                             ) const;
       #endif  


       // ���������� ����� ����� �������� ����.
       int Size(void) const;

       inline int SublistSize( int isublist ) const { return keywords[isublist].Size(); }

       inline const UCString& GetSublistKeyword( int isublist, int iword ) const { return keywords[isublist][iword]; }

       inline const UCString& GetKeyword( int super_index ) const
       {
        if( super_index & 0x80000000UL )
         {
          LEM_CHECKIT_Z(sol_id);
          return sol_id->GetSynGram().GetEntry( super_index & 0x7fffffffUL ).GetName();
         }

        return keywords[ GetSublist(super_index) ][ GetSubIndex(super_index) ];
       }

       void SaveBin( lem::Stream& bin );
       void LoadBin( lem::Stream& bin );
       void LoadForHash16( int Hash16, lem::Stream& bin );
       void LoadOffsets( lem::Stream& bin );

       // ����� ���������� ���������� �� ������� ����.
       void PrintInfo( OFormatter &out, bool dump_keywords ) const;

       // ������� �� ������ ����������� ������ �������� �������� ���� (�����
       // �� ������� ��������).
       virtual void PurgeBasicKeywords(void);
     };

   } // namespace Search_Engine
  } // namespace Solarix

#endif
