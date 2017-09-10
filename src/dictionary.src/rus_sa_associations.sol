﻿// CD->07.08.2012
// LC->20.02.2017

// поддакивать в споре
assoc_word language=Russian { существительное:спор{} :- rus_verbs:поддакивать{} = 1 }


// Японцы, захваченные боевиками «Исламского государства», живы
assoc_word language=Russian
{
 существительное:боевик{ одуш:одуш } :- прилагательное:исламский{} = 5
}

// Спал без сновидений!
assoc_word language=Russian
{
 глагол:спать{} :- существительное:сновидение{} = 5
}

// В бане мыл...
assoc_word language=Russian
{
 существительное:баня{} :- rus_verbs:мыть{} = 1
}


// Оставшимся душам был показан ад.
//            ^^^^^
assoc_word language=Russian
{
 существительное:душа{} :- существительное:ад{} = 1
}


// Двум полкам было присвоено звание гвардейских.
assoc_word language=Russian
{
 существительное:полк{} :- прилагательное:гвардейский{} = 1
}

// Геля для душа
assoc_word language=Russian
{
 существительное:гель{} :- существительное:душ{} = 1
}


// Налоговые полицейские инспектируют столичные банки.
//                                    ^^^^^^^^^^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:столичный{} = 1
}

// Крупные банки пересматривают прежние решения.
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:крупный{} = 1
}


// НЕМЕЦКИЕ БАНКИ ИЩУТ НАДЕЖНУЮ ОПОРУ.
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:немецкий{} = 1
}

// Петербургские банки создают расчетный пул.
//               ^^^^^         ^^^^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:расчетный{} = 1
}

// Массовая ликвидация грозит проблемным банкам.
//          ^^^^^^^^^^                   ^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- существительное:ликвидация{} = 1
}

// В калужские банки завезли бракованные евро
assoc_word language=Russian
{
 существительное:банк{} :- существительное:евро{} = 1
}

// Обыкновенные сороки являются оседлыми птицами.
assoc_word language=Russian
{
 существительное:сорока{} :- существительное:птица{} = 1
}


// Извлечённые биты формируют выходную последовательность.
assoc_word language=Russian
{
 существительное:бит{} :- существительное:последовательность{} = 1
}


// Судебная власть принадлежит Королевским судам.
assoc_word language=Russian
{
 существительное:суд{} :- прилагательное:судебный{} = 1
}


// Дальневосточное пароходство пополнится китайскими судами.
//                 ^^^^^^^^^^^            ^^^^^^^^^^
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- существительное:пароходство{} = 5
}

// Абордажными крючьями притягивали неприятельское судно.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:неприятельский{} = 5
}

// На самом деле это было грузовое судно.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:грузовой{} = 5
}

// Панамское судно потопило российский траулер.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- rus_verbs:потопить{} = 5
}

// Редкое судно бороздит речные просторы.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- rus_verbs:бороздить{} = 5
}

// Судно перевозило списанную нефтяную платформу.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- rus_verbs:перевозить{} = 5
}

// При подъеме судна открывались клапаны последних.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- существительное:подъем{} = 5
}



// Байкальский поисково-спасательный отряд получил уникальное судно
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- глагол:получить{} = 5
}

assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- существительное:отряд{} = 5
}


// Отходящее судно давало последние гудки.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- существительное:гудок{} = 5
}

// Непрерывная очередь накрыла несущееся судно;
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:несущийся{} = 5
}

// Это судно числится малайским грузовозом.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- существительное:грузовоз{} = 5
}


// Этот корабль был парусным судном;
//                  ^^^^^^^^^^^^^^^
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:парусный{} = 5
}


// Черные скорлупки рыбацких судов исчезли.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:рыбацкий{} = 5
}

// Неопределенная вера порождает дилетантские души.
assoc_word language=Russian
{
 существительное:душа{} :- существительное:вера{ одуш:неодуш } = 5
}


// От вампума до «итакского часа»
// ^^         ^^
assoc_word language=Russian
{
 предлог:до{} :- предлог:от{} = 5
}

// Великаньи глотки исторгли бешеный рев.
//           ^^^^^^                  ^^^
assoc_word language=Russian
{
 существительное:глотка{} :- существительное:рев{} = 5
}

// Приближались морские пути испанских судов.
assoc_word language=Russian
{
 существительное:судно{ OMONYM_RESOLUTION:1 } :- прилагательное:морской{} = 5
}


