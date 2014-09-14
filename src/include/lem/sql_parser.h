#ifndef LEM_SQL_PARSER
#define LEM_SQL_PARSER
#pragma once

 #include <vector>
 #include <string>

namespace lem
{
 namespace Sql_Parser
 {
  using std::vector;
  using std::string;

  // ***************************************************************

  // ******************************************************
  // ������� ����� ��� ����� ����������� SQL-������.
  // ******************************************************
  class Sql_Command
  {
   private:
    Sql_Command( const Sql_Command& );
    void operator=( const Sql_Command& );

   public:
    Sql_Command(void) {};
    virtual ~Sql_Command(void) {};
  };


  // ***************************************************************

  class Sql_Select : public Sql_Command
  {
   public:
    string sql_genuine;      // �������� ��� ������������� ���������
    vector<string> col_name; // ������������ ����� ��������
    vector<string> extract_cols; // ����������� ������� (����� ����� ��� �����
                             // ������� �����������).
    vector<string> vars;     // ������ ����������� ���������� �� INTO ...
    int n_col;               // ����� ����������� �������� (����������������,
                             // ���� ���� ������� �� �����������).

    vector<string> from;     // ��������, ������������� � FROM                           

    string xml_source_file; // �� ����� ����� ������ �������� ������ XML

   public:
    Sql_Select( const char *text ) { n_col=0; Parse(text); }
    virtual void Parse( const char *text );
  };

  // ***************************************************************

  class Parser
  {
   public:
    Parser(void) {};

    virtual Sql_Command* Parse( const char *text );
  };

 } // namespace Sql_Parser
} // namespace lem

#endif
