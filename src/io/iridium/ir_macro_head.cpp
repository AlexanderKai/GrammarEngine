// -----------------------------------------------------------------------------
// File IR_MACRO_HEAD.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ����� IR_Macro_Head - �������� ��������� �������: ��� � ���������� ���������
// � ������� �������.
// -----------------------------------------------------------------------------
//
// CD->30.07.1997
// LC->09.03.2010
// --------------

#include <lem/conversions.h>
#include <lem/ir_parser.h>
#include <lem/macro_parser.h>

using namespace lem;
using namespace lem::Iridium;


IR_Formal_Arg::IR_Formal_Arg(void)
{}

IR_Formal_Arg::IR_Formal_Arg( const UCString& x )
:UCString(x)
{}

IR_Formal_Arg::IR_Formal_Arg( const IR_Formal_Arg &x )
:UCString(x),def(x.def)
{}

IR_Formal_Arg::IR_Formal_Arg( const UCString& x, const lem::Collect<UFString> &Def )
:UCString(x), def(Def)
{}

void IR_Formal_Arg::operator=( const IR_Formal_Arg &x )
{  
 UCString::operator=(x);
 def=x.def;
 return;
}



// -------------------------------

IR_Macro_Head::IR_Macro_Head(void)
{}

IR_Macro_Head::IR_Macro_Head( Sol_IO &io, UTextParser &txtfile )
{
 LoadTxt(io,txtfile);
 return;
}

IR_Macro_Head::IR_Macro_Head( const IR_Macro_Head &h )
:name(h.name),arg(h.arg)
{}


void IR_Macro_Head::operator=( const IR_Macro_Head &h )
{ Init(h); }

void IR_Macro_Head::operator=( const UCString &Name )
{ name=Name; }


void IR_Macro_Head::Init( const IR_Macro_Head &h )
{
 name = h.name;
 arg  = h.arg;
}

/*******************************************************************
 ��������� ������ ������� �� ���������� �����. ���������� ��� ����
 �� �������������� ������-���� ������������������, �� ���� ��������
 ������ ������������ "as is".
********************************************************************/
void IR_Macro_Head::LoadTxt( Sol_IO &io, UTextParser &txtfile )
{
 // ��� ������� - ���������� ����� �������, ������� �������������
 // ��������������� �����������, �������������� ������� UTextSource<LEM_CSTRING_LEN>.
 const UToken n = txtfile.read();
 name=n.string();

 // ������ true ����� �������� �������� ������� ��������� � default value,
 // ��� ��� ����� �������������� ������������ ������� defaults ���
 // ��������� ����������.
 bool first_def=false;

 // �������� ��������� ������ ���������� � (...)
 const SourceState back = txtfile.tellp();
 if( txtfile.read() == Macro_Parser::t_OroundParen )
  while( !txtfile.eof() )
   {
    UToken Arg = txtfile.read();

    if( Arg == Macro_Parser::t_CroundParen )
     break;

    if( Arg==Macro_Parser::t_Backslash || Arg.eol() )
     continue;

    if( !arg.empty() )
     {
      txtfile.seekp(Arg.GetBegin());
      txtfile.read_it( Macro_Parser::t_Comma ); // ����������� ����������.
      Arg = txtfile.read();

      while( Arg==Macro_Parser::t_Backslash || Arg.eol() )
       Arg = txtfile.read();
     }

    if( !is_name( Arg.string().c_str() ) )
     {
      // ��� ����������� ��������� ������ ����������� �������� ��� ����.
      Print_Error( io, Arg, txtfile );
      io.merr().printf(
                       "Incorrect formal argument name [%vfE%us%vn] in macro [%vfE%us%vn]\n"
                       , Arg.string().c_str(), name.c_str()
                      );
      throw E_ParserError();
     }

    lem::Collect<UFString> def;
    // ����������� arg_name=default ������ �������� ��������� �� ���������.
    UToken t = txtfile.read();
    lem::UFString fstr;
    if( t==Macro_Parser::t_Equal )
     {
      txtfile.read(fstr);
      def.push_back(fstr);

      if( def.front()==Macro_Parser::t_OroundParen.c_str() )
       {
        def.clear(); 
        int n_open=1;

        while( !txtfile.eof() )
         {
          UFString tt;
          txtfile.read(tt);
          if( tt==Macro_Parser::t_CroundParen.c_str() )
           {
            n_open--;
            if( !n_open )
             break; 
           }
          else if( tt==Macro_Parser::t_OroundParen.c_str() )
           {
            n_open++;
           } 
          else if( !tt.empty() )
           def.push_back(tt);
         }  
       }

      first_def=true;
     }
    else
     {
      if( first_def )
       {
        Print_Error( io, Arg, txtfile );
        io.merr().printf(
                         "Formal argument [%vfE%us%vn] in macro [%vfE%us%vn] must "
                         "have a default value\n"
                         , Arg.string().c_str(), name.c_str()
                        );
        throw E_ParserError();
       }

      txtfile.seekp( t.GetBegin() );
     }

    arg.push_back( IR_Formal_Arg( Arg.string(), def ) );
   }
 else
  txtfile.seekp(back);

 return;
}

