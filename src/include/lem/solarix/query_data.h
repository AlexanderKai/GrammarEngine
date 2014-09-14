#ifndef FAIND_QUERY_DATA__H
#define FAIND_QUERY_DATA__H
#pragma once

 #include <stdlib.h>

 namespace Solarix
 {
  namespace Search_Engine
  {
   struct Scan_Options;
   struct Search_Options;

   struct Query_Data
   {
    int required_action; // 0 - continue with unchanged query,
                         // 1 - query is changed, continue searching

    const wchar_t *pattern; // �������� ����� �������.
    const Scan_Options *scanning; // �������� ������� ������
    const Search_Options *flags; // ����� ��������

    wchar_t *assign_pattern; // ��������� ����������� �������, ��������� ������������� ������� ������ Free � �������

    Query_Data(void)
    {
     required_action=0;
     pattern=NULL;
     scanning=NULL;
     flags=NULL;
     assign_pattern=NULL;
    }
   };

  }
 }


#endif
