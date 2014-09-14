#if defined FAIND_DATAMINE && !defined SE_DATA_MINER__H
#define SE_DATA_MINER__H
#pragma once

 #include <map>
 #include <lem/containers.h>
 #include <lem/ufstring.h>
 #include <lem/solarix/se_indexer_types.h>
 #include <lem/solarix/file_location.h>
 #include <lem/solarix/sg_autom.h>
 //#include <lem/solarix/ngrams_collector.h>

 namespace Solarix
 {
  class LexemDictionary;

  namespace Search_Engine
  { 
  // *********************************************************** 
  // ��������� ��� ��������� ���� ���������� (����������������),
  // ������������� �������������� ��������� ����������.
  // ***********************************************************

  class Crawler;
  class Base_File_Reader;
  class Fix_Context;
  class Word_Searcher;

  // ************************************************************
  // ������� ����� ��� ���������� ������ ��������� ����������.
  // ************************************************************
  class Base_DataMiner
  {
   protected:
    lem::Path outdir; // ������� ��� ���������� ������ � ��������

    // ��� ������ ������������ ������� (��� ���� ������������ ������������
    // ����������) ������ ������������ ��� ���� ���� - �������� ���������
    // ������-������� � ��������� ���������� � ���. ����� GUI �������� �����
    // �������� ������������ ���� "�������" � ������������ ������������� 
    // ������ �����.
    lem::Collect< std::pair< lem::Path, lem::UFString > > report_files;

   public:
    Base_DataMiner(void);
    virtual ~Base_DataMiner(void);

    // �������� ��������� �������� ��� ���������.
    virtual void Do( 
                    Crawler &engine,
                    const File_Location &filename,
                    Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   )=0; 

    // ����� ��������� ���������� �� ����������� ���������.
    virtual void Report( Crawler &engine ); 

    // ������� ��� �������� ������� �� ��� ���������� �����
    static Base_DataMiner* Create( const lem::UFString& name, const lem::UFString &arg );

    // ��� ������ ������ ����� ����������� �������.
    virtual bool DoesNeedDictionary(void) const;

    // ��� ������ ������ ����� ����������� ��������.
    virtual bool DoesNeedThesaurus(void) const;

    // ��� ������ ������ ����� ����������� ���� ������������
    virtual bool DoesNeedClassifier(void) const;
  };


/*
  // *****************************************************************  
  // ������������ ������������ �������: ��������� ��������� ���������
  // ���� ��������� (����������). ������� �����.
  // *****************************************************************  
  class DM_Topic_Base : public Base_DataMiner
  {
   protected:
    typedef enum { All, English, Russian, French, German, Italian, Spanish } Language;
    Language language;

   private:
    int n_to_list;
    lem::zbool translate_to_noun; // ��������� ����� � ���������������
    lem::zbool normalize; // ������������� ������� ����
    lem::zbool ngrams; // ��������� ������� N-�����

    void NormalizeFrequencies(
                              Crawler &engine,
                              std::map< Index_Entry, float > &word_freq,
                              const Word_Searcher &words 
                             );

   protected:
    virtual void ProcessUnsorted(
                                 Crawler &engine,
                                 const File_Location &filename,
                                 lem::MCollect<Fix_Context*> &contexts,
                                 const std::map< Index_Entry, float > &word_freq,
                                 const Word_Searcher &words,
                                 const Solarix::NGramsCollector & ngrams_collector
                                );

    virtual void ProcessSorted(
                               Crawler &engine,
                               const File_Location &filename,
                               lem::MCollect<Fix_Context*> &contexts,
                               const std::map< Index_Entry, float> &word_freq,
                               const lem::MCollect< std::pair<Index_Entry,float> > &sorted,
                               const Word_Searcher &words,
                               const Solarix::NGramsCollector & ngrams_collector
                              ) {}

   public:
    DM_Topic_Base( const lem::UFString &arg );

    virtual void Do( 
                    Crawler &engine,
                    const Solarix::Search_Engine::File_Location &filename,
                    Solarix::Search_Engine::Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   ); 


   virtual bool DoesNeedDictionary(void) const { return translate_to_noun; }
   virtual bool DoesNeedThesaurus(void) const { return translate_to_noun; }
  };


  // **********************************************************************
  // ������������ ���� ��������� �� ������� ��������� ���� ���������������.
  // **********************************************************************
  class DM_Topic_Real : public DM_Topic_Base
  {
   private:
    lem::zbool analyzer_mode; // ����� ������ ��� ���������� ���������� - ������� ����
                              // ��� ������ ���������� � XML �����, ��� ������� �������������
                              // ��������� - ���� ������ ������. 

    lem::Path outfile;
    lem::Ptr<lem::OUFormatter> xml;
    float min_topic_rel; // ����������� ������������� �������������� ������������ ������

    int boost_monograms, boost_ngrams; // ������������ ��� ���������/���������� ������� ���������
                                       // ���� � N-����� �� ������� �������������.


   protected:
    virtual void ProcessUnsorted(
                                 Crawler &engine,
                                 const File_Location &filename,
                                 lem::MCollect<Fix_Context*> &contexts,
                                 const std::map< Index_Entry, float> &word_freq,
                                 const Word_Searcher &words,
                                 const NGramsCollector & ngrams_collector
                                );

   public:
    DM_Topic_Real( const lem::UFString &arg );

    virtual bool DoesNeedClassifier(void) const;
    virtual bool DoesNeedDictionary(void) const;
    virtual void Report( Crawler &engine );
  };


  // ***********************************************************
  // ������������ ���� ��������� �� �������� ������ ������.
  // ���������� � ������ ��������� ���������� �� �������������
  // ���� � ����������.
  // ***********************************************************
  class DM_Topic_Top_Frequent : public DM_Topic_Base
  {
   private:
    int n_to_list;           // ������� ����� ������ ���� �������� 
    lem::zbool filter_nouns; // ������ ���������������
    lem::zbool accumulate;   // ��������� ���������� ��� ���� ������������ ������
    lem::zbool analyzer_mode; // ����� ������ ��� ���������� ���������� - ������� ����
                              // ��� ������ ���������� � XML �����, ��� ������� �������������
                              // ��������� - ���� ������ ������. 

    std::auto_ptr<Word_Searcher> total_words; // ����������� ���������� ����
    std::map< Index_Entry, float> total_word_freq; // ������������� �� ���� ���-�� ����������

    // ��� ������ ����������� ����������
    lem::Path outfile;
    typedef lem::PtrCollect< std::pair<lem::UFString,float> > Spectrum;
    lem::PtrCollect< lem::Path > docs;
    lem::PtrCollect< Spectrum >  spectra;
  
   protected:
    virtual void ProcessSorted(
                               Crawler &engine,
                               const File_Location &filename,
                               lem::MCollect<Fix_Context*> &contexts,
                               const std::map< Index_Entry, float> &word_freq,
                               const lem::MCollect< std::pair<Index_Entry,float> > &sorted,
                               const Word_Searcher &words,
                               const NGramsCollector & ngrams_collector
                              );

   public:
    DM_Topic_Top_Frequent( const lem::UFString &arg );

    virtual bool DoesNeedDictionary(void) const;

    virtual void Report( Crawler &engine ); 
  };



 namespace Empir
 {
  class WordProcessor;
  #if !defined SOL_NO_AA
  class SentanTextProcessor;
  #endif

  class CharProcessor;
  class SyllabProcessor;
  class WordStatProcessor;

  // ************************************************************************
  // ��������� ������� �������� - ��������� ���� ��������� ������ �� �������.
  // ************************************************************************
  class Class_Mapper
  {
   private:
    const Solarix::LexemDictionary *ld;

    lem::MCollect<int> ilexem_2_ientry;

    std::multimap<int, int> list;
    typedef std::multimap< int, int >::const_iterator ITER;
    typedef std::pair< int, int > VALUE;

    inline int Calc_Hash( const lem::UCString &s ) const
    { return (int(s.GetHash()) & 0x000000ff) + (s.back()<<16) + (s.length()<<20); }

   public:
    Class_Mapper( const Solarix::LexemDictionary *ptr, const Solarix::SynGram &sg );

    int Find_Entry( const lem::UCString &x ) const;
  };

 } 
 
 // *********************************************************
 // ������������ ������ ��� �������������� ��������� ������. 
 // *********************************************************
 class EmpirTextProcessor : public Base_DataMiner
 {
  private:
   friend class Solarix::Search_Engine::Empir::WordProcessor;

   typedef enum { Undefined, Scheme1, Scheme2, Sentan, LexiconProbing, ToNouns } Scheme;
   Scheme scheme;
    
   lem::zbool analyzer_mode;
   lem::Path outfile;
   lem::Ptr<OFormatter> xml;

   std::vector<int> sentence_ie;

   enum Correl { UnknownCorrel, Nouns, Noun_Adjs, Noun_Verbs };
   Correl correl;
 
   lem::zeroed<bool> verbose; // ��������� ������ �� ��������� �� ���� ���������

   lem::zeroed<bool> to_nouns; // ��� Scheme2 ���� 'to_nouns': ����������� ����� 
                               // �� ���� ����������� ���������� � �����
                               // ����������������.

   lem::zeroed<int> max_distance; // ��� Scheme2 ����. ���������� ����� ���������
                                  // ��� ����� �� ���������� 

   lem::UFString report_format;   // csv/xml/sql

   lem::zeroed<bool> raw_pairs; // ���������� �������� � ����������� ����� ��� ���������� � ����������

   // ������������� �� ���� ��������� ������ ���������� 

   // ������� ��������� ������
   std::map< int, int > word_freq;
   typedef std::map< int, int >::iterator WORD_FREQ_ITER;

   // ������ ���������� ����
   std::map< int, std::map< int, int >* > links;

   typedef std::map< int, std::map< int, int >* >::iterator ITER1;
   typedef std::map< int, std::map< int, int >* >::const_iterator CITER1;
   typedef std::map< int, std::map< int, int >* >::reverse_iterator RITER1;

   typedef std::map< int, int >::iterator ITER2;
   typedef std::map< int, int >::const_iterator CITER2;

   boost::posix_time::ptime t0;             // ��������������� ����� ������ ������

   std::auto_ptr<Solarix::Search_Engine::Empir::WordProcessor> words; // ����������� ����

   #if !defined SOL_NO_AA
   std::auto_ptr<Solarix::Search_Engine::Empir::SentanTextProcessor> sentan; // ������ ��������� ����������� SENTAN
   #endif

   bool run_chars;
   std::auto_ptr<Solarix::Search_Engine::Empir::CharProcessor> char_stat;
   std::auto_ptr<Solarix::Search_Engine::Empir::SyllabProcessor> syllab_stat;
   std::auto_ptr<Solarix::Search_Engine::Empir::WordStatProcessor> word_stat;

   int n_words_2; // ������� ���������� ���� �� ����� 2

   typedef enum { All, English, Russian, French, German, Italian, Spanish } Language;
   Language language;

   Solarix::Dictionary* sol_id;
   const Solarix::SynGram *sg;
   Solarix::LexicalAutomat *la;
   
   std::auto_ptr<Solarix::Search_Engine::Empir::Class_Mapper> cls_mapper; 

   int file_counter; // ����� ������������ ������

   void Report1( Solarix::Search_Engine::Crawler &crawler );
   void Report2( Solarix::Search_Engine::Crawler &crawler );

   // ��������� ��������� ������� �� ����� 1 (�������� �������������� 
   // ��������� ���� � ������������).
   void Process1( const lem::UCString &l );

   // ��������� ��������� ������� �� ����� 2 (���������� ��� ����).
   void Process2( const lem::UCString &l );

   void Set_Scheme1(void);
   void Set_Scheme2(void);
   void Set_Sentan(void);
   void Set_LexiconProbing(void);
   void Set_ToNouns(void);
   void ParseArgumentsList( lem::Collect<lem::UFString> &args );

   bool CheckClassForCorrel( int iclass ) const;
   bool IsNoun( int iclass ) const;
   bool IsAdj( int iclass ) const;
   bool IsVerb( int iclass ) const;

  public:
   EmpirTextProcessor( const lem::UFString &arg );

   virtual ~EmpirTextProcessor(void);

   virtual void Report( Crawler &engine ); 

   virtual void Do(
                   Crawler &engine,
                   const File_Location &filename,
                   Base_File_Reader *reader,
                   lem::MCollect<Fix_Context*> &contexts
                  ); 
 };


  // *****************************************************************  
  // ���������� ���-����� (MD5 � ��) ��� ����������.
  // *****************************************************************  
  class DM_HashCalc : public Base_DataMiner
  {
   private:
    lem::Path outfile; // ��� ����� � ������������ ������� 

    // ��������� � �� ����
    lem::PtrCollect< lem::Path >    docs;
    lem::PtrCollect< lem::FString > md5;

   public:
    DM_HashCalc( const lem::UFString &arg );

    virtual void Do( 
                    Crawler &engine,
                    const Solarix::Search_Engine::File_Location &filename,
                    Solarix::Search_Engine::Base_File_Reader *reader,
                    lem::MCollect<Fix_Context*> &contexts
                   ); 

    virtual void Report( Crawler &engine );
  };
*/
 }
}
#endif
