﻿// CD->24.03.2012
// LC->02.09.2017

automat sg
{

 omonym add инфинитив : завещать{}
 omonym add глагол : завещать{}
 
 entry завещать : ИНФИНИТИВ
 {
  ВИД:НЕСОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  МОДАЛЬНЫЙ
  ПАДЕЖ:Вин,Дат
 }

 entry завещать : ИНФИНИТИВ
 {
  ВИД:СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  МОДАЛЬНЫЙ
  ПАДЕЖ:Вин,Дат
 }

 link ИНФИНИТИВ:завещать { ВИД:НЕСОВЕРШ } <в_сов> ИНФИНИТИВ:завещать{ ВИД:СОВЕРШ }
 link ИНФИНИТИВ:завещать { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:завещать{ ВИД:НЕСОВЕРШ }



 entry завещать : ГЛАГОЛ
 {
  ВИД : НЕСОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  МОДАЛЬНЫЙ
  ПАДЕЖ:Вин,Дат
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { завещаю }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { завещаем }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { завещаешь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { завещаете }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { завещает }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { завещают }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { завещал }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { завещала }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { завещало }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { завещали }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  { завещай }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  { завещайте }
 }


 entry завещать : ГЛАГОЛ
 {
  ВИД : СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  МОДАЛЬНЫЙ
  ПАДЕЖ:Вин,Дат
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { завещаю }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { завещаем }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { завещаешь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { завещаете }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { завещает }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { завещают }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { завещал }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { завещала }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { завещало }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { завещали }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  { завещай }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  { завещайте }
 }




 link Глагол : завещать { вид:несоверш }   <в_инфинитив> ИНФИНИТИВ : завещать { вид:несоверш }
 link ИНФИНИТИВ : завещать { вид:несоверш } <в_предикат> Глагол : завещать { вид:несоверш }

 link Глагол : завещать { вид:соверш }  <в_инфинитив> ИНФИНИТИВ : завещать { вид:соверш }
 link ИНФИНИТИВ : завещать { вид:соверш } <в_предикат> Глагол : завещать { вид:соверш } 


 omonym remove Глагол:завещать{}
 omonym remove Инфинитив:завещать{}
 
 // ---------------------------------------------------------------
 


 omonym add инфинитив : доустанавливаться{}
 omonym add глагол : доустанавливаться{}
 
 entry доустанавливаться : ИНФИНИТИВ
 {
  ВИД:НЕСОВЕРШ
  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
 }

 entry доустанавливаться : ИНФИНИТИВ
 {
  ВИД:СОВЕРШ
  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
 }

 link ИНФИНИТИВ:доустанавливаться { ВИД:НЕСОВЕРШ } <в_сов> ИНФИНИТИВ:доустанавливаться{ ВИД:СОВЕРШ }
 link ИНФИНИТИВ:доустанавливаться { ВИД:СОВЕРШ } <в_несов> ИНФИНИТИВ:доустанавливаться{ ВИД:НЕСОВЕРШ }



 entry доустанавливаться : ГЛАГОЛ
 {
  ВИД : НЕСОВЕРШ
  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { доустанавливаюсь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { доустанавливаемся }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { доустанавливаешься }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { доустанавливаетесь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { доустанавливается }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:НАСТОЯЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { доустанавливаются }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { доустанавливался }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { доустанавливалась }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { доустанавливалось }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { доустанавливались }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  { доустанавливайся }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  { доустанавливайтесь }
 }

 entry доустанавливаться : ГЛАГОЛ
 {
  ВИД : СОВЕРШ
  ПЕРЕХОДНОСТЬ:НЕПЕРЕХОДНЫЙ
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { доустанавливаюсь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { доустанавливаемся }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { доустанавливаешься }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { доустанавливаетесь }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { доустанавливается }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { доустанавливаются }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { доустанавливался }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { доустанавливалась }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { доустанавливалось }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { доустанавливались }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  { доустанавливайся }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  { доустанавливайтесь }
 }






 link Глагол : доустанавливаться { вид:несоверш }   <в_инфинитив> ИНФИНИТИВ : доустанавливаться { вид:несоверш }
 link ИНФИНИТИВ : доустанавливаться { вид:несоверш } <в_предикат> Глагол : доустанавливаться { вид:несоверш }

 link Глагол : доустанавливаться { вид:соверш }  <в_инфинитив> ИНФИНИТИВ : доустанавливаться { вид:соверш }
 link ИНФИНИТИВ : доустанавливаться { вид:соверш } <в_предикат> Глагол : доустанавливаться { вид:соверш } 


 omonym remove Глагол:доустанавливаться{}
 omonym remove Инфинитив:доустанавливаться{}
 
 // ---------------------------------------------------------------
 
}