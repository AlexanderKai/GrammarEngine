// ������������ - ��������� ��� �������� (��������������, �����) ������ ������� ��������
// �� �������. ����� ����� �������� �������� ��������� ��� ��������� �������� �������� -
// ���������� ����� ������������ (��� � ������� ���-��).
//
// 06.09.2010 - ���������� ������ ���������� ������ ��������� ��� ������������� ��������� �������,
//              ������� ���������� ������ ���� ��������.
//
// LC->16.06.2012

#include <lem/conversions.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/LanguageEnumerator.h>
#include <lem/solarix/Languages.h>
#include <lem/solarix/sentencebroker.h>

using namespace lem;
using namespace Solarix;

class SimplePattern : public EuroSentenceTokenizer::Pattern
{
 private:
  lem::UCString pattern;
  
 public: 
  SimplePattern( const lem::UCString &x );
  virtual bool MatchBegin( const lem::UCString &s ) const;
  virtual bool Match( const lem::UCString &s ) const;
  virtual wchar_t GetFrontChar(void) const;
  virtual int Length(void) const;
  virtual int MatchInplace( const lem::UFString & s, int i0 ) const;

  #if LEM_DEBUGGING==1
  virtual lem::UFString GetText(void) const { return pattern.c_str(); }
  #endif
};


class MetaCharPattern
{
 public:
  MetaCharPattern(void) {}
  virtual ~MetaCharPattern(void) {}

  virtual bool Match( wchar_t c ) const=0;
  virtual bool IsSingleChar(void) const=0;
  virtual bool IsAnyChar(void) const=0;
  virtual int MinLen(void) const=0;
  virtual int MaxLen(void) const=0;
  virtual wchar_t GetChar(void) const { return 0; }

  // ���������� ��������� ���� �� ������� ������� � ������� i0 �
  // ���������� ����� ������������� �������. 
  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const=0;

  // ������ ����� y ������� �� ���� ���������� ������ �������. ������������
  // ��������� �� ��������� - �� ��������� ��� �������� ����� ������� ���������
  // ��������, �� � ��������� ������� ����� ��������� �������������, � ����������
  // ������� ���������� ���� ����� �����.
  virtual std::pair<MetaCharPattern*,MetaCharPattern*> Combine( MetaCharPattern *y ) const
  {
   return std::make_pair( (MetaCharPattern*)this, y );
  }
};


// ************************************************************
// ����� - ���� ����� ������.
// � ��������� .*c ������������ �� ���� until(c) ���������.
// ************************************************************
class AnyCharPattern : public MetaCharPattern
{
 public:
  AnyCharPattern(void) {}

  virtual bool Match( wchar_t c ) const { return true; }
  virtual bool IsSingleChar(void) const { return true; }
  virtual bool IsAnyChar(void) const { return true; }

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  { return std::make_pair(true,1); }

  virtual std::pair<MetaCharPattern*,MetaCharPattern*> Combine( MetaCharPattern *y ) const;

  virtual int MinLen(void) const { return 1; }
  virtual int MaxLen(void) const { return 0; }
};


// *********************************************************************
// ������� �������� ����������� ����� - * � +, ��� � ����� ������ {m,n}
// ���� ����� �������� ��������� ��� ������ ����������
// � �� ����� �������������� � ������� ���������� ��������.
// *********************************************************************
class MultiCharsPattern : public MetaCharPattern
{
 private:
  int min_len, max_len;

 public:
  MultiCharsPattern( int MinLen, int MaxLen=lem::int_max ): min_len(MinLen), max_len(MaxLen) {}

  virtual bool Match( wchar_t c ) const { LEM_STOPIT; return false; }
  virtual bool IsSingleChar(void) const { return false; }
  virtual bool IsAnyChar(void) const { return true; }
  virtual int MinLen(void) const { return min_len; }
  virtual int MaxLen(void) const { return max_len; }

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   LEM_STOPIT;
   return std::make_pair( false, 0 );
  }
};


