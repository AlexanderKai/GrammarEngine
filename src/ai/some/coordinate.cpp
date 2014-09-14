// -----------------------------------------------------------------------------
// File COORDINATE.CPP
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
// SOLARIX Grammar engine
// ����� GramCoord - �������� ���������� � �� ���������. ������������ ������
// ����� ��� ����������� ��������� ������������� ��������.
//
// 17.02.2008 - ��������� ��������� �������� ��� �������� � CSharp
// 12.12.2008 - ����� ��������� �� ����� ��� ����� ��������
// 12.01.2009 - ��������� ��������� ����������� ������ ��� Pascal
// 26.10.2011 - ��������� ��������� ����������� ������ ��� PHP
// -----------------------------------------------------------------------------
//
// CD->23.10.1995
// LC->26.10.2011
// --------------

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/coordinate.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;

GramCoord::GramCoord( const GramCoord& c )
: id(c.id), name(c.name), state(c.state)
 #if defined SOL_LOADTXT
 , c_name( c.c_name )
 #endif
{
 #if defined SOL_LOADTXT
 is_realized = c.is_realized;
 #endif
 return;
}

GramCoord::GramCoord(void)
 : id(UNKNOWN)
{
 #if defined SOL_LOADTXT
 is_realized=false;
 #endif
 return;
}



#if defined SOL_LOADTXT
GramCoord::GramCoord(
                     Macro_Parser& txtfile,
                     const Grammar& gram,
                     bool IsRealized
                    )
 : id(UNKNOWN)
{
 LoadTxt(txtfile,gram,IsRealized);
 return;
}
#endif

GramCoord::GramCoord( lem::Stream& binfile )
{ LoadBin(binfile); }

void GramCoord::operator=( const GramCoord& c )
{
 id = c.id;
 name        = c.name;
 state       = c.state;
 #if defined SOL_LOADTXT
 is_realized = c.is_realized;
 c_name = c.c_name; 
 #endif
 return;
}

void GramCoord::Add( const GramCoord &c )
{
 state.AddList( c.state );

 if( updator!=NULL )
  updator->Update( *this );

 return;
}

void GramCoord::Add( const GramCoordState &cs )
{
 state.push_back( cs );

 if( updator!=NULL )
  updator->Update( *this );

 return;
}

#if defined SOL_LOADTXT
void GramCoord::AddState( const UCString &s )
{
 GramCoordState cs;
 cs.push_back( s );
 state.push_back( cs );

 if( updator!=NULL )
  updator->Update( *this );

 return;
}
#endif


