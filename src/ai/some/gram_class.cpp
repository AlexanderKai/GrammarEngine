// -----------------------------------------------------------------------------
// File GRAM_CLASS.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� GramClass - �������� ��������������� ������ (���������) ��� �����
// ����������.
//
// 27.08.2008 - ��������� ����������� �������� ��� ������ ������ �����.
// 13.12.2008 - ��������� ����������� �������� ������ ������� ���������.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->20.11.2010
// --------------

#include <lem/macro_parser.h>
#include <lem/ucstring_functions.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/grammar.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/gram_class.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


GramClass::GramClass(void)
{
 #if defined SOL_LOADTXT && defined SOL_COMPILER
 is_realized = false;
 #endif
 is_parent = false;
 return;
}


#if defined SOL_LOADBIN
GramClass::GramClass( lem::Stream &bin )
{ LoadBin(bin); }
#endif

GramClass::~GramClass(void)
{}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/**********************************************************************
 �������� �������� ��������������� ������ �� ���������� ����� �������.
 ������:
        1. class ���_������ [,alias1,alias2,...] AS export_name

           ����� ������� ������. ����������� ���� ������ �����������,
           ��� ��������, ��� ��� ������. ������ ������ ������������ ��
           ���������� ������ '{' ����� ����� ������.

        2. class ���_������ [,alias1,alias2,...] AS export_name
           {
            ��������
            ���� 
            ���������
           }

          ������ ������. � �������� ��������� ���������� ���� ������,
          ��������� �� ������ ����������� ���������-��������� �
          ���������-���������.

         2.1 �������� ::= attributes
                          {
                           ���_����� [=���������_��_���������]
                           ���_����� [=���������_��_���������]
                              :
                              :
                          }

             ������ ��������� �������� �������� ���� ���������, ���
             ��������� ����������.

         2.2 ���� ::= tags
                      {
                       ���_�����
                       ���_�����
                          :
                          :
                      }
                        

         2.3 ��������� ::= dimensions
                           {
                            ���_�����
                            ���_�����
                                :
                                :
                           }

             ������ ��������� � �����-�� ���������� ������ ���������.

        3. ������� ������������ ������� ������ �������

           class X [,alias1,alias2,...] AS export_name : Y, Z ...

***********************************************************************/
void GramClass::LoadTxt(
                        Macro_Parser &txtfile,
                        Grammar& gram,
                        bool IsRealized
                       )
{
 is_realized = IsRealized;

 // *** ��� ������ ***
 const BethToken class_name = txtfile.read();
 sol_check_s_name(gram.GetDict(),txtfile,class_name,true);
 name=class_name.string();

 if( gram.GetDict().GetDebugLevel_ir()>=3 )
  {
   // ���-��������� � ������ ���������� ������.
   gram.GetIO().mecho().printf(
                               "%us [%vfE%us%vn]->",
                               sol_get_token(B_CLASS).c_str(),
                               name.c_str()
                              );
  }

 // ����� ���� ������ ������� - �������������� ���� ������
 if( txtfile.read().GetToken() == B_COMMA )
  {
   while( !txtfile.eof() )
    {
     UCString alias = txtfile.read();
  
     bool doubled = alias.eqi(name);
     if( !doubled )
      {
       for( lem::Container::size_type i=0; i<aliases.size(); i++ )
        if( aliases[i].eqi(alias) )
         {
          doubled=true;
          break; 
         }
      }

     if( doubled )
      {
       Print_Error( class_name, txtfile );

       gram.GetIO().merr().printf(
                                  "Alias [%ls] is already used as name or alias for class [%ls]",
                                  alias.c_str(), name.c_str()
                                 );

       throw E_ParserError();
      } 

     aliases.push_back(alias);

     if( txtfile.read().GetToken() != B_COMMA )
      {
       txtfile.backward(); 
       break; 
      }
    }
  }
 else
  {
   txtfile.backward(); 
  } 


 // ����� ���� ������ ��� ��� C-����
 if( txtfile.read().GetToken() == B_AS )
  c_name = txtfile.read();
 else
  txtfile.backward(); 

 // ���� �� ������� ������ ������������ �������.
 const BSourceState prepar = txtfile.tellp();
 if( txtfile.read().GetToken()==B_COLON )
  while( !txtfile.eof() )
   {
    // ��, ��������� �� �����.
    const BethToken par_name = txtfile.read();
    sol_check_s_name(gram.GetDict(),txtfile,par_name,true);

    const int ipar = gram.FindClass( par_name.string() );
    if( ipar==UNKNOWN )
     {
      // �� ������ �����...
      Print_Error(par_name,txtfile);
      gram.GetIO().merr().printf( "The class [%us] is not previously declared in grammar\n", par_name.string().c_str() );
      throw E_ParserError();
     }

    parent.push_back( ipar );

    // ������ �� �����, ��� ����� � �������� ipar �������� ������������.
    GramClass &P = gram.classes().GetClass( ipar );
    P.is_parent = true;

    // ����������, �� �������� ��������, ������� ���������, ����� � ���������.
    for( lem::Container::size_type ia=0; ia<P.attr_index.size(); ia++ )
     {
      if( attr_index.FindTwice(P.attr_index[ia])!=UNKNOWN || tag_index.FindTwice(P.attr_index[ia])!=UNKNOWN )
       {
        Print_Error(class_name,txtfile);

        gram.GetIO().merr().printf(
                                   "Attribute [%us] is already declared as an attribute or a tag for the class\n",
                                   gram.coords()[P.attr_index[ia].GetIndex()].GetName().string().c_str()
                                  );

        throw E_ParserError();
       }

      if( attr_index.FindTwice(P.attr_index[ia])==UNKNOWN )
       attr_index.push_back( P.attr_index[ia] );
     }

    for( lem::Container::size_type id=0; id<P.dim_index.size(); id++ )
     {
      if( attr_index.FindTwice(P.dim_index[id])!=UNKNOWN || tag_index.FindTwice(P.dim_index[id])!=UNKNOWN )
       {
        Print_Error(class_name,txtfile);

        gram.GetIO().merr().printf(
                                   "Dimension [%us] is already declared as an attribute or tag for the class\n",
                                   gram.coords()[P.dim_index[id].GetIndex()].GetName().string().c_str()
                                  );

        throw E_ParserError();
       }

      if( dim_index.FindTwice(P.dim_index[id])==UNKNOWN )
       dim_index.push_back( P.dim_index[id]);
     }

    for( lem::Container::size_type id=0; id<P.tag_index.size(); id++ )
     {
      if( attr_index.FindTwice(P.tag_index[id])!=UNKNOWN || dim_index.FindTwice(P.tag_index[id])!=UNKNOWN )
       {
        Print_Error(class_name,txtfile);

        gram.GetIO().merr().printf(
                                   "Tag [%us] is already declared as an attribute or dimension for the class\n",
                                   gram.coords()[P.tag_index[id].GetIndex()].GetName().string().c_str()
                                  );

        throw E_ParserError();
       }

      if( tag_index.FindTwice(P.tag_index[id])==UNKNOWN )
       tag_index.push_back( P.tag_index[id]);
     }


    // � ������� ��������� �������� ������ ������ ���������� �����.
    for( lem::Container::size_type ic=0; ic<P.parent.size(); ic++ )
     if( find( parent, P.parent[ic] )==UNKNOWN )
      parent.push_back( P.parent[ic] );

    // �������� ���������� ������������� ������ ���������.

    const BethToken precom = txtfile.read();
    if( precom.GetToken()!=B_COMMA )
     {
      txtfile.seekp( precom.GetBegin() );
      break;
     }
   }
  else
   txtfile.seekp(prepar);

 bool looping=true;

 // ��������, ����� ���� � ������� ������ ���������� ������ ���
 // ������� ����� '{}'

 const BSourceState prefig = txtfile.tellp();
 const BethToken isfig = txtfile.read();

 if( isfig.GetToken()!=B_OFIGPAREN )
  {
   txtfile.seekp(prefig);
   looping=false;
  }

 while( looping ) // ���� ���������� ������ �������� ������
  {
   if( txtfile.eof() )
    {
     // ���� ���������� ������, ��� ��������� ��������� ��������
     // ��������������� ������.
     Print_Error(txtfile);
     gram.GetIO().merr().printf(
                                "End of file has been reached before grammatical class [%us] completely loaded\n"
                                , name.c_str()
                               );
     throw E_ParserError();
    }

   const BethToken buffer = txtfile.read();

   switch(buffer.GetToken())
    {
     case B_ATTRIBUTES:
      LoadAttributesTxt(txtfile,gram);
      break;

     case B_TAGS:
      LoadTagsTxt(txtfile,gram);
      break;

     case B_DIMENTIONS:
      LoadDimentionsTxt(txtfile,gram);
      break;

     case B_CFIGPAREN:
      looping=false;
      break;

     default:
      {
       // ����������� ������ ����� ����� �������������� ���� � ���������
       // ��������.  
       if( !Load_Private_Data( buffer, txtfile, gram ) )
        {
         // ������������ ������������� ������� � ����������� ������.
         Print_Error(buffer,txtfile);
         gram.GetIO().merr().printf( "Error in class definition\n" );
         throw E_ParserError();
        }

       break;
      }
    }
  }

 if( gram.GetDict().GetDebugLevel_ir()>=3 )
  {
   // ���-���������: ������������� ����� ���������.
   gram.GetIO().mecho().printf( "%vfAOK%vn\n" );
  }

 return;
}
#endif // defined SOL_LOADTXT




