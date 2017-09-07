// -------------------------------------------------------------------------
// File CFG_INI_PARSER.CPP
//
// (c) by Koziev Elijah
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Content:
// ������ � ini-�������.
//
// 24.02.2006 - ��������� ������ � ini-���� ������ �������� ���������
//              ����������� ����� WinAPI ������� (� ������ ���������� ����
//              ���� �������)
//
// 12.05.2007 - ���������� ������ ������ ��� �������� ini-������ � ��������
// ------------------------------------------------------------------------
//
// CD->21.07.1995
// LC->07.09.2017
// --------------

#include <lem/path.h>
#include <lem/cfg_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Cfg_Parser;



SectionEntry::SectionEntry(void)
{
 next=prev=sub=supr=NULL;
 level=0;
 return;
}

SectionEntry::SectionEntry(
                           const std::string &Name,
                           const pos_type& Loc,
                           int Lev
                          ) : name(Name), location(Loc)
    {
     next=prev=sub=supr=NULL;
     level=Lev;
     return;
    }

SectionEntry::SectionEntry( const SectionEntry &se )
    : name(se.name), location(se.location)
    {
     next=se.next;
     prev=se.prev;
     sub=se.sub;
     supr=se.supr;
     level=se.level;
     return;
    }


SectionEntry::~SectionEntry(void)
{
 del();
 if( supr )
  supr->sub = NULL;

 return;   
}


SectionEntry& SectionEntry::operator=( const SectionEntry& se )
    {
     if( this!=&se )
      {
       name=se.name;
       location=se.location;

       next = se.next;
       prev = se.prev;
       sub  = se.sub;
       supr= se.supr;
       level=se.level;
      }

     return *this;
    }

void SectionEntry::del(void)
{
 SectionEntry *e=sub;
 SectionEntry *tmp=NULL;

 while(e)
  {
   tmp=e->next;
   e->del();
   delete e;
   e=tmp;
  }

 sub=NULL;
 return;
}


// ***********************************************


SectionTree::SectionTree(void)
{
 first=new RootEntry(this);
 current=first;
}

SectionTree::~SectionTree(void)
{
 first->del();
 lem_rub_off(first);
 current=NULL;
}

bool SectionTree::Next(void)
    {
     if( current && current->next )
      {
       current=current->next;
       return true;
      }

     return false;
    }

    bool SectionTree::Prev(void)
    {
     if( current && current->prev )
      {
       current=current->prev;
       return true;
      }

     return false;
    }


    bool SectionTree::Up(void)
    {
     if( current && current->supr )
      {
       current=current->supr;
       return true;
      }

     return false;
    }

    bool SectionTree::Down(void)
    {
     if( current && current->sub )
      {
       current=current->sub;
       return true;
      }

     return false;
    }

    // ------------------------------------------------------------------
    // ������������ � �������, ����������� ������ ������ loc, �� ��������
    // ���������. ���� ����� �����������, ������ false. � ������ ��������
    // �������� ������ true.
    // ------------------------------------------------------------------
    bool SectionTree::Move_To( const string &loc )
    {
     if(loc==":")
      {
       // ������������ � ����� ������.
       To_Start();
       return !!current;
      }

     if(!current)
      return false;

     if(loc[0]=='.')
      {
       // ������������ �� ����������������� �����
       // ������� �����.

       int i=0;
       while( loc[i] && loc[i++]=='.' )
        if(current->supr)
         current = current->supr;
        else
         return false;

       return true;
      }

     // �������, ��� ��� ���������� ��������� ��� �������� ������.
     if(current->sub)
      {
       // � ������� ������ ���� ���������.
       current = current->sub;

       // ������� �� ������� � ������� ��������� ���.
       while( current && current->name!=loc )
        current=current->next;

       if(current)
        return true;
       else
        return false;
      }

     return true;
    }

    // *******************************
    // ������ � �������� ���������.
    // *******************************
    void SectionTree::Clear(void)
    {
     if(first) first->del();
     first->sub=NULL;
     current=first;
     return;
    }

// ***********************************************


Ini_Parser::Ini_Parser(void):Text_Parser()
{
 bracket_level=0;
 status=0;

 SetFlag( SRC_STRIP_STRING, false );
 use_curled_brackets = false;

 return;
}


