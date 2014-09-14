// -----------------------------------------------------------------------------
// File YGRES.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
//
// Content:
// ���������� ������ Compiler - ���������� ������� (������������ � ���������
// Ygres).
// 26.05.2007 - � ������ > 3.2 �������� ����������� � ��������� �����.
// 04.01.2010 - ��������� ��������� ���� �������������
// 15.04.2010 - �������� ��������� ������������� �����������, ��������� ������
//              ������������ ����� ���������.   
// 29.08.2010 - ������� ��� ��������� ������ LITE
// -----------------------------------------------------------------------------
//
// CD->26.03.2004
// LC->21.10.2012
// --------------

#if defined SOL_COMPILER

#include <lem/cfg_parser.h>
#include <lem/user_interface.h>
#include <lem/system_config.h>
#include <lem/macro_parser.h>
#include <lem/char_buffer.h>
#include <lem/logfile.h>

#include <lem/solarix/ClassList.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/ucstring_functions.h>
#include <lem/solarix/PartOfSpeech.h>
#include <lem/solarix/Thesaurus.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/WordEntries.h>
#include <lem/solarix/WordEntryEnumerator.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/dsa_main.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/LEMM_Compiler.h>

#include <lem/solarix/LexiconStorage_SQLITE.h>
#include <lem/solarix/ThesaurusStorage_SQLITE.h>
#include <lem/solarix/WordEntries_File.h>
#include <lem/solarix/AlphabetStorage_SQLITE.h>
#include <lem/solarix/Charpos2EntryStorage_SQLITE.h>

#include <lem/solarix/ygres.h>

using namespace Solarix;
using namespace lem;
using namespace lem::Iridium;
using namespace lem::Cfg_Parser;
using namespace lem::UI;
using namespace lem::Char_Stream;


Compiler::Compiler( OFormatter &echo, OFormatter &err, const Dictionary_Config &cfg )
{
 // ������� �������-�������, �������� ��� ���������� ����������.
 sol_id = new Dictionary( &echo, &err, cfg );

 // ���������� ��������� �� ��� ���������
 lem::UFString sqlite_file;

 sqlite_file = lem::Path::GetTmpFilename().GetUnicode();
 AlphabetStorage_SQLITE *alphabet_storage = new Solarix::AlphabetStorage_SQLITE(sqlite_file);
 alphabet_storage->CreateSchema();
 sol_id->GetGraphGram().SetStorage(alphabet_storage,true);

 sqlite_file = lem::Path::GetTmpFilename().GetUnicode();
 LexiconStorage_SQLITE *lexicon_storage = new Solarix::LexiconStorage_SQLITE(sqlite_file);
 lexicon_storage->CreateSchema();
 sol_id->GetSynGram().SetStorage(lexicon_storage,true);
 sol_id->GetLexAuto().SetStorage(lexicon_storage,false);
 sol_id->GetAlephAuto().SetStorage(lexicon_storage,false);
 sol_id->GetDebugSymbols().SetStorage(lexicon_storage);

 sqlite_file = lem::Path::GetTmpFilename().GetUnicode();
 ThesaurusStorage_SQLITE *thesaurus_storage = new Solarix::ThesaurusStorage_SQLITE(sqlite_file);
 thesaurus_storage->CreateSchema();
 sol_id->GetSynGram().Get_Net().SetStorage(thesaurus_storage,true);

 sol_id->GetSynGram().SetEntries( new Solarix::WordEntries_File( &sol_id->GetSynGram(), cfg ) );

 trace_level = 2;
 bin_options.parsing = SRC_BETH_ECHO_PRINT | SRC_BETH_JOURNALIZE;

 // ������� �������� �� ��������� ��� ���������� �������
 cp = &lem::UI::get_UI().GetSessionCp();

 return;
}

Compiler::~Compiler(void)
{
 return;
}



