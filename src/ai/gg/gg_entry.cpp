// -----------------------------------------------------------------------------
// File GG_ENTRY.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� GG_Entry - ������ ����������� ����������, ������ ����� ���������, ��
// ���� ��������� ������������� ����� ����� ���������� �����. ������ �����
// �������� ����������� �� Base_Entry class.
// -----------------------------------------------------------------------------
//
// CD->10.08.1996
// LC->09.01.2012
// --------------

#include <lem/conversions.h>
#include <lem/macro_parser.h>
#include <lem/WideStringUcs4.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/gg_autom.h>
#include <lem/solarix/Symbol.h>


using namespace lem;
using namespace Solarix;

/*****************************************************************************
   ������ ����������� ���������� �������� �������� ������������ �������������
 ����� � ��� �� ����� ��������. � �������, ������� 'A' � 'a' ���� ��� �����
 ��� ������ ����� ���������� ��������. � ������� '�', '�', '�' � '�' ������
 ��������� ��������� ����� ������������� ����� '�' � ������� ������ � ������
 ����, ��� ��� �����, ��������� ����������, � ����������� ������� ������� ���
 'E', ���� ��� ����� ��� ������ �����.

   ����� ����� ����� ������������������ ���������� ������ ������������
 �������� �� ������� ������������ ��� ��������� ������. � ��� ����� �������
 ������������ ������������� ������, ���� ����������� ������, ���������,
 ��������, ��������� � ��� �����, ��� ���������� ��������� �����, ������������
 ����� ������. ����� ������������ �������������� ����� ����� � "�����������",
 �� ������ ������� ��������������� � ��������� ���������� �������������
 ������ ������������� ����.
******************************************************************************/



GG_Entry::GG_Entry(void):Base_Entry()
{
 name=0; id_alphabet=UNKNOWN;
}

GG_Entry::GG_Entry( const GG_Entry& e )
:Base_Entry(e), name(e.name), id_alphabet(e.id_alphabet), form(e.form)
{}

GG_Entry::GG_Entry(
                   lem::uint32_t Ucs4Name,
                   int _id_class,
                   int _id_alphabet,
                   const lem::MCollect<Solarix::GramCoordPair> &_attrs
                  )
 : Base_Entry()
{
 name = Ucs4Name;
 iclass = _id_class;
 id_alphabet = _id_alphabet;
 attr = _attrs;
 return;
}