// Отечественные пароходства обзаводятся отечественными судами.
//               ^^^^^^^^^^^                            ^^^^^^
assoc_word language=Russian
{
 существительное: судно{ OMONYM_RESOLUTION:1 } :- существительное:пароходство{} = 1
}


// Указанным полкам вручить Гвардейские знамена.
assoc_word language=Russian
{
 существительное:полк{} :- существительное:знамя{} = 1
}

// Фашистские стрелки открывают ответный огонь.
assoc_word language=Russian
{
 существительное:стрелок{} :- существительное:огонь{} = 1
}



// Средние банки заинтересовались высокорисковым бизнесом.
//         ^^^^^                                 ^^^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- существительное:бизнес{} = 1
}




// Погашаются внутренние долги российским банкам.
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:российский{} = 1
}

// Эти банки имеют общих собственников.
assoc_word language=Russian
{
 существительное:банк{} :- существительное:собственник{} = 1
}

// Особую роль играют отраслевые банки.
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:отраслевой{} = 1
}

// Нижегородский еврозайм озадачил местные банки.
//                                 ^^^^^^^^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- прилагательное:местный{} = 1
}

// бара у бассейна
assoc_word language=Russian
{
 существительное:бар{} :- существительное:бассейн{} = 5
}




// помыться в бане
assoc_word language=Russian { существительное:баня{} :- rus_verbs:помяться{} = 1 }

// пострелять в тире
assoc_word language=Russian { существительное:тир{} :- rus_verbs:пострелять{} = 1 }


// Банки в прибыли.
assoc_word language=Russian { существительное:банк{} :- существительное:прибыль{} = 1 }

// Западным банкам обещают российских вкладчиков.
assoc_word language=Russian { существительное:банк{} :- существительное:вкладчик{} = 1 }

// мы плывем в их море
assoc_word language=Russian
{ существительное:море{} :- rus_verbs:плыть{} = 1 }


// Антонио улегся на полу
//         ^^^^^^    ^^^^
assoc_word language=Russian { существительное:пол{} :- rus_verbs:улечься{} = 1 }
assoc_word language=Russian { существительное:пол{} :- rus_verbs:лечь{} = 1 }
assoc_word language=Russian { существительное:пол{} :- rus_verbs:ложиться{} = 1 }

// стоит ли моя свобода такой цены?
// ^^^^^                      ^^^^
assoc_word language=Russian { существительное:цена{} :- rus_verbs:стоить{} = 1 }
assoc_word language=Russian { существительное:деньга{} :- rus_verbs:стоить{} = 1 }

// купаться в море
assoc_word language=Russian { существительное:море{} :- rus_verbs:купаться{}  = 1 }
assoc_word language=Russian { существительное:море{} :- rus_verbs:искупаться{} = 1 }
assoc_word language=Russian { существительное:море{} :- rus_verbs:плавать{} = 1 }
assoc_word language=Russian { существительное:море{} :- rus_verbs:поплавать{} = 1 }


// летом сорок третьего года.
assoc_word language=Russian
{
 существительное:лето{} :- существительное:год{} = 1
}


assoc_word language=Russian { глагол:спеть{ вид:соверш } :- существительное:концерт{} = 1 }
assoc_word language=Russian { инфинитив:спеть{ вид:соверш } :- существительное:концерт{} = 1 }


// где мы вообще находимся?
// ^^^           ^^^^^^^^^
assoc_word language=Russian { глагол:находиться{ вид:несоверш } :- наречие:где{} = 1 }
assoc_word language=Russian { инфинитив:находиться{ вид:несоверш } :- наречие:где{} = 1 }

// где стоит ваш дом?
// ^^^ ^^^^^
assoc_word language=Russian { глагол:стоять{} :- наречие:где{} = 1 }
assoc_word language=Russian { инфинитив:стоять{} :- наречие:где{} = 1 }


// мы все спали до глубокого вечера.
//        ^^^^^              ^^^^^^
assoc_word language=Russian { глагол:спать{} :- существительное:вечер{} = 1 }
assoc_word language=Russian { инфинитив:спать{} :- существительное:вечер{} = 1 }



// увлечь в прогулку по парку
assoc_word language=Russian
{
 существительное:парк{} :- существительное:прогулка{} = 1
}


// полный рот золотых зубов.
//        ^^^         ^^^^^
assoc_word language=Russian
{
 существительное:рот{} :- существительное:зуб{} = 1
}


