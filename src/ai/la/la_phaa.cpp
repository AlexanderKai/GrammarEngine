// -----------------------------------------------------------------------------
// File LA_PHAA.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// LEM C++ library  http://www.solarix.ru
// ������������ ����-������� - ����� ���� ������������ ��������, �� ����
// ���������� ������ LexicalAutomat. ���������� ���������� ������������
// ����������� ��� ������������, ��� ��������� ������������ ����� � ��������
// (either ������� ����������, or ������������ ������� ������ ������ ��
// keyboard, ���� �������� ������� �� ���� ������������� ������������� �����,
// and so forth).
// -----------------------------------------------------------------------------
//
// CD->01.09.1997
// LC->09.06.2011
// --------------

#if defined SOL_CAA

#include <lem/stl.h>
#include <lem/logfile.h>
#include <lem/solarix/LA_PhoneticMatcher.h>
#include <lem/solarix/LA_PhoneticRule.h>
#include <lem/solarix/LA_RecognitionTrace.h>
#include <lem/solarix/LA_FuzzyMatching.h>
#include <lem/solarix/la_autom.h>

using namespace lem;
using namespace Solarix;

namespace Solarix
{
 struct LA_AA_item : public Lexem
 {
  Real1 val;

  LA_AA_item(void):Lexem(){};
  LA_AA_item( const Lexem &l, Real1 Val ):Lexem(l) { val=Val; }
 };
}

typedef MCollect<LA_AA_item> LA_AA_list;

/*****************************************************************************

                         ������������ ����-�������.

  ������ ��� ������������ ��������� � ������� ������ ��� ������������� ����,
  ���������� �� ������ �����, � �������, � ���������������� ��������.

  ������� ���������;

   proj - ������� �� ��������, �������� �������������, ������� ��������������
          � �������� �����������.

  ������������ ���������:

   ����� �������� proj ������������ ������ ������������ ����������� ��
   �����-���������.
*****************************************************************************/
void LexicalAutomat::ProducePhonInv( MLProjList &proj, int id_language, LA_RecognitionTrace *trace )
{
 // � ����� ���������� ������ � "��������"
 int n_org = 1 + CastSizeToInt(proj.get_Broken().size());

 std::set<lem::UCString> created_phonetic_variants;

 for( int iorg=0; iorg<n_org; iorg++ )
  {
   const RC_Lexem &word = !iorg ?
                                 proj.GetContent() :
                                 proj.get_Broken()[iorg-1];

   const Lexem &mlex = *word;

   // ���� ��������, ������������ ������� ����� ������ ������� � ������������.
   // ��� ���������� ����� �������� �� ����� ������ - ��� � ��� �������������.
   if( created_phonetic_variants.find(mlex)==created_phonetic_variants.end() )
    {
     created_phonetic_variants.insert(mlex);

     // ������� ������ ������������ ����������� ��� ������ �� nlex ������,
     // �������� � �������������.
     MCollect<LA_AA_list*> packs;
     LA_AA_list *list = new LA_AA_list;
     list->reserve(16);
     list->push_back( LA_AA_item( mlex, Real1(100) ) );

     // ������ ������������ ��������.
     LA_Pack *pack = AlephAuto( id_language, mlex, proj.get_Miss_Parameter(), trace );

     for( Container::size_type j=0; j<pack->size(); j++ )
      {
       const Solarix::Lexem &ph_lex = *(pack->get(j));

       if( created_phonetic_variants.find(ph_lex)==created_phonetic_variants.end() )
        {
         created_phonetic_variants.insert(ph_lex);
         list->push_back( LA_AA_item( ph_lex, pack->get(j)->get_Val() ) );
        }
      }

     delete pack;

     packs.push_back( list );

     const int NTOT = CastSizeToInt(packs.front()->size());

     // ���������� ��������� �������������� �������
     for( int i=1; i<NTOT; i++ )
      {
       const LA_AA_item &x = packs.front()->get(i);
       Lexem *mutated = new Lexem(x);

       proj.AddPhonInv( RC_Lexem( mutated ), x.val );
      }

     // ������� �������� ����� ������ ������������ ����������� ��� ����������.
     ZAP_A(packs);

     // ����������� ������� �� �������� �������������.
     proj.SortPhonInv();

/*
     // ����� ������������� ���������.
     const int ninv=proj.GetnPhonInv();
     if( ninv && GetDebugLevel()>=2 )
      {
       lem::LogFile::logfile->printf( "LA: Phonetic invariants production: %d item(s)\n", ninv );

       for( int i=0; i<ninv; i++ )
        {
         lem::LogFile::logfile->printf( "#%d ", i );
         const RC_Lexem &ml = proj.GetPhonInv(i);
         lem::LogFile::logfile->printf( "%us\n", ml->c_str() );
        }

       lem::LogFile::logfile->eol();
      }
*/
    }
  } // for - ���� �� ����������

 return;
}


// ��������� ����, ����������� ������� � ��������� word.
// ������������ ������ ���������, ������� �������� �����, � ������ �� ��������������.
void LexicalAutomat::ProducePhonInv(
                                    const lem::UCString &word,
                                    int id_language,
                                    lem::MCollect<lem::UCString> &res,
                                    lem::MCollect<lem::Real1> &rels,
                                    LA_RecognitionTrace *trace
                                   )
{
 MCollect<LA_AA_list*> packs;
 LA_AA_list *list = new LA_AA_list;
 list->reserve(16);
 list->push_back( LA_AA_item( word, Real1(100) ) );

 // ������ ������������ ��������.
 LA_Pack *pack = AlephAuto( id_language, word, 1, trace );

 for( Container::size_type j=0; j<pack->size(); j++ )
  {
   const Solarix::Lexem &ph_lex = *(pack->get(j));
   if( res.find( ph_lex )==UNKNOWN )
    {
     Real1 r = pack->get(j)->get_Val();
     rels.push_back(r);
     res.push_back( ph_lex );
    }
  }

 return;
}