#if defined SOL_LOADTXT
/*************************************************************************

                 �������� �������� �� ���������� �����

  1. ����� ������:

     1.1 ���������

     enum ���, �������1, �������2, ...

     ����� ��������� ����� ����� ������������� �������������� �����
     ���������� (��������). ��� ���������� ��� ������ � ����������
     ������������� ������������� (���� ����� '�������'). ��� ����������
     ������ ���������� � ����� ��� ������� '_'.

     1.2 ������ ��������� (��� ����������������� ������):

     ... = ���_���������

     - ����� �������� ���������� [���] �������� ��� �� ������ ���������,
       ��� � ��������� ��� [���_��������].

     ... { ����1 ����2 ... ����N }

     - � �������� ��������� ������������� ����� ���������.

  2. ���� �� ������ ������� - ���������� � ����� �����������,
     ������������� �� ������ ��� TRUE � FALSE. ������ �������
     �� ��������� ����. ���������� ����� ����� ������:

                 :

     enum ���_����������

                 :


     �� ���� ����� ��������� ���� �� �����������. ���������� ��������
     ����� �� ����������� ����������� ������� ���������, �� ��� ���������
     � ������������ ��������� ���������� � ������� ����������� ���������
     ������������� � ����� �����������.
**************************************************************************/
void GramCoord::LoadTxt(
                        Macro_Parser &txtfile,
                        const Grammar& gram,
                        bool IsRealized
                       )
{
 is_realized = IsRealized;

 BethToken coord_name = txtfile.read();
 sol_check_coord_name(gram.GetDict(),txtfile,coord_name);
 name.push_back(coord_name.c_str());

 const bool Me = gram.GetDict().GetDebugLevel_ir()>=3;
 if( Me )
  {
   // ���-���������: ������ ���������� ����������.
   gram.GetIO().mecho().printf(
                               "%us [%vfE%us%vn]->",
                               sol_get_token(B_COORDINATE).c_str(),
                               name.get(0).c_str()
                              );
  }


 BSourceState back = txtfile.tellp();

 bool cname_loaded=false;
 if( txtfile.read().GetToken() == B_AS )
  {
   c_name = txtfile.read();
   back = txtfile.tellp();
   cname_loaded = true;
  }
 else
  txtfile.seekp(back);  

 // ���� �������� ����������� �������� ����������.
 bool loading=true;
 while(loading)
  {
   const BethToken t1 = txtfile.read();

   switch( t1.GetToken())
    {
     case B_EQUAL:
      {
       // ��������� ������������ '='. ��� ��� ���������� ���� ���������
       // ������ ����������, ��� ������� ��� ������.

       const BethToken another = txtfile.read();
       const GramCoordAdr ianother = gram.FindCoord(another.string());

       if( ianother.GetIndex()==UNKNOWN )
        {
         Print_Error(another,txtfile);
         MemFormatter f;
         f.printf(
                  "The coordinate [%us] is not previously "
                  "declared in grammar\n"
                  , another.c_str()
                 );
         throw E_Solarix( f.string().c_str() );
        }

       state = gram.coords()[ianother.GetIndex()].state; // ���������� ���� ���������

       #if defined SOL_COMPILER  
       // ������� C-����� ���������
       for( lem::Container::size_type i=0; i<state.size(); ++i )
        {
         state[i].Clear_API_Names();
        } 
       #endif

       loading=false; // ������ ��������� ������
       break;
      }

     case B_COMMA:
      {
       // ����� ������� ���� �������� ����� ����������.
       const BethToken t2 = txtfile.read();
       sol_check_s_name(gram.GetDict(),txtfile,t2,true);
       if( name.Find(t2.c_str())!=UNKNOWN )
        {
         Print_Error(t2,txtfile);
         MemFormatter f;
         f.printf( "Duplication of the name in coordinate [%us] declaration\n", t2.c_str() );
         throw E_Solarix( f.string().c_str() );
        }

       name.push_back(t2.c_str());
       break;
      }

     case B_OFIGPAREN:
      {
       // � �������� ��������� ����������� ��������� ��������� ����������.

       while(!txtfile.eof())
        {
         const BSourceState back2 = txtfile.tellp();

         // ���� ��� '}', �� ������ ��������� ��������.
         if( txtfile.read().GetToken()==B_CFIGPAREN )
          break;

         txtfile.seekp(back2);
         GramCoordState dummy;
         dummy.LoadTxt( gram.GetIO(), txtfile );

         // ��� ��������� ���������� ���������?
         for( lem::Container::size_type i=0; i<dummy.size(); i++ )
          {
           // ��������, ����� � ����������� ��������� �� ���� ����
           // ���������� ����.
           for( lem::Container::size_type j=0; j<dummy.size(); j++ )
            if( i!=j )
             if( dummy[i]==dummy[j] )
              {
               Print_Error(txtfile);
               MemFormatter f;
               f.printf( "Two equal names in a coordinate [%us] state subgroup\n", name.string().c_str() );
               throw E_Solarix( f.string().c_str() );
              }

           const UCString& look_for = dummy.get(i);
           if( FindState(look_for)!=UNKNOWN )
            {
             Print_Error(txtfile);
             MemFormatter f;
             f.printf( "Two states of coordinate [%us] have got the same name\n", name.string().c_str() );
             throw E_Solarix( f.string().c_str() );
            }
          }

         state.push_back(dummy);

         if( Me )
          gram.GetIO().mecho().printf('.');
        }

       loading=false;
       break;
      }

     default:
      {
       if( states().size() )
        {
         Print_Error(t1,txtfile);
         MemFormatter f;
         f.printf(
                  "Definition of the coordinate [%us] is not"
                  " identical to previous one.\n"
                  , name.string().c_str()  
                 );
         throw E_Solarix( f.string().c_str() );
        }

       // ���� ��� �� ����������� �������� ��������, �� ����� ����������
       // � ����� ����������� TRUE � FALSE (������������ ����������).
       txtfile.seekp(back);

       // �� ���� ���������� �������� �����������.
       loading = false;
       break;
      }
    } // end of switch
  } // end of while


 // ��������, ����� ����� ���������� ��������� �� ��������� SOL_MAXCATEGORY -
 // ����� ����� � int32 (��. "lem_bita.h")
 //
 // ������� ���� ������ �� ��������, ��� ��� �������� ������������� �����
 // ��������� � int-�����.
/*
 if( GetTotalStates()>LEM_MAXCATEGORY )
  {
   Print_Error( coord_name, txtfile, 1 );
   gram.GetIO().merr().printf(
            "Number of enumeration [%us] states exceeds the maximum number of flag bitfield digits\n"
            , name.string().c_str() 
           );
  }
*/

 if( Me )
  {
   // ���-���������: ��������� ���������� ����������.
   gram.GetIO().mecho().printf( "%vfAOK%vn\n" );
  }

 return;
}
#endif