// ***********************************************
// ���������� c+ � c*
// ***********************************************
class RepeatPattern : public MetaCharPattern
{
 private:
  lem::Ptr<MetaCharPattern> ch;
  int min_len, max_len;

 public:
  RepeatPattern( int MinLen, int MaxLen, MetaCharPattern *Ch )
   :ch(Ch), min_len(MinLen), max_len(MaxLen) {}

  virtual bool Match( wchar_t c ) const { return ch->Match(c); }
  virtual bool IsSingleChar(void) const { return false; }
  virtual bool IsAnyChar(void) const { return true; }
  virtual int MinLen(void) const { return min_len; }
  virtual int MaxLen(void) const { return max_len; }

  // ������ �������� - ����� ������� ������������ �� ������, ������� � ������� � ������� i0
  // ������ �������� - ������� �������� ������� �������, ����� ���� 0 ��� ������� ? � *
  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   int n_matched=0;
   for( int i=i0; i<slen && n_matched<=max_len; ++i )
    if( Match(s[i]) )
     n_matched++;
    else
     break;

   return std::make_pair( n_matched>=min_len && n_matched<=max_len, n_matched );
  }
};



// *********************************************************
// ��������� ����������� ��� ������� .*c � .+c
// ��� ��������� �������� �� ����� ������� ���� . � *
// *********************************************************
class UntilTmpPattern : public MetaCharPattern
{
 private:
  int min_len, max_len;

 public:
  UntilTmpPattern( int MinLen, int MaxLen ) : min_len(MinLen), max_len(MaxLen) {}

  virtual bool Match( wchar_t c ) const { LEM_STOPIT; return false; }
  virtual bool IsSingleChar(void) const { return false; }
  virtual bool IsAnyChar(void) const { return true; }
  virtual int MinLen(void) const { return min_len; }
  virtual int MaxLen(void) const { return max_len; }

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   LEM_STOPIT; 
   return std::make_pair( false, 0 );
  }

  virtual std::pair<MetaCharPattern*,MetaCharPattern*> Combine( MetaCharPattern *y ) const;
};



class UntilPattern : public MetaCharPattern
{
 private:
  lem::Ptr<MetaCharPattern> ch;
  int min_len, max_len;

 public:
  UntilPattern( int MinLen, int MaxLen, MetaCharPattern* Ch ):ch(Ch), min_len(MinLen), max_len(MaxLen) {}

  virtual bool Match( wchar_t c ) const { return !ch->Match(c); }
  virtual bool IsSingleChar(void) const { return false; }
  virtual bool IsAnyChar(void) const { return true; }
  virtual int MinLen(void) const { return min_len; }
  virtual int MaxLen(void) const { return max_len; }

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   int n_matched=0;
   bool final_matched=false;
   for( int i=i0; i<slen; ++i )
    if( Match(s[i]) )
     n_matched++;
    else
     {
      n_matched++;
      final_matched=true;
      break;
     }

   return final_matched ?
           std::make_pair( n_matched>=min_len && n_matched<=max_len, n_matched ) :
           std::make_pair( false, 0 );
  }
};


class SingleCharPattern : public MetaCharPattern
{
 public:
  SingleCharPattern(void) {}
  virtual bool IsSingleChar(void) const { return true; }
  virtual bool IsAnyChar(void) const { return false; }
  virtual std::pair<MetaCharPattern*,MetaCharPattern*> Combine( MetaCharPattern *y ) const;
  virtual int MinLen(void) const { return 1; }
  virtual int MaxLen(void) const { return 1; }
};



class CharPattern : public SingleCharPattern
{
 private:
  wchar_t ch;
  wchar_t lowered_ch;

 public:
  CharPattern( wchar_t c )
  {
   ch = c;
   lowered_ch = lem::to_ulower(c);
   return;
  }
  
