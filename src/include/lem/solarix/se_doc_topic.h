// ----------------------------------------------------------------------------
// File SE_DOC_TOPIC.H
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SEARCH ENGINE Core
//
// ��������������. 
//
// 23.05.2006 - ������� ���������� �������������� ���� �� �����
// 19.06.2008 - �������� ����� Topic_Finder::SaveXML ��� ����������� ����������
//              ������ ������ ���, ��� ������������ � ���������� ������.
// ----------------------------------------------------------------------------
//
// CD->23.02.2006
// LC->14.10.2011
// --------------

#ifndef SE_DOC_TOPIC__H
#define SE_DOC_TOPIC__H
#pragma once

// #if defined FAIND_DATAMINE

 #include <map>
 #include <lem/mqueue.h>
 #include <lem/oformatter.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/file_factory.h>
 //#include <lem/solarix/text_processor.h>
 #include <lem/solarix/se_fix_context.h>
 #include <lem/solarix/se_word_searcher.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/se_search_options.h>
 #include <lem/solarix/se_echo_options.h>
 #include <lem/solarix/search_engine_callbacks.h>
 //#include <lem/solarix/ngrams_collector.h>
 #include <lem/solarix/search_engine.h>


 namespace Solarix
 {
  namespace Search_Engine 
  {
   extern const wchar_t CORPUS_TOPIC_NAME[]; // ��� �������, � ������� ���������� ������,
                                             // ������������ �������������������� ������.


   // �������� ������ ���������� (����� ������������ ������� ��� "����")
   struct Id_Criterion
   {
    int id;           // PK
    bool actual;      // false ��� ��������� ������
    lem::UFString text;    // ��������� ��������

    Id_Criterion(void);

    Id_Criterion( int Id, const lem::UFString &Text );

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
   };



  // ********************************************
  // ������� CRITERIA
  // ********************************************
  class Tbl_Criteria
  {
   private:
    PtrCollect<Id_Criterion> rows;

    lem::Path GetFileName(void) const;
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

   public:
    Tbl_Criteria(void);

    int Find( int Id ) const;
    int Find( const UFString &Name ) const;    
    inline const Id_Criterion& operator[]( int i ) const { return *rows[i]; }
    inline       Id_Criterion& operator[]( int i )       { return *rows[i]; }

    inline int size(void) const { return CastSizeToInt(rows.size()); }

    // ���������� ��������� id ��� ����������� ������
    int GetNextId(void) const;

    // ������� �� ������� ������ � �������� id
    bool DeleteById( int Id );

    void AddChecked( Id_Criterion *NewRec );
    void AddUnsafe( Id_Criterion *NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;
    void CreateIndex(void);
  };






  // ********************************** 
  // �������� ������� � ������� TOPIC
  // ********************************** 
  struct Id_Topic //: public boost::noncopyable
  {
   int id;           // PK
   bool actual;      // false ��� ��������� ������
   int id_criterion; // ID ��������
   UFString text;    // ��������� �������� �������
   UFString code;    // ��� ������� (���� ���)
   UFString info;    // ����������

   float norma; // ����������� ��� �������� ����� ����� ���� ����������� ����,
                // ������������ ��� ������������ �����������.
   float norma2; // ���������� ��� �������

   Id_Topic(void) { id=UNKNOWN; norma=norma2=1.0F; actual=true; }

   Id_Topic( int Id, int Id_Criterion, const UFString &Text );

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };


  // ********************************************
  // ������� TOPIC
  // ********************************************
  class Tbl_Topic
  {
   private:
    PtrCollect<Id_Topic> rows;
    std::map< int /*PK*/, int /*rows[i]*/ > idx;

    lem::Path GetFileName(void) const;
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

   public:
    Tbl_Topic(void);

    int Find( int Id ) const;
    int Find( const UFString &Name ) const;    
    inline const Id_Topic& operator[]( int i ) const { return *rows[i]; }
    inline       Id_Topic& operator[]( int i )       { return *rows[i]; }

    inline int size(void) const { return CastSizeToInt(rows.size()); }

    // ���������� ��������� id ��� ����������� ������
    int GetNextId(void) const;

    // ������� �� ������� ������ � �������� id
    bool DeleteById( int Id );

    //! ������� ��� ������, ����������� �� id_criterion
    void DeleteCascadeByIdCriteria( int id_criterion );

    //! ���� �� ������, ����������� �� id_criterion
    bool DoesReferCriterion( int id_criterion ) const;

    //! ������ id �������, ����������� �� id_criterion
    void SelectByIdCriterion( int id_criterion, lem::MCollect<int> &id_topics ) const;

    void AddChecked( Id_Topic *NewRec );
    void AddUnsafe( Id_Topic *NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;
    void CreateIndex(void);
  };



  typedef lem::PtrCollect<Id_Topic> Tbl_Topic_Alias;


  // ******************************************************************
  // ������ � ������� KEYWORD - �������� �����,
  // ����������� �������� � ������ ��������� ���������� ��������������
  // ��������� � ����� �� ������.
  // ******************************************************************
  struct Rec_Keyword
  {
   int id;        // PK ������
   lem::UCString word; // �������� �����
   int ie1; // �������� ����� �� �������� - ��������� ���� ��������� ������

   lem::uint16_t hash;

   enum RecType { None, Word, Regex };
   RecType type;      // ��� ������ (0 - ������� �����, 1 - ���. ��������� ?)

   Rec_Keyword(void) { id=ie1=UNKNOWN; type=None; }

   Rec_Keyword( int Id, const UCString &W );

   // ������������� ���-���� ����� ��������� ������������ �����������
   inline void calc_hash(void)
   { hash = word.GetHash(); }

   inline lem::uint16_t GetHash(void) const { return hash; }

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   inline int GetId(void) const { return id; }
  };


  // �������� ��������������
  struct Rec_NGram : lem::NonCopyable
  {
   int id;        // PK ������
   lem::MCollect<lem::UCString> words;
   lem::MCollect<int> ies; // �������� ���� �� ��������
   Rec_Keyword::RecType type;

   Rec_NGram(void) { id=UNKNOWN; type=Rec_Keyword::None; }
   Rec_NGram( int Id, const lem::MCollect<UCString> &Words, const lem::MCollect<int> &EntryKeys );

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   inline int GetId(void) const { return id; }
   inline int Length(void) const { return CastSizeToInt(words.size()); }

   bool Match( const lem::MCollect<lem::UCString> &Words, const lem::MCollect<int> &Ies ) const;
  };


  // ���������� � �������� ������ � ���������������, ������� ������� � ������ ������
  struct Rec_Headword
  {
   int minlen, maxlen;
   Rec_Headword(void) : minlen(UNKNOWN), maxlen(UNKNOWN) {}

   void Apply( int len );
   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };

  // ************************************************
  // ������� KEYWORD - ������ �������� ���� (��� ���)
  // ************************************************
  class Tbl_Keyword
  {
   private:
    int seq_id, seq_id_ngram; // �������� ��� ��������� ����� id

    lem::PtrCollect<Rec_Keyword> rows; // ������

    // ������� ��� ��������� �������
    std::map< int /*PK*/, int /*rows[i]*/ > idx;
    std::map< int /*ie_1*/, int /*rows[i]*/ > idx_ie1;
    std::map< UCString /*word*/, int /*rows[i]*/ > idx_word;

    // NGRAM
    int ngram_maxlen; // ����. ����� (����� ����) � N-�������
    lem::PtrCollect<Rec_NGram> rows_ngram;
    std::map< int /*PK*/, int /*rows[i]*/ > idx_ngram;

    lem::PtrCollect<Rec_Headword> headwords;
    std::map<int,Rec_Headword*> ie2headword;
    std::map<lem::UCString,Rec_Headword*> word2headword;
    std::multimap< int /*ie*/, const Rec_NGram* > ie2ngram;
    std::multimap< lem::UCString, const Rec_NGram* > word2ngram;

    void CreateIndex(void);

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
    lem::Path GetFileName(void) const;

   public:
    Tbl_Keyword(void);

    inline int Count(void) const { return CastSizeToInt(rows.size()); }
    inline const Rec_Keyword& operator[]( int i ) const { return *rows[i]; }

    int CountNGram(void) const { return CastSizeToInt(rows_ngram.size()); }
    inline const Rec_NGram& GetNGram( int i_ngram ) const { return *rows_ngram[i_ngram]; }

    int Find( int Id ) const;
    int FindNGram( int Id ) const;
    int Find( const UCString &s ) const;
    int FindIE1( int IE1 ) const;

    int GetNGramMaxLen(void) const { return ngram_maxlen; }
    bool IsHeadword( const lem::UCString &word, int ie, Rec_Headword &info ) const;
    int FindNGram( const lem::MCollect<lem::UCString> &words, const lem::MCollect<int> &ies ) const;

    void AddChecked( Rec_Keyword *NewRec );
    void AddUnsafe( Rec_Keyword *NewRec );

    void AddChecked( Rec_NGram *NewRec );
    void AddUnsafe( Rec_NGram *NewRec );

    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;

    inline int GetNextId(void) { return seq_id++; }

    //! ������� ��� ������, ����������� �� id_topic
    void DeleteCascadeByIdTopic( int id_topic );
  };


  // ������� ����� KW_2_TOPIC

  struct Kw_2_Topic
  {
   int id_kwd; // FK(KEYWORD)
   int id_topic; // FK(TOPIC)
   float w;

   Kw_2_Topic(void) { id_kwd=id_topic=NULL; w=0; }
  };


  class Tbl_Kw_2_Topic
  {
   public:
    typedef std::multimap<int,int>::const_iterator II;

   private:
    MCollect<Kw_2_Topic> rows;
    std::multimap< int /*id_kwd*/, int /*rows[i]*/ >   idx_kwd;
    std::multimap< int /*id_topic*/, int /*rows[i]*/ > idx_topic;

    void CreateIndex(void);
    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
    lem::Path GetFileName(void) const;

   public:
    Tbl_Kw_2_Topic(void);

    std::pair< std::multimap<int,int>::const_iterator, std::multimap<int,int>::const_iterator > Find_Kwd( int Id_Keyword ) const;    
    std::pair< std::multimap<int,int>::const_iterator, std::multimap<int,int>::const_iterator > Find_Topic( int Id_Topic ) const;    

    inline const Kw_2_Topic& operator[]( int i ) const { return rows[i]; }
    inline       Kw_2_Topic& operator[]( int i )       { return rows[i]; }

    void AddChecked(
                    const Kw_2_Topic& NewRec,
                    const Tbl_Topic &Topic,
                    const Tbl_Keyword &Keyword
                   );

    void AddUnsafe( const Kw_2_Topic &NewRec );
    void Purge(void);
    void Commit( const lem::Path &folder );
    void Load( const lem::Path &folder );
    void SaveXML( lem::OUFormatter &out ) const;

    void DeleteCascadeByIdTopic( int id_topic );

    // ��� ������, ����� ������ ��������� ����� ������������� ���� �������,
    // ���������� ID ������� �� ID ��������� �����.
    int /*id_topic*/ Keyword2Topic( int id_keyword ) const;
  };
  






  class Word_Searcher;
  class Document_Index;
  class Topic_Finder;


  struct TF_Total_Statistics : boost::noncopyable
  {
   lem::Collect< lem::triple< int /*id_topic*/, UFString /*text*/, int /*nkwd*/ > > topics;

   int CountTopics(void) const;
   int CountKeywords(void) const;
  };


  // ***************************************************
  // ������� ����� �����������.
  // ***************************************************

  class Word;
  class CommandParser;

  class Topic_Finder
  {
   private:
    Solarix::Dictionary *sol_id;

    // ������ �������������� ������� ��������� ���� � ������ ���� �����
    lem::PtrCollect<Solarix::Search_Engine::Word> word_matchers;
    lem::MCollect<int> word_matchers_ind;

    void Purge(void);

   public:
    Tbl_Criteria tbl_criteria;
    Tbl_Topic tbl_topic;
    Tbl_Keyword tbl_keyword;
    Tbl_Kw_2_Topic tbl_kw_2_topic;

    Solarix::Search_Engine::Progress_Callback *progress;

    lem::zbool filter_nouns;

   public:
    Topic_Finder( Solarix::Dictionary *Sol_id );
    ~Topic_Finder(void);

    // �������� ����������� ������ (������������) �� XML ����� - ���
    // ���������� ����� � ���������� ���������� ��.
    void LoadXML( lem::Stream &file, Solarix::Dictionary *dict );

    int FindIE( const UCString &word, Solarix::Dictionary *dict ) const;

    void PrepareForMultiwordSearch(
                                   const Search_Options &flags,
                                   Dictionary *dict,
                                   Solarix::Search_Engine::Fuzzy_Comparator *fuzzy_eq,
                                   const Lexer_Options &lexer_options
                                   #if !defined SOL_NO_AA
//                                   , Solarix::Text_Processor *tpu
                                   #endif
                                  );

    int FindKeywordDirect( const UCString &word ) const;

    int FindKeywordWordforms(
                             Solarix::Search_Engine::File_Lexem &word,
                             Solarix::Search_Engine::Text &text, 
                             const Search_Options &flags,
                             const Solarix::LD_Seeker *seeker,
                             Solarix::Dictionary *dict,
                             Search_Engine::Fuzzy_Comparator *fuzzy_eq
                            ) const;
  };


 } // namespace Search_Engine

} // namespace Solarix 


// #endif // defined FAIND_DATAMINE

#endif
