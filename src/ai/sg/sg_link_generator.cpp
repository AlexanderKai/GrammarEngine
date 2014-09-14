// -----------------------------------------------------------------------------
// File SG_LINK_GENERATOR.CPP
//
// (c) by Elijah Koziev www.solarix.ru
//
// -----------------------------------------------------------------------------
//
// CD->20.05.2006
// LC->19.11.2010
// --------------

#if defined SOL_LOADTXT && defined SOL_COMPILER
 
#include <lem/solarix/tokens.h>
#include <lem/solarix/sg_autom.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/ThesaurusStorage.h>
#include <lem/solarix/WordLinkEnumerator.h>
#include <lem/solarix/WordEntry.h>
#include <lem/solarix/Thesaurus.h>

using namespace std;
using namespace lem;
using namespace Solarix;

Link_Generator::Link_Generator(void)
{
 iclass0=iclass1=UNKNOWN;
}


void Link_Generator::LoadTxt(
                             Macro_Parser &txtfile,
                             SynGram &sg,
                             const Binarization_Options &options
                            )
{
 if( txtfile.probe(B_OFIGPAREN) )
  {
   multitier = true;

   // ������ �������
   BethToken c0 = txtfile.read();
   txtfile.read_it( B_COLON );
   Aname = txtfile.read();

   direct_link.LoadTxt(txtfile,sg);

   BethToken c1 = txtfile.read();
   txtfile.read_it( B_COLON );
   Bname = txtfile.read();

   // ������ �������
   BethToken c2 = txtfile.read();
   txtfile.read_it( B_COLON );
   Cname = txtfile.read();

   link2.LoadTxt(txtfile,sg);

   BethToken c3 = txtfile.read();
   txtfile.read_it( B_COLON );
   Dname = txtfile.read();
  
   txtfile.read_it( B_CFIGPAREN );

   // ���������

   txtfile.read_it( B_ARROW_R );

   Xname = txtfile.read();
   reverse_link.LoadTxt(txtfile,sg);
   Yname = txtfile.read();


   iclass0 = sg.FindClass( c0 );
   iclass1 = sg.FindClass( c1 );
   iclass20 = sg.FindClass( c2 );
   iclass21 = sg.FindClass( c3 );

   if( iclass0==UNKNOWN )
    {
     lem::Iridium::Print_Error( c0, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c0.c_str() );
     throw E_ParserError();
    }

   if( iclass1==UNKNOWN )
    {
     lem::Iridium::Print_Error( c1, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c1.c_str() );
     throw E_ParserError();
    }
   
   if( iclass20==UNKNOWN )
    {
     lem::Iridium::Print_Error( c2, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c2.c_str() );
     throw E_ParserError();
    }

   if( iclass21==UNKNOWN )
    {
     lem::Iridium::Print_Error( c3, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c3.c_str() );
     throw E_ParserError();
    }
  }
 else
  {
   // ������:
   //        �����0 <������_������> �����1  ->  <��������_������>

   BethToken c0 = txtfile.read();
   direct_link.LoadTxt(txtfile,sg);
   BethToken c1 = txtfile.read();
   txtfile.read_it( B_ARROW_R );
   reverse_link.LoadTxt(txtfile,sg);

   iclass0 = sg.FindClass( c0 );
   iclass1 = sg.FindClass( c1 );

   if( iclass0==UNKNOWN )
    {
     lem::Iridium::Print_Error( c0, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c0.c_str() );
     throw E_ParserError();
    }

   if( iclass1==UNKNOWN )
    {
     lem::Iridium::Print_Error( c1, txtfile );
     sg.GetIO().merr().printf( "Unknown class [%us]\n", c1.c_str() );
     throw E_ParserError();
    }
  }

 return;
}


// ***************************************************************
// ���� ��������� ������ ������ �������� ��� �������, �� ���� 
// ������������ �������� ������
// ***************************************************************
bool Link_Generator::Match(
                           int iClass0,
                           const Tree_Link &l,
                           int iClass1
                          ) const
{
 if( iclass0!=iClass0 ||
     iclass1!=iClass1 ||
     l != direct_link
   )
  return false;

 return true;
}



// **************************************************************************
// ��� ������������� ���������� � 2�� ��������� � ����� ����� - ���������
// ������ � ���������� ������-����������.
// **************************************************************************
bool Link_Generator::Match2(
                            SynGram &sg,
                            int ek0,
                            const Tree_Link &l,
                            int ek1,
                            lem::MCollect< lem::foursome<int,int,int,int> > &generated
                           ) const
{
 if( lem::is_quantor(ek0) || lem::is_quantor(ek1) )
  return false;

 if( l!=direct_link )
  return false;

 bool ret=false;

 const SG_Entry &e0 = sg.GetEntry(ek0);
 const SG_Entry &e1 = sg.GetEntry(ek1);

 if( e0.GetClass()==iclass0 && e1.GetClass()==iclass1 )
  {
   // ������ ������� �������.
   
   lem::MCollect<UCString> vars;
   lem::MCollect<int> values;

   vars.push_back( Aname ); 
   values.push_back( ek0 );

   vars.push_back( Bname ); 
   values.push_back( ek1 );

   // ������ ���� ����� ��� �����, ��������������� ������� �������.
   SG_Net &net = sg.Get_Net();

   if( Cname==Aname )
    {
     // ���������� �� A==B
     // ���� ����� ��� �������� ��� D.
          
     // ���� ��������� �� A ����� ��������� ������ �������� ����
     lem::Ptr<WordLinkEnumerator> rs( sg.Get_Net().EnumerateWordLinks(ek0, link2.GetState()) );

     while( rs->Fetch() )
      {
       const int ekey2 = rs->GetEntryKey2();
       const int link_type = rs->GetLinkType();
       const int itags = rs->GetTagsId(); 

       vars.push_back(Dname);
       values.push_back(ekey2);

       // ������� ������-���������.
       int res_ek0=UNKNOWN, res_ek1=UNKNOWN;

       int iX = vars.find(Xname);
       if( iX==UNKNOWN )
        {
         LEM_STOPIT;
        }

       res_ek0 = values[iX]; 

       int iY = vars.find(Yname);
       if( iY==UNKNOWN )
        {
         LEM_STOPIT;
        }

       res_ek1 = values[iY];

       lem::foursome<int,int,int,int> res( res_ek0, res_ek1, reverse_link.GetState(), 0 );
       if( generated.find(res)==UNKNOWN )
        {
         generated.push_back(res);
         ret = true;
        }
 
       vars.resize(2);
       values.resize(2);
      }
    }
   else if( Dname==Aname )
    {
     // ���������� �� D==B

     LEM_STOPIT;
    }
   else
    {
     LEM_STOPIT;
    }
  }

 return ret;
}

#endif