  virtual bool Match( wchar_t c ) const
  { return lem::to_ulower(c)==lowered_ch; } 

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   if( Match( s[i0] ) )
    return std::make_pair(true,1);
   else
    return std::make_pair(false,0);
  }

  virtual wchar_t GetChar(void) const { return ch; }
  virtual bool IsSingleChar(void) const { return true; }
  virtual bool IsAnyChar(void) const { return false; }
};


class CasedCharPattern : public SingleCharPattern
{
 private:
  wchar_t ch;

 public:
  CasedCharPattern( wchar_t c )
  {
   ch = c;
   return;
  }
  
  virtual bool Match( wchar_t c ) const
  { return c==ch; } 

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   if( Match( s[i0] ) )
    return std::make_pair(true,1);
   else
    return std::make_pair(false,0);
  }

  virtual wchar_t GetChar(void) const { return ch; }
  virtual bool IsSingleChar(void) const { return true; }
  virtual bool IsAnyChar(void) const { return false; }
};


class CharGroupPattern : public SingleCharPattern
{
 private:
  std::set<wchar_t> ch;
  std::set<wchar_t> lowered_ch;
  bool cased;

 public:
  CharGroupPattern( const std::set<wchar_t> &c, bool case_sensitive ) : ch(c), cased(case_sensitive)
  {
   if( !cased )
    {
     for( std::set<wchar_t>::const_iterator it=ch.begin(); it!=ch.end(); it++ )
      lowered_ch.insert( lem::to_ulower(*it) );
    }

   return;
  }
  
  virtual bool Match( wchar_t c ) const
  {
   return cased ? 
    ch.find(c)!=ch.end() :
    lowered_ch.find(lem::to_ulower(c))!=lowered_ch.end();
  }

  virtual std::pair<bool,int> MatchInplace( const wchar_t * s, int slen, int i0 ) const
  {
   if( Match( s[i0] ) )
    return std::make_pair(true,1);
   else
    return std::make_pair(false,0);
  }

  virtual bool IsSingleChar(void) const { return true; }
  virtual bool IsAnyChar(void) const { return false; }
};



std::pair<MetaCharPattern*,MetaCharPattern*> AnyCharPattern::Combine( MetaCharPattern *y ) const
{
 if( dynamic_cast<MultiCharsPattern*>(y)!=NULL )
  {
   // .* --> ��������� ����� ��� ������������ ����������� .*c � ���� until(c)
   UntilTmpPattern *z = new UntilTmpPattern(y->MinLen(),y->MaxLen());
   delete y;
   return std::make_pair( z, (MetaCharPattern*)NULL );
  }
 else
  return std::make_pair( (MetaCharPattern*)this, y );
}



std::pair<MetaCharPattern*,MetaCharPattern*> UntilTmpPattern::Combine( MetaCharPattern *y ) const
{
 // ����������� ������ ���� ��������� ������, ����� ���������� ��������� .*c
 if( dynamic_cast<SingleCharPattern*>(y)==NULL )
  {
   throw E_BaseException( L"Quantor .* requires single char on the right side" );
  }

 UntilPattern *z = new UntilPattern( MinLen(), MaxLen(), y );
 return std::make_pair( z, (MetaCharPattern*)NULL );
}


std::pair<MetaCharPattern*,MetaCharPattern*> SingleCharPattern::Combine( MetaCharPattern *y ) const
{
 // ����������� c+ � c* ���������� � ���� ����� repeat(c)
 if( dynamic_cast<MultiCharsPattern*>(y)!=NULL )
  {
   RepeatPattern *z = new RepeatPattern(y->MinLen(),y->MaxLen(),(MetaCharPattern*)this);
   delete y;
   return std::make_pair( z, (MetaCharPattern*)NULL );
  }
 else
  {
   return std::make_pair( (MetaCharPattern*)this, y );
  }
}




class RxPattern : public EuroSentenceTokenizer::Pattern
{
 private:
  lem::UFString pattern;
 
  lem::zbool has_asterisk;
  lem::PtrCollect<MetaCharPattern> chars;
  std::pair<MetaCharPattern*,MetaCharPattern*> Compile( MetaCharPattern *x, MetaCharPattern *y );
  void Push( MetaCharPattern *x );
  std::pair<bool,int> MatchAsPossible( const wchar_t * s, int slen, int i0 ) const;
  
