#include <lem/solarix/sentencebroker.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/TextTokenizationRules.h>

using namespace Solarix;


wchar_t TextTokenizationRules::DefaultSpaceChars[] = L" \u00a0\t\r\n";


TextTokenizationRules::TextTokenizationRules( const lem::MCollect<int> & langs, SentenceTokenizer * _tokenizer )
 : id_language(langs), tokenizer(_tokenizer)
{
 LEM_CHECKIT_Z( _tokenizer!=NULL );
 segmentation_flag=Whitespace;
 return;
}



void TextTokenizationRules::AddSpaceCharacters( const wchar_t * whitespace )
{
 int i=0;
 while( 0!=whitespace[i] )
  {
   if( spaces.find(whitespace[i])==UNKNOWN )
    spaces.push_back( whitespace[i] );

   i++;
  }

 AddDelimiterCharacters(whitespace);

 return;
}


void TextTokenizationRules::AddDelimiterCharacters( const wchar_t * delimiter_chars )
{
 int i=0;
 while( 0!=delimiter_chars[i] )
  {
   if( delimiters.find(delimiter_chars[i])==UNKNOWN )
    delimiters.push_back(delimiter_chars[i]);

   i++;
  }

 return;
}




// ���������� ��� ���������� ������� � ������� �������.
// ���������� ������� ������� ��-����������� �������.
int TextTokenizationRules::SkipSpace( const lem::UFString & Text, int pos ) const
{
 while( pos<Text.length() )
 {
  // ���� ������� ������ - ������, �� ���������� ������.
  if( spaces.find(Text[pos])==UNKNOWN )
   break;

  pos++;
 }

 return pos;
}


