#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/LA_RecognitionRule.h>

using namespace lem;
using namespace Solarix;

LA_RecognitionRule::LA_RecognitionRule(void)
 : id_language(UNKNOWN), id_entry(UNKNOWN), score(0), src_location(UNKNOWN)
{
}

LA_RecognitionRule::LA_RecognitionRule( int Id, const lem::UCString &Name, bool CaseSensitive, int Id_Lang,
     bool IsSyllab, bool IsRegex, bool IsPrefix,
     bool IsAffix, bool IsForced, const lem::UFString &Condition, int EntryId, float Score, const Solarix::CP_Array &Coords,
     int SourceID )
 : id(Id), name(Name), case_sensitive(CaseSensitive), id_language(Id_Lang), id_entry(EntryId), str(Condition), is_syllab(IsSyllab),
   is_regex(IsRegex), is_prefix(IsPrefix), is_affix(IsAffix), is_forced(IsForced), coords(Coords), score(Score), src_location(SourceID)
{
 if( is_regex )
  {
   if( CaseSensitive )
    rx = boost::wregex( str.c_str() );
   else
    rx = boost::wregex( str.c_str(), boost::basic_regex<wchar_t>::icase );
  }

 return;
}



#if defined SOL_LOADTXT && defined SOL_COMPILER

static bool IsRegexChar( wchar_t c )
{
 return c==L'?' || c==L'[' || c==L']' || c==L'(' || c==L')' || c==L'{' || c==L'}' || c==L'*' || c==L'.' || c==L'+';
}

void LA_RecognitionRule::LoadTxt( lem::Iridium::Macro_Parser &txtfile, Dictionary &dict )
{
 score = 0;

 // �������� ��������� ������� � �������� �������
 lem::Iridium::BSourceState point_begin = txtfile.tellp();
 src_location = dict.GetDebugSymbols().RegisterLocation( txtfile, point_begin );

 // ������������ ���
 while( !txtfile.eof() )
  {
   lem::Iridium::BethToken t0 = txtfile.read();
   if( t0.GetToken()==B_OFIGPAREN )
    break;
   else if( t0.string()==L"forced" )
    {
     txtfile.read_it( B_EQUAL );
     is_forced = txtfile.read().string()==L"true";
     
    }
   else if( t0.GetToken()==B_LANGUAGE )
    {
     // ������ ���� ������������ �����, � ������ �������� ��������� �������.
     txtfile.read_it( B_EQUAL );
     lem::Iridium::BethToken t1 = txtfile.read();
     id_language = dict.GetSynGram().Find_Language(t1.string());
     if( id_language==UNKNOWN )
      {
       lem::Iridium::Print_Error(t1,txtfile);
       dict.GetIO().merr().printf( "Unknown language name %us\n", t1.c_str() );
       throw lem::E_BaseException();
      }
    }
   else if( name.empty() )
    {
     // ������ ��� �������
     name = t0.string();
     name.strip_quotes();
    }
   else
    {
     lem::Iridium::Print_Error(t0,txtfile);
     dict.GetIO().merr().printf( "Unexpected token %us\n", t0.c_str() );
     throw lem::E_BaseException();
    }
  }

 txtfile.read_it( B_IF );

 is_syllab = txtfile.probe(B_SYLLAB);

 // ����� ������� ������ �������������� � ��������, ������ ��� ������������� ��������, ���� � ��� �����.
 case_sensitive = txtfile.probe( L"@" );

 str = txtfile.read().GetFullStr();
 str.strip( L'"' );

 if( id_language!=UNKNOWN )
  {
   // ������� ����������� ����� �������� ��� �������� �����.
   dict.GetSynGram().languages()[id_language].SubstParadigmPattern(str);
  }

 // ���� ������ ������� ����� ��� "(.+)�������" ��� "(.*)�������",
 // �� �������� ���������� ��������� �� �������� ��������

 if( str.eq_beg(L"(.+)") || str.eq_beg(L"(.*)") )
  {
   is_affix = true;

   // ��������, ��� ����� (.+) ��� ������������ ����������� ���������
   for( int j=4; j<str.length(); ++j ) 
    {
     const wchar_t c = str[j];
     if( IsRegexChar(c) )
      {
       is_affix=false;
       break;
      }
    }

   if( is_affix )
    str = str.c_str()+4; // �������� ��������� ����������� (.+) ��� (.*)
  }
 else if( str.eq_beg(L".+") || str.eq_beg(L".*") )
  {
   is_affix = true;

   for( int j=2; j<str.length(); ++j ) 
    {
     const wchar_t c = str[j];
     if( IsRegexChar(c) )
      {
       is_affix=false;
       break;
      }
    }

   if( is_affix )
    str = str.c_str()+2;
  }
 else if( str.eq_end(L"(.+)") || str.eq_end(L"(.*)") )
  {
   is_prefix=true;

   // ��������, ��� �� ����������� (.+) ��� ������������ ����������� ���������
   for( int j=0; j<str.length()-4; ++j ) 
    {
     const wchar_t c = str[j];
     if( IsRegexChar(c) )
      {
       is_prefix=false;
       break;
      }
    }

   if( is_prefix )
    str = lem::left(str,str.length()-4);
  }
 else if( str.eq_end(L".+") || str.eq_end(L".*") )
  {
   is_prefix=true;

   // ��������, ��� �� ����������� (.+) ��� ������������ ����������� ���������
   for( int j=0; j<str.length()-2; ++j ) 
    {
     const wchar_t c = str[j];
     if( IsRegexChar(c) )
      {
       is_prefix=false;
       break;
      }
    }

   if( is_prefix )
    str = lem::left(str,str.length()-2);
  }

 if( !is_affix && !is_prefix && !is_syllab )
  {
   for( int k=0; k<str.length(); ++k )
    {
     if( str[k]==L'\\' )
      continue;

     if( wcschr( L"%+.?[]{}()~!$*|<>", str[k] )!=NULL )
      {
       is_regex = true;
       break;
      }
    }

   if( is_regex )
    {
     if( case_sensitive )
      rx = boost::wregex( str.c_str() );
     else
      rx = boost::wregex( str.c_str(), boost::basic_regex<wchar_t>::icase );
    }
   else
    {
     dict.GetLexAuto().TranslateLexem( str, true, id_language );
    }
  }

 txtfile.read_it( B_THEN );
 
 SynGram &sg = dict.GetSynGram();

 lem::Iridium::BethToken t2 = txtfile.read();
 const int id_class = sg.FindClass(t2.string());
 if( id_class==UNKNOWN )
  {
   lem::Iridium::Print_Error(t2,txtfile);
   dict.GetIO().merr().printf( "Unknown part of speech %us\n", t2.c_str() );
   throw lem::E_BaseException();
  }

 txtfile.read_it( B_COLON );

 lem::Iridium::BethToken tentry = txtfile.read();
 UCString entry_name(tentry.string());
 entry_name.strip(L'"'); 
 lem::MCollect<Word_Coord> ies;
 id_entry = sg.FindEntry( entry_name, id_class, false );

 if( id_entry==UNKNOWN )
  {
   lem::Iridium::Print_Error(tentry,txtfile);
   dict.GetIO().merr().printf( "Can not find wordentry %us:%us\n", t2.c_str(), entry_name.c_str() );
   throw lem::E_BaseException();
  }

 txtfile.read_it( B_OFIGPAREN );

 // ������ ������ �������������� ��������� � �������� �������
 while( !txtfile.eof() )
  {
   if( txtfile.pick().GetToken()==B_CFIGPAREN )
    {
     txtfile.read();
     break;
    }
   
   // ��� �������: ����������:���������
   // ��� ������������: ����������
   // ��� ������������ � ������������ � ����������� ������ ����� =���_�����:����������
   lem::Iridium::BethToken coord_name = txtfile.read();

   bool AFFIRM=true;

   if( coord_name.GetToken()==B_NEGATIVE )
    {
     // �������� ��������� ����� ������������ ����������!
     AFFIRM=false;
     coord_name = txtfile.read();
    }

   const GramCoordAdr iglob_coord = sg.FindCoord(coord_name.string());

   if( !iglob_coord.IsDefined() )
    {
     sg.GetIO().merr().printf( "Unknown coordinate %us\n", coord_name.c_str() );
     lem::Iridium::Print_Error(coord_name,txtfile);
     throw lem::E_BaseException();
    }

   if( sg.coords()[iglob_coord.GetIndex()].IsBistable() )
    {
     // ��� ��������� �� ����� ���� �������.
     coords.push_back(GramCoordPair(iglob_coord,AFFIRM));
    }
   else
    {
     // ����� ��������� ������ ���� ��� ��������� ��� ����������.
     txtfile.read_it(B_COLON);

     // ��� ���������.
     BethToken state_name = txtfile.read();

     // ������� ������ ��������� ��� ������������ ����������.
     const int istate = sg.coords()[iglob_coord.GetIndex()]
                            .FindState(state_name.string());
     if( istate==UNKNOWN )
      {
       // ��� ������ ��������� ��� ����� ���������.
       lem::Iridium::Print_Error(state_name,txtfile);
       sg.GetIO().merr().printf(
                                "State [%vfE%us%vn] is not declared for coordinate [%vfE%us%vn]\n"
                                , state_name.c_str(),coord_name.c_str()
                               );
       throw E_ParserError();
      }

     coords.push_back( GramCoordPair(iglob_coord,istate) );
    }
  }

 // ����� ���� ������ ����� ��������� ��� ��������� �� ������������� �������
 if( txtfile.probe(B_EQUAL) )
  { 
   if( txtfile.probe( B_SUB ) )
    score = -txtfile.read_real();
   else
    score = txtfile.read_real();
  }

 txtfile.read_it( B_CFIGPAREN );


 return;
}
#endif