void Ini_Parser::Open( const lem::Path &filepath )
{
 lem::BinaryFile *ini_file = new lem::BinaryReader(filepath);
 lem::StreamPtr ini_file_x(ini_file);
 
 lem::Char_Stream::WideStream *reader=NULL;
 
 if( lem::UI::get_UI().GetSessionCp().IsSingleByte() )
  reader = new lem::Char_Stream::Char_Reader(ini_file_x);
 else
  reader = new lem::Char_Stream::UTF8_Reader(ini_file_x);

 lem::Char_Stream::WideStreamPtr reader_x( reader );

 Open( reader_x );
 return;
}


void Ini_Parser::Open( lem::Ptr<lem::Char_Stream::WideStream> txt )
{
 bracket_level=0;
 Text_Parser::Open(txt);
 beginning=tellp();
 status=0;
 
 ReadDirectory();
 stream = txt;

 return;
}

    /******************************************************************************
     ��������� ������� ������ �� ����� � ������ ����������������� ������.
     tosection - ���� � ������.

     ���� ������������ ���������� ����, ��� ��� �������� � �������� �������.
     ����� ��������� ������ ������������� ����� '\\', ������� ������ ������������
     '.', �������� ��� ������� '..', � �.�. ��� �������� �� ����� ������ �������
     ������������ ������ ':'

     �� ���������, ���� ���� � ������ �� ���������� � '.' ��� '..', ������
     �������������� ��������������� �� �������� ������ ':', ��� ��� ����
     ':\section1' � 'section1' �������� � ������ ����������.
    *****************************************************************************/
bool Ini_Parser::seek_section( const string& tosection )
    {
     bracket_level=0;
     string *list=NULL;
     int nstr=ParseSectionPath(tosection,&list);
     bool stat=false;

     if( nstr && (list[0]!="." && list[0]!="..") )
      // �� ��������� ��������������� � �������� ������.
      tree.To_Start();

     // ������ �������� ����������� �� ������ ���������.
     for( int i=0; i<nstr; i++ )
      {
       stat = tree.Move_To(list[i]);
       if(!stat)
        break;
      }

     if(nstr)
      lem_rub_off_array(list);

     if(stat)
      seekp( tree.current->location );

     return stat;
    }

    /*************************************************************************
     ������� � ������ �������� ���������� � ������ name � ������,
     ����������������� ����� path. ���� ������ path ������, �� ������������
     ������� ������.
     �������� def ���������� ������������ ��������, ���� ��������� ��������
     ������������� ���������� �� �������.
    *************************************************************************/
    int Ini_Parser::get_int(
                const string &path,
                const string &name,
                int def
               )
    {
     int res=def;

     SectionEntry *back=tree.current;

     if(path.length())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     // ���� ��� "-", �� ��������� �����, ������ ������.
     if(val=="-")
      val += NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!lem::to_int(val.c_str(),&res))
      return def;

     return res;
    }

    bool Ini_Parser::get_bool(
                  const string &path,
                  const string &name,
                  bool def
                 )
    {
     bool res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!to_bool(val.c_str(),&res))
      return def;

     return res;
    }

    #if !defined LEM_NOREAL
    double Ini_Parser::get_real(
                                         const string &path,
                                         const string &name,
                                         double def
                                        )
    {
     double res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      if(!seek_section(path))
       {
        seekp(back->location);
        tree.current=back;
        return res;
       }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

     string val=NextFromSection();

     // ���� ��� "-", �� ��������� �����, ������ ������.
     if(val=="-")
      val += NextFromSection();

     seekp(back->location);
     tree.current=back;

     if(!to_real(val.c_str(),&res))
      return def;

     return res;
    }
    #endif


    /*****************************************************************************
     ������� � ��������� ������� ��� ��������� ������ � ������ name,
     ����������� �� ������ path. ���� ���� ����� ������ �������, �� ������������
     ������� ������.

     ���� ����� ���������� �� �������, ������������ �������� ������ def.
    *****************************************************************************/
    const string Ini_Parser::get_string(
                                        const string &path,
                                        const string &name,
                                        const string &def
                                       )
    {
     string res=def;

     SectionEntry *back=tree.current;

     if(!path.empty())
      {
       if(!seek_section(path))
        {
         seekp(back->location);
         tree.current=back;
         return res;
        }
      }

     if(!seek_variable(name))
      {
       seekp(back->location);
       tree.current=back;
       return res;
      }

//     res=NextFromSection();

     FString s = Text_Parser::read_fstring();
     s.strip_quotes();
     res = s.c_str();

     seekp(back->location);
     tree.current=back;
     return res;
    }


    // ***************************************************************************
    // ���������� ��������� ������ � ����� �� ������� ����� ����� ����������,
    // �� ���� ����� ������� '=', ���� ��� �������. � ��������� ������ ���������
    // ��������� ������ � ����� ��������������.
    // ***************************************************************************
    bool Ini_Parser::seek_variable( const string& name )
    {
     string word = GetNextVar();

     while( !word.empty() && word!=name ) word=GetNextVar();

     if(word.empty())
      return false;

     return true;
    }

    // ***************************************************************************
    // ���������� ��� ��������� ���������� � ������� ������. ���� ������
    // �����������, ���������� ������ ������.
    // ***************************************************************************
    const string Ini_Parser::GetNextVar(void)
    {
     // ���� ������ =.

     string first=NextFromSection();
     string second=NextFromSection();
     string var;

     while(!second.empty())
      {
       while( second!="=" && !second.empty() )
        {
         first=second;
         second=NextFromSection();
        }

       if(second.empty())
        {
         // ��������� ���������� �������� �� �������.
         return var;
        }

       // ������ ������� first ���������� (��������) ���
       // ��������� ����������.
       if(is_correct_var_name(second))
        {
         var=first;
         break;
        }

       first=second;
       second=NextFromSection();
      }

     return var;
    }

    // ***************************************************************************
    // ����������, ����� �� ������� var ���� ������ ����������.
    // ***************************************************************************
    bool Ini_Parser::is_correct_var_name( const string& var )
    {
     int l=var.length();

     for( int i=0; i<l; i++ )
      {
       if(!isalpha(var[i]))
        if(!strrchr( "_$@#", var[i] ))
         {
          // ��� ���������� �� ����� ���������� � �����.
          if( !i && isdigit(var[i]) )
           return false;

          // � ��������� �������� ����� ������������ ��������.
          if( i && !isdigit(var[i]) )
           return false;
         }
      }

     return true;
    }



