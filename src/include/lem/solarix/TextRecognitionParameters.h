#if !defined TextRecognitionParameters__H
#define TextRecognitionParameters__H

#include <lem/containers.h>
#include <lem/solarix/syntax_analyzer_timeout.h>

namespace Solarix
{

 struct TextRecognitionParameters
 {
  lem::MCollect<int> language_ids; // ������ ������, ������ � ������ - ��������.
  bool Pretokenized; // ����������� ��� ������� �� ����� ����������� ��������
  bool RecognizeWordforms; // �� ��������� true - ��������� ��������������� ������������� ������
  bool AllowPrimaryFuzzyWordRecog; // ��������� �������� ������������� ����, ������� �� ������� � ���������.
  bool AllowFuzzyRecogMixin; // ���� ��� ��������� ������� ������ �������� ����� � ��������� ����� ����������� �������� � ��������.
  bool AllowDynform; // ��������� �������� ��������� � ������������ �������� ��� �������� �������������
  bool CompleteAnalysisOnly; // ����������� ������ ������ ����� �����������, � �� ����������.
  bool UseTokenReconstruction; // ��������������� ����������� ������ � ���������� ����� ����

  // ����������� (������ � ������������� �������) �������� ������ ��� ���������� ��������, ������� �������� �������������.
  int min_score_bound; 

  // ������������ ����� ����������� �������� �, �������������, ������������ ����������.
  // ���� ��������� ��� �������� � 0, �� ������� ������ �� ����� ������������.
  // ��� ������ ��������, ��� ���������� ����� ������������� (� �������� ����� ��������� �����������), ��
  // ��� ������� ����� �������.
  int max_filter_len;

  bool ApplyCollocFilters; // ��������� �� ��������� ������� ��������������

  int LookAheadTokens; // �� ������� ������� ������ ����� ����������� �������� ���������� �����������.

  bool UseSparsePatterns; // �������� ������, ������������ � �������� �������� ���������
  bool SkipInnerTokens; // ���� ��������� ���������� ����� ������ ���������
  bool SkipOuterToken; // ���� ��������� ���������� ����� ����� ��� ����� ���������
  int MaxSkipToken; // ������� ������� �������� ����� ���������� ��� �������� �������
  bool UseTopDownThenSparse; // ������� ����� ������ - ������� ������� top down ������, ���� ������� - �� ������� ���������������.

  bool ReorderTree; // ����������� ����� � ������� ����������� ������� ����.
  bool ApplyModel; // ��������� �������������� ������ ��� ������ ����. ���������������

  SyntaxAnalyzerTimeout timeout;

  TextRecognitionParameters();

  int GetLanguageID() const { return language_ids.front(); }
  void SetLanguageID( int id ) { language_ids.clear(); language_ids.push_back(id); }
  bool LanguageUnknown() const { return language_ids.empty() || language_ids.front()==UNKNOWN; }
  bool CanSkipInnerTokens() const { return SkipInnerTokens && !CompleteAnalysisOnly; }
  bool CanSkipOuterTokens() const { return SkipOuterToken && !CompleteAnalysisOnly; }

  // ������������ ��������������� ����� ������ ������� � ����� �����������.
  int GetMaxRightLeaves() const { return timeout.max_tokenization_paths>0 ? timeout.max_tokenization_paths : lem::int_max; }

  // ������������� ��������� MaxSkipToken � ����������� �� ������ ������������� ����������.
  void ConfigureSkipToken();
 };

}

#endif
