// -----------------------------------------------------------------------------
// File IR_PARSER_STACK.CPP
//
// (c) 2005 by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// Licensed under the terms of GNU Lesser GPL
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// ����� IR_Parser_Stack - ����������� ��� ������������� �������. ���������
// ������� ����� ������, �������������� ������� UTextSource<LEM_CSTRING_LEN>,
// � ���������� ���������� ���������. ������������ ����������� ���� ������
// INT � STRING.
// -----------------------------------------------------------------------------
//
// CD->02.07.1997
// LC->01.12.2006
// --------------

#include <lem/conversions.h>
#include <lem/lexers.h>
#include <lem/sol_io.h>
#include <lem/macro_parser.h>
#include <lem/ir_parser.h>

using namespace lem;
using namespace lem::Iridium;

IR_Parser_Stack::IR_Parser_Stack( Sol_IO &Io ):io(Io)
{
 TOS        = 0;
 opened_par = 0;
 return;
}

/********************************************************************
 ���������� ���������� ����������� ��������� � ���������� ���������.
 ������� �������� vt - ������� ������� ��������, ������� �����������
 ����� � ��� ����������.
*********************************************************************/
bool IR_Parser_Stack::get_bool_exp(
                                   const IR_Var_Table &vt,
                                   const IR_Macro_Table &mt
                                  )
{
 IR_Parser_Variable *res=calculate(vt,mt);
 const int r=res->GetIntValue();
 delete res;
 return !!r;
}

/********************************************************************
 ���������� ������ get_bool_exp, ���������� ���������� ��������������
 ��������� � ���������� ���������. ������� �������� vt - ������
 ������� ��������, ������� ������������ ����� � ��� ����������.
*********************************************************************/
int IR_Parser_Stack::get_int_exp(
                                   const IR_Var_Table &vt,
                                   const IR_Macro_Table &mt
                                  )
{
 IR_Parser_Variable *res = calculate(vt,mt);
 const int r=res->GetIntValue();
 delete res;
 return r;
}

/*********************************************************************
 ������������ ��������� ��������� � ���������� ���������. �������
 �������� vt - ������� ������� ��������, ������� ������������ ����� �
 ��� ����������.
***********************************************************************/
const UFString IR_Parser_Stack::get_string_exp(
                                                 const IR_Var_Table &vt,
                                                 const IR_Macro_Table &mt
                                                )
{
 IR_Parser_Variable *res = calculate(vt,mt);
 const UFString r=res->GetStringValue();
 delete res;
 return r;
}

/*****************************************************************
 ����� ������� ��� ���������� ������������� ���������. ����������
 ��������� - ����������, ������ �� ��������� ��������� ������
 ����������� ������� ��� ����������.
******************************************************************/
IR_Parser_Variable* IR_Parser_Stack::calculate(
                                             const IR_Var_Table &/*vt*/,
                                             const IR_Macro_Table &mt
                                            )
{
 Reduce(mt);
 const IrPrepParsToken tk_res=Result(mt);
 IR_Parser_Variable *var_res = new IR_Parser_Variable(*tk_res.GetOperand());
 return var_res;
}

/************************************************************************
 ����� ��������� ������ �� ������ txtfile �� ����� ������� ������ �
 �������� �� �� �������������� ����.
*************************************************************************/
void IR_Parser_Stack::Parse(
                              UTextParser &txtfile,
                              const IR_Var_Table &vt,
                              const IR_Macro_Table &mt
                             )
{
 while( !txtfile.eof() )
  {
   const UToken t = txtfile.read();
   if( t.GetToken()==LEM_SOURCE_EOL )
    break;

   if( GetToken(t).GetType()==IR_PTK_STRING )
    {
     // ������ � ������� ���������� �� ������ ������� ������ �������,
     // ��� ����� �������-������ ���������� ���������� ����������
     // LEM_CSTRING_LEN.
     txtfile.seekp(t.GetBegin());
     const UFString ls = txtfile.read_fstring();
     Push(t,ls,vt,mt);
    }
   else
    Push(t,t.string().c_str(),vt,mt);
 }

 return;
}

bool IR_Parser_Stack::PushList(
                               const lem::Collect<UFString> &list,
                               const IR_Var_Table &vt,
                               const IR_Macro_Table &mt
                              )
{
 push_value( list, mt );
 return true;
}