 public: 
  RxPattern( const lem::UFString &x, const Solarix::Dictionary &dict );
  virtual bool MatchBegin( const lem::UCString &s ) const;
  virtual bool Match( const lem::UCString &s ) const;
  virtual wchar_t GetFrontChar(void) const;
  virtual int Length(void) const;
  virtual int MatchInplace( const lem::UFString & s, int i0 ) const;

  #if LEM_DEBUGGING==1
  virtual lem::UFString GetText(void) const { return pattern; }
  #endif
};




SimplePattern::SimplePattern( const lem::UCString &x )
 : pattern(x)
{
 pattern.to_lower();
 return;
}

bool SimplePattern::MatchBegin( const lem::UCString &s ) const
{
 return pattern.eq_begi(s);
}

bool SimplePattern::Match( const lem::UCString &s ) const
{
 return pattern.eqi(s);
}

wchar_t SimplePattern::GetFrontChar(void) const
{
 return pattern.front();
}

int SimplePattern::Length(void) const
{
 return pattern.length();
}


int SimplePattern::MatchInplace( const lem::UFString & s, int i0 ) const
{
 if( i0+pattern.length() > s.length() )
  return 0;

 for( int k=0; k<pattern.length(); ++k )
  if( lem::to_ulower(s[i0+k]) != pattern[k] )
   return 0;

 return pattern.length();
}




