#ifndef SE_TEXT__H
#define SE_TEXT__H
#pragma once

 #include <lem/math/fp1.h>
 #include <lem/solarix/file_factory.h>
 #include <lem/solarix/form_table.h> 
// #include <lem/solarix/phrasoblock.h> 

 namespace Solarix
 {
  namespace Search_Engine
  {
   using lem::MCollect;
   using lem::Real1;
   using lem::UFString;

  // ******************************
  // ���������� �������� �������
  // ******************************
  struct Lexem_Projs
  {
   private:
    Lexem_Projs( const Lexem_Projs& );
    void operator=( const Lexem_Projs& );

   public:
    MCollect<Word_Coord> found_list;
    MCollect<Real1> val_list;

    Lexem_Projs(void) {};
  };

 // ***********************************
 // ��� ������� ����� ����� �����, ���
 // � ����� ��� ���� �����������.
 // ***********************************
 struct File_Lexem : public Solarix::Search_Engine::Base_File_Lexem
 {
  int sent_number;       // ����� �����������, � �������� ����������� �����
//  UCString uppered_word; // ����� � ������� ��������
  Lexem_Projs *projs;    // �������� ������� �� �������� (NULL, ���� �������� �� �������)

  File_Lexem(void)
  {
   sent_number=UNKNOWN;
   projs = NULL;
  } 
 };



  // *************************************************************
  // ���� ����������� ������. ������ �� ���� �����, � ������� ����
  // � ����������� ������.
  // *************************************************************
  struct Sentence
  {
   int number;     // ���������� ����� � ������
   int from, upto; // �������, �������� � �����������.

   #if !defined SOL_NO_AA
//   Solarix::PhrasoBlock *fblo; // ��������� ��������������� �������. ������� �� ��.
   #endif

   Sentence(void)
   {
    number=UNKNOWN;
    from=upto=UNKNOWN;

    #if !defined SOL_NO_AA
//    fblo=NULL;
    #endif
   }

   // ���������� ����� ���� � �����������
   inline int length(void) const { return upto-from+1; }
  };


  // ***********************************
  // ���� ����������� ����� ���������.
  // ***********************************
  class Text
  {
   private:
    Text( const Text& );
    void operator=( const Text& );

   public:
    UFString whole_text; // ����� � ���� ����� ������
    MCollect<File_Lexem> lexems; // �������� �� ������� �����
    MCollect<Sentence> sent; // �����������

    MCollect<Lexem_Projs*> projs; // �������� ��� ������

    #if !defined SOL_NO_AA
//    MCollect<Solarix::PhrasoBlock*> fblos; // ���������� - ���������� ���������������
                                           // ������� �����������. 
    #endif

    bool loaded; // ���� �� �������� ������� ��������� �����

    Text(void)
    {
     loaded=false;

     projs.reserve(1024);

     #if !defined SOL_NO_AA
     //fblos.reserve(1024);
     #endif

     lexems.reserve(1024);
     sent.reserve(128);
    }

    ~Text(void)
    {
     ZAP_A(projs);
     #if !defined SOL_NO_AA
//     ZAP_A(fblos);
     #endif
    }
  };

 } // namespace Search_Engine
 } // namespace Solarix

#endif