// *******************************************************************
// ���������� �������. ����� proj_file ��������� �� ��������� ���� ��
// ������� ������������� ���������� (����� *.sol).
// *******************************************************************
void Compiler::CompileProject( lem::Stream &proj_file )
{
 // � ������ 3.1 ������ ����� ������ �������� XML. �� ������ �������������
 // ����� ����� �� ���������� ��������� ���� <?xml

 sol_id->GetSynGram().GetStorage().BeginTx();
 sol_id->GetSynGram().Get_Net().GetStorage().BeginTx();

 const lem::Stream::pos_type beg = proj_file.tellp();
 lem::CharBuffer xml_tag(6); 
 proj_file.read( (char*)xml_tag, 5 );
 
 proj_file.seekp( beg );

 if( strcmp(xml_tag,"<?xml")==0 )
  CompileXmlProject(proj_file);
 else
  CompileAsciiProject(proj_file);

 sol_id->GetSynGram().GetStorage().CommitTx();
 sol_id->GetSynGram().Get_Net().GetStorage().CommitTx();

 return;
}
 

// ************************************************************
// ������ ������� ������� �������� - plain text
// ************************************************************
void Compiler::CompileAsciiProject( lem::Stream &proj_file )
{
 // ��������� ���� �� ������� ��� ������������� ������.
 // ���� ����� ���� � ����������� ��������� ������� ������,
 // ���� � utf ��������� � BOM.
 lem::Ptr<WideStream> rdr = lem::Char_Stream::WideStream::GetReader( lem::Ptr<Stream>(&proj_file,lem::null_deleter()) );

 UFString next_fn;

 while( !rdr->eof() )
  {
   // ������ ��� �����.
   next_fn.clear();
   rdr->read_line(next_fn);
   next_fn.trim();
   next_fn.strip_quotes();
   if( next_fn.empty() )
    continue;

   // ����������� - ��� ������, ������������ � // ��� #
   if( next_fn.front()==L'#' || next_fn.eq_beg(L"//") )
    continue;

   if( next_fn.empty() || next_fn==";" )
    break;

   // ���� ������ ���������� � $, �� ��� ���������.
   if( next_fn.front()==L'$' )
    {
     if( next_fn.eq_beg( L"$dictionary_xml" ) )
      {
       lem::UFString s = lem::right( next_fn, next_fn.length()-16 );
       xml_injection.push_back( new UFString(s) );
      }

     continue;
    }

   // ���� ��� ����� �������� ����������� * � ?, �� ����
   // ����� ���� ������ �� �����.
   if( next_fn.search(L'*')!=UNKNOWN || next_fn.search(L'?')!=UNKNOWN )
    {
     lem::Path p( next_fn );
  
     UFString mask = p.GetUnicode();

     p.RemoveLastLeaf(); 
     std::vector< lem::Path > file_list;
     p.ListFiles( mask.c_str(), file_list, false );

     for( lem::Container::size_type i=0; i<file_list.size(); ++i )
      {
       const lem::Path & p2 = file_list[i];
       BinaryReader txt(p2);
       sol_id->LoadTxt( txt, defines.c_str(), bin_options, *cp, root_dir );
      }
    }
   else
    {
     // ��� ����� ����� ���� ���������� - ����� �� �� ����� ������������ ��������
     // ������� �������.
     lem::Path p2(next_fn);
     if( p2.DoesExist() )
      {
       BinaryReader txt(p2);
       sol_id->LoadTxt( txt, defines.c_str(), bin_options, *cp, root_dir );
      }
     else
      { 
       lem::Path p( root_dir + next_fn );
       BinaryReader txt(p);
       sol_id->LoadTxt( txt, defines.c_str(), bin_options, *cp, root_dir );
      }
    }
  }

 return;
}


// ************************************************************
// ������ ������ ������� �������� - XML utf-8
// ************************************************************
void Compiler::CompileXmlProject( lem::Stream &proj_file )
{
 LEM_STOPIT;
 return;
}

void Compiler::CompileFile( lem::Stream &sol_file )
{
 sol_id->LoadTxt( sol_file, defines.c_str(), bin_options, *cp, root_dir );
 return;
}


void Compiler::Optimize(void)
{
 sol_id->Optimize();
}


void Compiler::CreateAffixTable(void)
{
 affix_table = new Affix_Table( sol_id->GetSynGram() );
 return;
}


void Compiler::EmptyAffixTable(void)
{
 affix_table = new Affix_Table();
 return;
}


