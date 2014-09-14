#ifndef SE_LEXER_OPTIONS__H
#define SE_LEXER_OPTIONS__H
#pragma once

 #include <map>
 #include <lem/ucstring.h>
 #include <lem/solarix/se_general_options.h>

 namespace Solarix
 {
  namespace Search_Engine 
  {
    // *************************************************
   // ��������� ����-���� � ������ ���������� ��������
   // *************************************************
   struct Lexer_Options
   {
    // ������ ����-����
    std::multimap< lem::UCString::hash_type, lem::UCString > stopwords_list;
    typedef std::multimap< lem::UCString::hash_type, lem::UCString >::const_iterator SW_ITER; 

    // �������� ������ �� ���������� �����
    void LoadStopwords( const General_Options& generals );

    // ����� �� ������������ ����� (����������� � ������ ����-����)?
    bool IsStopword( const lem::UCString &Word ) const;

    // ������� . ? !
    bool IsSentenceBreak( const lem::UCString &Word ) const;
   };

  }
 }
#endif