#if defined SOL_LOADTXT && defined SOL_COMPILER
/***********************************************************************
               ��������� ������ �������� ���������

 ������������� ����� ���������, ������� ����� ��������� �������������
 (����������) ���������� ������ ��� ������� ��������������� ������.
 ������������ � ������ ���������� ������ ���� ��� ��������� � ������
 ����������, �� ���� ������ ������ �� ���������.
************************************************************************/
void GramClass::LoadAttributesTxt(
                                  Macro_Parser &txtfile,
                                  const Grammar& gram
                                 )
{
 // ������ ������ - ������ '{'
 txtfile.read_it(B_OFIGPAREN);

 FOREVER
  {
   if( txtfile.eof() )
    {
     // ���� ���������� ������, ��� ��������� ��������� ����������
     // ������ ��������� � �������� ��������������� ������.
     Print_Error(txtfile);
     gram.GetIO().merr().printf(
                                "End-of-file has been reached before attributes section is read "
                                "for the class [%us]\n"
                                , name.c_str()
                               );
     throw E_ParserError();
    }

   // ��� ��������, ��������.
   const BethToken attr_name = txtfile.read();

   // ���� ��� '}', �� ������ ��������� ��������.
   if( attr_name.GetToken()==B_CFIGPAREN )
    break;

   // ���� ������� (����������) � ����� ������ � ������ �������.
   const GramCoordAdr iattr = gram.FindCoord(attr_name.string());

   if( iattr.GetIndex()==UNKNOWN )
    {
     // ����������, ��� ������� ������������, �� ���������.
     Print_Error(attr_name,txtfile);
     gram.GetIO().merr().printf(
                                "The coordinate [%us] is not previously declared in grammar\n"
                                , attr_name.c_str()
                               );
     throw E_ParserError();
    }

   // �������� �� ��������� ����������� ���������� � ������.
   // ������������� ������ ��� ����������� ���������...
   if( attr_index.FindTwice(iattr)!=UNKNOWN )
    {
     // �����!
     Print_Error(attr_name,txtfile);
     gram.GetIO().merr().printf( "Attribute is already defined for the class\n" );
     throw E_ParserError();
    }

   // ������� �� ����� ���� ������������ ���������� ��� ������ �� ������.
   // ������������� ������ ��� ������������ ���������.
   if( dim_index.FindTwice(iattr)!=UNKNOWN || tag_index.FindTwice(iattr)!=UNKNOWN )
    {
     Print_Error(attr_name,txtfile);
     gram.GetIO().merr().printf( "Attribute is already declared as dimension or tag for the class\n" );
     throw E_ParserError();
    }

   // ��������� ������ ���������� � ������ ���������.
   attr_index.push_back( iattr );

   if( txtfile.pick().GetToken()==B_EQUAL )
    {
     // ������ �������� �� ��������� ��� ��������
     txtfile.read();
     BethToken state_name = txtfile.read();

     if( state_name.GetToken()==B_UNKNOWN )
      {
       // ����������� ���� ����������=? ������ ������ ��������� - �� ���� �� ���������
       // ������� �� ���������, � ��� �� �������� �������.
       attr_defaults.push_back( std::make_pair(GramCoordAdr(iattr),UNKNOWN) );
      }
     else
      { 
       const int istate = gram.coords()[iattr.GetIndex()].FindState(state_name);
       if( istate==UNKNOWN )
        {
         Print_Error(state_name,txtfile);
         gram.GetIO().merr().printf( "State [%us] is not defined for attribute [%us] in class [%us]\n",
          state_name.c_str(), attr_name.c_str(), GetName().c_str() );
         throw E_ParserError();
        }

       lem::zbool found;
       for( lem::Container::size_type i=0; i<attr_defaults.size(); ++i )
        if( attr_defaults[i].first==iattr )
         {
          found=true;
          break; 
         }

       if( !found )
        {
         attr_defaults.push_back( std::make_pair(GramCoordAdr(iattr),istate) );
        }
      }
    }
  }

 return;
}
#endif // defined SOL_LOADTXT