// раздеться до трусов
assoc_word language=Russian
{
 существительное:трусы{} :- rus_verbs:раздеться{} = 1
}


// моргнуть веками
assoc_word language=Russian
{
 существительное:веко{} :- rus_verbs:моргнуть{} = 1
}


assoc_word language=Russian
{
 существительное:веко{} :- rus_verbs:моргать{} = 1
}


// слабый нежный аромат незнакомых духов.
//               ^^^^^^            ^^^^^
assoc_word language=Russian
{
 существительное:духи{} :- существительное:аромат{} = 1
}


// выпекать из пшеничной муки
// ^^^^^^^^              ^^^^
assoc_word language=Russian
{
 существительное:мука{ aux stress="мук^а" } :- rus_verbs:выпекать{} = 1
}


// В Азербайджане подорожала мука
//                           ^^^^
assoc_word language=Russian
{
 существительное:мука{ aux stress="мук^а" } :- rus_verbs:подорожать{} = 1
}


// выпекаться из ржаной муки
// ^^^^^^^^^^           ^^^^
assoc_word language=Russian
{
 существительное:мука{ aux stress="мук^а" } :- rus_verbs:выпекаться{} = 1
}

// кондитерские изделия из рисовой муки
assoc_word language=Russian { существительное:мука{ aux stress="мук^а" } :- прилагательное:рисовый{} = 1 }
assoc_word language=Russian { существительное:мука{ aux stress="мук^а" } :- прилагательное:пшеничный{} = 1 }


assoc_word language=Russian
{
 существительное:лицо{ одуш:неодуш } :- rus_verbs:расплыться{} = 1
}

assoc_word language=Russian
{
 существительное:лицо{ одуш:неодуш } :- rus_verbs:расплываться{} = 1
}


// Лицо её было бледно, а губы побледнели и задрожали
// ^^^^         ^^^^^^
assoc_word language=Russian
{
 существительное:лицо{ одуш:неодуш } :- прилагательное:бледный{} = 1
}


// Морщины избороздили его лицо.
assoc_word language=Russian
{
 существительное:лицо{ одуш:неодуш } :- существительное:морщина{} = 1
}


// С его лица капали крупные капли пота
//       ^^^^                      ^^^^
assoc_word language=Russian
{
 существительное:лицо{одуш:неодуш} :- существительное:пот{} = 1
}


// букет/букетик/букетище цветов
assoc_word language=Russian
{
 существительное:цветы{} :- rus_nouns:букет{} = 1
}



#define a_n(a,n) \
#begin
assoc_word language=Russian
{
 существительное:n{} :- прилагательное:a{} = 1
}
#end

a_n(точный,час)
a_n(наручный, час)
a_n(механический, час)
a_n(раритетный, час)
a_n(электронный, час)
a_n(атомный, час)
a_n(сломанный, час)


// палитра цветов
assoc_word language=Russian
{
 существительное:цвет{} :- существительное:палитра{} = 1
}

// ваза с цветами
assoc_word language=Russian
{
 существительное:цвет{} :- существительное:ваза{} = 1
}


// написать письмо
assoc_word language=Russian
{
 глагол:написать{ aux stress="напис^ать" } :- "письмо" = 1
}




// хранить деньги в банке
assoc_word language=Russian
{
 существительное:банк{} :- существительное:деньга{} = 1
}


// Другие банки из первой сотни платят куда меньше.
//        ^^^^^                 ^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- глагол:платить{} = 1
}

// Красноярские банки не дают ипотечных кредитов инвалидам и пенсионерам
//              ^^^^^                   ^^^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- существительное:кредит{} = 1
}

// Однако банки не принимают их в качестве залога.
//        ^^^^^                            ^^^^^^
assoc_word language=Russian
{
 существительное:банк{} :- существительное:залог{} = 1
}


// поддакивать в споре
assoc_word language=Russian { существительное:спор{} :- <в_класс>инфинитив:поддакивать{} = 1 }
assoc_word language=Russian { существительное:спор{} :- <в_класс>глагол:поддакивать{} = 1 }
assoc_word language=Russian { существительное:спор{} :- <в_класс>деепричастие:поддакивая{} = 1 }


// Хранить огурцы в банке
assoc_word language=Russian
{
 существительное:банка{} :- <в_класс>существительное:еда{} = 1
}


// Банки попадали, разбиваясь вдребезги.
// ^^^^^           ^^^^^^^^^^
assoc_word language=Russian
{
 существительное:банка{} :- rus_verbs:разбиваться{} = 1
}