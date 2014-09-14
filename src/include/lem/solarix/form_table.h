// -----------------------------------------------------------------------------
// File FORM_TABLE.H
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ������� ������ ��� �������� ��������� ������ � �����������.
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->27.11.2010
// --------------

#ifndef SOL_ENTR__H
#define SOL_ENTR__H
#pragma once

 #include <lem/macros.h>
 #include <lem/containers.h>
 #include <lem/noncopyable.h>

 #include <lem/solarix/WordCoord.h>
 #include <lem/solarix/coord_pair.h>

 #undef AddForm
 #undef GetForm

 namespace lem
 {
  namespace Iridium {
                     class Macro_Parser;
                     class BethToken;
                    } 
  class OFormatter;
  class Stream;
 }

 namespace Solarix
 {
  using lem::Iridium::Macro_Parser;
  using lem::Iridium::BethToken;
  using lem::OFormatter;
  using lem::Stream;
  using lem::IntCollect;

 class Grammar;


 struct WordFormName : lem::NonCopyable
 {
  lem::UCString form_name;
  lem::Collect< std::pair< lem::UCString /*aux_type*/, lem::UFString /*aux_data*/ > > aux;

  void clear(void) { aux.clear(); }

  void AddAux( const lem::UCString &aux_type, const lem::UFString &aux_data );
  bool HasAux(void) const { return !aux.empty(); }
 };


 /********************************************************
  ������� ����� ��� ������ ��������� � ��������� ������.
 *********************************************************/
 class Dictionary;
 class Form_Table
 {
  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadFormName(
                     Macro_Parser & txtfile,
                     Grammar & gram,
                     WordFormName & form_name
                    ) const;
   #endif

  protected:
   int key;  // ���������� ����-������������� ��� ��������� ������ ���
                // �������� ������������� ��� ��� ������� ���������.
                
   int iclass;  // �������������� ����� (��� ������ � ����������), � ��������
                // ��������� ��������� ������ ��� ����� ���������� ��� ������,
                // ���������� ��� ������� ������� ������� ��������� �� �������
                // ���������.

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   bool is_realized; // false, ���� ���� ����������, true, ���� ���� ����������.
   #endif

   #if defined SOL_LOADTXT && defined SOL_COMPILER

   // ����� ������ ���� ���������� ��� �������������� ���������, ����� ���������
   // ������������ ������������ ���� ���� ����������:* � ���������� ����������.
   virtual bool StoreQuantors(void) const { return false; }

   virtual void BeforeFirstForm( Grammar& gram );
   virtual void Loaded( const Dictionary &dict );
   bool LoadAttribute( Macro_Parser &txtfile, Grammar& gram );
   void LoadForm(
                 Macro_Parser& txtfile,
                 Grammar& gram,
                 CP_Array &common,
                 const GramCoordAdr Do_Autoload,
                 int iDoAutoload,
                 const GramCoordAdr Indexing,
                 int iIndexing,
                 int AllQuantor
                );

   void LoadFormsGroup(
                       Macro_Parser& txtfile,
                       Grammar& gram,
                       CP_Array &dim,
                       const GramCoordAdr do_autoload,
                       int iDoAutoload,
                       const GramCoordAdr indexing,
                       int iIndexing,
                       int AllQuantor
                      );

   void AddForms(
                 CP_Array &dim,
                 const WordFormName& form_name,
                 const GramCoordAdr do_autoload,
                 int iDoAutoload,
                 Grammar& gram
                );

   #endif

   void Init( const Form_Table& ft );

  protected:
   CP_Array attr; // ������ ������������ ��� ���������.

   virtual Grammar& GetGrammar( Dictionary &dict )=0;
   virtual const Grammar& GetGrammar( const Dictionary &dict )=0;

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual bool ProcessSection(
                               Macro_Parser &txtfile,
                               Grammar &gram,
                               const BethToken &t
                              ) { return false; }

   virtual void LoadName(
                         Macro_Parser &txtfile,
                         Dictionary &dict
                        ) {}

   virtual void LoadBody( Macro_Parser &txtfile, Grammar &gram );

   virtual void AddForm(
                        const CP_Array& dim,
                        const WordFormName& form_name,
                        Dictionary &dict
                       );

   virtual void ReadAdditionalInfo( Grammar &gram, int iForm, Macro_Parser& txtfile ) {}

   #endif

   #if defined SOL_SAVETXT
   virtual bool DoSaveAttrTxt( int iattr, const Grammar &gram ) const;
   void SaveCoordinatesTxt(
                           OFormatter& txtfile,
                           const Grammar& gram
                          ) const;
   #endif

  public:
   Form_Table(void);
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   Form_Table(
              Macro_Parser& txtfile,
              Grammar& gram,
              bool IsRealized
             );
   #endif

   Form_Table( lem::Stream& bin );
   Form_Table( const Form_Table& e );

   virtual ~Form_Table(void) {}

   void operator=( const Form_Table& e );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual int CountForms(void) const=0;
   #endif

   inline int GetKey(void) const { return key;    }
   inline int GetClass(void)  const { return iclass; }

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void LoadTxt(
                Macro_Parser &txtfile,
                Grammar& gram,
                bool IsRealized
               );
   #endif

   /*****************************************************************
    ������ ������ ������������� �������� ���������� �����.
    ��� ������� ��� ����, ����� ���������� ��������� ������ � ������
    ���������� �� ������ �� ������� �������.
   ******************************************************************/
   inline void SetKey( int NewKey ) { key=NewKey; }

   #if defined SOL_SAVEBIN
   void SaveBin( lem::Stream& bin ) const;
   #endif

   void LoadBin( lem::Stream& bin );

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   inline bool IsRealized(void) const { return is_realized; }
   inline void HasBeenRealized(void) { is_realized=true; }
   #endif

   inline const CP_Array& attrs(void) const { return attr; }
   inline CP_Array& attrs(void) { return attr; }

   void SetAttr( const Solarix::GramCoordPair &p );   

   /*******************************************************
    ���������� ��������� ������ �������� � ������ ������.
    ���� ������� �� ������, �� ���������� UNKNOWN
   ********************************************************/
   inline int GetAttr( const GramCoordAdr id_attr ) const
   { return attr.FindTwice(id_attr); }

   // ������������ ��������� ��� ��������� ��������.
   // ���� ������� �� ������, �� ���������� UNKNOWN
   int GetAttrState( const GramCoordAdr id_attr ) const;
   const IntCollect GetAttrStates( const GramCoordAdr id_attr ) const;

   virtual void PrintName( OFormatter &/*dst_stream*/ ) const {}
 };

 /*************************************************************
  ������� ����� ��� �������� ��������� ������ ���� ���������.
 **************************************************************/
 class Base_Entry : public Form_Table
 {
  private:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   void CheckAttr( Macro_Parser& txtfile, Grammar& gram );
   void LoadTxtEx( Macro_Parser& txtfile, Grammar& gram );
   virtual void SkipNetSection(
                               Macro_Parser &txtfile,
                               Grammar &gram
                              ) {}
   #endif

   void Init( const Base_Entry& e );

  protected:
   #if defined SOL_LOADTXT && defined SOL_COMPILER
   virtual void BeforeFirstForm( Grammar& gram );
   virtual bool ProcessSection(
                               Macro_Parser &txtfile,
                               Grammar &gram,
                               const BethToken &t
                              );

   /***********************************************************************
    ������ ����� ������ ���� ���������� ����������� �������. �� ����������
    "�����" ��� �������� ����� ������.
   ***********************************************************************/
   virtual void LoadName(
                         Macro_Parser& txtfile,
                         Dictionary &dict
                        ) {}

   virtual void LoadBody( Macro_Parser &txtfile, Grammar &gram );
   #endif

  public:
   Base_Entry(void);

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   Base_Entry(
              Macro_Parser& txtfile,
              Grammar& gram,
              bool IsRealized
             );
   #endif

   Base_Entry( lem::Stream& bin );

   virtual ~Base_Entry(void) {}

   #if defined SOL_LOADTXT && defined SOL_COMPILER
   /*********************************************************************
    ����� ������� ������� ������ ����������� ���������� � ���������
    ����� ������� ����� ������������ �������� ������ ������, � ������� -
    ��� ���������� ������ ������ �� ������ ������. ����� ������� ������
    ���� ������� ������� ������ ����������� ����������������� �� ������
    ������� ��������� ����� ������� � ������ ����������.
   ***********************************************************************/
   virtual void AfterFirstRead(void) {}
   #endif

   /***********************************************************
    ����� ���������� ��� ������ ����� ������ � ��������� �����.
   ************************************************************/
   virtual void PrintName( OFormatter &/*dst_stream*/ ) const {}
 };

 } // namespace 'Solarix'

#endif
