#if !defined SG_Calibrator__H
 #define SG_Calibrator__H

 #include <lem/solarix/lexem.h>
 #include <lem/sol_io.h>
 #include <lem/solarix/coord_pair.h>

 namespace lem
 {
  namespace Iridium
  {
   class Macro_Parser;
  }
 }

 namespace Solarix
 {
  class SynGram;

  #if defined SOL_LOADTXT && defined SOL_COMPILER
  /***************************************************************************
   ����������: ��������� ����� ������������ ����������. ����� ����� ��������
   ��������� �������������� ��������� ��� ������������ ��������, �� ���������,
   ���� �� ������� ����������� �������������� ���������� � �����.
  ****************************************************************************/
  struct SG_calibrator
  {
   lem::zbool wordform;
   Solarix::Lexem word; // ����������� ����������
   int id_class;
   Solarix::CPE_Array coords; 
   int freq;  // ���������� ������� �������������.

   SG_calibrator(void) : id_class(UNKNOWN), freq(0) {}
   SG_calibrator( const SG_calibrator &x );
   SG_calibrator( const Solarix::SynGram &sg, const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile, bool _wordform );

   void operator=( const SG_calibrator &x );

   inline const Lexem& GetWord(void) const { return word; }
   inline int GetFreq(void) const { return freq; }
   int GetClass(void) const { return id_class; }

   bool MatchCoords( const CP_Array &form_coords ) const;

   bool IsWordEntry(void) const { return !wordform; }
   bool IsWordForm(void) const { return wordform; }

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };
  #endif

 }
#endif
