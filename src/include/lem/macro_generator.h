// -----------------------------------------------------------------------------
// File MACRO_GENERATOR.H
//
// (c) Koziev Elijah
//
// Content:
// ������ ��� ���������� ������� ��.
// -----------------------------------------------------------------------------
//
// CD->01.02.2004
// LC->23.04.2007
// --------------

#pragma once
#ifndef LEM_MACRO_GENERATOR
#define LEM_MACRO_GENERATOR

 #include <set>

 #include <lem/config.h> 
 #include <lem/oformatter.h>
 #include <lem/fstring.h>
 #include <lem/sql_parser.h>
 #include <lem/string_parser.h>
 #include <lem/stl.h>
 #include <lem/db.h>

 #if defined LEM_DOT_NET
 #include <vcclr.h>
 using namespace System;
 #endif


 namespace lem
 {
  namespace Macro_Generator
  {
   class Macro_Formatter;
   class Macro_Frame;

   using lem::StrParser;
   using lem::FString;
   using std::vector;
   using lem::Database::SQL_Data_Source;

  // *************************************************
  // ������������������ ������ ��� �������� ��������.
  // �������� � 1-��������� ���������, ������� ��
  // ���������� � �����.
  // *************************************************
  class A_Parser : public StrParser<FString>
  {
   public:
    A_Parser( const FString &Txt ) : StrParser<FString>(Txt)
   {
    // ����� �������� �� �������� ������������� ��� ������� �������.
    delims = remove_chars( delims, "${}" );
   }
  };


   // *************************************************************************
   // ��������� ��� �������� �� �������� ���������� ��������������� - ��������,
   // ��� ���������� ���������� BREAK � CONTINUE ������ �����.
   // *************************************************************************
   struct Execution_Flow
   {
    typedef enum { NORMAL, BREAK_LOOP, CONTINUE_LOOP } STATUS;
    STATUS status;

    Execution_Flow(void) { status=NORMAL; }
   };


   // ����������� ���������� - ���������, ����� � ������ ��������������
   // ����������� �������� ������ �������, ���� � ������� �� ����.
   class E_MG_Alien_Command : public E_ParserError {};


   // ***********************************
   // ������� ����� ��� ������������. ���
   // ����������� ����������� �����������
   // �� ����� ������.
   // ***********************************
   class Base_Command
   {
    protected:
     FString name; // ��� ������������ (��� ����������� �������-��������
                   // ������������, �������� '$'). ��� ���� ����������������
                   // � ������������ ������������ ������, � ����� ������������
                   // �������� ��� ������ ����������� � ������.

     Base_Command( const Base_Command& );
     void operator=( const Base_Command& );

    public:
     Base_Command( const char *Name ):name(Name) {};
     virtual ~Base_Command(void) {};

     inline bool operator==( const FString &Name ) const
     { return name==Name; }

     inline const FString& Get_Name(void) const { return name; }

     // *****************************************************************
     // ����� ������ ����������� ������ - ���������������� � �����������
     // ��� ���������� ������ ���������� ������������.
     // *****************************************************************

     // **********************************************************************
     // ����������� ��� ����������� ������������ - �� ���� �� ���� (��������,
     // ��� ����� - ���������� �����, ��������� ��������, ���� �����). ���
     // ���������������� ���������� ������������ ������ ��� �� �����������
     // �� ������ �������, � ������������ ����������� � ���� ������.
     // **********************************************************************
     virtual bool LoadHead( A_Parser &txt, int i_start )=0;

     // ***************************
     // ���������� ������������.
     // ***************************
     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      )=0;

     // ******************************************
     // ����������� ����������� - ������� ����.
     // ******************************************
     virtual Base_Command* New(void) const =0;
   };


   // ***************************
   // ���������� ��� FOR-�����
   // ***************************
   class For : public Base_Command
   {
    protected:
     FString var;      // ��� ���������� �����
     FString iterator; // ����� ������ �����������
     int begin;
     int body_pos;     // ������� ������� ������� ���� �����
     int n0;           // ��������� �������� ���������
     int n_pass;       // ������� �������� �����
     int i_pass;       // ������� �������� ���������� �����
     vector<FString> sn; // ������ ����������� ���������� ��������.

    public:
     For(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_start );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class If : public Base_Command
   {
    private:
     FString condition; // �������

     int if_begin;      // ������ ���������
     int then_begin;    // ������ then-�����

     int Get_Priority( const FString &com ) const;
     FString Parse_Expression( A_Parser &txt, int &i_cur );

    public:
     If(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class Break : public Base_Command
   {
    public:
     Break(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *************************************************************************

   class Continue : public Base_Command
   {
    public:
     Continue(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // ******************************************************************

   class Correlator : public Base_Command
   {
    private:
     FString word;   // ���������� �����
     int    value;   // �����, � ������� ���������
     int    l_case;  // �������������� �����
     int beg, end;   // ������ � ����� ���������end - ������ ����� ')'

    public:
     Correlator(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // *****************************************************
   // ��������������� ����� � ����������� �������������
   // *****************************************************
   class Convertor : public Base_Command
   {
    private:
     int    value; // �����
     int beg, end; // ������ � ����� ��������� end - ������ ����� ')'

    public:
     Convertor(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // **********************************************************************
   // ��������������� ��������������� ��������� � ����������� �������������
   // **********************************************************************
   class Calculator : public Base_Command
   {
    private:
     FString expr;
     int beg, end;

    public:
     Calculator(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Call : public Base_Command
   {
    private:
     FString proc;   // ��� ���������� PL/SQL ���������

     // ��������� ������ ���������
     std::vector< std::pair< FString /*name*/, FString /*value*/ > > args; 
     int beg, end;

    public:
     Call(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Odbc : public Base_Command
   {
    private:
     FString alias, login, psw;

     int beg, end;

    public:
     Odbc(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Define : public Base_Command
   {
    private:
     FString var;   // ��� ������������ �������
     FString value; // ����������

     int beg, end;

    public:
     Define(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Ask : public Base_Command
   {
    private:
     FString var;      // ��� ������������ �������
     FString question; // ������������ ������

     int beg, end;

    public:
     Ask(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };



   class Subst : public Base_Command
   {
    private:
     FString str;     // ������������� ������
     FString pattern; // ������� - ��� ������
     FString new_str; // �� ��� ������
     int beg, end;    // ������ � ����� ��������� - ������ ����� ')'

    public:
     Subst(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };

   // ********************************************** 
   // ���������� ������� ������������������ ������.
   // ********************************************** 
   class Format : public Base_Command
   {
    private:
     FString str; // ������������� ������
     FString fmt; // ������
     int beg, end;    

     FString i_fmt; // ����� ������� ��� ����� �����
     FString f_fmt; // ����� ������� ��� ������� ����� 
     int f_count;   // ������� ������ � ������� ����� ���� �������.
     char f_dot;    // ���������� ������� �����

    public:
     Format(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   // ***************************************************************

   // ***************************************************************

   class Sql_Select : public Base_Command
   {
    private:
     string add_front, add_back; // �������, ����������� � ����� ��������

     int beg, end;
     int body_beg, body_end;   // ���� ���� ���� ��������� $BEGIN ... $END
     FString sql;              // ����������� SELECT
     vector<FString> options;  // ������ ����� ��������������
     lem::Sql_Parser::Sql_Select *parsed_sql;

    protected:
     void Prepare_Macro_Name( string &macro_name ) const;

    public:
     Sql_Select(void);

     Sql_Select( const Sql_Select &x );
     void operator=( const Sql_Select &x );

     virtual ~Sql_Select(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );

     void Add_Macro_Front( const char *s ) { add_front=s; }
     void Add_Macro_Back( const char *s ) { add_back=s; }
   };

   // *************************************************************************

   class Group : public Base_Command
   {
    private:
     int group_beg, body_beg, body_end, outside_beg;

    public:
     Group(void);

     virtual Base_Command * New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Print : public Base_Command
   {
    private:
     int beg, end;
     FString text; // ����� ��� ������ �� �������

    public:
     Print(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };


   class Debug : public Base_Command
   {
    private:
     int beg, end;
     FString text; // ����� ��� ������ � ������

    public:
     Debug(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };

   class Reinterpret : public Base_Command
   {
    private:
     int beg, end;

    public:
     Reinterpret(void);

     virtual Base_Command* New(void) const;

     virtual bool LoadHead( A_Parser &txt, int i_cur );

     virtual void Exec(
                       FString &txt,
                       Macro_Frame &macros,
                       Macro_Formatter &ruler,
                       Execution_Flow &flow
                      );
   };



   // ***************************************************************
   // ������� ��������: ������ ������� ���� ������ � ����� �� �����
   // ������� ��������� C++-������.
   // ***************************************************************
   class Cmd_Factory
   {
    protected:
     vector<Base_Command*> cmd_list; // ������ ������������ ������
     bool case_sensitive; // ��������� ������� �������� ��� ������ ������

    public:
     Cmd_Factory(void);
     virtual ~Cmd_Factory(void) { ZAP_A(cmd_list); }

     virtual Base_Command* Find( const FString &Txt ) const;

     inline void Case_Sensitive(void) { case_sensitive=true; }
   };


   // **************************************************************


   // *************************************************************************
   // ��������� ������� ��������. ������ - ��� ������ ���� ����� ���-��������.
   // *************************************************************************
   class Macro_Frame : public vector< std::pair<FString/*name*/,FString/*value*/> >
   {
    private:
     std::set<char> first_chars;
     Macro_Frame *prev;

     std::pair<FString,FString>* Find_Macro( const FString &name );

     Macro_Frame( const Macro_Frame& );
     void operator=( const Macro_Frame& );

     void push_back( const std::pair< FString, FString > & ); // blocked!

    public:
     Macro_Frame( Macro_Frame *Prev=NULL ) { prev = Prev; }

     // *********************************************************************
     // � ������ �������� ����������� ������� � ������ name
     // ����� ��������. ���� ������ ������� ���, �� ��������� ���.
     // *********************************************************************
     bool Set_Macro( const FString &name, const FString &value );
     void Subst_Macros( FString &txt );

     void Rescan(void);
   };


   // *****************************
   // ����� ����� ���������� - ��� ������ ���� ����� ��������������
   // � ��������� ���������.
   struct Exec_Options
   {
    bool show_alert; // � ������ ������������� ������ - ����������
                     // �� ������ MessageBox.
    FString error_stamp; // ���������, ����������� � �����, ��� �������������
                         // ������

    Exec_Options(void)
    {
     show_alert=false; 
     error_stamp = "#error#";
    }
   };


   // ************************************************************************

   class Macro_Formatter
   {
    private:
     FString *text; // �������������� ������ (���������� � ���� ������).
     OFormatter *console; // ��������� ��� ������ ��������� ��������� �� �������
     SQL_Data_Source* db;

    protected:
     Exec_Options exec_flags;
     Cmd_Factory *cmd_factory;

    public:
     inline void Set_DB( SQL_Data_Source* Db ) { db=Db; }
     inline SQL_Data_Source* Get_DB(void) { return db; }

     Macro_Formatter( FString *Text=NULL );

     virtual void Build_Commands(void);

     virtual void Set_Console( OFormatter *Console );
     inline OFormatter* Get_Console(void) { return console; }

     virtual ~Macro_Formatter(void);

     void Interpret(
                    FString &txt,
                    Macro_Frame &macros,
                    Execution_Flow &flow
                   );

     void Interpret( FString *Text=NULL );

     inline const Cmd_Factory& Get_Cmd_Factory(void) const { return *cmd_factory; }

     inline const Exec_Options& get_Exec_Flags(void) const { return exec_flags; }
   };

 } // namespace macro_generator

} // namespace lem


#endif
// ------------------------- End Of File [MACRO_GENERATOR.H] -------------------