// **************************************************
// �������������� ������ ������ �� �������� �����.
// **************************************************
void Ini_Parser::ReadDirectory(void)
{
 AToken word;

 section_type *inprocess=new section_type; // ������� ����������������.
 bool del_inprocess=false;
 section_type *last=NULL;             // ����. �� ����� ������.
 section_type *supr=tree.first;      // �������� ��� �������.


 int CurLevel=0;                     // ������� ������� �����������.
 int subbrackets=0;                  // ����� �������� �������� ��������,
                                     // �� ������� ��������� � ���������
                                     // ��������.

 tree.Clear();
 tree.Set_First(inprocess);
 seekp(beginning);

 tree.current->location = tellp();

 FOREVER
  {
   word=read();

   if( word.string().empty() || eof() )
    break;

   if( word.string()=='[' )
    {
     // ����������� ����� ������.

     string secname=read().string().c_str();

     // ��������� ��� ������.
     FOREVER
      {
       word=read();

       if( word.string()==']' || eof() || !word.string().length() )
        break;

       secname += string(" ")+word.string().c_str();
      }

     del_inprocess=false;
     inprocess->name     = secname;
     inprocess->location = tellp();
     inprocess->level    = CurLevel;
     inprocess->prev     = last;
     inprocess->supr     = supr;

     if(last)
      {
       // ���������� ��������� �� ����.
       last->next = inprocess;
       last=inprocess; // ������ �� ����� ����������.
      }

     if(supr)
      if(!supr->sub)
       {
        // �������� ��������� �� ���� ������ ���������.
        supr->sub=inprocess;
       }

     // �� ����������� ������ ����� ���� ����������� �������� - ������ ���� ������.
     word=read();

     if( use_curled_brackets && word.string()=='{' )
      {
       // ����������� ����� ����������.
       CurLevel++; // ������ !!!

       // ������� �������������� ������ ����������
       // ��������.
       supr = inprocess;

       // �������� ������� ������� �� ���� ���������.
       last=NULL; // ������ � �������.

       inprocess = new section_type;

       inprocess->level=CurLevel;
       inprocess->supr=supr;
       del_inprocess=false;
      }
     else if( use_curled_brackets && word.string()!='{' )
      {
       throw ECheckFault( to_wstr("Missing '{' after section head\n").c_str() );
      }
     else
      {
       // ���� ������ ������ ��� �������� �������� - ����� ����������
       // ������ ������� ����� ������ (������� '[').
//       use_curled_brackets = false;

       last = inprocess;
       inprocess=new section_type;
       del_inprocess=true;

       while( !eof() && !word.string().empty() )
        {
         word = read();

         if( word.string() == '[' )
          {
           seekp( word.GetBegin() );
           break;
          }
        }
      }

     continue;
    }

   if( use_curled_brackets && word.string()=='{' )
    {
     // �������� �������� ��������� ����, �� ������� ��������� � ���������
     // ������. ���������������� ��������� ����� ���� ������������ �����������
     // ��� ������ ���-������ �� ����� ��������.
     subbrackets++;
     continue;
    }

   if( use_curled_brackets && word.string()=='}' )
    {
     if(subbrackets)
      {
       subbrackets--;
       continue;
      }

     // ������� ������� ��������. �������� � ������������ ����������� ������.

     // �������� ������ ��� ������������ ������.
     section_type *s1 = inprocess->supr;

     CurLevel--; //s1->level;

     // ��������� ��������� ������, ������������
     // �� ����� ������� ������.
     last = s1;
     while(last->next) last=last->next;

     // �������� ��� ����� ������ ��������.
     supr = s1->supr;

     inprocess->supr=supr;
     del_inprocess=false;

     continue;
    }
  } // end while

 if( del_inprocess )
  lem_rub_off(inprocess);

 tree.To_Start();
 return;
}