GG_Entry& GG_Entry::operator=( const GG_Entry& e )
{
 if( &e!=this )
  {
   Base_Entry::operator=(e);
   name        = e.name;
   form        = e.form;
   id_alphabet = e.id_alphabet;
  }

 return *this;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/*****************************************************************************
 ������� ����� Base_Entry �������� ����������� ����� (����������) �����
 ������, � ������ �� ������ ������� �� ������ �������������� �������� -
 ������ ������������ ��� � ����� - ���������� � �������� �� � ���� ����������
 ������. �� ������ ������ �������������� ������ ANSI-�������� � UNICODE-������
 ������ ����������� � ����� [SOL_UNIC.CPP], ��� ��� formname ����� ���������
 ������� �������� ������������� UNICODE-�������.
******************************************************************************/
void GG_Entry::AddForm(
                       const CP_Array& dim,
                       const WordFormName& form_name,
                       Dictionary&
                      )
{
 lem::uint32_t ucs4=0;

 UCString tmp(form_name.form_name);
 tmp=strip_quotes(tmp);

 if( tmp.eq_beg( L"0x" ) )
  {
   int code;
   if( lem::to_int( tmp.c_str()+2, &code, 16 ) )
    {
     ucs4 = code;
    }
   else
    {
     lem::MemFormatter mem;
     mem.printf( "Invalid symbol definition [%us]", form_name.form_name.c_str() );
     throw E_BaseException( mem.string() );
    }
  }
 else
  {
   WideStringUcs4 senum( tmp.c_str() );
   ucs4 = senum.Fetch();

   if( senum.Fetch()!=0 )
    {
     lem::MemFormatter mem;
     mem.printf( "Invalid symbol definition [%us]", form_name.form_name.c_str() );
     throw E_BaseException( mem.string() );
    }
  }
 

 form.push_back( GG_EntryForm( dim, ucs4 ) );
 return;
}
#endif


void GG_Entry::Add( const GG_EntryForm &f )
{
 form.push_back(f);
 return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
/***************************************************************************
 ��������� ��� ����������� �� ���������� ����� �������. ��� ��� �������
 ������� � ���������-����������� ���������� �������� ���� UNICODE, �
 ��������� ���� ������� ������������ �� ���� ����� ������� ANSI, ��
 ���������� ����� ����������� ��� UNICODE-������� ����� �������
 ANSI-��������. ����� �������������� �������������� ��������
 sol_str_to_unicode, ��� ������� ����������� � ������������ � �����
 SOL_UNIC.CPP.
****************************************************************************/
void GG_Entry::LoadName( Macro_Parser& txtfile, Dictionary &dict )
{
 lem::UCString str( strip_quotes( txtfile.read().string() ) );

 WideStringUcs4 senum( str.c_str() );
 name = senum.Fetch();
 if( senum.Fetch()!=0 )
  {
   lem::MemFormatter mem;
   mem.printf( "Invalid symbol entry name [%us]", str.c_str() );
   throw E_BaseException( mem.string() );
  }

 txtfile.read_it(B_COLON);

 if( dict.GetDebugLevel_ir()>=3 )
  {
   dict.GetIO().mecho().printf(
                               "%us [",
                               sol_get_token(B_ENTRY).c_str()
                              );
   PrintName( dict.GetIO().mecho() );
   dict.GetIO().mecho().printf( "]->" );
  }

 return;
}
#endif


// *****************************************************************
// ������ ����� ����������� ������ (�����������) � ��������� �����.
// *****************************************************************
void GG_Entry::PrintName( OFormatter &to ) const
{
 to.printf( "%vfE%us%vn", GetNameWide().c_str() );
 return;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
bool GG_Entry::ProcessSection(
                              Macro_Parser &txtfile,
                              Grammar &gram,
                              const BethToken &t
                             )
{
 if( t.GetToken() == B_ALPHABET )
  {
   const UCString abc_name = txtfile.read().string();
   id_alphabet = static_cast<const GraphGram&>(gram).Find_Alphabet( abc_name );

   if( id_alphabet == UNKNOWN )  
    {
     lem::Iridium::Print_Error(txtfile);
     gram.GetIO().merr().printf( "Unknown alphabet [%us] referenced\n", abc_name.c_str() );
     throw E_ParserError();
    }

   return true;
  }

 return false;
}
#endif

const Grammar& GG_Entry::GetGrammar( const Dictionary &dict )
{
 return dict.GetGraphGram();
}

Grammar& GG_Entry::GetGrammar( Dictionary &dict )
{
 return dict.GetGraphGram();
}

lem::CString GG_Entry::GetNameUtf8(void) const
{
 return Solarix::EncodeChar32ToUtf8(name);
}

lem::UCString GG_Entry::GetNameWide(void) const
{
 return Solarix::EncodeChar32ToWide(name);
}

/*********************************************************************
 ����� ���������� ����������. ������� �������� �� ��, ��� ���� ������
 ����� i ����� ��� UNKNOWN, �� ������ ���������� ����� ������� �������
 ����� ��������� � ������� ��. ����� �������� ��������� ��� ������ ��
 �������, ������� �� ����� ���������. � �������, ������ ������ ���
 ������������.
**********************************************************************/
const GG_EntryForm GG_Entry::GetForm( int i ) const
{
 return form.empty() ? GG_EntryForm( attrs(), GetName() ) : form[i];
}
