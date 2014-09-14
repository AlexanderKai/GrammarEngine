#ifndef SE_GENERAL_OPTIONS__H
#define SE_GENERAL_OPTIONS__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/path.h>
 #include <lem/containers.h>
 #include <lem/zeroed.h>

 namespace Solarix
 {
  namespace Search_Engine
  {

   struct ResultPageTemplate
   {
    lem::zbool use;

    lem::UFString header;

    lem::UFString query_form; // ����� ��� ����� ��������

    lem::UFString hits_begin; // ���� ����� ������� ������ ����������� ������
    lem::UFString row; // ���������� ������ ���� � ������ �����������
    lem::UFString hits_end; // ���� ����� ������ ����������� ������

    lem::UFString stat; // ������ ��� ������ ���������� ������
   };

   // **********************************************************
   // ������ ������ �����, �������� �� ������ ��������� ������
   // � �����, �������� - ���� � ������ � �������� ������������.
   // **********************************************************
   struct General_Options : lem::NonCopyable
   {
    lem::Path prog_path; // ������� (������ ���������� ����), � ������� ��������� exe
    lem::Path raw_reader_kb; // ���� � ����� ������ ��� Raw Reader'�
    lem::zbool needs_dictionary;   // ����� ��������� �������
    lem::zbool needs_thesaurus;    // ����� ��������
    lem::zbool lemmatizer_only;    // ���� �� ��������� ������� ����� ������ ������������
    lem::zbool needs_classifier;   // ����� ���������������� ����������
   
    lem::Path work_dir; // �������� ������� ������� (��� ���������� �������,
                        // ������ ������� � �.�.)

    // ���� � ������ ����������� �������
    lem::Path dictionary_filename;
    lem::Path stopwords_filename;
    lem::Path log_filename;
    lem::Path topic_db_files; // ���� � �������� � ������� ���� �����������
    lem::Path ini_path; // ���� � �����, �� �������� ������� ������������

    lem::UFString dict_langs_str; // ������ ������, ��� ������� ����������� ��������� � �.�.
    lem::MCollect<lem::UCString> dict_langs;

    lem::zbool allow_plugins; // ��������� �� �������� � ������������� ��������
    lem::Path plugins_path; // ����� ���� � ��������
    bool append_plugin_subfolders; // ���� ������� � ����������� �� ���� ����� ������ � ...\formats, ...\media � ��� �����

    lem::zbool save_files; // ����� �� ��������� ����� �������, ��������� �����
                                  // � ��������� ����������� � �.�. (��� ������ �� ������).

    lem::zbool start_httpd;  // ��������� HTTP ������ ��� ������������ �������� �� ��������
    lem::FString httpd_ip; // �� ����� ���������� ��������� HTTPD
    lem::zeroed<int> httpd_port; // �� ����� �����

    ResultPageTemplate result_page; // ������ ��� ������������ �������� ����������� ������ ���-��������
    lem::UFString hidden_query_fields; // ������� ���� �� ����� ���������� �������

    bool use_text_cache; // ������������ ��� ������ ��� ���������� ����������� ���������� ������ � ������� OCR

    General_Options(void); 

    inline bool All_Languages(void) const { return dict_langs_str==L'*'; }

    inline bool Accept_Language( const lem::UCString &lang ) const
    {
     return All_Languages() ||
            std::find( dict_langs.begin(), dict_langs.end(), lang )!=dict_langs.end(); 
    } 
   }; 

  }
 }
#endif