// ***********************************************************
// ���������� ���������� �������, ����������� C++-������ ����� 
// ��������� � �������� outdir.
// ***********************************************************
void Compiler::PostCompile( const lem::Path &outdir )
{
 sol_id->GetSynGram().GetStorage().BeginTx();
 sol_id->GetSynGram().Get_Net().GetStorage().BeginTx();

 sol_id->PrepareAfterTranslation(outdir,bin_options);

 sol_id->GetSynGram().GetStorage().CommitTx();
 sol_id->GetSynGram().Get_Net().GetStorage().CommitTx();

 #if defined SOL_PRINTREP
 // ����� � ����������� ����������.
 sol_id->Report();
 #endif

 return;
}


void Compiler::ParadigmasStorage( bool save )
{
 if( save )
  sol_id->GetSynGram().Get_DSA().AutoParadigmasMustBeStored();

 return;
}


void Compiler::SaveAlphabet( const lem::Path &db_path ) const
{
 sol_id->GetGraphGram().GetStorage().CopyDatabase( db_path );
 return;
}


void Compiler::SaveMorphology( lem::Stream &bin, const lem::Path &lexicon_db_path )
{
 sol_id->SaveBin( bin );
 sol_id->GetSynGram().SaveLexiconDb(lexicon_db_path);
 return;
}


void Compiler::SaveSeeker( lem::Stream &bin ) const
{
 lem::Ptr<LD_Seeker> seeker( sol_id->GetSynGram().GetEntries().Get_Seeker() );
 seeker->SaveBin(bin);
 return; 
}


// *********************************************************************
// ��������� � ����������� � �������� ������ ������� � ��������������
// ��������� ��� ��������.
// *********************************************************************
void Compiler::SaveAffixes( lem::Stream &bin ) const
{
 affix_table->SaveBin(bin);
 return;
}


void Compiler::SaveThesaurusDb( const lem::Path &p ) const
{
 sol_id->GetSynGram().Get_Net().SaveThesaurusDb(p);
 return; 
}


void Compiler::SavePrefixEntrySearcher( const lem::Path &p ) const
{
 // �������� ������� ����������� ������ ����
 Charpos2EntryStorage_SQLITE *stg = new Charpos2EntryStorage_SQLITE(p.GetUnicode());
 PrefixEntrySearcher pes( stg, lem::int_max );

 lem::Ptr<WordEntryEnumerator> wenum( sol_id->GetSynGram().GetEntries().ListEntries() ); 
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();
   pes.AddEntry( e.GetKey(), e );
  }
 
 pes.Commit();

 return;
}

static void WriteEncodedString(
                               lem::Stream &bin,
                               const UCString &s,
                               const std::map<wchar_t,lem::uint8_t> & wchar2i,
                               int compression
                              )
{
 char buf[ lem::UCString::max_len+1 ];
 for( int i=0; i<s.length(); ++i )
  {
   const wchar_t wc = s[i];

   if( wchar2i.find(wc)==wchar2i.end() )
    {
     UFString str = lem::format_str( L"Error in WriteEncodedString: unknown character %c code=%d in string [%s]", wc, unsigned(wc), s.c_str() );
     throw E_BaseException(str);
    }

   lem::uint8_t c = wchar2i.find(wc)->second;
   buf[i] = c;
  }

 buf[ s.length() ] = 0;

 if( compression==0 )
  {
   bin.write( buf, UCString::max_len );
  } 
 else
  {
   bin.write_uint8( s.length() );
   bin.write( buf, s.length() );
  }

 return;
}


namespace
{
 struct Normalizator : lem::NonCopyable
 {
  lem::UCString form;
  lem::MCollect<int> inorm; // �������������� ������� (������ ����) � �����������

