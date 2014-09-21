// -----------------------------------------------------------------------------
// File IPR_TRANSLATOR.H
//
// (c) by koziev Elijah
//
// Content:
// ���������� ��� �������������� RULER (����� ipr_*.* - �� InterPReter).
// ��� �������� ������� � ������������ ���� lem::Interpreter
// -----------------------------------------------------------------------------
//
// CD->28.01.1997
// LC->27.01.2009
// --------------

#ifndef LEM_RULER__H
#define LEM_RULER__H
#pragma once

 #include <stack>
 #include <lem/clc_calculator.h>
 #include <lem/oformatter.h>
 #include <lem/containers.h>

 namespace lem
 {
  namespace Translator
  {
   using lem::Calc::VarType;
   using lem::Calc::VarTable;

   const int LEM_NTOKEN=35;
   enum {
         LEM_TT_PRINT=0,
         LEM_TT_STOP,
         LEM_TT_STREND,
         LEM_TT_DAPOSTROF,
         LEM_TT_DEFREAL,
         LEM_TT_EQUAL,
         LEM_TT_ADD,
         LEM_TT_DEL,
         LEM_TT_RUN,
         LEM_TT_FOR,
         LEM_TT_DO,
         LEM_TT_WHILE,
         LEM_TT_OROUNDPAREN,
         LEM_TT_CROUNDPAREN,
         LEM_TT_BEGIN,
         LEM_TT_END,
         LEM_TT_COMMA,
         LEM_TT_OS,
         LEM_TT_EXIST,
         LEM_TT_DEFINT,
         LEM_TT_DEFSTRING,
         LEM_TT_IF,
         LEM_TT_ELSE,
         LEM_TT_BREAK,
         LEM_TT_CONTINUE,
         LEM_TT_SWITCH,
         LEM_TT_DEFAULT,
         LEM_TT_EXTERN,
         LEM_TT_STRUCT,
         LEM_TT_DEFBOOL,
         LEM_TT_CONST,
         LEM_TT_VOLATILE,
         LEM_TT_OARRAY,     // [
         LEM_TT_CARRAY,     // ]
         LEM_TT_CLASS,
         LEM_TT_DEFVOID  
        };

   extern UCString LEM_TOKENS[LEM_NTOKEN];

   const int LEM_N_COMPL_TOKEN=18;
   extern UCString LEM_COMPL_TOKENS[LEM_N_COMPL_TOKEN];

   class Interpreter;

   class Function : lem::NonCopyable
   {
    public:
     VarType ret; // ��� ������������� �������
     lem::Collect< std::pair<VarType,UCString> > args; // ������ ���������� ����������

     Function(void) {}
   };



   /***********************************************************
    ��������� �������� �� ���� ������ Statement::Execute ���
    ����������� ������ ������ ����������� �����������.
   ************************************************************/
   const int LEM_TT_FIRST_PASS    = 0; // ������������� �����: ����� ������ ����������� ����.
   const int LEM_TT_ROUTINE_PASS  = 1; // ��� ������ ������� ������ � ����������� ���� �����.
   const int LEM_TT_CONTINUE_PASS = 2; // ������ ���� ��������� �������� continue.  
   const int LEM_TT_BREAK_PASS    = 3; // ������ ���� ��������� �������� break.

   class Statement
   {
    public:
     Statement(void){}
  
     virtual void operator=( const Statement& s ){}
     virtual bool Execute(
                          UTextParser &txtfile,
                          Interpreter &trans,
                          int flag
                         ) { return false; }
     virtual bool DoesMatch( int t ) const { return false; }
   };

   class ForLoop : public Statement
   {
    private:
     SourceState ini;        // �� �������������.
     SourceState condition;  // �� ������ ����� ������� ����������� �����.
     SourceState change;     // �� ������ ����� ���������, ������������ � ����� ������� �������.
     SourceState begin_body; // �� ������ ���� �����.
     SourceState end_body;   // ��������� �������� ���� (';' ��� '}').
     SourceState end_for;    // ������ �������� ��� �����.

     // ���������...
     ForLoop(void);

    public:
     ForLoop( UTextParser &txtfile, Interpreter &trans );

     virtual bool DoesMatch( int t ) const { return t==LEM_TT_FOR; }
     virtual bool Execute(
                          UTextParser &txtfile,
                          Interpreter &trans,
                          int flag
                         );
   };

   class BeginBlock: public Statement
   {
    public:
     BeginBlock(void):Statement() {}

     virtual bool DoesMatch( int t ) const
     { return t==LEM_TT_BEGIN; }

     virtual bool Execute(
                          UTextParser &txtfile,
                          Interpreter &trans,
                          int flag
                         ) { return false; }
   };

   class IfStatement: public Statement
   {
    public:
     IfStatement(void);

     virtual bool DoesMatch( int t ) const { return t==LEM_TT_IF; }
     virtual bool Execute(
                          UTextParser &txtfile,
                          Interpreter &trans,
                          int flag
                         );
   };

   class BlockStack : public std::stack<Statement*>
   {
    public:
     BlockStack(void);
     void Reduce( UTextParser &txtfile, Interpreter &trans );
     void Break( UTextParser &txtfile, Interpreter &trans );
     void Continue( UTextParser &txtfile, Interpreter &trans );
   };

   extern bool MyUserFunction(
                              const UToken &t,
                              UTextParser &txtfile,
                              Calc::CalcVariable **res,
                              bool *did_return
                             );


   // ���������� �������.
   class FunctionDecl
   {
   };


   class Interpreter
   {
    private:
     Calc::VarTable vars;
     int ret_value; // ��� �������� �� main � ��.
     BlockStack block_stack;

    public:
     Interpreter(void);

     // ����������� ��������� � ��������� �����. ������� ���������� ����� �����������
     // ���������, ���� clear_vars=true
     int Execute( const lem::Path &file, bool clear_vars=true );

     // ���������� ��������� �� ��������� ������
     int Execute( UTextParser &txtfile );

     // ���������� ���������, �������� ������� ������
     int ExecuteText( const wchar_t *progtext );

     VarTable& GetVarTable(void) { return vars; }

     void Stop( UTextParser &txtfile );
     void Expression( UTextParser &txtfile, int add_limiter=LEM_TT_STREND );
     void DeclareForLoop( UTextParser &txtfile );
     void DeclareIf( UTextParser &txtfile );
     void SkipBranch( UTextParser &txtfile, UToken &last );
     void SkipBranch( UTextParser &txtfile );
     int RunExternal( UTextParser &txtfile );
     int OsShell( UTextParser &txtfile );
     int DoesExist( UTextParser &txtfile );
     void PrintTo( UTextParser &txtfile, OFormatter &to );
     void AddToFile( UTextParser &txtfile );
     int DeleteFile( UTextParser &txtfile );
     void Read_Type( UTextParser &txtfile, VarType &type );

   };

   extern Interpreter *translator;

  } // namespace Translator
 } // namespace lem

#endif