bool IR_Parser_Stack::Push(
                           const UToken &tok,
                           const UFString &ls,
                           const IR_Var_Table &vt,
                           const IR_Macro_Table &mt
                          )
{
 memoria=tok;
 bool proceed=true;

 if( memoria.string().empty() )
  return false;

 const IR_Prep_Token tk=GetToken(memoria);

 switch( tk.GetType() )
  {
   case IR_PTK_NUMBER:   // ��������� �������� ������ �������� �� ����
    {
     int dummy;
     to_int(memoria.string().c_str(),&dummy);
     push_value(dummy,memoria.string().c_str(),mt);
     break;
    }

   case IR_PTK_STRING:
    {
     // ��������� ���������.
     UFString str=ls; str.strip_quotes();
     push_value( str.c_str(), mt );
     break;
    }

   case IR_PTK_VARIABLE:
    {
     const int ivar=vt.Find(memoria.string());

     if(ivar==UNKNOWN)
      // Lexem is not a variable name, so we consider it as a string
      // constant.
      push_value( memoria.string().c_str(), mt );
     else
      {
       IR_Parser_Variable *tv = new IR_Parser_Variable(*vt[ivar]);
       push_tmp_var(tv,mt);
      }

     break;
    }

   case IR_PTK_FUNCTION:
   case IR_PTK_OPERATOR: // ����������� ��� ����������� �������
    {
     if( tk.string()==Macro_Parser::t_CroundParen && GetPars()==0 )
      {
       proceed=false;
       break;
      }

     push_com( tk.GetKey(), mt );
     break;
    }

   case IR_PTK_EOL:
    proceed=false;   // ����������� �������� ���������
    break;

   default:
    proceed=false;   // ����������� �������� ���������
    break;
  }

 return proceed;
}

/***********************************************************
 ��������� �������� �� �������� �����( ���� ��� ����������).
************************************************************/
void IR_Parser_Stack::Reduce( const IR_Macro_Table &mt )
{
 if( TOS==1 )                          // ���� �� ����� ��� ���������,
  return;                              // �� �� ���������� ��������

 if( stack[TOS-2].GetCommand()==IR_T_OROUNDPAREN ) // ���� �������� - ����������� ������
  return;                              // �� ��������� ������

 const IrPrepParsToken &op2 = pop();
 const Ir_Token_Key      cm = pop().GetCommand();
 const IrPrepParsToken &op1 = IsUnary(cm) ? op2 : pop();

 const IrPrepParsToken t(Compute( op1, cm, op2, mt ));
 const IrPrepParsToken res(t); // ���������
 push(res,mt);
 return;
}

/************************************************************************
 ��� ������� ���������� �������� ����� �������, ���� ��� ��������.
 ����� ������������ ������ ����� � ����� SOL_IR_PTK_ILLEGAL. ��� �����������
 ����� � ���� ������������ ������� - ��. ���� ir_token.cpp.
*************************************************************************/
const IR_Prep_Token IR_Parser_Stack::GetToken( const UToken &t ) const
{
 const UCString &str = t.string();

 if( str[0]==L'\n' && !str[1] )
  return IR_Prep_Token( str, IR_PTK_EOL );

 if( in_quotes(str) )
  return IR_Prep_Token( strip_quotes(str), IR_PTK_STRING );

 int i=0;

 // ���� � �������.
 while( ir_tokens[i].GetKey() != UNKNOWN )
  if( ir_tokens[i].string() == t )
   return ir_tokens[i];
  else
   i++;

 // ����� � ������� �� �������. ��� ����� ���� ���� ��� ����������,
 // ���� �����. ������ ������ ����� - ��-����� ?
 if( is_name(str.c_str()) )
  return IR_Prep_Token(str,IR_PTK_VARIABLE);  // ��� ��� ����������.

 // ��� ����� (������ ���� �����!).
 int dummy;
 if( to_int(str.c_str(),&dummy) )
  return IR_Prep_Token(str,IR_PTK_NUMBER);

 return IR_Prep_Token(str,IR_PTK_ILLEGAL);
}