/****************************************************************************
 ���������, ����� �� ��������� ���������������� � ������������������
 �������, ������ ������� (�� 1 � ����� ���������) �������� � ������ list.
 ���� �������������� � list ������� �� ������, �� ��������� �����������
 ����� �� ��������� ���������� ����� txtfile ����������� ������� ::get_next.
 ����� ������ 'subst' ���������� �������� ������������� ���������� ����������
 �������������� �������. ����� �������� n_to_reduce ���������� �����
 ��������� � list, ������� ���������� ������� � ���������� ������ ��� ����
 ������� � ������� ���������� ���������� �� ��������� �������������.

 � ������ table ����������� ����������, �� ���� ������ �������
 ��������������� ������������� ���������� ������ �������.
****************************************************************************/
bool IR_Macro_Head::DoesMatch(
                              Sol_IO &io,
                              Collect<UFString> &list,
                              int ifirst,
                              UTextParser &txtfile,
                              Collect<IR_Macro_Subst> &subst,
                              int *n_to_reduce,
                              IR_Var_Table *table
                             ) const
{
 if( list[ifirst] != name.c_str() )
  return false;

 *n_to_reduce=1;

 // ���� �������� ������� �� �������� ���������� ����������, �� �����
 // �������, ��� ���������� ����� ������� � ������� ������� ��� �����������
 // �����...
 if( !GetnArg() )
  return true;

 int icursor=ifirst+1;

 // ������ ������ ���� ����������� ������ - �� ��� ������ �������� ���������� ����������
 const UFString s( get_next( io, list, &icursor, txtfile ) );

 if( s != Macro_Parser::t_OroundParen.c_str() )
  {
   Print_Error( io, txtfile );
   io.merr().printf(
                    "[%vfE%us%vn] macro substitution : '(' expected, '%vfE%us%vn' is taken\n"
                    , name.c_str(), s.c_str()
                   );
   throw E_ParserError();
  }

 // ������ ��������� ������������� ��� ������� ����������� ���������.
 bool closed=false; // true, ����� ����� ��������� ')'
 for( int iarg=0; iarg<GetnArg(); iarg++ )
  {
   // ����� ����� ����������� ���������������� �������. ������� ������
   // ��������, ��� ���� ���������� �������� ����� ���� ���������������
   // ����� ������� ������. ��������, ��� �������:
   //
   //               #define M(a,b)  a+b
   //
   // �����������
   //
   //               M( 1 2, 3 )
   //
   // ����� ������� �
   //
   //               1 2 + 3
   //
   //
   // ���� ����� ������ ��������� ��� �������, � ������� ���� ������� - ��������:
   //
   //               M( (1,2), 3 ) 
   //
   // ����� ������ � 
   //
   //               1,2 + 3

   IR_Macro_Subst sub( GetArg(iarg) );

   if( closed )
    {
     // ���������� �������� �������� �������� �� ���������.
     std::copy( GetArg(iarg).def.begin(), GetArg(iarg).def.end(), std::back_inserter(sub) );
    }
   else
    {
     // ����� ��������� ������� ��� �������� ������ ���������.
     bool first_tok=true;

     while( !txtfile.eof() )
      {
       const UFString s( get_next( io, list, &icursor, txtfile ) );

       if( s==Macro_Parser::t_OroundParen.c_str() )
        {
         if( first_tok )
          {
           // ������ ������ - ������ ������ � ������� �������, �������
           // ���������� � ����������� ���������.
 
           first_tok = false;

           int n_open=1; 
           
           while( !txtfile.eof() )
            { 
             const UFString s( get_next( io, list, &icursor, txtfile ) );

             if( s==Macro_Parser::t_OroundParen.c_str() )
              {
               n_open++;
              }
             else if( s==Macro_Parser::t_CroundParen.c_str() )
              {
               n_open--;
               if( !n_open )
                break;  
              }
             else if( s==L'\n' )
              continue; 

             sub.push_back( s );
            }                
  
           // �������� ����������� ��������� ���������.
           break;
          }  
         else
          {
           Print_Error( io, txtfile );
           io.merr().printf(
                            "[%vfE%us%vn] macro substitution : opening parentess can not be used in this context\n"
                            , name.c_str()
                           );
           throw E_ParserError();
          }
        }  
 
       if( s==L'\n' )
        continue;

       first_tok = false;

       if( s == Macro_Parser::t_Comma.c_str() )
        {
         if( iarg == GetnArg()-1 )
          {
           Print_Error( io, txtfile );
           io.merr().printf(
                            "[%vfE%us%vn] macro substitution : too many arguments, macro definition requires only %d\n"
                            , name.c_str(), GetnArg()
                           );
           throw E_ParserError();
          }

         // ����������� ����������� ��������� ���������.
         break;
        }

       if( s == Macro_Parser::t_CroundParen.c_str() )
        {
         if( iarg==GetnArg()-1 )
          {
           // ��������� ��������� ����������� ���� ����������� ��� ����������.
           closed=true;

           // ���� �������� ������ ��������, � �� ����� �������� �� ���������...
           if( iarg==0 && sub.empty() && !GetArg(iarg).def.empty() )
            {
             std::copy( GetArg(iarg).def.begin(), GetArg(iarg).def.end(), std::back_inserter(sub) );
            }

           break;
          }
         else
          {
           // ���� ���������� ��������� ����� ����� �������� �� ���������, ��
           // �� ���������.
           bool have_def=true;
           for( int ii=iarg+1; ii<GetnArg() && have_def; ii++ )
           have_def = !GetArg(ii).def.empty();

           if( !have_def )
            {
             Print_Error( io, txtfile );
             io.merr().printf(
                              "[%vfE%us%vn] macro substitution : too few arguments, %d in macro definition\n"
                              , name.c_str(), GetnArg()
                             );
             throw E_ParserError();
            }

           closed=true;
           break;
          }
        }

       sub.push_back( s );
      }
    } 

   // ��������������� ��������� ���������� ��������.
   subst.push_back( sub );

   // ������� ��� ���� �������� ���� - �������� ��������� ���������� ��
   // �����������. ����� ���� ���� �������� �� ���������� �������������...
   table->push_back( sub.CreateVar() );
  }

 if( !closed )
  {
   const UFString s( get_next( io, list, &icursor, txtfile ) );
   if( s != Macro_Parser::t_CroundParen.c_str() )
    {
     Print_Error( io, txtfile );
     io.merr().printf(
                      "[%vfE%us%vn] macro substitution : missing ')', got '%vfE%us%vn'\n"
                      , name.c_str(), s.c_str()
                     );
     throw E_ParserError();
    }
  }

 *n_to_reduce = icursor-ifirst;
 return true;
}

/***************************************************************************
 �������� �������� ��������� ������� �� ������ list, � ���� ���� ������
 ��������, �� ���������� ����� �� ��������� �����. ���������� �� ::DoesMatch
****************************************************************************/
const UFString IR_Macro_Head::get_next(
                                       Sol_IO &io,
                                       lem::Collect<UFString> &list,
                                       int *icursor,
                                       UTextParser &txtfile
                                      ) const
{
 if( *icursor >= CastSizeToInt(list.size()) )
  {
   if( txtfile.eof() )
    {
     Print_Error( io, txtfile );
     io.merr().printf(
                      "[%vfE%us%vn] macro substitution : end of file reached\n"
                      , name.c_str()
                     );
     throw E_ParserError();
    }

   // � �������� ������ �� ������� ������ - ��������� �� ��������� �����.
   lem::UFString fstr;
   txtfile.read(fstr);
   list.push_back(fstr);
  }

 return UFString( list[ (*icursor)++ ] );
}