  void SaveBin( lem::Stream &bin, int char_size, const std::map<wchar_t,lem::uint8_t> &wchar2i ) const
  {
   if( char_size==sizeof(wchar_t) )
    {
     lem::Save_Packed( form, bin );
    }
   else if( char_size==1 )
    {
     WriteEncodedString( bin, form, wchar2i, 1 );
    }
   else
    {
     LEM_STOPIT;
    }
   
   // ��������� �����������: ��� ��� ������ ������� ������ 1 ����� ��� �����, ��
   // ��������� ���� ���������� ���� ����� ������.

   if( inorm.size()>255 )
    throw E_BaseException( L"Normalizator 8bit count field overflow" );

   const lem::uint8_t n = (lem::uint8_t)inorm.size();
   bin.write_uint8(n);

   lem::uint8_t x8[3];
   for( lem::Container::size_type i=0; i<inorm.size(); ++i )
    {
     // ������ 32-������� ������ ����� ��������� ������ 24 �����, ��� ��� ������������ ������,
     // ��� � ��� ����� ���������� � 16 ���������� ����.
     const int x32 = inorm[i];

     if( x32>0x00ffffff )
      {
       throw E_BaseException( L"Normalizator 24bit field overflow" );
      }

     x8[0] = (x32&0x00ff0000)>>16;
     x8[1] = (x32&0x0000ff00)>>8;
     x8[2] = (x32&0x000000ff);
   
     bin.write( x8, 3 );     
    }
   
   return;
  }
 };

}

typedef Normalizator* PNormalizator;
static bool norm_sorter( PNormalizator &a, PNormalizator &b )
{
 return a->form > b->form;
}


static bool suffix_sorter(
                          const std::pair<UCString,UCString> &a,
                          const std::pair<UCString,UCString> &b
                         )
{
 const int la=a.first.length(), lb=b.first.length();

 if( la>lb )
  return true;

 if( la<lb )
  return false;

 // ���������� ����� - ���������� � �������� �������� ��������, ������ ������
 for( int i=la-1; i>=0; --i )
  {
   wchar_t ca = a.first[i];
   wchar_t cb = b.first[i];
   if( ca>cb )
    return true;

   if( ca<cb )
    return false;
  }

 return false;
}


struct LemmSuffix
{
 lem::MCollect<lem::UCString> new_suffix;
 lem::MCollect<int> freq;

 LemmSuffix(void) {}

 void Add( const lem::UCString &s, int f )
 {
  const int i = new_suffix.find(s);
  if( i==-1 )
   {
    new_suffix.push_back(s);
    freq.push_back(f);
   }
  else
   {
    freq[i] += f;
   }

  return;
 }

 void SelectBestNewSuffix( lem::UCString &x ) const
 {
  int max_freq=0, ibest=UNKNOWN;
  for( lem::Container::size_type i=0; i<new_suffix.size(); ++i )
   {
    if( freq[i] > max_freq )
     {
      max_freq = freq[i];
      ibest = CastSizeToInt(i);
     }
   }

  if( ibest!=UNKNOWN )
   x = new_suffix[ibest];

  return;
 }
};