/*******************************************************************
 ��������� ��������� ��� ���������� ����������� ���� ���������� �
 ��������. ����� ��������� ������ � ���� ����������, ���� ������
 ����� ��������������. � ���� ������ ������������� ������� �������
 ���������� - ����������� ��������� ����, ���������� ����� ������.
********************************************************************/
bool Ini_Parser::write_to_config(
                                 const char *section_name,
                                 const char *var_name,
                                 const char *new_value
                                )
{
 #if defined LEM_WINDOWS
 stream->close();
 return WritePrivateProfileStringA(
                                   section_name,
                                   var_name,
                                   new_value,
                                   GetName().GetAscii().c_str()
                                  )==TRUE;
 #else

 // ...

 #endif

/*
 // �������� ��� ��������.
 const lem::Path filename=GetName();

 // ��� ���������� �����.
 const FString tmp_file_name = get_tmp_name();

 bool print_in_var_name     = false;
 bool print_in_section_name = false;

 if( !seek_section(section_name) )
  {
   // ���� ������ � ��������� ������ �� ����������! �������� � �����.
   print_in_section_name = true;
   print_in_var_name     = true;

   // ������������ � ����� �����, ��� � ����� ��������� ����� ������...
   SourceState back=tellp();

   while( !eof() )
    back=read(false).GetBegin();

   seekp(back);
  }
 else
  {
   // �� ������� ����, ����� ������ ����.
   if( !seek_variable( var_name ) )
    {
     // ������ ����������, �� ����� ���������� � ��� ���. �������
     // �������� ���� ������������� ��������� ��� ����������. ���������
     // ������� �������� ������������� - � ������ ���� ������.
     seek_section(section_name);
     print_in_var_name = true;
    }
  }

 // ������ ���� ������� ���� profile, ������� ��� ��� ������, ����������
 // ����, ������� ���� ��� ������ � ����� ������� ��� ���� ������.
 const SourceState field_pos=tellp();

 int ne=0;
 if( !print_in_var_name )
  {
   // ����������, ������� ����� �� ������� ����� ������. ��� ������� ����������
   // �������� ����������.
   while( !eof() )
    {
     char c = get();
     if( c==L'\n' || c==L'\r' )
      break;

     ne++;
    }
  }

 // ��������� ������� ����� ��� ��������, ����� �� �� ���� ��� ������� ���
 // ������ ���.
 close();

 BinaryFile bin_old( filename, true,  false );

 lem::Path tmp(tmp_file_name);
 BinaryFile bin_new( tmp, false, true );

 // ��������� � ����� ����� ������ �� ������ �������� �� �����: ������
 // ���� �������� ����������, ���: ������ ���� ������, ���: ����� �����.
 char *buffer;
 const long s = field_pos.GetPos()+1;

 #if defined LEM_16
 // ����������� �� memory chunk because of 16-������� ��������!
 if(s>=LEM_MAX_MEM_SIZE)
  LEM_STOPIT;
 #endif

 buffer = new char[(size_t)s];
 bin_old.read(  buffer, (size_t)field_pos.GetPos() );
 bin_new.write( buffer, (size_t)field_pos.GetPos() );
 delete[] buffer;
 buffer = NULL;

 // ����� ��������� ��������� ������?
 if( print_in_section_name )
  {
   bin_new.write( "\r\n\r\n[", 5 );

   // ���� ��������� ���� � ������ �� ���������� � ������� ���������
   // ��������� - ���������� ��� ������.
   string *path=NULL;
   int nsec = ParseSectionPath( section_name, &path );
   bin_new.write( path->c_str(), path->length() );

   if( use_curled_brackets )
    bin_new.write( "]\r\n{\r\n", 6 );
   else
    bin_new.write( "]\r\n", 3 );

   delete[] path;
  }

 // ����� �� ��������� ��� ����������?
 if( print_in_var_name )
  {
   if( !print_in_section_name )
    bin_new.write( "\r\n", 2 );

   bin_new.write( " ", 1 );
   bin_new.write( var_name, lem_strlen(var_name) );
   bin_new.write( " = ", 3 );
  }

 // ����� �������� ����� �������� ����...
 bin_new.write( new_value, lem_strlen(new_value) );

 // ���� ����������� ����� ����������, �� ���������� �������� ������� ������.
 if( print_in_var_name && !print_in_section_name )
  bin_new.write( "\r\n", 2 );

 // � ���� ���� ������� ����� ������, �� ������� ��������� ������� � ����.
 if( print_in_section_name )
  {
   if( use_curled_brackets )
    bin_new.write( "\r\n}\r\n", 5 );
   else
    bin_new.write( "\r\n\r\n", 4 );
  }

 // ������ ����� �������� ������� ������� ��������. ���������� ��������
 // ����������, ���� ������� ����...
 bin_old.seekp( field_pos.GetPos()+ne );
 while( !bin_old.eof() )
  {
   const int ch=bin_old.get();
   if( ch==EOF )
    break;

   bin_new.write( &ch, 1 );
  }

 // ������ ����� ���������� �������� ��������� �� ��������� �����.
 // ���������� ����� bin_new ������������ � bin_old.
 bin_old.close();
 bin_new.close();

 lem::Path::Copy_File( lem::Path(tmp_file_name), filename );

 // ������� ��������� ����.
 lem::Path(tmp_file_name).Do_Remove();

 // ����������� ������� �� ����� ���� � ���������� ������.
 BinaryFile fil( filename, true, false );
 lem::Char_Stream::WideStream *reader = lem::Char_Stream::WideStream::get_Suitable_Reader( lem::Ptr<Stream>(&fil,null_deleter()) );
 Text_Parser::Open( lem::Ptr<Char_Stream::WideStream>(reader) );
 ReadDirectory();

 // �� ������� ���������.
 return true;
*/

 return true;
}