void GramCoord::LoadBin( lem::Stream& bin )
{
 name.Load_Packed(bin);

 state.LoadBin(bin);

 #if defined SOL_LOADTXT
 is_realized=true;
 #endif

 return;
}

#if defined SOL_SAVEBIN
void GramCoord::SaveBin( lem::Stream& bin ) const
{
 name.Save_Packed(bin);

 state.SaveBin(bin);
 return;
}
#endif

/**************************************************************************
  ����, �� ������ ��������� ���������� ��������� ��������� ��������:

  enum ��� { ����1 ����2 ... { ����5 ����6 ... } ... }

  ����� �������, ����� ������������ ��������� ���������. ��� ������� � ���
  �������, ����� ����� ��������� ����� ��������� ������ ����� ���������
  ����� ��� ����5, ����6 ... . � ���� ������ �������, ��� ����5 � �����
  �������� ���� ��������������� ����5.

  ���������� ������ �������� ��������� � ������������ ���������:


   i=0   i=1  ...  i=5  i=6
  ����1 ����2 ... ����5 ...
                  ����6
                    :
                    :


  �� ���� ��� �������� ��������� ������� ������ ������ i ����� ��
  ��������������� ������������� � ������ ������ ������� ���������.

  ���� ��������, ��� ����� ���������, �������� �� ����, ������������
  ��������� � ���������� ������� ��������������� �����.
***************************************************************************/
int GramCoord::FindState( const UCString& sname ) const
{
 int index=0;

 if( sname==sol_get_token(B_ANY) )
  return ANY_STATE;

 if( sname==sol_get_token(B_UNKNOWN) )
  return UNKNOWN_STATE;

 for( lem::Container::size_type i=0; i<states().size(); i++ )
  {
   // 12.12.2008: ����� ��� ����� ��������!
   const int res = GetTopState(i).FindNoCase(sname);

   if( res!=UNKNOWN )
    return res+index;

   index+=CastSizeToInt(GetTopState(i).size());
  }

 return UNKNOWN;
}

/********************************************************************
 �������� ������ LI ����������� � ������ ���������.
*********************************************************************/
int GramCoord::GetIndexOfState( int LI ) const
{
 int index=0;

 for( int i=0; i<LI; i++ )
  index+=CastSizeToInt(GetTopState(i).size());

 return index;
}

