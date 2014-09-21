// -----------------------------------------------------------------------------
// File MS_DICT.H
//
// Copyright:    Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//               Yhem High Tech Software
//
// Content:
// ������������ - ���������� ���������� ������ ������� ��� ������������� �
// �������� ���������� ������������� ���������� ��������� (� ����� ������
// ������������ ��������� � ��� �����). ����������� ���������� � ��� �������
// ������ �������� � �.�.
// -----------------------------------------------------------------------------
//
// CD->07.03.1997
// LC->23.04.2007
// --------------

#ifndef SOL_MS_DICT__H
#define SOL_MS_DICT__H
#pragma once

 #include <vector>
 #include <map>
 
 #include <lem/cstring.h>
 #include <lem/fstring.h>
 #include <lem/unicode.h>
 #include <lem/quantors.h>
 #include <lem/runtime_checks.h>


 namespace lem
 {
  namespace Micro_Solaris
  {

 // ������������� ����� ��� ����������� ��������������� ���������
 // ���������� ��� �������� � ������ ������.

 // ���.
 enum {
       MASCULINE_GENDER,    // �������
       FEMININE_GENDER,     // �������
       NEUTER_GENDER        // �������
      };

 // �����.
 enum {
       NOMINATIVE_CASE,     // ������������
       GENITIVE_CASE,       // �����������
       INSTRUMENTAL_CASE,   // ������������
       ACCUSATIVE_CASE,     // �����������
       DATIVE_CASE,         // ���������
       PREPOSITIONAL_CASE   // ����������
      };

 // ������� ��������������
 enum {
       ANIMATIVE_FORM,      // ������������
       INANIMATIVE_FORM     // ��������������
      };

 // �����.
 enum {
       SINGULAR_NUMBER,     // ������������
       PLURAL_NUMBER        // �������������
      };

 // ����� ����.
 enum {
       NOUN_PART,           // ��� ���������������
       ADJECTIVE_PART       // ��� ��������������
      };


 /************************************************************
  ������� ���������������� - ������� ��������� ��������� ���
  �������� ����������������.
 ************************************************************/
 class MS_Declension
 {
  private:
   int code;      // �������� ��� ���������, �� ������� ��������� ��������� ������.
   int part;      // ����� ����, ��� ������� �������� �������.

   int anim;      // ������� ��������������
   int gender;    // �������������� ���

   int to_reduce; // ����� ���������� �������� ������� (� ������������
                  // ����������� ������� �����).

   std::vector<UCString> affix; // ������ ��������.

   MS_Declension( const MS_Declension & );
   void operator=( const MS_Declension & );

  public:
   MS_Declension(void)
   {
    code=part=anim=gender=UNKNOWN;
    to_reduce=0;
   }

   MS_Declension(
                 int Code,
                 int Part,
                 int Anim,
                 int Gender,
                 int To_Reduce,
                 const char *Affices,
                 lem::CodeConverter &cp
                );

   inline int GetCode(void) const     { return code;      }
   inline int GetToReduce(void) const { return to_reduce; }
   inline int GetPart(void) const     { return part;      }

   inline int GetAnim(void) const
   { LEM_CHECKIT_Z(part==NOUN_PART); return anim; }

   inline int GetGender(void) const
   { LEM_CHECKIT_Z(part==NOUN_PART); return gender; }

   inline const std::vector<UCString>& affices() const { return affix; }
 };


 /********************************************
   ����� ��� ������������� ��������� ������.
 *********************************************/
 class MS_Entry
 {
  private:
   UCString word; // ����������� ���������� ������� ����� ���������.
   int decl;      // �������� ������ ������� ���������.

   std::vector<UCString> form; // ���������� ��� "������������" ���������������,
                               // � ���������� ��������� �������� ��� ������
                               // ���������� �� �������.

   MS_Entry( const MS_Entry & );
   void operator=( const MS_Entry & );

  public:
   MS_Entry(void) { decl=UNKNOWN; }

   MS_Entry( int Decl, const char *Root, CodeConverter &cp );

   // �������� �����
   inline const UCString& GetWord(void) const { return word; }

   // ��� ���������
   inline int GetDecl(void) const { return decl; }

   // ������ ���������
   inline const std::vector<UCString>& forms(void) const { return form; }
 };



 /***************************************************************************
  ������� - ������ ��������� ������ (��������) � ������ ���������(���������).
 ****************************************************************************/
 class MS_Dictionary
 {
  protected:
   // Maps are born to be used for dictionary...
   std::map< int /*id_decl*/, MS_Declension* /*T*/ > decl;
   std::multimap< lem::uint8_t /*hash*/, MS_Entry* /*T*/ > entry;

   const MS_Declension* FindDecl( int Decl ) const;
   const MS_Entry* FindWord( const UCString &word ) const;

  public:
   MS_Dictionary(void) {};
   virtual ~MS_Dictionary(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;

   virtual const UFString Correlate(
                                    const UCString &word1,
                                    const UCString &word2,
                                    int value,
                                    int Case
                                   ) const;

  virtual const UFString Correlate(
                                   const UCString &word1,
                                   const UCString &word2,
                                   int value
                                  ) const;

   virtual int GetGender( const UCString &word ) const;
   
   int GetAnim( const MS_Entry &e ) const;
   int GetGender( const MS_Entry &e ) const;
   int GetPart( const MS_Entry &e ) const;

   // ****************************************************************
   // ������������� � ����������� �������� �����: �� ����������
   // ������������� ������ ���������� ��� ���.
   // ****************************************************************
   virtual int ParseCase( const char *Case ) const { return NOMINATIVE_CASE; }

   // ��� ��������� ����� ���� ���������� ������ ������� �� ����������
   // ������ ������� ������ MS_Declension ��� ��������� ��������������
   // ���������.
   virtual int GetAffix(
                        int Part,
                        int Case,
                        int Number,
                        int Gender,
                        int Anim
                       ) const { return 0; }
 };


 // **********************************************
 // ������� ��� �������� �����
 // **********************************************
 class RusDict : public MS_Dictionary
 {
  private:
   const UCString Correlate_All(
                                const UCString &word,
                                int factor,
                                int Case,
                                int Gender,
                                int Anim,
                                int Part
                               ) const;

   const UCString Correlate_Nom(
                                const UCString &word,
                                int factor,
                                int Gender,
                                int Anim,
                                int Part
                               ) const;

   const UCString Correlate_Instr(
                                  const UCString &word,
                                  int factor,
                                  int Gender,
                                  int Anim,
                                  int Part
                                 ) const;

   const UCString Correlate_Accus(
                                  const UCString &word,
                                  int factor,
                                  int Gender,
                                  int Anim,
                                  int Part
                                 ) const;

  public:
   RusDict(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;

   virtual const UFString Correlate(
                                    const UCString &word1,
                                    const UCString &word2,
                                    int value,
                                    int Case
                                   ) const;

   virtual int FindGender( const UCString &word ) const;

   virtual int ParseCase( const char *Case ) const;

   virtual int GetAffix(
                        int Part,
                        int Case,
                        int Number,
                        int Gender,
                        int Anim
                       ) const;
 };


 // **********************************************
 // ������� ��� ����������� �����
 // **********************************************
 class EngDict : public MS_Dictionary
 {
  private:
   virtual int GetAffix( int Part, int Case, int Number, int Gender, int Anim ) const;
   virtual int ParseCase( const char *Case ) const;

  public:
   EngDict(void);

   virtual const UCString Decline(
                                  const UCString &word,
                                  int Case,
                                  int Number,
                                  int Gender=MASCULINE_GENDER,
                                  int Anim=INANIMATIVE_FORM
                                 ) const;

   virtual const UCString Correlate(
                                    const UCString &word,
                                    int value,
                                    int Case=NOMINATIVE_CASE,
                                    int Gender=MASCULINE_GENDER,
                                    int Anim=INANIMATIVE_FORM
                                   ) const;
 };


  // ��������� ��������� ������� ��� ������ � �������.
  extern RusDict ms_rus;
  extern EngDict ms_eng;


   } // namespace Micro_Solaris
 } // namespace lem

#endif
// ------------------------- End Of File [MS_DICT.H] ---------------------------