#if defined SOL_LOADTXT && defined SOL_COMPILER
/***********************************************************************
               ��������� ������ �������� �����

 ������������� ����� ���������, ������� ����� ��������� ������ -
 ������������� ���������� ������ ��� ������� ��������������� ������.
 ������������ � ������ ���������� ������ ���� ��� ��������� � ������
 ����������, �� ���� ������ ������ �� ���������.
************************************************************************/
void GramClass::LoadTagsTxt(
                            Macro_Parser &txtfile,
                            const Grammar& gram
                           )
{
 // ������ ������ - ������ '{'
 txtfile.read_it(B_OFIGPAREN);

 FOREVER
  {
   if( txtfile.eof() )
    {
     // ���� ���������� ������, ��� ��������� ��������� ����������
     // ������ ����� � �������� ��������������� ������.
     Print_Error(txtfile);
     gram.GetIO().merr().printf(
                                "End-of-file has been reached before tags section is read "
                                "for the class [%us]\n"
                                , name.c_str()
                               );
     throw E_ParserError();
    }

   // ��� ����.
   const BethToken tag_name = txtfile.read();

   // ���� ��� '}', �� ������ ����� ��������.
   if( tag_name.GetToken()==B_CFIGPAREN )
    break;

   // ���� ���������� � ����� ������ � ������ �������.
   const GramCoordAdr itag = gram.FindCoord(tag_name.string());

   if( itag.GetIndex()==UNKNOWN )
    {
     // ����������, ��� ������� ������������, �� ���������.
     Print_Error(tag_name,txtfile);
     gram.GetIO().merr().printf(
                                "The coordinate [%us] is not previously declared in grammar\n"
                                , tag_name.c_str()
                               );
     throw E_ParserError();
    }

   // �������� �� ��������� ����������� ����� � ������.
   // ������������� ������ ��� ����������� ���������...
   if( tag_index.FindTwice(itag)!=UNKNOWN )
    {
     // �����!
     Print_Error(tag_name,txtfile);
     gram.GetIO().merr().printf( "Tag is already defined for the class\n" );
     throw E_ParserError();
    }

   // ��� �� ����� ���� ������������ ���������� ��� ��������� ��� ������ �� ������.
   // ������������� ������ ��� ������������ ��������� � ���������.
   if( dim_index.FindTwice(itag)!=UNKNOWN || attr_index.FindTwice(itag)!=UNKNOWN )
    {
     Print_Error(tag_name,txtfile);
     gram.GetIO().merr().printf( "Tag is already declared as dimension or attribute for the class\n" );
     throw E_ParserError();
    }

   // ��������� ������ ���������� � ������ �����.
   tag_index.push_back( itag );
  }

 return;
}
#endif // defined SOL_LOADTXT