bool LA_RecognitionRule::Match(
                               const lem::UCString & normalized_word,
                               const lem::UCString & original_word
                              ) const
{
 if( is_syllab )
  {
   LEM_CHECKIT_Z( case_sensitive==false );
   return normalized_word.eqi(str.c_str());
  }
 else if( is_regex )
  {
   if( case_sensitive )
    return boost::regex_match( original_word.c_str(), rx );
   else
    return boost::regex_match( normalized_word.c_str(), rx );
  }
 else if( is_prefix )
  {
   if( case_sensitive )
    return original_word.eq_beg(str.c_str());
   else
    return normalized_word.eq_begi(str.c_str());
  }
 else if( is_affix )
  {
   if( case_sensitive )
    return original_word.eq_endi(str.c_str());
   else
    return normalized_word.eq_endi(str.c_str());
  }
 else
  {
   LEM_STOPIT;
   return 0;
  } 
}


LA_RecognitionRule::HashType LA_RecognitionRule::GetHash(void) const
{
 return CalcHash( str.c_str(), is_prefix, is_affix );
}

LA_RecognitionRule::HashType LA_RecognitionRule::CalcHash( const wchar_t * str, bool IsPrefix, bool IsAffix )
{
 LEM_CHECKIT_Z( !lem::lem_is_empty(str) );

 if( IsPrefix )
  {
   return lem::to_uupper(str[0]);
  }
 else if( IsAffix )
  {
   return lem::to_uupper(str[ lem::lem_strlen(str)-1 ]);
  }
 else
  {
   LEM_STOPIT;
   return 0;
  }
}
