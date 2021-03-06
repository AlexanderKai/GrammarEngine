﻿// -----------------------------------------------------------------------------
// File RUS_VERBS_7044.SOL
//
// (c) Koziev Elijah
//
// Content:
// Лексикон - определения предикатов, причастий и прочая (глаголов) для Словаря.
// Особенности описания глаголов и инфинитивов http://www.solarix.ru/russian_grammar_dictionary/russian-verbs.shtml
// Спряжение русских глаголов http://www.solarix.ru/for_developers/api/russian-verb-conjugation.shtml
// Словарные статьи http://www.solarix.ru/for_developers/docs/entries.shtml#words
//
// -----------------------------------------------------------------------------
//
// CD->05.10.1995
// LC->29.08.2017
// --------------

#include "sg_defs.h"

automat sg
{
 // ********************************************************************
 // Чтобы проще создавать статьи сразу с грамматической сетью - связью
 // от предиката к инфинитиву.
 // ********************************************************************
 #define Verb( Name, i_DeclTable ) \
  #begin
   extern entry Name : ИНФИНИТИВ
   entry Name : ГЛАГОЛ
   {
    paradigm Глагол_##i_DeclTable
    <в_инфинитив>ИНФИНИТИВ:Name{}
   }
  #end

 Verb( СМИРиться , 7044 )
 Verb( ПРИМИРиться , 7044 )
 Verb( ПОКОРиться , 7044 )
 Verb( УДОВЛЕТВОРиться , 7044 )
 Verb( РАСТВОРиться , 7044 )
 Verb( ПРОВЕТРиться , 7044 )
 Verb( СВАРИТЬСЯ , 7044 )
 Verb( ВЫГОВОРИТЬСЯ , 7044 )
 Verb( ИСХИТРИТЬСЯ , 7044 )
 Verb( ОТГОВОРИТЬСЯ , 7044 )
 Verb( ПОСМОТРеТЬСЯ , 7044 )
 Verb( ЗАТВОРИТЬСЯ , 7044 )
 Verb( ВСМОТРеТЬСЯ , 7044 )
 Verb( ЗАСМОТРеТЬСЯ , 7044 )
 Verb( УГОВОРИТЬСЯ , 7044 )
 Verb( НАКУРИТЬСЯ , 7044 )
 Verb( ОБКУРИТЬСЯ , 7044 )
 Verb( ЗАГОВОРИТЬСЯ , 7044 )
 Verb( РАСЩЕДРИТЬСЯ , 7044 )
 Verb( ОЗАРИТЬСЯ , 7044 )
 Verb( УМОРИТЬСЯ , 7044 )
 Verb( ИЗНУРИТЬСЯ , 7044 )
 Verb( ОТДАРИТЬСЯ , 7044 )
 Verb( ВОДВОРИТЬСЯ , 7044 )
 Verb( ПОДБОДРИТЬСЯ , 7044 )
 Verb( НАВОСТРИТЬСЯ , 7044 )
 Verb( ПООСМОТРеТЬСЯ , 7044 )
 Verb( ОБВАРИТЬСЯ , 7044 )
 Verb( ОХМУРИТЬСЯ , 7044 )
 Verb( ОБОДРИТЬСЯ , 7044 )
 Verb( НАПУДРИТЬСЯ , 7044 )
 Verb( ПОПУДРИТЬСЯ , 7044 )
 Verb( УКУПОРИТЬСЯ , 7044 )
 Verb( ЗАТИХАРИТЬСЯ , 7044 )
 Verb( ПОМАТЕРИТЬСЯ , 7044 )
 Verb( ВЫМАТЕРИТЬСЯ , 7044 )
 Verb( НАПУЗЫРИТЬСЯ , 7044 )
 Verb( ВЫЯСНИТЬСЯ        , 7044 )
 Verb( ПРИТВОРИТЬСЯ      , 7044 )
 Verb( СВАЛИТЬСЯ         , 7044 )
 Verb( РАСПРОСТРАНИТЬСЯ  , 7044 )
 Verb( РАЗГОВОРИТЬСЯ   , 7044 )
 Verb( РАЗЪЯРИТЬСЯ     , 7044 )
 Verb( ВОЦАРИТЬСЯ      , 7044 )
 Verb( РАЗОРИТЬСЯ      , 7044 )
 Verb( УДАЛИТЬСЯ       , 7044 )
 Verb( УКОРЕНИТЬСЯ     , 7044 )
 Verb( УМУДРИТЬСЯ      , 7044 )
 Verb( УСОМНИТЬСЯ      , 7044 )
 Verb( ДОГОВОРИТЬСЯ    , 7044 )
 Verb( ЗАТРУДНИТЬСЯ    , 7044 )
 Verb( ИЗМЕНИТЬСЯ      , 7044 )
 Verb( НАГОВОРИТЬСЯ    , 7044 )
 Verb( НАКЛОНИТЬСЯ     , 7044 )
 Verb( ОТКЛОНИТЬСЯ     , 7044 )
 Verb( ПОВТОРИТЬСЯ     , 7044 )
 Verb( ПОКЛОНИТЬСЯ     , 7044 )
 Verb( ПРЕКЛОНИТЬСЯ    , 7044 )
 Verb( ПРИСОЕДИНИТЬСЯ  , 7044 )
 Verb( ПРОГОВОРИТЬСЯ   , 7044 )
 Verb( ПРОЯСНИТЬСЯ     , 7044 )
 Verb( РАЗЪЯСНИТЬСЯ    , 7044 )
 Verb( СГОВОРИТЬСЯ     , 7044 )
 Verb( СКЛОНИТЬСЯ      , 7044 )
 Verb( УКЛОНИТЬСЯ      , 7044 )
 Verb( УЯСНИТЬСЯ       , 7044 )
 Verb( НАКРЕНИТЬСЯ     , 7044 )
 Verb( ВЗБОДРИТЬСЯ , 7044 )
 Verb( ВНЕДРИТЬСЯ , 7044 )
 Verb( ВОЗГОРДИТЬСЯ , 7044 )
 Verb( ВОЗРОДИТЬСЯ , 7044 )
 Verb( ВСПОМНИТЬСЯ , 7044 )
 Verb( ВЫПОЛНИТЬСЯ , 7044 )
 Verb( ЗАПОЛОНИТЬСЯ , 7044 )
 Verb( ЗАРОДИТЬСЯ , 7044 )
 Verb( ЗАСТОПОРИТЬСЯ , 7044 )
 Verb( НАПОЛНИТЬСЯ , 7044 )
 Verb( ОБОСТРИТЬСЯ , 7044 )
 Verb( ОБЪЕДИНИТЬСЯ , 7044 )
 Verb( ОГОВОРИТЬСЯ , 7044 )
 Verb( ОТДЕЛИТЬСЯ , 7044 )
 Verb( ПЕРЕМЕНИТЬСЯ , 7044 )
 Verb( ПЕРЕПОЛНИТЬСЯ , 7044 )
 Verb( ПОДЧИНИТЬСЯ , 7044 )
 Verb( ПОЖЕНИТЬСЯ , 7044 )
 Verb( ПОПОЛНИТЬСЯ , 7044 )
 Verb( ПОСТОРОНИТЬСЯ , 7044 )
 Verb( ПРЕИСПОЛНИТЬСЯ , 7044 )
 Verb( ПРИМЕНИТЬСЯ , 7044 )
 Verb( ПРОВАЛИТЬСЯ , 7044 )
 Verb( РАЗВАЛИТЬСЯ , 7044 )
 Verb( СМЕНИТЬСЯ , 7044 )
 Verb( СОБЛАЗНИТЬСЯ , 7044 )
 Verb( СОЕДИНИТЬСЯ , 7044 )
 Verb( УДЛИНИТЬСЯ , 7044 )
 Verb( УМИЛИТЬСЯ , 7044 )
 Verb( УСЛОЖНИТЬСЯ , 7044 )
 Verb( УСТРАНИТЬСЯ , 7044 )
 Verb( УХИТРИТЬСЯ , 7044 )
 Verb( протыриться, 7044 )
 Verb( отабориться, 7044 )
 Verb( приговориться, 7044 )
 Verb( передариться, 7044 )
 Verb( одобриться, 7044 )
 Verb( вбуриться, 7044 )
 Verb( воскуриться, 7044 )
 Verb( полуотвориться, 7044 )
 Verb( сдобриться, 7044 )
 Verb( закуклиться, 7044 )
 Verb( причислиться, 7044 )
 Verb( обнулиться, 7044 )
 Verb( вызволиться, 7044 )
 Verb( выхвалиться, 7044 )
 Verb( самоисцелиться, 7044 )
 Verb( провеселиться, 7044 )
 Verb( уделиться, 7044 )
 Verb( увеселиться, 7044 )
 Verb( подзакалиться, 7044 )
 Verb( разрулиться, 7044 )
 Verb( переопределиться, 7044 )
 Verb( подразделиться, 7044 )
 Verb( вычислиться, 7044 )
 Verb( застелиться, 7044 )
 Verb( скруглиться, 7044 )
 Verb( наделиться, 7044 )
 Verb( подразвалиться, 7044 )
 Verb( взрыхлиться, 7044 )
 Verb( начислиться, 7044 )
 Verb( самоопылиться, 7044 )
 Verb( козлиться, 7044 )
 Verb( высветлиться, 7044 )
 Verb( полуразвалиться, 7044 )
 Verb( полупровалиться, 7044 )
 Verb( предохраниться, 7044 )
 Verb( отъединиться, 7044 )
 Verb( подмениться, 7044 )
 Verb( самовоспламениться, 7044 )
 Verb( самосохраниться, 7044 )
 Verb( захорониться, 7044 )
 Verb( сочиниться, 7044 )
 Verb( усредниться, 7044 )
 Verb( оброниться, 7044 )
 Verb( поясниться, 7044 )
 Verb( затениться, 7044 )
 Verb( взаимодополниться, 7044 )
 Verb( перевыполниться, 7044 )
 Verb( вычлениться, 7044 )
 Verb( доуточниться, 7044 )
 Verb( недооцениться, 7044 )
 
 
 
}

