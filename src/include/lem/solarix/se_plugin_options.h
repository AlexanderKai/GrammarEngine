#ifndef PLUGIN_OPTIONS__H
#define PLUGIN_OPTIONS__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  {
   // ����� ��� ���� PluginOptions::flags
   const int PLUGOPT_OCR = 0x00000001; // �������� OCR
  
   // **********************************************************************
   // ��������� ��� �������� ��������� ���������� � ������� ��� ����������
   // � �������� ������.
   // **********************************************************************
   struct PluginOptions
   {
    unsigned short int_count; // ���-�� ���������� �������������� ����
    unsigned short str_count; // ���-�� ���������� ���������� ����
    unsigned short flags;     // ����� ����� ������� (��� �������������)
 
    PluginOptions(void)
    { clear(); }
 
    void clear(void) { int_count = str_count = flags = 0; }
   };
  }
 }

#endif
