#ifndef SE_ACTION_OPTIONS__H
#define SE_ACTION_OPTIONS__H
#pragma once

 #include <lem/ufstring.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/tuple.h>
 #include <lem/solarix/se_data_miner.h>
 #include <lem/solarix/se_hit_statistics.h>

 namespace Solarix
 {
  namespace Search_Engine
  { 
   class File_Location;
   class Fix_Context;
   struct Query;
   struct Pattern;

   class Base_DataSet_Printer;
   class Base_Report;

  // ����� ��� ������������ �����������.
  struct Action_Options : boost::noncopyable
  {
   lem::UFString command; // ����������� ������� - ������� {} ���������� �� ��� �����
   bool confirm;          // ��������� �� ������������� ����� ������ �����������

   Base_DataSet_Printer *res_dataset; // ������������� ����� ����������� (Result DataSet)
                                      // ����� ���� ������ ���� ������ ����������� ������
                                      // � ����� ������ �������� ��� �������� �����������
                                      // ������� ���������. 


   #if defined FAIND_AWK  
   Base_DataSet_Printer *awk; // ���������� AWK-��������
   #endif

//   int hit_count; // ������� ��������� ����������

   Hit_Statistics hit_count;
   
   lem::UCString sort_field; // �� ������ ���� ���������� �����������
   lem::zeroed<bool> sort_desc; // ����������� � ������� ��������
   lem::MCollect< lem::triple< lem::UFString* /*ZoneName*/, File_Location*, Fix_Context* > > to_sort;

   lem::zbool subst_shares; // � ����� ���������� ������ �������� ��������� ����� �� ������� ����
   lem::zbool got_shares;
   lem::Collect<lem::UFString> shares;
   lem::Collect<lem::UFString> sh_folders;
   void GetLocalShares(void);
   File_Location SubstShares( const File_Location &file );


   #if defined FAIND_REPORTS
   lem::MCollect< Base_Report* > reports; // ������ ����������� �������
   #endif

   #if defined FAIND_DATAMINE
   lem::PtrCollect< Base_DataMiner > miners; // �������������� ����������
   #endif

   Action_Options(void);
   
   ~Action_Options(void);

   void clear(void);

   // ������ ������ - �������� � �������
   void Print_DataSet( const Query &q );
   void Print_DataSet( const lem::MCollect<Pattern*> &qlist );

   // � ���� ������ - ������ ��������� ��������
   void Print_DataSet(
                      const wchar_t *ZoneName,
                      const File_Location &file,
                      const Fix_Context *ctx
                     );

   // ����� �������� - ���������� ������ ����� � ��������� �������� �����������
   void Print_DataSet( const Hit_Statistics &hits, const Query &q );

   bool CanShowRawFileList(void) const;
   void PrintRaw( const wchar_t *ZoneName, const File_Location &where );

   void PrintSimple( const UFString &str, const UFString &format );
  };
 }
}
#endif