/********************************************************************
  ���������� ��� ��������� �� ��� ��������� ������� RI.
*********************************************************************/
const UCString& GramCoord::GetStateName( int RI ) const
{
 if( RI == ANY_STATE )
  return sol_get_token(B_ANY);

 int index=0;

 for( lem::Container::size_type i=0; i<state.size(); i++ )
  {
   const int ns = CastSizeToInt(state[i].size());

   if( index+ns>RI )
    {
     #if defined LEM_BORLAND
     // 27.08.2006 CBuilder code generator bug - original code
     //            causes Access Violation.
     const GramCoordState &y = state.get(i);
     const UCString &z = y.get(RI-index);
     return z;
     #else
     return state[i][RI-index];
     #endif
    }   

   index+=ns;
  }

 LEM_STOPIT;
 return GetTopState(0).get(0);
}

/*****************************************************************
 ���������� ������ ��������� ������������, � ������� �����������
 ���������.
*****************************************************************/
int GramCoord::GetSubgroup( int RI ) const
{
 int index=0;

 for( lem::Container::size_type i=0; i<states().size(); i++ )
  {
   const int ns = CastSizeToInt(GetTopState(i).size());

   if( index+ns>RI )
    return i;

   index+=ns;
  }

 return UNKNOWN;
}

/**************************************************************************
 ����������� �� ��������� � ��������� ����������������� (�������������)
**************************************************************************/
bool GramCoord::IsDefState( int RI ) const
{
 const int isubgroup = GetSubgroup(RI);

 // ������ ������� ������ ���...
 if( isubgroup==UNKNOWN )
  return false;

 // �����������, ���� � ������ ����� ������ ��������.
 return GetTopState(isubgroup).size()>1;
}

/*************************************************
 ���� �� ������ ������?
**************************************************/
bool GramCoord::HasDefStates(void) const
{
 for( Container::size_type i=0; i<states().size(); i++ )
  if( GetTopState(i).size()>1 )
   return true;

 return false;
}

/*******************************************************************
 ������ ������ �������� ���������, �������� � ��������� ���������.
*******************************************************************/
const IntCollect GramCoord::GetSubgroupIndeces( int isubgroup ) const
{
 int istart=0;

 for( int i1=0; i1<isubgroup; i1++ )
  istart += CastSizeToInt(GetTopState(i1).size());

 IntCollect is;
 for( lem::Container::size_type i2=0; i2<GetTopState(isubgroup).size(); i2++ )
  is.push_back(istart+i2);

 return is;
}

/**********************************************************************
 ����������, �������� �� ��������� ������� � ��������� �������������.
 ������� ��������, ��� ���� ������ ������ � 1 ��������� �����������.
**********************************************************************/
bool GramCoord::IsHeadState( int RI ) const
{
 const int ig = GetSubgroup(RI);
 int istart=0;

 for( int i=0; i<ig; i++ )
  istart += CastSizeToInt(GetTopState(i).size());

 return istart==RI;
}

/*****************************************************
 ������������ ����� ����� ��������� �� ���� �������.
*****************************************************/
int GramCoord::GetTotalStates(void) const
{
 int ts=0;

 for( lem::Container::size_type i=0; i<states().size(); i++ )
  ts += CastSizeToInt(GetTopState(i).size());

 return ts;
}

/***********************************************************
 ���������, ��������� �� ����� ��������� � ���� ���������.
***********************************************************/
bool GramCoord::operator!=( const GramCoord& x ) const
{
 if( states().size() != x.states().size() )
  {
   #if LEM_DEBUGGING==1
   int n1 = states().size();
   int n2 = x.states().size();
   #endif
   return true;
  }

 for( lem::Container::size_type i=0; i<states().size(); i++ )
  if( GetTopState(i)!=x.GetTopState(i) )
   return true;

 return false;
}


bool GramCoord::operator==( const GramCoord& x ) const
{
 if( states().size() != x.states().size() )
  return false;

 for( lem::Container::size_type i=0; i<states().size(); i++ )
  if( GetTopState(i)!=x.GetTopState(i) )
   return false;

 return true;
}


/********************************************************************
 ���� ������ ������� �������� ����� �� ���� ����������, ��
 ���������� ������ ����� � ������. ���� ����� ��� �� ������������ �
 ������ ���������, ������ UNKNOWN.
********************************************************************/
int GramCoord::IsName( const UCString& s ) const
{
 for( lem::Container::size_type i=0; i<name.size(); i++ )
  if( GetName()[i].eqi(s) )
   return i;

 return UNKNOWN;
}