RxPattern::RxPattern( const lem::UFString &_x, const Solarix::Dictionary &dict )
 : pattern(_x)
{
 int icur=0;

 UFString x(_x);

 lem::Ptr<LanguageEnumerator> lenum( dict.GetSynGram().languages().Enumerate() );
 while( lenum->Fetch() )
  {
   const SG_Language &lang = lenum->GetItem();
   
   for( lem::Container::size_type j=0; j<lang.params.size(); ++j )
    {
     const SG_LanguageParam &param = *lang.params[j];
     if( param.name == L"TokenizerSubst" )
      {
       for( lem::Container::size_type k=0; k<param.values.size(); k+=2 )
        {
         const UFString & macro = param.values[k];
         const UFString & value = param.values[k+1];
         x.subst_all( macro, value );
        }
      }
    }
  }

 while( icur<x.length() )
  {
   wchar_t c = x[icur++];
   if( c==L'\\' )
    {
     c = x[icur++];
     if( c==L'u' )
      {
       // ������� unicode-������� ����� 16 ������� ��� \uNNNN
       wchar_t u[5];
       u[0] = x[icur++]; if( icur>=x.length() ) throw E_BaseException( lem::format_str( L"RxPattern error: insufficient string length for \\uXXXX in [%s]", x.c_str() ).c_str() );
       u[1] = x[icur++]; if( icur>=x.length() ) throw E_BaseException( lem::format_str( L"RxPattern error: insufficient string length for \\uXXXX in [%s]", x.c_str() ).c_str() );
       u[2] = x[icur++]; if( icur>=x.length() ) throw E_BaseException( lem::format_str( L"RxPattern error: insufficient string length for \\uXXXX in [%s]", x.c_str() ).c_str() );
       u[3] = x[icur++];

       int ucode=0;
       if( !lem::to_int( u, &ucode, 16 ) )
         throw E_BaseException( lem::format_str( L"RxPattern error: incorrent hexadecimal code [%s] in \\uXXXX", x.c_str() ).c_str() ); 
      }
     else 
      {
       Push( new CharPattern(c) );
      }
    }
   else if( c==L'[' )
    {
     // ������������ ������ ��������:
     // [abc...xyz] - ����� �� �������� �������� (��� ����� ��������)
     // [<abc...xyz>] - ����� �� �������� �������� � ��������� ��������
     // [:digit:] - ����� 0...9
     // [:space:] - ���������� (����������) ������, ������� �������� ������
     // [:punct:] - �����������
     UFString group;
     while( icur<x.length() )
      {
       wchar_t c = x[icur++];
       if( c==']' )
        break;
 
       group += c;   
      }

     LEM_CHECKIT_Z( !group.empty() );
     
     lem::zbool cased;
     if( group==L":digit:" )
      group = L"0123456789";
     else if( group==L":space:" )
      group = L" \r\n\t"; 
     else if( group==L":punct:" )
      group = L"~!@%^&*()-+=|[{]};:<,>.?";

     if( group.front()==L'<' && group.back()==L'>' )
      {
       cased = true;
       group = lem::mid( group, 1, group.length()-2 );
      }

     std::set<wchar_t> ch;
     for( int j=0; j<group.length(); ++j )
      ch.insert( group[j] );

     Push( new CharGroupPattern( ch, cased ) );
    }
   else if( c==L'.' )
    {
     // ���� ������������ ������
     Push( new AnyCharPattern );
    }
   else if( c==L'*' || c==L'+' || c==L'?' || c==L'{' )
    {
     if( chars.empty() || !chars.back()->IsSingleChar() )
      throw E_BaseException( lem::format_str( L"RxPattern error: metatokens *, +, ? and {} require char definition on the left side, pattern=[%s]", x.c_str() ).c_str() );

     has_asterisk = true;

     int min_len=-1, max_len=-1;

     switch(c)
     {
      case L'*': min_len=0; max_len=lem::int_max; break;
      case L'+': min_len=1; max_len=lem::int_max; break;
      case L'?': min_len=0; max_len=1; break;
      case L'{':
      {
       // ��������� ����������� {n,m}
       // ������ n ��� m ����� �������������: {,5} ��� {1,}
       // ����� �������� ������� {n} - ������ ���-�� ��������
       lem::UCString m, n;
       bool comma=false;
       
       while( icur<x.length() )
        {
         if( x[icur]==L',' || x[icur]==L'}' )
          break;

         m += x[icur++];
        }

       if( x[icur]!=L'}' )
        {
         comma = true;
         icur++;        

         while( icur<x.length() )
          {
           if( x[icur]==L'}' )
            {
             icur++; 
             break;
            }

           n += x[icur++];
          }
        }
       else
        {
         icur++; // ����������� �������� � {m}
        } 

       if( !m.empty() )
        min_len = lem::to_int(m);
       else
        min_len = 0; 

       if( comma ) 
        {
         if( !n.empty() )
          max_len = lem::to_int(n);
         else
          max_len = lem::int_max; 
        }
       else
        {
         max_len=min_len;
        }  

       break; 
      }

      default: LEM_STOPIT;
     }

     MultiCharsPattern *asterisk = new MultiCharsPattern(min_len,max_len);
     Push(asterisk);
    } 
   else
    {
     Push( new CharPattern(c) );
    }
  }

 return;
}


std::pair<MetaCharPattern*,MetaCharPattern*> RxPattern::Compile( MetaCharPattern *x, MetaCharPattern *y )
{
 return x->Combine(y);
}


void RxPattern::Push( MetaCharPattern *y )
{
 if( chars.empty() )
  chars.push_back( y );
 else
  {
   MetaCharPattern *x = chars.back();
   std::pair<MetaCharPattern*,MetaCharPattern*> p = Compile(x,y);

   if( p.first!=x )
    {
     chars[ chars.size()-1 ] = p.first;
    }
   else
    {
     if( p.second!=NULL )
      chars.push_back(p.second);
    }
  } 

 return;
}

