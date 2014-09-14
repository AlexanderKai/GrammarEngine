#ifndef SE_HIT_STATISTICS__H
#define SE_HIT_STATISTICS__H
#pragma once
 
 namespace Solarix
 {
  namespace Search_Engine
  { 

  // *****************************************************************************
  // ���������� �� ��������� ������� - � ��� ������������� �������� � ����������
  // ������������ ������ � �.�.
  // *****************************************************************************
  struct Hit_Statistics
  {
   lem::zeroed<int> hits;    // ������� ���������� �������������
   lem::zeroed<int> files;   // ������� ������ ����������
   lem::zeroed<int> folders; // ������� ��������� ���������� (�� ������ ���������)
   lem::zeroed<int> packs;   // ������� ������� ����������
   lem::zeroed<int> sites;   // ������� ������ ��������������
   lem::zeroed<int> uris;    // ������� ���������� �������� �� ���������
   lem::zeroed<int> pipes;   // ������� ����������� ������� ����������.

   boost::posix_time::ptime started;  // ����� ����� �����
   boost::posix_time::ptime stopped; // ����� ����� ��������

   Hit_Statistics(void) {}

   void clear(void);

   const lem::UFString Get_XML(void) const;
   const lem::UFString Get_HTML(void) const;

   void Started(void);
   void Stopped(void);
   int Elapsed(void) const;

   inline void Success(void) { hits++; }
  };

 }
}

#endif