#if defined SOL_LOADTXT && defined SOL_COMPILER
/************************************************************************
                ��������� ������ �������� ���������.
 ������������� ����� ���������, ������� ����� �������� ��� ��������� �
 ������ ����� ������, � ����� ������� �������� ���� �������������� �����
 �� ������. ������������ � ������ ���������� ������ ���� ��� ��������� �
 ������ ����������, �� ���� ������ �� ����������� ������ �� ���������.
**************************************************************************/
void GramClass::LoadDimentionsTxt(
                                  Macro_Parser &txtfile,
                                  const Grammar& gram
                                 )
{
 // ������ ������ ���������� ������� '{'
 txtfile.read_it(B_OFIGPAREN);

 FOREVER
  {
   if( txtfile.eof() )
    {
     // ���� ���������� ������, ��� ��������� ��������� ����������
     // ������ ��������� � �������� ��������������� ������.
     Print_Error(txtfile);
     gram.GetIO().merr().printf(
                                "End-of-file has been reached before dimensions section is read "
                                "for the class [%us]\n"
                            , name.c_str()
                           );
     throw E_ParserError();
    }

   // ��� ���������?
   const BethToken dim__name = txtfile.read();

   // ���� ��� '}', �� ������ ��������� ��������.
   if( dim__name.GetToken()==B_CFIGPAREN )
    break;

   // ���� ���������� � ����� ������ � ������ �������.
   const GramCoordAdr idim = gram.FindCoord(dim__name.string());

   if( idim.GetIndex()==UNKNOWN )
    {
     // ������������ ��� ����������� ����������.
     Print_Error(dim__name,txtfile);
     gram.GetIO().merr().printf(
                                "The coordinate [%us] is not previously declared in grammar\n"
                                , dim__name.c_str()
                               );
     throw E_ParserError();
    }

   // �������� �� ��������� ����������� ��� ������.
   // ������������� ������ ��� ����������� ���������...
   if( dim_index.FindTwice(idim)!=UNKNOWN )
    {
     // ����� !
     Print_Error(dim__name,txtfile);
     gram.GetIO().merr().printf( "Redefinition of dimension for the class\n" );
     throw E_ParserError();
    }

   // ��������� �� ����� ���� ������������ ��������� ��� ������!
   if( attr_index.FindTwice(idim)!=UNKNOWN || tag_index.FindTwice(idim)!=UNKNOWN )
    {
     Print_Error(dim__name,txtfile);
     gram.GetIO().merr().printf( "Dimension is already declared as attribute or tag for the class\n" );
     throw E_ParserError();
    }

   dim_index.push_back( idim ); // ��������� ������ ���������� � ��� ������.
  }

 return;
}
#endif // defined SOL_LOADTXT