/****************************************************************************
 ������ ��������� ������� �� ������� ��������� ������. ����������� ���������
 �������� ��������. ����� ������� ��������� ������ ���������, ��������
 ���������� ������ ������. ���� ���������� ��������� ������, �� ����������
 ��� � �����. ������ ����.
****************************************************************************/
const string Ini_Parser::NextFromSection(void)
{
 AToken word;

 if(bracket_level<0 )
  return word.string().c_str();

 word = read();

 if( !use_curled_brackets && word.string()=='[' )
  {
   // ������ ����� ������ - ��� ��� ��������� ������ ���������, ��
   // ������ ����� ��������� ������� � ������ �� �������.
   seekp( word.GetBegin() );
   return "";
  }

 while(word.string()=='[')
  {
   // �� ��! ��������� �� ��������� ������.
   // �� ���� ������.
   while( word.string()!=']' && !eof() ) word=read();

   // ������ ������ ���, ��� � �������� ���������...

   word=read(); // �� ��� ��� ��� �� "{"...

   int brackets=1;

   if( word.string()!='{' )
    throw ECheckFault( to_wstr("Missing '{' after section head\n").c_str() );

   while( brackets && !eof() )
    {
     word=read();
     if(word.string()=='{')
      brackets++;
     else
      if(word.string()=='}')
       brackets--;
    }

   // ��������, ��� ��� ���� ������...
   word=read();
  } // end while

 if( word.string()=='{' )
  bracket_level++;

 if( word.string()=='}' )
  bracket_level--;

 if(bracket_level<0)
  word=AToken();


 if( word.string().front()=='"' )
  {
   seekp( word.GetBegin() );
   FString whole_str = read_fstring();
   whole_str.strip_quotes();
   return whole_str.c_str();
  }

 return word.string().c_str();
}