/******************************************************
 ���������� �� ����, �������� �� �������� �����������.
*******************************************************/
bool IR_Parser_Stack::IsUnary( Ir_Token_Key cmd ) const
{
 int i=0;

 while( ir_tokens[i].GetKey()!=UNKNOWN )
  if( ir_tokens[i].GetKey()==cmd )
   return ir_tokens[i].GetnArg()==1;
  else
   i++;

 return false;
}

/********************************************************************
 ���������� ��������������� �������. �������� ����� �� ������ �����.
*********************************************************************/
const IrPrepParsToken IR_Parser_Stack::Result( const IR_Macro_Table &mt )
{
 // ���������� ���� �� �����
 while( TOS>1 )
  {
   int OLDTOS=TOS;
   Reduce(mt); // ��������� ��������...

   if( OLDTOS==TOS )
    io.merr().printf("Preprocessor expression syntax \n");
  }

 if( opened_par != 0 ) // �������� �������� �������� ?
  io.merr().printf("�������� �������� ������ '(' � ��������� ��� �������������\n");

 // ������� ����� ������ ���� ������, � �� ��������!
 if( !stack[0].IsNumber() )
  io.merr().printf("Preprocessor expression syntax \n");

 TOS=0;
 return stack[0];
}

void IR_Parser_Stack::push_value(
                                 int arg,
                                 const wchar_t *repr,
                                 const IR_Macro_Table &mt
                                )
{
 IR_Parser_Variable *cv = new IR_Parser_Variable( L"", arg, repr );
 push( IrPrepParsToken( cv ), mt );
 return;
}


void IR_Parser_Stack::push_value(
                                 const lem::Collect<UFString> &list,
                                 const IR_Macro_Table &mt
                                )
{
 push( IrPrepParsToken( new IR_Parser_Variable( L"", list ) ) , mt );
 return;
}


void IR_Parser_Stack::push_value(
                                 const wchar_t *arg,
                                 const IR_Macro_Table &mt
                                )
{
 push( IrPrepParsToken( new IR_Parser_Variable( L"", arg ) ) , mt );
 return;
}

void IR_Parser_Stack::push_tmp_var(
                                   IR_Parser_Variable *arg,
                                   const IR_Macro_Table &mt
                                  )
{
 push( IrPrepParsToken( arg ) , mt );
 return;
}

void IR_Parser_Stack::push(
                           const IrPrepParsToken &tk,
                           const IR_Macro_Table &mt
                          )
{
 if( tk.IsNumber() )
  {
   // ���� ��������� �� ������� ��������, �� ������������ ��������� �����

   if(
      TOS>0 &&
      stack[TOS-1].GetCommand()!=IR_T_OROUNDPAREN &&
      IsUnary( stack[TOS-1].GetCommand() )
     )
    {
     push(
          IrPrepParsToken( Compute( tk, pop().GetCommand(), tk, mt ) ),
          mt
         );
     return;
    }
  }

 if( TOS==SOL_IR_MAXPARSERSTACK1 )
  throw ECheckFault( L"Preprocessor stack overflow: too complex expression" );

 stack[TOS++]=tk;
 return;
}

/*************************************************************************
 ��������� ��������� �� ����. ��������, �������� ������� ������� ����...
**************************************************************************/
void IR_Parser_Stack::push_com( Ir_Token_Key com, const IR_Macro_Table &mt )
{
 if( com == IR_T_CROUNDPAREN )                   // ���� ����������� ������...
  {
   // ���������� �������� �����
   if( TOS<2 )  // ���� �������� ������
    io.merr().printf(": the same marque [%us] for different signals\n");

   // ���������� ���� �� ����� �� ������� � ������ �������
   while( TOS>0 && stack[TOS-2].GetCommand()!=IR_T_OROUNDPAREN )
    Reduce(mt); // ��������� ��������...

   IrPrepParsToken operand=pop(); // ������ ��������� ����������� ������
   pop();               // ������� ������
   push(operand,mt);    // ����� ������ �� �����
   opened_par--;
   return;
  }

 if( TOS==SOL_IR_MAXPARSERSTACK1 ) // �������� ����� �� ������������
  throw ECheckFault( L"Preprocessor stack overflow: too complex expression" );

 // ��������, �������� ��� ������� ����� ��� ����, ��� �������
 if( TOS==0 || stack[TOS-1].IsCommand() ) // ���� ��� ������ �������� � �����
  {                                       // ������ ��� ��� ������ �� ����� �����
   if( !IsUnary(com) )
    throw ECheckFault( L"Macroprocessor expression contains invalid unary operation" );
  }

 if( com!=IR_T_OROUNDPAREN && !IsUnary(com) )
  if( TOS>2 )                               // ���� ���� ���������� ��������
   if( !stack[TOS-2].IsNumber() )           // � ��� ����� �����
    if( Priority(stack[TOS-2].GetCommand()) >= Priority(com) ) // � �� ��������� ������
     {                                     // �� ���������� �� �����
      // ��������� �������
      Reduce(mt);
      stack[TOS++]=IrPrepParsToken(com);
      return;
     }

 stack[TOS++]=IrPrepParsToken(com);          // �������� �����-������� �� ����
 if( com == IR_T_OROUNDPAREN )
  opened_par++;

 return;
}

