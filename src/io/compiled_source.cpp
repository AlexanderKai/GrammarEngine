// -----------------------------------------------------------------------------
// File COMPILED_SOURCE.CPP
//
// (c) by Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ���������� ��� ������� Source ��� ������ � �������������������� ��������, ��
// ���� ������ ������� ����������� � ����������� ������, � ����� ����� ������
// ��������� �� �� ������, ������������...
// -----------------------------------------------------------------------------
//
// CD->28.01.97
// LC->16.10.04
// ------------

#include <lem/compiled_source.h>

using namespace std;
using namespace lem;

CompiledSource::CompiledSource( int NTOKEN, CString *TOKENS )
:Text_Parser(),text(0,128)
{
 vector<CString> Tokens;
 Tokens.reserve(NTOKEN);
 for( int i=0; i<NTOKEN; i++ )
  Tokens.push_back(TOKENS[i]);

 SetTokens(Tokens);

 next=0;
 compiled=false;
 return;
}

// ********************************************************************
// ��������� ��������� ����-��������, ������ �� ���� ���������������
// ��� ������ � ���������� �� � ������ � ������. ������ ����� ���������
// ���� ��������� ����� ����� ���������� ������ �������� ����!
// ********************************************************************
void CompiledSource::Open( const char *TxtName )
{
 Text_Parser::Open(TxtName);

 // ������ � ��������� ��� ������ � ����������� ������.
 while( !Text_Parser::eof() )
  {
   AToken t = Text_Parser::read();

   // ����� � ������� ������ - ����� ������� ����� �����.
   if( !t.string().length() )
    break;
   else
    text.push_back(t);
  }

 compiled=true;
 return;
}

// ***********************************************************
// ���������� ��������� ����� �� ������ � ����������� ������.
// ���������� ��������� �� ��������� ������� � ������.
// ***********************************************************
const AToken CompiledSource::read(void)
{
 if( next>=text.size() )
  {
   // �� ��������� ������! ����� ������ �����...
   AToken dummy;
   return dummy;
  }

 return text.get(next++);
}

/******************************************************************
 ������������ � ������ ������, � ������� ���������� �����, �������
 ����� ��������� ��� ������ read();
*******************************************************************/
void CompiledSource::ToLineBegin(void)
{
 const AToken &t = text.get(next);
 Text_Parser::seekp(t.GetBegin());
 Text_Parser::ToLineBegin();
 return;
}

// ********************************************************************
// ���������� ��������� � �������� ��������� �����, ���� �� �� ������
// ������ ������ � �� �� ������ � ����������� ������.
// ********************************************************************
const SourceState CompiledSource::ftell(void) const
{
 return !compiled ?
         Text_Parser::tellp()
                  :
         ( text.get( next>=text.size() ? text.size()-1 : next).GetBegin() );
}

// ********************************************************************
// ������������ � ������ � ����������� ������, ������� ������� �
// ������� � �������� ��������� �����, �������� ��� SourceState.
// ��������� �� ����, ��� ������ (99% �������) ������������ �����
// �� ���� ����� �����.
// ********************************************************************
void CompiledSource::fseek( const SourceState &ss )
{
 if( !compiled )
  {
   Text_Parser::seekp(ss);
   return;
  }

 // ���� ����� ������� ����������� �� ���� ����� �����!
 if( next!=0 && text[next-1].GetBegin()==ss )
  {
   // ������� ����� �� ���� �����.
   next--;
   return;
  }

 // ���� ��������������� ������� ����� ������� ����� ���������� � ��������.
 // ���������� �� ��� ���������, � ��� ������ ��� ����� �����, ��� ������
 // ����������� ������.
 bool found=false;
 int i,ifound;
 for( i=next-2; i>=0 && !found; i-- )
  found = text[ifound=i].GetBegin()==ss;

 if( found )
  {
   next=ifound;
   return;
  }

 // ���������� ����� ������.
 found=false;
 for( i=next-1; i<text.size() && !found; i++ )
  found = text[ifound=i].GetBegin()==ss;

 if( found )
  {
   next=ifound;
   return;
  }

 // ������ ���������������� �����!
 LEM_STOPIT;
}

/******************************************************
 ����� ������ ������� true, ���� ��� ������ ���������.
*******************************************************/
bool CompiledSource::eof(void)
{
 if( !compiled )
  return Text_Parser::eof();

 return next>=text.size();
}

// -------------------------- End Of File [COMPILED_SOURCE.CPP] -----------------------