#if defined SOL_SAVETXT
/*****************************************************
 �������������� ��������� ���� ���������� ����������.
 ��� ���������� � ��������� ��������� �����.
*****************************************************/
void GramCoord::SaveTxt( OFormatter& txtfile ) const
{
 txtfile.printf(
                " %us %us",
                sol_get_token(B_COORDINATE).c_str(),
                GetName().front().c_str()
               );

 for( lem::Container::size_type ivar=1; ivar<name.size(); ivar++ )
  txtfile << sol_get_token(B_COMMA) << name[ivar];

 if( state.empty() )
  txtfile.printf( " /* no states */\n" );
 else
  txtfile.printf(
                 " /* %d state(s) */\n"
                 , state.size()
                );

 if( !state.empty() )
  {
   txtfile.printf( " %s ", sol_get_token(B_OFIGPAREN).c_str() );

   for( lem::Container::size_type i=0; i<state.size(); i++ )
    {
     GetTopState(i).SaveTxt(txtfile);
     txtfile.printf(' ');
    }

   txtfile << sol_get_token(B_CFIGPAREN);
  }

 txtfile.eol();
 txtfile.eol();
 return;
}
#endif

#if defined SOL_COMPILER
void GramCoord::Save_API( OFormatter &cpp, lem::Binding::Language lang ) const
{
 if( lang==lem::Binding::CPP || lang==lem::Binding::CSharp )
  {
   if( !state.empty() )
    {
     cpp.printf( "// Coordiname %us states:\n", GetName().front().c_str() );
    }
  }
 else if( lang==lem::Binding::Pascal )
  {
   if( !state.empty() )
    {
     cpp.printf( "{ Coordiname %us states: }\n", GetName().front().c_str() );
    }
  }
 else if( lang==lem::Binding::Python )
  {
   if( !state.empty() )
    {
     cpp.printf( "# Coordiname %us states:\n", GetName().front().c_str() );
    }
  }
 else if( lang==lem::Binding::PHP )
  {
   if( !state.empty() )
    {
     cpp.printf( "// Coordiname %us states:\n", GetName().front().c_str() );
    }
  }
 else
  {
   LEM_STOPIT;
  } 

 int istate=0;
 for( lem::Container::size_type i=0; i<state.size(); i++ )
  {
   const GramCoordState& s = state[i];

   if( !s.get_C_Name().empty() )
    {
     if( lang==lem::Binding::CPP || lang==lem::Binding::CSharp )
      {
       if( lang==lem::Binding::CSharp )
        cpp.printf( " public " );

       cpp.printf(
                  "const int %us = %d; %50t // %us : %us\n", 
                  s.get_C_Name().c_str(),
                  istate,
                  GetName().front().c_str(),
                  s.front().c_str()
                 );   
      }
     else if( lang==lem::Binding::Pascal )
      {
       cpp.printf(
                  "const %us: integer = %d; %50t // %us : %us\n", 
                  s.get_C_Name().c_str(),
                  istate,
                  GetName().front().c_str(),
                  s.front().c_str()
                 );
      }
     else if( lang==lem::Binding::Python )
      {
       cpp.printf(
                  "%us = %d %50t # %us : %us\n", 
                  s.get_C_Name().c_str(),
                  istate,
                  GetName().front().c_str(),
                  s.front().c_str()
                 );
      }
     else if( lang==lem::Binding::PHP )
      {
       cpp.printf(
                  "define( '%us', %d ); %50t // %us : %us\n", 
                  s.get_C_Name().c_str(),
                  istate,
                  GetName().front().c_str(),
                  s.front().c_str()
                 );
      }
     else
      {
       LEM_STOPIT;
      } 
    }

   s.Save_API( istate, cpp, lang );

   istate += CastSizeToInt(s.size());
  }

 return;
}
#endif