/**********************************************************************
 ���������� ��������� ��������, �������� ���������� com ��� ��� ������.
***********************************************************************/
int IR_Parser_Stack::Priority( Ir_Token_Key com ) const
{
 // ���������� ( � ������� ������������ ������� � �������).
 // 0 - ����� ������� ���������.
 struct Prior { Ir_Token_Key key; int prior; };

 static Prior pri[]={
                     { IR_T_LOGNOT,       10 },   //   '!'
                     { IR_T_LOGNE,        5  },   //   '!='
                     { IR_T_LOGEQ,        5  },   //   '=='
                     { IR_T_LOGGT,        5  },   //   '>'
                     { IR_T_LOGGE,        5  },   //   '>='
                     { IR_T_LOGLT,        5  },   //   '<'
                     { IR_T_LOGLE,        5  },   //   '<='
                     { IR_T_AMPERSAND,    4  },   //   '&'
                     { IR_T_LOGAND,       4  },   //   '&&'
                     { IR_T_ORSIGN,       3  },   //   '|'
                     { IR_T_LOGOR,        3  },   //   '||'
                     { IR_T_OROUNDPAREN,  100 },  //   '('
                     { IR_T_CROUNDPAREN,  2   },  //   ')'
                     { IR_T_DEFINED,      1   }   //   'defined'
                    };

 for( size_t i=0; i<DIM_A(pri); i++ )
  if( pri[i].key==com )
   return pri[i].prior;

 return UNKNOWN;
}

/*************************************************************
 ���������� ����������������� �������� op ��� ����� ����������
 first � second, ������ ������� � �������� �����. ��� �������
 �������� (���������� � �����������) ������������ ������
 �������� first.
**************************************************************/
const IrPrepParsToken IR_Parser_Stack::Compute(
                                               const IrPrepParsToken& first,
                                               Ir_Token_Key op,
                                               const IrPrepParsToken& second,
                                               const IR_Macro_Table &mt
                                              ) const
{
 switch(op)
  {
   case IR_T_LOGEQ:     return first == second;
   case IR_T_LOGNE:     return first != second;
   case IR_T_LOGLT:     return first <  second;
   case IR_T_LOGLE:     return first <= second;
   case IR_T_LOGGT:     return first >  second;
   case IR_T_LOGGE:     return first >= second;
   case IR_T_LOGOR:     return first || second;
   case IR_T_ORSIGN:    return first || second;
   case IR_T_LOGAND:    return first && second;
   case IR_T_AMPERSAND: return first && second;
   case IR_T_LOGNOT:    return !first;
   case IR_T_DEFINED:
    {
     const bool ival = mt.Find( first.GetOperand()->GetName() )!=UNKNOWN;
     IR_Parser_Variable *res = new IR_Parser_Variable(
                                              L"",
                                              ival,
                                              to_ustr( int(ival) ).c_str()
                                             );
     return IrPrepParsToken(res);
    }

   default:
    throw ECheckFault( L"Invalid macroprocessor expression - internal error" );
  }

// return first;
}

/*************************************
 ������ ������ � �������� �����.
*************************************/
IrPrepParsToken& IR_Parser_Stack::pop(void)
{
 if( TOS==0 ) // �������� ����� �� ����������������
  throw ECheckFault(L"Preprocessor calculator stack underflow");

 return stack[--TOS];
}
