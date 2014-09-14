#ifndef ITAG_STREAM__H
#define ITAG_STREAM__H
#pragma once

 namespace Solarix
 {
  namespace Search_Engine
  {
   // *******************************************************************
   // ��������� ��� �������� �������-�����������, � ������� ������������
   // ����� ����������� �� ����� �����.
   // *******************************************************************
   class ITagStream
   {
    public:
     ITagStream(void) {}
   
     virtual void WriteTag( const UFString &Param, const UFString &Value )=0;
   };
  }
 }
#endif