// ********************************************************************************************
// � ������, ������� ���������� � Text, ���� �������������� �������� ��������� ����.
// ��� �������� ���������� ����� ������ words.
// ��������� ������ - ��������� �� ������ ����, �� ���� ������ ������ ����� �������� ��������.
// ********************************************************************************************
int TextTokenizationRules::Extract(
                                   Solarix::Dictionary & dict,
                                   const lem::UFString &Text,
                                   int CurrentPosition,
                                   lem::MCollect<int> & WordLengths,
                                   bool * is_unbreakable_token
                                  )
{
 WordLengths.clear();

 if( segmentation_flag==Whitespace )
  {
   // ���������� ���������� �������.
   const int NewStartPos = SkipSpace(Text,CurrentPosition);

   if( NewStartPos<Text.length() )
    {

/*
     *is_unbreakable_token=false;
     int WordLen=0, Pos=NewStartPos;
     if( delimiters.find(Text[Pos])!=UNKNOWN )
      {
       WordLen=1;
      }
     else
      {
       while( Pos<Text.length() )
       {
        wchar_t c = Text[Pos];
        if( delimiters.find(c)!=UNKNOWN )
         break;

        WordLen++;
        Pos++;
       }
      }

     if( NewStartPos+WordLen+1 < Text.length() )
      {
       // ��������� ������� ������, ������� � NewStartPos ������ WordLen+1, �������� ������� ������������ ������?
       lem::UCString probe( Text.c_str()+NewStartPos, Text.c_str()+NewStartPos+WordLen+1 );
       probe.to_upper();

       #if defined LEM_THREADS
       lem::Process::RWU_ReaderGuard rlock(cs_unbreakable_begginnings);
       #endif
       std::set<lem::UCString>::const_iterator it = not_unbreakable_begginnings.find(probe);
       if( it==not_unbreakable_begginnings.end() )
        {
         #if defined LEM_THREADS
         lem::Process::RWU_WriterGuard wlock(rlock);
         #endif

         // ��� ������������ ���� ������� ������ �������� �� ��������� � ���, �� ��� ��� ����������� � ��� ������ �������
         // �������� ������, �� �� ����� ����� ������.

         if( tokenizer->IsUnbreakableFront( probe ) )
          {
           if( tokenizer->MatchAllLens( Text, NewStartPos, WordLengths ) )
            {
             *is_unbreakable_token=true;
            }
          }
         else
          {
           not_unbreakable_begginnings.insert(probe);
          }
        }
      }
     else if( NewStartPos+WordLen == Text.length()-1 )
      {
       // ����������� ����� � ������-����������� ����� ���� �������� ���������� � ������.
       lem::UCString probe( Text.c_str()+NewStartPos, Text.c_str()+NewStartPos+WordLen+1 );

       #if defined LEM_THREADS
       lem::Process::RWU_ReaderGuard rlock(cs_not_unbreakable);
       #endif
       std::set<lem::UCString>::const_iterator it = not_unbreakable.find(probe);
       if( it==not_unbreakable.end() )
        {
         #if defined LEM_THREADS
         lem::Process::RWU_WriterGuard wlock(rlock);
         #endif

         // ��� ������������ ���� ������� ������ �������� �� ��������� � not_unbreakable, �� ��� ��� ����������� � ��� ������ �������
         // �������� ������, �� �� ����� ����� ������.
         if( tokenizer->IsMatched( probe ) )
          {
           // ����������� ����� � ����������� ����� ���� �������� ����������� ���������!
           *is_unbreakable_token=true;
           WordLengths.push_back( WordLen+1 );
          }
         else
          {
           not_unbreakable.insert( probe );
          }
        }
      }

     if( !*is_unbreakable_token )
      WordLengths.push_back(WordLen);
*/

     if( tokenizer->MatchAllLens( Text, NewStartPos, WordLengths ) )
      {
       *is_unbreakable_token=true;
      }
     else
      {
       // ����������� ������� �� ����������, ������� ������� �� ������ ������� �������� �� ������� ��� �� �����������.
       *is_unbreakable_token=false;
       int WordLen=0, Pos=NewStartPos;
       if( delimiters.find(Text[Pos])!=UNKNOWN )
        {
         WordLen=1;
        }
       else
        {
         while( Pos<Text.length() )
         {
          wchar_t c = Text[Pos];
          if( delimiters.find(c)!=UNKNOWN )
           break;

          WordLen++;
          Pos++;
         }
        }

       WordLengths.push_back(WordLen);
      }
    }

   return NewStartPos;
  }
 else if( segmentation_flag==Streaming )
  {
   if( CurrentPosition < Text.length() )
    {
     // ��� ������ ���� ���������� - ����� ������������ ���, ������ �����
     // ���� ������������ ���������� � ���, ����� �������� ������� (������������ PrefixEntrySearcher::IsValidPrefix)
     // � ����� ������� ���� � ����� (IsWordForm).
     // ���������� ����� ���������� ���� �� ��� ���, ���� ��� �������� ��������� ����������, � ���������
     // ����� ��� ���������, ������� �������� ���������� ���������.
  

     // ������������ ����� ��������� ��������.  
     const int max_prefix_len = prefix_lookup->FindMaxPrefixLen( Text.c_str()+CurrentPosition );

     // ������ ����� ������ ������� ������ ����� ������ �� ������������� ��������.
   
     Solarix::Lexem prefix;
 
     for( int prefix_len=1; prefix_len<=max_prefix_len; ++prefix_len )
     {
      prefix += Text[CurrentPosition+prefix_len-1];
      
      // ��� ��������� �������?
      if( dict.GetSynGram().IsWordForm(prefix) )
       {
        // �� - ��������� ����� � ������ ��������� ����.
        WordLengths.push_back( prefix_len );
       }
     }
    }

   return CurrentPosition;
  }

 return UNKNOWN;
}



// ������������ ��� ������ ������������.
// � ��������� ������� �������� �������� NumberToExtract ���� � ���������� �� ������ ����� extracted.
void TextTokenizationRules::ExtractNextWords(
                                             Solarix::Dictionary & dict,
                                             const lem::UFString & Text,
                                             int CurrentPosition,
                                             int NumberToExtract,
                                             lem::MCollect<TextTokenizationItem> & extracted
                                            ) const
{
 extracted.clear();

 int Pos=CurrentPosition;
 while( CastSizeToInt(extracted.size()) < NumberToExtract && Pos<Text.length() )
 {
  Pos = SkipSpace(Text,Pos);
  int NewStartPos=Pos;
  
  int WordLen=0;
  if( delimiters.find(Text[Pos])!=UNKNOWN )
   {
    WordLen=1;
    Pos++;
   }
  else
   {
    while( Pos<Text.length() )
    {
     wchar_t c = Text[Pos];
     if( delimiters.find(c)!=UNKNOWN )
      break;

     WordLen++;
     Pos++;
    }
   }

  if( WordLen>0 )
   {
    TextTokenizationItem w;
    w.len = WordLen;
    w.start_pos = NewStartPos;
    w.word = lem::mid(Text,NewStartPos,WordLen).c_str();
    extracted.push_back(w);
   }
 }

 return;
}