void Compiler::SaveLemmatizer( const lem::Path &filename, bool verbose ) const
{
 const int MAX_SFX_LEN=8; // ����������� ����������� ����� ��������
 const int L_NHASHGROUP=1024; // ���-�� �������� ��� �������� ��������� ���-����� ����

 // ��������� ������ ������������� ��������.
 std::set<wchar_t> wchars;
 
 wchars.insert(L'\0'); // ����� �� ��������� ������� � ������������� �����, ������������� ������ ��� � �������.

 lem::Ptr<WordEntryEnumerator> wenum( sol_id->GetSynGram().GetEntries().ListEntries() );
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();
   if( e.IsTerminal() )
    {
     for( int k=0; k<e.GetName().size(); ++k )
      {
       wchars.insert( e.GetName()[k] );
      }

     for( Container::size_type iform=0; iform<e.forms().size(); iform++ )
      {
       const Lexem& name = e.forms()[iform].name();

       for( int k=0; k<name.size(); ++k )
        {
         wchars.insert( name[k] );
        }
      }
    }
  }

 int char_size = sizeof(wchar_t);
 lem::uint8_t char_i=0;
 std::map<wchar_t,lem::uint8_t> wchar2i;

 if( wchars.size()<256 )
  {
   // ���� ������������ ������� ��������� � 256 �������, ������� ����� ������������ ��������.
   char_size=1;
   for( std::set<wchar_t>::const_iterator it=wchars.begin(); it!=wchars.end(); ++it, ++char_i )
    {
     wchar2i.insert( std::make_pair( *it, char_i ) );
    }
  }

 if( verbose )
  {
   lem::mout->printf( " char_size=%vfA%d%vn ", char_size );
  }


 if( lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf( "LEMMATIZATOR: character set contains %d items:", CastSizeToInt(wchars.size()) );

   int ic=0;
   for( std::set<wchar_t>::const_iterator it=wchars.begin(); it!=wchars.end(); it++, ic++ )
    {
     lem::LogFile::logfile->printf( " %uc", unsigned(*it) );
     if( ic>0 && !(ic%10) )
      lem::LogFile::logfile->eol();
    }

   lem::LogFile::logfile->eol();
  }



 // ������� ������� ������ �������, ������� ���� ������������� ������������ ���� �� ���� - �������.
 std::map< const UCString*, std::pair<UCString/*�����*/,int/*������� ����*/> > form_lem_count;
 int n_omonym=0, n_form=0;

 wenum = sol_id->GetSynGram().GetEntries().ListEntries();
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();

   if( e.IsNonterminal() )
    continue;

   n_form += CastSizeToInt(e.forms().size());

   for( Container::size_type iform=0; iform<e.forms().size(); iform++ )
    {
     const Lexem& name = e.forms()[iform].name();

     std::map<const UCString*,std::pair<UCString,int> >::iterator it = form_lem_count.find(&name);
     if( it==form_lem_count.end() )
      {
       // ������ ��� ���� ������� ��� �� ������� - ���������.
       form_lem_count.insert( std::make_pair( &name, std::make_pair( e.GetName(), 1 ) ) );
      }
     else
      {
       // ����� ������� ��� ����. ��������� �� ���������� �����?
       if( it->second.first!=e.GetName() )
        {
         // ��� - �������� �������������� ���� � ������ ��������� ������.
         it->second.second++;
         if( it->second.second==2 )
          n_omonym++;
        }
      }
    }
  }

 if( verbose )
  {
   lem::mout->printf( " total_forms=%vfA%d%vn omonyms=%vfA%d%vn ", n_form, n_omonym );
  }

 lem::MCollect< std::pair<lem::UCString /*suffix*/, lem::UCString /*lemma_suffix*/> > suffices;

 // ***********************************
 // �������� ������� ���������
 // ***********************************
 lem::PtrCollect<LemmSuffix> new_sfx;
 std::map< UCString /*�������*/, LemmSuffix* /*������ ��� ��������� �����*/ > afx_tmp;
 typedef std::map< UCString, LemmSuffix* >::iterator AIT;

 wenum = sol_id->GetSynGram().GetEntries().ListEntries();
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();

   if( e.IsNonterminal() )
    continue;

   const UCString& eroot = e.GetRoot();

   if( eroot.length()<2 )
    continue;

   // �������������� ������ (���� ���������� �������� ��������) �� ���������
   // � ��������� ��������.
   if( e.GetName().Count_Lexems()>1 )
    continue;

   const int id_class = e.GetClass();
   int id_language=UNKNOWN;
   if( !lem::is_quantor(id_class) )
    {
     const SG_Class &cls = static_cast<const SG_Class&>( sol_id->GetSynGram().classes()[id_class] );
     id_language = cls.GetLanguage();
    }

   if( e.GetName().length() <= eroot.length() )
    {
     // ����� ����� ���� ��� ��������� ���� � ���������� ����������, 
     // ����� ��� ������ (�������) ���������� �� ��� ���������� ��
     // ��������� (�������� � ���������).
     continue;
    }

   const int LEFT_SUFFIX_ADDITION = 1; // ������� �������� ����� �� �������� �������� ��� ����� ������� ����������� ������������� ���������.

   const UCString base_afx = right( e.GetName(), e.GetName().length() - eroot.length() + LEFT_SUFFIX_ADDITION ); 

   // ���� �� ������ ������
   for( Container::size_type iform=0; iform<e.forms().size(); iform++ )
    {
     const Lexem& name = e.forms()[iform].name();

     // ����� �� �������� ��������?
     std::map<const UCString*,std::pair<UCString,int> >::iterator it = form_lem_count.find(&name);
     if( it!=form_lem_count.end() && it->second.second>1 )
      {
       // ��� ������ - ���������� ��.
       continue;        
      }

     // �������������� ����� ���������� - ���� �� �� ������ ��� ����������
     // � ���� ������� ������� ����� ������. �� ����� ���� �����, � �������
     // ����� �������������� ���� ���������� �������������� - �������� ���-����
     // ��������� ��� ���.
     if( name.Count_Lexems()>1 )
      continue;

     if( name.length() > eroot.length() )
      {
       // �������� ������.   
       UCString afx = right( name, name.length() - eroot.length() + LEFT_SUFFIX_ADDITION );

//       if( afx!=base_afx )
        {
         if( afx.length()<=MAX_SFX_LEN )
          {   
           // ����� �������, �� ������ �����, ��� ������ afx ���� ������������ ������� �� base_afx.
/*
#if LEM_DEBUGGING==1
 if( base_afx==L"���" && afx==L"���" )
  {
   lem::mout->printf( "\n%us\n", name.c_str() );
  }
#endif
*/
           AIT ait = afx_tmp.find(afx);
           if( ait!=afx_tmp.end() )
            {
             // ����� ������ ��� ����.
             LemmSuffix *s = ait->second;
             s->Add( base_afx, 1 /*e.GetFreq()*/ );
            }
           else
            {
             // ������ ��� ��������� ����� ������ - ����������.
             LemmSuffix *s = new LemmSuffix();
             s->Add( base_afx, e.GetFreq() );
             new_sfx.push_back(s);
             afx_tmp.insert( std::make_pair( afx, s ) );
            }
          }
        }
      }
    }
  }

 // ******************************************
 // ������� ����� ��������� ������
 // ******************************************

 int min_sfx_len=lem::int_max, max_sfx_len=0;
 std::map< lem::UCString, lem::UCString > precise_suffix;

 // ���������� ������ ��������� ��������� �� ��������� ������� afx_tmp � ���������� ���������
 for( AIT ait=afx_tmp.begin(); ait!=afx_tmp.end(); ++ait )
  {
   lem::UCString best_new_suffix;
   ait->second->SelectBestNewSuffix(best_new_suffix);

/*
#if LEM_DEBUGGING==1
 if( ait->first==L"���" )
  {
   lem::mout->printf( "\n%us\n", best_new_suffix.c_str() );
  }
#endif
*/


//   if( ait->first!=best_new_suffix )
    {
     std::pair<lem::UCString, lem::UCString> p ( std::make_pair( ait->first, best_new_suffix ) );
     suffices.push_back( p );
     precise_suffix.insert(p);

     min_sfx_len = std::min( min_sfx_len, int(ait->first.length()) ); 
     max_sfx_len = std::max( max_sfx_len, int(ait->first.length()) ); 
    }
  }
 
 // ���� ��� ��������� ���������� ������� � suffices ���, ����� ��������� ����� ����������� ��������.
 std::sort( suffices.begin(), suffices.end(), suffix_sorter );

 if( verbose )
  {
   lem::mout->printf( " n_suffix1=%vfA%d%vn ", CastSizeToInt(suffices.size()) );
  }

 if( lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf( "\n\nLEMMATIZATOR table: %d suffices\n", CastSizeToInt(suffices.size()) );
  
   for( lem::Container::size_type i=0; i<suffices.size(); ++i )
    {
     lem::LogFile::logfile->printf( "%us --> %us\n", suffices[i].first.c_str(), suffices[i].second.c_str() );  
    }

   lem::LogFile::logfile->printf( "%40h-\n\n" );
  }


 lem::MCollect<lem::UCString> normales;
 std::map<lem::UCString,int> inormales;

 lem::Ptr_NC_Collect<Normalizator> forms;
 std::map<lem::UCString,int> iforms;

 std::multimap< int /*hash16*/, Normalizator* > norm_groups;
 typedef std::multimap< int, Normalizator* >::const_iterator ITG;
 
 int n_form_via_suffix=0; // ������� ���� ��������������� ����� ����������� ��������
 int n_form_via_table=0; // ������� ���� ��������������� ������ ��������� ����

 std::set<lem::UCString> applied_precise_suffices;

 wenum = sol_id->GetSynGram().GetEntries().ListEntries();
 while( wenum->Fetch() )
  {
   const SG_Entry &e = wenum->GetItem();

   if( e.IsNonterminal() )
    continue;

   const lem::UCString &ename = e.GetName();

   int inormal=UNKNOWN;

   // ���������� ����� ��������� ������.
   for( lem::Container::size_type j=0; j<e.forms().size(); ++j )
    {
     const SG_EntryForm &f = e.forms()[j];
     const lem::UCString &fname = f.name();
    
     // ����� ��������� ������������ ����� ������ ��������?
     bool match_sfx=false, sfx_lemma=false;

     // ����� �� �������� ��������?
     bool omonym=false;
     std::map<const UCString*,std::pair<UCString,int> >::iterator it = form_lem_count.find(&fname);
     if( it!=form_lem_count.end() && it->second.second>1 )
      {
       // ���� �������� - ���������� ������� �������� ���������.
       omonym = true;
      }

     if( !omonym )
      {
       for( int sl=max_sfx_len; sl>=min_sfx_len; --sl )
        {
         if( sl>fname.length() )
          // ������� ����� ����� �������� ����������.
          continue;

         UCString sfx = lem::right( fname, sl );

         std::map< lem::UCString, lem::UCString >::const_iterator cit = precise_suffix.find(sfx);

         if( cit!=precise_suffix.end() )
          {
           match_sfx = true;

           // ������ �����. ��� ���������?
           UCString root = lem::left( fname, fname.length()-sl );
  
           root += cit->second;
           if( root!=ename )
            {
             // ���, ����� ���� ���� ����������.  
             sfx_lemma = false;
            }
           else
            {
             // ��, ����� ��������������� ���������.
             sfx_lemma = true;
             applied_precise_suffices.insert( sfx );
            }

           break; 
          } 
        } 
      }

     if( sfx_lemma==true )
      {
       // ����� ���������� ��������������� � ������� ����������� ��������.
       n_form_via_suffix++;
       continue;
      }

     n_form_via_table++;

     if( fname==ename && !omonym )
      {
       // ����� ��������� � �������. �������� ���.
       // ���� �� ���� ���������� ��� ��� ���������, �� ������ �� �����
       // ������ �� �� ����������.
       if( !match_sfx )
        continue;
      }

     if( inormal==UNKNOWN )
      {
       std::map<lem::UCString,int>::const_iterator it = inormales.find(ename);
       if( it==inormales.end() )
        {
         inormal = CastSizeToInt(normales.size());
         normales.push_back(ename);
         inormales.insert( std::make_pair( ename, inormal ) );     
        }
       else
        {
         inormal = it->second;
        }  
      }

     int iform = UNKNOWN;
     std::map<lem::UCString,int>::const_iterator itf = iforms.find(fname);
     if( itf==iforms.end() )
      {
       iform = CastSizeToInt(forms.size());
       Normalizator *n = new Normalizator;
       n->form = fname;
       n->inorm.push_back(inormal);
       forms.push_back( n ); 
       iforms.insert( std::make_pair( fname, iform ) );

       const int h16 = fname.GetHash16()&(L_NHASHGROUP-1);
       norm_groups.insert( std::make_pair( h16, n ) );
      }
     else
      {
       iform = itf->second;
       Normalizator *n = forms[iform];
       if( n->inorm.find(inormal)==UNKNOWN )
        n->inorm.push_back(inormal);
      }
    }
  }

 if( lem::LogFile::IsOpen() )
  {
   lem::LogFile::logfile->printf( 
    "Compression: %d forms lemmatizated using suffix, %d forms done using explicit enumeration of lemmas"
    , n_form_via_suffix, n_form_via_table );
  }

 if( verbose )
  {
   lem::mout->printf( " n_form_via_suffix=%vfA%d%vn n_form_via_table=%vfA%d%vn ", n_form_via_suffix, n_form_via_table );

   if( sol_id->GetLemmatizerCompiler()!=NULL )
    {
     sol_id->GetLemmatizerCompiler()->PrintModelInfo( *lem::mout );
    }
  }

 iforms.clear();
 inormales.clear();

 lem::BinaryWriter bin( filename );

 lem::Stream::pos_type norm_pos=0;
 bin.write( &norm_pos, sizeof(norm_pos) );

 lem::Stream::pos_type model_pos=0;
 bin.write( &model_pos, sizeof(model_pos) );

 bin.write_int( min_sfx_len );
 bin.write_int( max_sfx_len );
 suffices.SaveBin(bin);

 bin.write_int( char_size );
 bin.write_int( L_NHASHGROUP );

 if( char_size==sizeof(wchar_t) )
  {
   bin.write_int(0);
  }
 else
  {
   bin.write_int( CastSizeToInt(wchars.size()) );

   for( std::set<wchar_t>::const_iterator it=wchars.begin(); it!=wchars.end(); it++ )
    {
     wchar_t wc = *it;
     bin.write( &wc, sizeof(wc) );
    }
  }

 // �������� ���������� ���������� ����.
 bin.write_int( CastSizeToInt(normales.size()) );
 if( char_size==1 )
  {
   for( lem::Container::size_type i=0; i<normales.size(); ++i )
    {
     WriteEncodedString( bin, normales[i], wchar2i, 0 );
    }
  }
 else if( char_size==sizeof(wchar_t) )
  {
   for( lem::Container::size_type i=0; i<normales.size(); ++i )
    {
     bin.write( &normales[i], sizeof(normales[i]) );
    }
  }
 else
  {
   LEM_STOPIT;
  }


 model_pos = bin.tellp();

 if( sol_id->GetLemmatizerCompiler()!=NULL )
  {
   sol_id->GetLemmatizerCompiler()->SaveBin(bin);
  }
 else
  {
   bin.write_bool(false);
  }


 norm_pos = bin.tellp();



 lem::Stream::pos_type subgroup_pos[L_NHASHGROUP];
 memset( subgroup_pos, 0, sizeof(subgroup_pos) );
 
 // ������ ������ ������ ��� ������ ��������� ����������, ���� - ������.
 const lem::Stream::pos_type pos_subgroup_pos = bin.tellp();
 bin.write( subgroup_pos, sizeof(subgroup_pos) );
 
 // ���������� ������� �������������� �� ������� �� �������.
 for( int h=0; h<L_NHASHGROUP; ++h )
  {
   subgroup_pos[h] = bin.tellp();

   int hX = h;
   std::pair< ITG, ITG > r = norm_groups.equal_range(hX);

   // ������� ����������, ������� ��������� � ����� ������
   int n = 0;
   if( r.first!=norm_groups.end() )
    {
     for( ITG g=r.first; g!=r.second; ++g )
      n++;
    }

   bin.write_int(n);

   for( ITG g=r.first; g!=r.second; ++g )
    {
     const Normalizator *norm = g->second;
     norm->SaveBin(bin,char_size,wchar2i);
    }
  }

 // �������� ������� ��������� ��� ��� �������, ����� ����� �� ������� � ������� ���������� � �� �������
 // �� ��� ���� �� ������ ���������.

 int n_missed_suffix=0;
 for( AIT ait=afx_tmp.begin(); ait!=afx_tmp.end(); ++ait )
  {
   const lem::UCString &sfx = ait->first;
   if( applied_precise_suffices.find(sfx)==applied_precise_suffices.end() )
    {
     // ���� ������� �� ����������� � ������ ������������...
     n_missed_suffix++;
    }
  }
 
 bin.seekp(0);
 bin.write( &norm_pos, sizeof(norm_pos) );
 bin.write( &model_pos, sizeof(model_pos) );

 // ������� ����������� ������� ������� ����� ���������.
 bin.seekp( pos_subgroup_pos );
 bin.write( subgroup_pos, sizeof(subgroup_pos) );

 // ������������ ���� ������������� ���������. 
 bin.seekp( 0, SEEK_END );

 return;
}


void Compiler::StemmerPrintInfo( OFormatter &out ) const
{
 affix_table->PrintInfo(out);
}

const Solarix::Dictionary& Compiler::GetDictionary(void) const
{
 LEM_CHECKIT_Z(sol_id!=NULL);
 return *sol_id;
}


lem::UFString Compiler::GetDictionaryXmlString(void) const
{
 lem::UFString res;

 for( lem::Container::size_type i=0; i<xml_injection.size(); ++i )
  {
   res += *xml_injection[i];
   res += L"\n";
  }

 return res;
}

#endif
