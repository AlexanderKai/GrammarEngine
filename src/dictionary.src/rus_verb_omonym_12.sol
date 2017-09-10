﻿// Омонимы с дериватами для ЗАПАХНУТЬ

// CD->22.02.2016
// LC->22.02.2016

automat sg
{
 omonym add Глагол:запахнуть{}
 omonym add Инфинитив:запахнуть{}

 entry ЗАПАХНУТЬ : ИНФИНИТИВ
 {
  aux stress="зап^ахнуть"
  ВИД:СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  ПАДЕЖ:ТВОР
 }

 entry ЗАПАХНУТЬ : ИНФИНИТИВ
 {
  aux stress="запахн^уть"
  ВИД:СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  ПАДЕЖ:ВИН
 }

 entry запахнуть : ГЛАГОЛ
 {
  aux stress="зап^ахнуть"
  ВИД : СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  ПАДЕЖ:ТВОР
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { [запахну stress="зап^ахну"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { [запахнём yo="зап^ахнем"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { [запахнёшь yo="зап^ахнешь"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { [запахнёте yo="зап^ахнете"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { [запахнёт yo="зап^ахнет"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { [запахнут stress="зап^ахнут"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { запах }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { запахла }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { запахло }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { запахли }
 }

 

 
 entry запахнуть : ГЛАГОЛ
 {
  aux stress="запахн^уть"
  ВИД : СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  ПАДЕЖ:ВИН
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:ЕД  { [запахну stress="запахн^у"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:1 ЧИСЛО:МН  { [запахнём yo="запахнём"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:ЕД  { [запахнёшь yo="запахнёшь"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:2 ЧИСЛО:МН  { [запахнёте yo="запахнёте"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:ЕД  { [запахнёт yo="запахнёт"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:БУДУЩЕЕ ЛИЦО:3 ЧИСЛО:МН  { [запахнут stress="запахн^ут"] }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:МУЖ  { запахнул }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:ЖЕН  { запахнула }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:ЕД РОД:СР  { запахнуло }
  НАКЛОНЕНИЕ:ИЗЪЯВ ВРЕМЯ:ПРОШЕДШЕЕ ЧИСЛО:МН  { запахнули }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:ЕД  { [запахни stress="запахн^и"] }
  НАКЛОНЕНИЕ:ПОБУД ЛИЦО:2 ЧИСЛО:МН  { [запахните stress="запахн^ите"] }
 }

 

 entry ЗАПАХНУВ : ДЕЕПРИЧАСТИЕ
 {
  aux stress="запахн^ув"
  ВИД : СОВЕРШ
  ПЕРЕХОДНОСТЬ:ПЕРЕХОДНЫЙ
  ПАДЕЖ:ВИН
 }



 link ИНФИНИТИВ:ЗАПАХНУТЬ { ПАДЕЖ:ВИН } <в_сущ> СУЩЕСТВИТЕЛЬНОЕ:ЗАПАХИВАНИЕ {}
 link ГЛАГОЛ:запахнуть{ ПАДЕЖ:ВИН } <в_инфинитив> ИНФИНИТИВ:запахнуть{ ПАДЕЖ:ВИН }
 link ГЛАГОЛ:запахнуть{ ПАДЕЖ:ТВОР } <в_инфинитив> ИНФИНИТИВ:запахнуть{ ПАДЕЖ:ТВОР }

 link ИНФИНИТИВ:запахнуть{ПАДЕЖ:ВИН} <в_прил> ПРИЛАГАТЕЛЬНОЕ:запахнувший{ПАДЕЖ:ВИН}
 link ПРИЛАГАТЕЛЬНОЕ:запахнувший{} <в_инфинитив> ИНФИНИТИВ:запахнуть{ПАДЕЖ:ВИН}
 link ДЕЕПРИЧАСТИЕ:запахнув{} <в_инфинитив> ИНФИНИТИВ:запахнуть{ПАДЕЖ:ВИН}

 link ПРИЛАГАТЕЛЬНОЕ:ЗАПАХНУТЫЙ {} <в_инфинитив> ИНФИНИТИВ:запахнуть {ПАДЕЖ:ВИН}
 
 link ГЛАГОЛ:запахнуть{ПАДЕЖ:ТВОР} <в_инфинитив> ИНФИНИТИВ:запахнуть{ПАДЕЖ:ТВОР}


 omonym remove Глагол:запахнуть{}
 omonym remove Инфинитив:запахнуть{}
 
}