#if defined SOL_SAVEBIN
/************************************************************
 ���������� �������� ��������������� ������ � �������� �����.
*************************************************************/
void GramClass::SaveBin( lem::Stream &bin ) const
{
 Save_Packed( name, bin );
 aliases.Save_Packed(bin);

 bin.write( &is_parent, sizeof(is_parent) );

 attr_index.SaveBin(bin);
 dim_index.SaveBin(bin);
 tag_index.SaveBin(bin);
 parent.SaveBin(bin);
 attr_defaults.SaveBin(bin);
 return;
}
#endif

/**********************************************
 �������� �������� ������ �� ��������� �����.
***********************************************/
void GramClass::LoadBin( lem::Stream &bin )
{
 Load_Packed( &name, bin );
 aliases.Load_Packed(bin);

 bin.read( &is_parent, sizeof(is_parent) );
 attr_index.LoadBin(bin);
 dim_index.LoadBin(bin);
 tag_index.LoadBin(bin);
 parent.LoadBin(bin);
 attr_defaults.LoadBin(bin);

 #if defined SOL_LOADTXT && defined SOL_COMPILER
 is_realized = true;
 #endif

 return;
}



#if defined SOL_SAVETXT
/*******************************************************************
 ���������� � ��������� ��������� ����� �������� ����� ����������
 ��������������� ������.
********************************************************************/
void GramClass::SaveTxt(
                        OFormatter& txtfile,
                        Grammar& gram
                       ) const
{
 txtfile.printf(
                " // class %us   %d attribute(s)  %d dimension(s)   %d tag(s)\n"
                , name.c_str()
                , CastSizeToInt(attrs().size())
                , CastSizeToInt(dims().size())
                , CastSizeToInt(tags().size())
               );

 txtfile.printf(
                " %us %us",
                sol_get_token(B_CLASS).c_str(),
                name.c_str()
               );

 if( !aliases.empty() )
  {
   for( lem::Container::size_type i=0; i<aliases.size(); ++i )
    {
     txtfile.printf( ", %us", aliases[i].c_str() );
    }
  }

 if( !parents().empty() )
  {
   // ����� ������� �������� ������������ �������
   txtfile << sol_get_token(B_COLON);

   for( lem::Container::size_type i=0; i<parent.size(); i++ )
    {
     if( i )
      txtfile << sol_get_token(B_COMMA);

     txtfile << gram.classes()[ parent[i] ].GetName();
    }

   txtfile.eol();
  }


 txtfile.printf( " %us\n", sol_get_token(B_OFIGPAREN).c_str() );

 if( !attrs().empty() || !dims().empty() || !tags().empty() )
  {
   SaveAttributesTxt(txtfile,gram);
   SaveDimentionsTxt(txtfile,gram);
   SaveTagsTxt(txtfile,gram);
  }

 Save_Private_Txt( txtfile, gram );

 txtfile.printf( " %us\n\n", sol_get_token(B_CFIGPAREN).c_str() );

 return;
}
#endif