// ***********************************************************************
// �������� �������: ��� �������� ������ lex ������� � ���������� ������
// ������������ ���������.
//
// n_max_tran - ������������ ���������� ����� � �������� �������.
// ***********************************************************************
LA_Pack* LexicalAutomat::AlephAuto( int id_language, const Lexem &lex, int n_max_tran, LA_RecognitionTrace *trace )
{
 // ����� ����� ������������ ������ ��� �������� �����.
 const LA_PhoneticMatcherForLanguage *matcher = phonetic_matcher->GetMatcherForLanguage(id_language);

 // ������������ ����� �����������.
 LA_Pack *to_ret = new LA_Pack(lex);

 bool changed=false;
 wchar_t context[LEM_CSTRING_LEN1];

 wchar_t Created_e[LEM_CSTRING_LEN1]; // ����� ����������� ������

 int nmaxpass=1, ipass=0;

 do
  {
   // ����� ��������� ������ � ����������� �� ���� ����������,
   // ������� ����������� � ���� ������ �������� ����� ���������
   // ����������� �� �����.
   const int was_variators = CastSizeToInt(to_ret->size());

   // *** ���� �� ���� ���������� ����� ������� ***
   for( int ivariator=0; ivariator<was_variators; ivariator++ )
    {
     // � ���� ���������� ����� ��������
     const LA_Variator &variator = *(to_ret->get(ivariator));

     if( variator.IsFrozen() )
      continue;

     const int vl = variator.length();

     // ���������� �� ��������� ������ �� 1 �������
     for( int ipos=0; ipos<vl; ipos++ )
      {
       // ��� ������� ������� ����� ��������� ������� � ������������ ������� ���� ������� ��������
       const int min_len = matcher->GetMinContext();
       const int max_len = std::min( matcher->GetMaxContext(), vl-ipos );

       for( int clen=min_len; clen<=max_len; ++clen )
        {
         // ����� ��������� ��� ������� � ������ �������� ��������� = clen
         const LA_PhoneticRuleGroup &group = matcher->GetGroup(clen);
         if( group.empty() )
          continue; // � ������ ��� ������

         // ������� �������� ������ clen
         for( int ii=0; ii<clen; ii++ )
          context[ii] = variator[ipos+ii];

         context[clen] = 0;

         int ntran=0; // ������� ������������� ������� � ����������

         const lem::MCollect<const LA_PhoneticRule*> &grules = group.rules;
         for( Container::size_type irule=0; irule<grules.size() && (variator.get_Tran()+ntran)<=n_max_tran; irule++ )
          {
           const LA_PhoneticRule &rule = *grules[irule];
/*
#if LEM_DEBUGGING==1
 if( wcscmp( context, L"��" )==0 && rule.GetName()==L"���-��" )
  {
   printf("");
  }
#endif
*/

           if( rule.GetCondition().DoesMatch(context) )
            {
             /*---------------------------------------------------------------
              ��!
              ������������ ������������ ���������.


                +---+---+---+-...-+---+---+-...-+
                |   |   |###|#####|###|   |     |
                +---+---+---+-...-+---+---+-...-+
                          |           |
                          ipos        ipos+clen


              ### - ����� �������, �������� �� ������������ ���������.
             -----------------------------------------------------------------*/

             ntran++;

             int ii,ito;
             const Lexem& res_part = rule.GetResult().GetContext();

             // ���������� � Created_x ���������� �� variator, ������� � 0
             // � �� ipos (�� �������).
             for( ito=0; ito<ipos; ito++ )
              {
               Created_e[ito] = variator[ito];
              }

             // ��������� ������������ ����� �������
             const int res_len = res_part.length();
             for( ii=0; ii<res_len; ii++, ito++ )
              {
               Created_e[ito] = res_part[ii];
              }

             // ��������� ����� variator, ������������ ����� �����
             // ��������, �������� �� ������������� �������� ���������.
             for( ii=ipos+clen; ii<vl; ii++, ito++ )
              {
               Created_e[ito] = variator[ii];
              }

             Created_e[ito] = 0;

             // �������� ������� �� ���� �������: ���� ������, ��������
             // ���� � ������ ���������.
             Lexem clex(Created_e);
             LA_Variator *created = new LA_Variator(clex);

             // ��������� ������ ���� ���������. ������������� ������ ���
             // ������������ ����������.
             bool found=false;
             for( ii=0; ii<CastSizeToInt(to_ret->size()) && !found; ii++ )
              found = (*created)==(*to_ret->get(ii));

             if( !found )
              {
               // ����� �������� �������� - ��������� � ������� ������.

               created->set_Tran( variator.get_Tran()+ntran );
               created->set_Val( variator.get_Val() * rule.GetVal() );
               to_ret->push_back( created );
               (*to_ret)[ivariator]->Froze();

               if( trace!=NULL )
                {
                 trace->PhoneticRuleProduction( lex, clex, created->get_Val(), &rule );
                }
              }
             else
              delete created;
            }
          }
        }
      }
    }

   // ���� ���� ����� ��������� ������?
   const int now_variators = CastSizeToInt(to_ret->size());
   changed = now_variators>was_variators;
  }
 while(changed && ++ipass<nmaxpass );

 for( Container::size_type i=0; i<to_ret->size(); i++ )
  {
   TranslateLexem( *(*to_ret)[i], true );
  }

 return to_ret;
}

#endif // defined SOL_CAA