// *********************************************************************************
// ������������ ������� �������� ���� ������� � �������� � 
// ����� �������� �� s, ������� � i0, ������� ������������� ��������.
// *********************************************************************************
std::pair<bool,int> RxPattern::MatchAsPossible( const wchar_t * s, int slen, int i0 ) const
{
 LEM_CHECKIT_Z( i0>=0 && i0<slen );

 int icur=i0;
 std::pair<bool,int> matching;
 matching.first = true;

 for( lem::Container::size_type i=0; i<chars.size(); ++i )
  {
   if( icur>=slen )
    {
     // �� ��� ������ �������� �������������. � ��������� ������� ��� �� ��������
     // �������� (�������� �� �������� ��������� ��������� �������� ����� � ���������).
     matching.first = false;  
     break;
    }

   std::pair<bool,int> m = chars[i]->MatchInplace( s, slen, icur );
   if( !m.first )
    {
     matching.first = false;  
     break;
    }

   icur += m.second;
   matching.second += m.second;
  }
 
 return matching;
}


// ***************************************************************
// ���������, ��� ������ s �������� ��� ��������� ����� ��������.
// ***************************************************************
bool RxPattern::MatchBegin( const lem::UCString &s ) const
{
 const int match_len = MatchAsPossible( s.c_str(), s.length(), 0 ).second;
 return match_len==s.length();
}


// ***************************************************************
// ���������, ��� ������ s ��������� �������� ��� �������.
// ***************************************************************
bool RxPattern::Match( const lem::UCString &s ) const
{
 std::pair<bool,int> match_len = MatchAsPossible( s.c_str(), s.length(), 0 );
 return match_len.first && match_len.second==s.length();
}


int RxPattern::MatchInplace( const lem::UFString & s, int i0 ) const
{
 const std::pair<bool,int> match_len = MatchAsPossible( s.c_str(), s.length(), i0 );
 return match_len.first ? match_len.second : 0;
}


wchar_t RxPattern::GetFrontChar(void) const
{
 // 0 - ����������� ������������ ������ ������ (������ � �������������-����������)
 return chars.front()->GetChar();
}

int RxPattern::Length(void) const
{
 return CastSizeToInt(chars.size()) + (has_asterisk ? lem::UCString::max_len : 0);
}


SentenceTokenizer::SentenceTokenizer( const Solarix::Dictionary &dict, int language ) : ilanguage(language)
{}



// ��������� ��� ��������� ������ ������ � ������� i0 � ������ s, ����������
// �� ����� ����� lens.
bool SentenceTokenizer::MatchAllLens( const lem::UFString & s, int i0, lem::MCollect<int> & lens ) const
{
 // ���������� �� ����� ���� ��������� ����.

 int len1 = MatchLen(s,i0);
 if( len1>0 )
  lens.push_back(len1);

 return !lens.empty();
}



#define IsTire(c) ((c)=='-' /*|| (c)==151*/ || (c)==0x2014)