#if defined SOL_SAVETXT
/*****************************************************
 �������������� ���������� �������� ���������� ������
*****************************************************/
void GramClass::SaveAttributesTxt(
                                  OFormatter &txtfile,
                                  const Grammar& gram
                                 ) const
{
 if( attrs().empty() )
  return; /* if nothing there, exit...*/

 txtfile.printf(
                "  %us\n  %us\n",
                sol_get_token(B_ATTRIBUTES).c_str(),
                sol_get_token(B_OFIGPAREN).c_str()
               );

 for( lem::Container::size_type i=0; i<attrs().size(); i++ )
  {
   txtfile.printf(
                  "   %us",
                  gram.coords()[
                                attrs()[i].GetIndex()
                               ].GetName()[ attrs()[i].GetVar() ].c_str()
                 );


   for( lem::Container::size_type j=0; j<attr_defaults.size(); ++j )
    if( attr_defaults[j].first==attrs()[i] )
     {
      if( attr_defaults[j].second==UNKNOWN )
       txtfile.printf( "%us%us",
        sol_get_token(B_EQUAL).c_str(),
        sol_get_token(B_UNKNOWN).c_str()
        );
      else 
       txtfile.printf( "%us%us", 
        sol_get_token(B_EQUAL).c_str(),
        gram.coords()[attr_defaults[j].first.GetIndex()].GetStateName( attr_defaults[j].second ).c_str()
       ); 
      break;
     }

   txtfile.eol();
  } 

 txtfile.printf( "  %us\n", sol_get_token(B_CFIGPAREN).c_str() );
 return;
}
#endif

#if defined SOL_SAVETXT
/****************************************************
 �������������� ���������� �������� ������ ���������
*****************************************************/
void GramClass::SaveDimentionsTxt(
                                  OFormatter& txtfile,
                                  const Grammar& gram
                                 ) const
{
 if( dims().empty() )
  return; /* if nothing there, exit...*/

 txtfile.printf(
                "  %us\n  %us\n",
                sol_get_token(B_DIMENTIONS).c_str(),
                sol_get_token(B_OFIGPAREN).c_str()
               );

 for( lem::Container::size_type i=0; i<dims().size(); i++ )
  txtfile.printf(
                 "   %us\n",
                 gram.coords()[
                               dims()[i].GetIndex()
                              ].GetName()[ dims()[i].GetVar() ].c_str()
                );

 txtfile.printf( "  %us\n", sol_get_token(B_CFIGPAREN).c_str() );
 return;
}
#endif


#if defined SOL_SAVETXT
/****************************************************
 �������������� ���������� �������� ������ �����
*****************************************************/
void GramClass::SaveTagsTxt(
                            OFormatter& txtfile,
                            const Grammar& gram
                           ) const
{
 if( tags().empty() )
  return; /* if nothing there, exit...*/

 txtfile.printf(
                "  %us\n  %us\n",
                sol_get_token(B_TAGS).c_str(),
                sol_get_token(B_OFIGPAREN).c_str()
               );

 for( lem::Container::size_type i=0; i<tags().size(); i++ )
  txtfile.printf(
                 "   %us\n",
                 gram.coords()[
                               tags()[i].GetIndex()
                              ].GetName()[ tags()[i].GetVar() ].c_str()
                );

 txtfile.printf( "  %us\n", sol_get_token(B_CFIGPAREN).c_str() );
 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
bool GramClass::operator==( const GramClass & c ) const
{ return dim_index==c.dim_index && attr_index==c.attr_index && tag_index==c.tag_index; }

bool GramClass::operator!=( const GramClass & c ) const
{ return dim_index!=c.dim_index || attr_index!=c.attr_index || tag_index!=c.tag_index; }
#endif


/************************************************************************
 ������� ���������� ������ FindLocAttrIndex � FindLocDimIndex, ���������
 ����� � ����� ���������, � ����� ���������.
*************************************************************************/
bool GramClass::FindLocCoordIndex( const GramCoordAdr iglobal, bool strict ) const
{
 return
       dim_index.find_fuzzy(iglobal,strict) != UNKNOWN
       ||
       tag_index.find_fuzzy(iglobal,strict) != UNKNOWN
       ||
       attr_index.find_fuzzy(iglobal,strict) != UNKNOWN;
}


bool GramClass::MatchName( const lem::UCString &n ) const
{
 if( name.eqi(n) )
  return true;

 for( lem::Container::size_type i=0; i<aliases.size(); ++i )
  if( aliases[i].eqi(n) )
   return true;

 return false;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
bool GramClass::Load_Private_Data( 
                                  const BethToken &t,
                                  Macro_Parser &txtfile,
                                  Grammar& gram
                                 )
{
 return false;
}
#endif

#if defined SOL_SAVETXT
void GramClass::Save_Private_Txt( OFormatter& txtfile, const Grammar& gram ) const
{}
#endif
