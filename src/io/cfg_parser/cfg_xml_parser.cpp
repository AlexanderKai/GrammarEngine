// -------------------------------------------------------------------------
// File CFG_XML_PARSER.CPP
//
// (c) by Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ������ � ����������������� ������� � ������� XML-�������.
// ------------------------------------------------------------------------
//
// CD->21.07.1995
// LC->13.08.2006
// --------------

#include <lem/cfg_parser.h>
#include <lem/cfg_parser.h>

using namespace std;
using namespace lem;
using namespace lem::Cfg_Parser;

Xml_Parser::Xml_Parser(void)
:Base_ProFile< SectionEntry< Xml_Entry<char,Text_Parser> > >()
{
 return;
}

// **************************************************
// �������������� ������ ������ �� �������� �����.
//
//  ����� ��� ������ �����:
//
//   <aaa>
//
//    <bbb>
//       ...
//    </bbb>
//
//   </aaa>
//
// **************************************************
void Xml_Parser::ReadDirectory(void)
{
 Read_Head();

 AToken word;
 section_type *inprocess=new section_type; // ������� ����������������.
 section_type *last=NULL;                  // ����. �� ����� ������.
 section_type *supr=tree.first;           // �������� ��� �������.

 int CurLevel=0;                     // ������� ������� �����������.

 tree.Clear();
 tree.Set_First(inprocess);
 seekp(beginning);

 tree.current->location = tellp();

 FOREVER
  {
   word=read();

   if( word.string().empty() || eof() )
    break;

   if( word.string()=='<' )
    {
     // ����������� ����� ������.
     string secname=read().string().c_str();

     if( word.string()=='/' )
      {
       string end_node = read().string().c_str();

       if( end_node != inprocess->name )
        throw ECheckFault( to_wstr("Invalid XML file: mismatched nodes") );

       // ������� ������� ��������. �������� � ������������ ����������� ������.

       read_it( ">" );

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

       continue;
      }

     // ��������� ��� ������.
     FOREVER
      {
       word=read();

       if( word.string()=='>' || eof() || !word.string().length() )
        break;

       secname += string(" ")+word.string().c_str();
      }

     inprocess->name     = secname;
     inprocess->location = tellp();
     inprocess->level    = CurLevel;
     inprocess->prev     = last;
     inprocess->supr    = supr;

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

     // ���� ������ ������.

     last = inprocess;
     inprocess=new section_type;

     while( !eof() && !word.string().empty() )
      {
       word = read();

       if( word.string() == '<' )
        {
         seekp( word.GetBegin() );
         break;
        }
      }

     continue;
    }

  } // end while

 if(inprocess->name.empty())
  lem_rub_off(inprocess);

 tree.To_Start();
 return;
}



/****************************************************************************
 ������ ��������� ������� �� ������� ��������� ������. ����������� ���������
 �������� ��������. ����� ������� ��������� ������ ���������, ��������
 ���������� ������ ������. ���� ���������� ��������� ������, �� ����������
 ��� � �����. ������ ����.
****************************************************************************/
const string Xml_Parser::NextFromSection(void)
{
 AToken word;

 if(bracket_level<0 )
  return word.string().c_str();

 word = read();

 if( word.string()=='<' )
  {
   // ������ ����� ������ - ��� ��� ��������� ������ ���������, ��
   // ������ ����� ��������� ������� � ������ �� �������.
   seekp( word.GetBegin() );
   return "";
  }

 return word.string().c_str();
}

void Xml_Parser::Read_Head(void)
{
 // ��������� ������ ����������� ���:
 // <?xml version="1.0"?>
 read_it( "<" );

 read_it( "?" );

 head_section.Read(*this);

 read_it( ">" );
 return;
}

// ---------------------- End Of File [CFG_XML_PARSER.CPP] ---------------------