void SentenceTokenizer::Tokenize(
                                 const Solarix::Dictionary &dict,
                                 const lem::UFString &buffer,
                                 lem::MCollect<UCString> &words,
                                 lem::PtrCollect<lem::UFString> &classes,
                                 std::map< int, lem::UFString > & tokenizer_flags,
                                 LA_PreprocessorTrace *trace
                                ) const
{
 // ������� � ��������� ����� �������� ������������� �������������.
 const int l = buffer.length();

 int word_start_pos=0;
 UCString word;
 int i=0;

 while( i<l )
  {
   wchar_t c = buffer[i];

   if( lem::is_uspace(c) ) // ����� ���� ������ ������ UNICODE-������� ���������� ����� � �.�.
    c = L' ';

   #if defined SOL_CAA && !defined SOL_NO_AA
   // �� ������ �� ��� ������� ������...
   if( word.empty() && c!=L' ' && i<(l-1) )
    {
     bool matched=false;
     const int ml = MatchLen( buffer, i );

     if( ml>0 )
      {
       // ����� ���������� � ������ �������.
       matched = true;
 
       word_start_pos=i;

       for( int k=0; k<ml; ++k )
        word += buffer[i++];

       words.push_back(word);
       word.clear();
       continue;
      }
    }  
   #endif

   const bool delimiter = IsTokenDelimiter(c);

   if( delimiter )
    {
     switch(c)
     {
      case L' ':
      case L'\r': 
      case L'\n':
      case L'\t':
       {
        if( !word.empty() )
         {
          if( word.length()==1 && IsTire(word.front()) )
           {
            tokenizer_flags.insert( std::make_pair( CastSizeToInt(words.size()), L"word_separation" ) );
           }

          words.push_back(word);
          word.clear();
         }

        i++;
        while( i<l )
        {
         c = buffer[i];
         // ������� ����������
         if( c==L' ' || c==L'\r' || c==L'\n' )
          i++;
         else
          break;  
        }

        break;
       }

      case L'.':
      case L'!':
      case L'?':
       {
        // ����� - ������ ������
        if( c==L'.' )
         {
          // � ����� �����������?
          bool eol=true;
          UCString dot; dot=c;

          i++;
          while( i<l )
           {
            wchar_t c2 = buffer[i];
            if( lem::is_uspace(c2) )
             c2 = L' ';   
  
            if( c2==L'\r' || c2==L'\n' || c2==L' ' || c2==L'\t' || c2==L'"' )
             break;

            if( c2!=L'.' )
             {
              eol=false;
              break; 
             }
  
            dot += c2;
            i++;
           }
        
          if( eol )
           {
            // ��, ����� � ����� �����������
            if( word.empty() )
             {
              words.push_back(dot);
              break;
             } 
            else
             {
              words.push_back(word);
              words.push_back(dot);
              word.clear();
              break;
             }  
           }  
          else
           {
            if( dot==L"..." )
             {
              if( word.empty() )
               {
                words.push_back(dot);
               } 
              else
               {
                words.push_back(word);
                words.push_back(dot);
                word.clear();
               }  

              break;
             }
           }
 
          // ���, ��� ����� ���� �������� ������ ����� "3.141", ���� ������ ���������� "��.",
          // ���� ������ ���������� "..."
          word += c;
          break;
         }

        if( word.empty() )
         {
          i++;
          word = c;

          // ����� ���� ��������� ???, !!!, ... ��� ���� ����� ?!
          while( i<l )
           {
            wchar_t c2 = buffer[i];
            if( c2==L'.' || c2==L'!' || c2=='?' )
             {
              word+=c2;
              i++;              
             }
            else
             {
              break;
             }  
           }

          words.push_back(word); 
          word.clear();
         }
        else
         {
          words.push_back(word);
          word.clear();
         }
  
        break;
       }

      default:
       {
        if( word.empty() )
         {
          i++;
          word = c;

          if( IsTire(c) )
           {
            tokenizer_flags.insert( std::make_pair( CastSizeToInt(words.size()), L"word_separation" ) );
           }

          words.push_back(word); 
          word.clear();
         }
        else
         {
          words.push_back(word);

          if( IsTire(c) )
           {
            if( word_start_pos+word.length()==i )
             tokenizer_flags.insert( std::make_pair( CastSizeToInt(words.size()), L"word_conjunction" ) );
            else
             tokenizer_flags.insert( std::make_pair( CastSizeToInt(words.size()), L"word_separation" ) );
           }

          i++;
          word = c;
          words.push_back(word); 
          word.clear();
         }

        break;
       }
     }
    }
   else
    {
     if( word.empty() )
      word_start_pos=i;

     word+=c;
     i++;
    }
  }

 // ��������� ����� ������������� ������ ������
 if( !word.empty() )
  words.push_back(word);

 #if defined SOL_CAA
 // �����, ��� ��� � Sentence ��� ���������� Segmentation(...)
// dict.GetLexAuto().Segmentation(words);
 #endif

 {
// for( lem::Container::size_type i=0; i<words.size(); ++i )
//  classes.push_back( new UFString() );
  classes.resize(words.size());
  classes.Nullify();
 }

 return;
}



EuroSentenceTokenizer::EuroSentenceTokenizer( const Solarix::Dictionary &dict, int language )
:SentenceTokenizer(dict,language)
{
 if( language!=UNKNOWN )
  {
   const SG_Language &lang = dict.GetSynGram().languages()[language];
   int ipar = lang.FindParam( L"WordDelimiters" );

   if( ipar!=UNKNOWN )
    {
     for( lem::Container::size_type j=0; j<lang.params[ipar]->values.size(); ++j )
      delimiters += lang.params[ipar]->values[j].c_str();
    }
  }
 else
  {
   delimiters = L" ,.!?:;+-|[{]}<>";
  }

 return;
}


void EuroSentenceTokenizer::AddSimplePattern( const lem::UFString &p, const Solarix::Dictionary &dict )
{
 LEM_CHECKIT_Z( !p.empty() );
 #if LEM_DEBUGGING==1
 int n = unbreakable.size();
 //mout->printf( "AddSimplePattern n=%d text=%us\n", n, p.c_str() );
 #endif
 unbreakable.push_back( new SimplePattern( to_lower(p).c_str() ) );
 return;
}

void EuroSentenceTokenizer::AddRxPattern( const lem::UFString &p, const Solarix::Dictionary &dict )
{
 LEM_CHECKIT_Z( !p.empty() );
 #if LEM_DEBUGGING==1
 int n = unbreakable.size();
 //mout->printf( "AddRxPattern n=%d text=%us\n", n, p.c_str() );
 #endif
 unbreakable.push_back( new RxPattern(p,dict) );
 return;
}



static bool pr1( const EuroSentenceTokenizer::Pattern *a, const EuroSentenceTokenizer::Pattern *b )
{
 return a->Length() > b->Length();
}


void EuroSentenceTokenizer::InitSpecialCases(void)
{
 for( lem::Container::size_type i=0; i<unbreakable.size(); ++i )
  {
   const wchar_t c = unbreakable[i]->GetFrontChar();
   if( c==0 )
    {
     // ���� �� ��������� ��������� ������������ ��������� ������ - �������� �� ������ ������� ������� �����������.
     unbreakable_front.clear();
     break;
    }

   unbreakable_front.insert(c); 
  }

 #if LEM_DEBUGGING==1
// int len1 = unbreakable[36]->Length(); 
 //int len2 = unbreakable[37]->Length(); 
 #endif

 // ����������� �� �������� ����� - ������� ������ ����������� ����� ������� ����������.
 std::sort( unbreakable.begin(), unbreakable.end(), pr1 );

/*
 #if LEM_DEBUGGING==1
 for( lem::Container::size_type i=0; i<unbreakable.size(); ++i )
  {
   mout->printf( "%d %us\n", CastSizeToInt(i), unbreakable[i]->GetText().c_str() );
  }
 #endif
*/

 return;
}


bool EuroSentenceTokenizer::IsUnbreakableFront( const lem::UCString &s ) const
{
 for( lem::Container::size_type i=0; i<unbreakable.size(); ++i )
  if( unbreakable[i]->MatchBegin(s) )
   return true;

 return false;
}


bool EuroSentenceTokenizer::IsMatched( const lem::UCString &s ) const
{
 for( lem::Container::size_type i=0; i<unbreakable.size(); ++i )
  if( unbreakable[i]->Match(s) )
   return true;

 return false;
}

bool EuroSentenceTokenizer::IsTokenDelimiter( wchar_t c ) const
{
 if( delimiters.empty() && (lem::is_udelim(c) || lem::is_uspace(c) || c==L'\r' || c==L'\n' ) || c==151 )
  return true;

 if( !delimiters.empty() && delimiters.find(c)!=0 )
  return true;

 return false;
}

int EuroSentenceTokenizer::MatchLen( const lem::UFString & s, int i0 ) const
{
 int imax=UNKNOWN, lmax=0;

 for( lem::Container::size_type i=0; i<unbreakable.size(); ++i )
  {
   const int l = unbreakable[i]->MatchInplace(s,i0);
   if( l>lmax )
    {
     if( i0+l==s.length() || IsTokenDelimiter( s[i0+l] ) )
      {
       imax = i;
       lmax = l;
      }
    }
  }

 return lmax;
}

