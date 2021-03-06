﻿

// Присоединяемое наречие редко стоит ПОСЛЕ глагола НАЧАТЬ (и других модальных):
// легкие начали мучительно гореть.
//        ~~~~~~ ^^^^^^^^^^ ^^^^^^
#define SUPRESS_AFTER_VERB(v) \
#begin
tree_scorer language=Russian
{
 if context { глагол:v{1}.наречие:*{2} }
  then -2
}

tree_scorer ВалентностьГлагола language=Russian
{
 if context { глагол:v{1}.наречие:*{ 2 СТЕПЕНЬ:АТРИБ } }
  then -2
}
#end

SUPRESS_AFTER_VERB(начать) // легкие начали мучительно гореть.
SUPRESS_AFTER_VERB(продолжать) // лейтенант продолжал тяжело дышать.
SUPRESS_AFTER_VERB(обещать) // обещали завтра отпустить домой.
SUPRESS_AFTER_VERB(хотеть) // сначала они хотели попросту сбежать.
SUPRESS_AFTER_VERB(стать) // земля стала мерно уходить назад.
SUPRESS_AFTER_VERB(заставить) // неприятный шорох заставил быстро обернуться.
SUPRESS_AFTER_VERB(казаться) // лицо казалось особенно молодым.


wordentry_set ЗапретЛевНареч=наречие:{
уже,
гораздо, // эта задача оказалась гораздо легче первой.
слишком, // это был слишком долгий день
столь, // прошло столь много лет!
поистине, // Развитие телекоммуникаций приобрело поистине невиданный размах
'всего лишь', // это были всего лишь мыши
'по крайней мере', // ты спасла по крайней мере одну человеческую жизнь
даже, // это было заметно даже сквозь железные ставни
лишь, // через это испытание могут пройти лишь немногие
максимально, // Мы создали максимально информативный и простой сервис управления корпоративной связью
невероятно, // В последние месяцы своей жизни он выглядел невероятно уставшим
заведомо, // обвиняемый использовал заведомо подложный документ
'только что', // В Бурятии местные жители линчевали только что освободившегося педофила
почти, // стало почти совсем темно.
абсолютно, // их носят абсолютно все
несколько, // сам сделал несколько таких.
еще, // жена старика умерла еще молодой. НО: он съел еще.
неожиданно,
неизменно, // голос его оставался неизменно спокойным
очень, // все остались очень довольны.
совершенно, // лицо Марины казалось совершенно спокойным.
только, // раньше мы могли только догадываться.
много, // тут мы нашли много интересного.
совсем, // Это совсем лишнее.
немедленно, // наш командир велел немедленно собираться.
чрезвычайно, // положение оказалось чрезвычайно тяжелым.
хорошо, // все казалось хорошо знакомым.
достаточно, // дыра оказалась достаточно широкой.
предельно, // моя жизнь оставалась предельно пустой.
довольно, // толпа вокруг ворот оказалась довольно плотной.
существенно, // блюдо получилось существенно более острым.
вполне, // объяснение оказалось вполне естественным.
чуть, // каменные стены позволяли чуть расслабиться.
практически, // следующий мир оказался практически мертвым.
необычайно, // напиток оказался необычайно крепким.
весьма, // Костя улыбнулся весьма странной улыбкой.
относительно, // получилась относительно ровная площадка.
постепенно, // пятно продолжало постепенно приближаться.
полностью, // Кот притворялся полностью безразличным и совсем незаинтересованным
рекордно, // Немецкая полиция задержала рекордно пьяного водителя
скандально, // В Петербурге открылась скандально известная выставка
поразительно, // последовало поразительно долгое молчание.
удивительно, // раздался удивительно неприятный звук.
смутно, // коридор показался смутно знакомым.
именно // почему вы выбрали именно этот мир?
}

// Некоторые наречия предпочитают атрибутировать именно правого соседа:
// дорога оказалась неожиданно легкой.
//                  ^^^^^^^^^^ ^^^^^^
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{1}.ЗапретЛевНареч{ 2 степень:атриб }.[not]*:*{} } // не будем срабатывать на особые паттерны "ТОЛЬКО РАЗ"
  then -1
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{1}.ЗапретЛевНареч{ 2 степень:атриб }.наречие:*{} }
  then -1
}

// это было заметно даже сквозь железные ставни
//          ^^^^^^^^^^^^
tree_scorer ВалентностьПрил language=Russian generic
{
 if context { *:*{1}.ЗапретЛевНареч{2}.[not]*:*{} } // не будем срабатывать на особые паттерны "ТОЛЬКО РАЗ"
  then -1
}



// --------------------------------------

// наречия КАК, КАК БУДТО редко употребляются справа от глагола,
// что позволяет отделить их от употребления сопоставительного
// оборота с КАК:
// как у вас тут рабочие ходят?
wordentry_set НаречиеКак=наречие:{
КАК, СЛОВНО, "КАК БУДТО", БУДТО
}


tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { безлич_глагол:*{1}.НаречиеКак{2}.[not]*:*{} }
  then -8
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{1}.НаречиеКак{2}.[not]*:*{} }
  then -8
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{1}.НаречиеКак{2}.[not]*:*{} }
  then -8
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { деепричастие:*{1}.НаречиеКак{2}.[not]*:*{} }
  then -10
}


tree_scorers ОбъектДляКак

tree_scorer ОбъектДляКак language=Russian { if context { предлог:*{} } then 1 }
tree_scorer ОбъектДляКак language=Russian { if context { существительное:*{} } then 1 }
tree_scorer ОбъектДляКак language=Russian { if context { местоимение:*{} } then 1 }


tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{2}.НаречиеКак{1}.ОбъектДляКак }
  then -10
}

// смех словно по команде стих
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { глагол:*{3}.{
                           <SUBJECT>*:*{}
                           НаречиеКак{2}.ОбъектДляКак
                          } }
  then 10
}


tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { инфинитив:*{2}.НаречиеКак{1}.ОбъектДляКак }
  then -10
}

tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { деепричастие:*{2}.НаречиеКак{1}.ОбъектДляКак }
  then -10
}

// --------------------------------------


// Порядок ПОДОЛЕЖАЩЕЕ-ГЛАГОЛ-ДОПОЛНЕНИЕ для неодушевленного подлежащего:
#define S_v_O(v,aspect=NULL) \
#begin

tree_scorer ВалентностьПредиката language=Russian
{
 #if aspect==NULL
 if context { глагол:v{ 2 }.{
 #else
 if context { глагол:v{ 2 вид:aspect }.{
 #endif
                             <SUBJECT>*:*{ 3 }
                             <OBJECT>*:*{ 1 }
                            } }
  then -1 // штрафуем за обратный порядок
}

#end


// --------------------------------

S_v_O(заливать)

// Порядок слов для ИМЕТЬ:
// смерть имеет свой особый запах.
//        ^^^^^
S_v_O(иметь)


// -----------------------------------------------------

S_v_O(обещать) // правый проход тоже обещал сюрприз.
S_v_O(давать) // любовь дает врагу слишком большое преимущество.
S_v_O(задавать) // такой удар задавал тон битве.
S_v_O(означать) // нарушение такой клятвы означает смерть.
S_v_O(исполнить) // Оркестр исполнил гимн Японии.
S_v_O(портить) // Сырость портит обувь.
S_v_O(замедлить) // Поезд замедлил ход.
S_v_O(замедлять) // Поезд замедляет ход.
S_v_O(набирать) // Поезд набирает скорость.
S_v_O(держать) // Печь хорошо держит тепло.
S_v_O(изменить) // однако обстоятельства изменили наши намерения.
S_v_O(показать) // однако вид старика показал мне выход.
S_v_O(возбудить) // Его поведение возбудило моё любопытство.
S_v_O(резать) // Мой нож режет мясо. (S-резать-O)
S_v_O(принимать) // дело принимает чересчур серьезный оборот. (S-принимать-O)
S_v_O(сжимать) // босые ноги сжимали бока лошади. (S-сжимать-O)
S_v_O(подать) // Генри подал ему знак. (S-подать-o)
S_v_O(уничтожить) // взрыв уничтожил тот мир. (S-уничтожить-O)
S_v_O(дать) // поиски вскоре дали свои плоды. (S-дать-O))
S_v_O(знать) // корабль знает свое дело. (S-знать-O)
S_v_O(сделать) // камень сделает свое дело. (S-сделать-O)
S_v_O(закрывать) // необычно густой снег закрывал солнечный свет. (S-закрывать-O)
S_v_O(освещать) // кровавый свет освещал алтарь передо мной. (S-освещать-O)
S_v_O(напоминать) // голос мой напоминал шорох древнего пергамента. (S-напоминать-O)
S_v_O(осветить) // тусклый свет фонаря осветил ближайший участок каменной стены. (S-осветить-O)
S_v_O(занять) // путешествие заняло немного времени. (S-занять-O)
S_v_O(искать) // ваш мир ищет свой путь. (искать = S-V-O)
S_v_O(взять) // Пароход взял курс на восток.
S_v_O(пронзить) // внезапно резкий тонкий звук пронзил зал насквозь.
S_v_O(продолжить) // вскоре отряд продолжил путь.
S_v_O(нанести) // ворон нанес сильный удар мечом сверху вниз.
S_v_O(поднимать) // значит ветер поднимал песок.
S_v_O(образовывать) // иногда сны образовывали сложные картины.
S_v_O(носить) // большинство женщин носили длинные юбки.
S_v_O(требовать) // последнее требовало немало времени.
S_v_O(выдать) // снова компьютер выдал правильный ответ.
S_v_O(рассечь) // клинок со свистом рассек воздух. (рассечь)
S_v_O(подготавливать) // Правительство подготавливает проект договора. (подготавливать)
S_v_O(составлять) // Это составляет значительный процент. (составлять)
S_v_O(выражать) // все ее тело выражало участие.
S_v_O(вызвать) // этот вопрос снова вызвал его гнев. (вызвать)
S_v_O(потерять) // горный дух потерял его след! (потерять)
S_v_O(наполнить) // страшный звон наполнил его мозг! (наполнить)
S_v_O(коснуться) // ее губы коснулись его щеки. (коснуться)
S_v_O(скрывать) // желтые глаза скрывали его мысли. (скрывать)
S_v_O(влечь) // уменьшение налоговых сборов влечет снижение расходов на науку (влечь)
S_v_O(ознаменовать) // ваше вступление в должность ознаменует новый этап (ознаменовать)
S_v_O(упразднить) // власти России упразднили налоги (упразднить)
S_v_O(снизить) // эти запредельные счета снизят наши доходы вдвое (снизить)
S_v_O(вызывать) // Это  вызывает всеобщее любопытство (вызывать)
S_v_O(отнести) // он отнес коробку к дедушке (отнести)
S_v_O(покрывать) // это покрывает лишь часть наших расходов (S-покрывать-O)
S_v_O(превосходить) // результат его забега превосходил предыдущий результат на пять секунд (S-превосходить-O)
S_v_O(причинять) // ваше равнодушие причиняет мне боль (S-причинять-O)
S_v_O(сбрасывать) // когда деревья сбрасывают листья (S-сбрасывать-O)
S_v_O(выдержать) // какой порт выдержит такое время? (S-выдержать-O)
S_v_O(обжигать) // Резкий холод обжигал лицо.
S_v_O(ЗАНИМАТЬ) // палочки занимали все мысли.
S_v_O(ЖДАТЬ) // все ждали нападения врагов.
S_v_O(ПОДНЯТЬ) // все подняли глаза кверху.

S_v_O(УКАЗЫВАТЬ) // свет звезд указывал ей путь. (УКАЗЫВАТЬ)
S_v_O(НАЙТИ) // остальные боевые машины нашли себе другие цели. (НАЙТИ)
S_v_O(НЕСТИ) // два солдата несли факелы. (НЕСТИ)
S_v_O(приносить) // до сих пор путешествие приносит только раздражение. (приносить)
S_v_O(мутить) // Алкоголь мутит сознание. (мутить)
S_v_O(ОПРЕДЕЛЯТЬ) // Бытие определяет сознание. (ОПРЕДЕЛЯТЬ)
S_v_O(перевозить) // Грузовики перевозят большие грузы. (перевозить)
S_v_O(ОТРАЗИТЬ) // Зеркало отразило улыбающееся лицо. (ОТРАЗИТЬ)
S_v_O(ПРЕВЫШАТЬ) // Доход превышает расход. (ПРЕВЫШАТЬ)
S_v_O(БУКСИРОВАТЬ) // Буксир буксирует танкер к месту стоянки
S_v_O(вкидывать) // Манипулятор вкидывает груз в контейнер
S_v_O(вкидать) // Манипулятор вкидал груз в контейнер
S_v_O(покинуть) // их корабль покинул порт час назад.
S_v_O(ЗАКРЫТЬ) // Майя закрыла за нами дверь. (ЗАКРЫТЬ)
S_v_O(СОХРАНЯТЬ) // Дом из дерева хорошо сохраняет тепло (СОХРАНЯТЬ)
S_v_O(ИМЕТЬ) // какое значение здесь имеет власть! (ИМЕТЬ)
S_v_O(ПОДДЕРЖАТЬ) // Внешний оптимизм поддержал сегодня российский рынок акций (ПОДДЕРЖАТЬ)
S_v_O(РАЗБИТЬ) // ближе к вечеру маленький отряд разбил лагерь. (РАЗБИТЬ)
S_v_O(ПОДХВАТИТЬ) // Российский рынок подхватил общий позитивный тренд  (ПОДХВАТИТЬ)
S_v_O(СОПРОВОЖДАТЬ) // Чай в Японии сопровождает каждый приём пищи. (СОПРОВОЖДАТЬ)
S_v_O(НОРМАЛИЗОВАТЬ) // Крепкий чай нормализует пищеварение (НОРМАЛИЗОВАТЬ)
S_v_O(ОКАЗЫВАТЬ) // Употребление чая оказывает благотворное воздействие на самые различные системы органов человека (ОКАЗЫВАТЬ)
S_v_O(ЗАНЯТЬ) // объяснение заняло несколько минут. (ЗАНЯТЬ)
S_v_O(ЗАПОЛНИТЬ) // этот запах заполнил весь воздух. (ЗАПОЛНИТЬ)
S_v_O(ПЕРЕСЛАТЬ) // второй сервер переслал пакет дальше (ПЕРЕСЛАТЬ)
S_v_O(СПАСТИ) // только его уничтожение спасет будущее человечества. (СПАСТИ)
S_v_O(ОБЕСПЕЧИТЬ) // Это обеспечит мир во всём мире. (ОБЕСПЕЧИТЬ)
S_v_O(ВЫДЕЛЯТЬ) // Это соединение выделяет при реакции водород. (ВЫДЕЛЯТЬ)
S_v_O(ПРИОТКРЫТЬ) // Генри приоткрыл один глаз. (ПРИОТКРЫТЬ)
S_v_O(ВКЛЮЧИТЬ) // Том снова включил свет.
S_v_O(ОТСЕЧЬ) // мощный удар отсек второй побег.
S_v_O(чувствовать) // пальцы чувствовали гладкие деревянные доски.
S_v_O(ПОТРЯСТИ) // удар потряс огромный корпус корабля.
S_v_O(ИМЕТЬ) // каждое мгновение имеет собственное назначение.
S_v_O(ОХВАТИТЬ) // сердце мое охватило мрачное отчаяние.
S_v_O(ПОПРОБОВАТЬ) // Гарри попробовал свой напиток.
S_v_O(повторить) // Гарри повторил свой вопрос.
S_v_O(терять) // флот теряет свой смысл.
S_v_O(опровергать) // эти факты опровергают представления об устройстве Вселенной
S_v_O(ПРИНЕСТИ) // ветер принес запах дыма.
S_v_O(УЛОВИТЬ) // Генри уловил кусочек фразы.
S_v_O(ЛЮБИТЬ) // наше общество любит убийство.
S_v_O(ОБОЙТИ) // Слух обошёл весь город.
S_v_O(ЛОМИТЬ) // Спелые яблоки ломят сучья.
S_v_O(ПОТЯНУТЬ) // Этот кризис потянул за собой весь мир.
S_v_O(ЗАХВАТИТЬ) // Огонь захватил соседний дом.
S_v_O(МЕНЯТЬ) // Дождь меняет вид берегов.
S_v_O(ОСВЕЖИТЬ) // Дождь освежил воздух.
S_v_O(ПИЛИТЬ) // какие-то скрипки где-то пилят чьи-то узкие плечи
S_v_O(предсказывать) // Антонио иногда очень не точно предсказывал результат скачек

S_v_O(ПЕРЕСЕЧЬ) // маленький поток пересек ему путь (ПЕРЕСЕЧЬ)
S_v_O(праздновать) // Отдельный полк связи ВДВ празднует Крещение  (праздновать)
S_v_O(ПРЕДПОЛАГАТЬ) // Сам процесс признания предполагает много допросов (ПРЕДПОЛАГАТЬ)
S_v_O(ПОКАЗЫВАТЬ) // Толстые линии показывают связи между участками коры (ПОКАЗЫВАТЬ)
S_v_O(ДЕМОНСТРИРОВАТЬ) // Любое живое существо, обладающее мозгом, демонстрирует гибкое и сложное поведение (ДЕМОНСТРИРОВАТЬ)
S_v_O(ИЗУЧАТЬ) // Как на самом деле физики изучают элементарные частицы (ИЗУЧАТЬ)
S_v_O(УДОВЛЕТВОРИТЬ) // Хозяйственный суд Киева в сентябре прошлого года частично удовлетворил иск министерства обороны РФ (УДОВЛЕТВОРИТЬ)
S_v_O(ЗАНЯТЬ) // все наблюдение заняло несколько секунд (ЗАНЯТЬ)
S_v_O(ОТКЛАДЫВАТЬ) // отсутствие развитой системы социальной защиты привело к тому, что правительство откладывало проведение важных экономических реформ, занимаясь спасением нерентабельных компаний и рабочих мест (ОТКЛАДЫВАТЬ)
S_v_O(УВЕЛИЧИВАТЬ) // ограничения на запуск нового бизнеса увеличивают доходы существующих фирм, но сокращают общий рост производительности в данном сегменте экономики (УВЕЛИЧИВАТЬ)
S_v_O(СПАСТИ) // один из наших кораблей спас ваш город! (СПАСТИ)
S_v_O(ВЗЯТЬ) // вместо ответа один из воинов взял меч (ВЗЯТЬ)
S_v_O(ДЕРЖАТЬ) // один из солдат держал над головой фонарь (ДЕРЖАТЬ)
S_v_O(ПОСТАВИТЬ) // один из стражников поставил перед ней стул (ПОСТАВИТЬ)
S_v_O(ЗАТРАГИВАТЬ) // Фильм затрагивает часть биографии шестнадцатого президента США (ЗАТРАГИВАТЬ)
S_v_O(ОБЖЕЧЬ) // холодный зимний воздух обжег Антошке нос (ОБЖЕЧЬ)
S_v_O(ВЫЯВИТЬ) // Инспекции выявили нарушения в уборке снега с крыш. (ВЫЯВИТЬ)
S_v_O(ПОЛУЧИТЬ) // Кишинёвский погром получил большой общественный резонанс в России, Европе и Америке (ПОЛУЧИТЬ)
S_v_O(ПОЛУЧАТЬ) // В процессе внутриутробного развития хрусталик получает питание от стекловидной артерии (ПОЛУЧАТЬ)
S_v_O(ПОВЛЕЧЬ) // Необычные холода повлекли за собой неурожай и голод (ПОВЛЕЧЬ)
S_v_O(ОБРАЗОВЫВАТЬ) // Ежегодно одно растение образует несколько сотен ягод (ОБРАЗОВЫВАТЬ)
S_v_O(ОБОСТРЯТЬ) // Брусничный сироп обостряет зрение (ОБОСТРЯТЬ)
S_v_O(ПОРАЖАТЬ) // Болезни культурных видов лука не поражают дикорастущие (ПОРАЖАТЬ)
S_v_O(НЕЙТРАЛИЗОВАТЬ) // Эти соли нейтрализуют кислотные соединения, которые содержатся во многих пищевых продуктах и нарушают обменные процессы (НЕЙТРАЛИЗОВАТЬ)
S_v_O(ПОВЫШАТЬ) // Свежий огурец эффективно повышает кислотность желудочного сока (ПОВЫШАТЬ)
S_v_O(СНИЖАТЬ) // Капустный сок снижает содержание сахара в крови, усиливает выделение излишней жидкости из организма (СНИЖАТЬ, УСИЛИВАТЬ)
S_v_O(УСИЛИВАТЬ)
S_v_O(ШЕВЕЛИТЬ) // ночной ветер шевелил их мех. (ШЕВЕЛИТЬ)
S_v_O(УСЛЫШАТЬ) // вдруг уши ее услышали голоса. (УСЛЫШАТЬ)
S_v_O(УКРАШАТЬ) // металлические шлемы украшали их головы. (УКРАШАТЬ)
S_v_O(ЗНАЧИТЬ) // Что значит это слово? (ЗНАЧИТЬ)
S_v_O(ДЕЛАТЬ) // все делали друг другу маленькие подарки. (ДЕЛАТЬ)
S_v_O(ЗАБРАТЬ) // институт все равно забрал бы лес. (ЗАБРАТЬ)
S_v_O(СДЕРЖИВАТЬ) // Неравенство сдерживает восстановление (СДЕРЖИВАТЬ)
S_v_O(ПЕРЕЖИВАТЬ) // ООН: Мир переживает кризис эволюции (ПЕРЕЖИВАТЬ)
S_v_O(УТРАЧИВАТЬ) // Поэтому из-за хронической нехватки капитализации эти отрасли постепенно утрачивают всякие стандарты (УТРАЧИВАТЬ)
S_v_O(УВЕЛИЧИТЬ) // Банк Японии вдвое увеличил целевой показатель по инфляции (УВЕЛИЧИТЬ)
S_v_O(ОБЪЯСНЯТЬ) // Правительство Японии объясняет рост дефицита торгового баланса растущей зависимостью от импорта нефти и газа (ОБЪЯСНЯТЬ)
S_v_O(ОДОБРИТЬ) // Евросоюз одобрил новый пакет санкций по сокращению источников финансирования ядерной программы страны (ОДОБРИТЬ)
S_v_O(ВВЕСТИ) // Совет ЕС ввел запрет на импорт, приобретение и транспортировку иранской нефти и нефтепродуктов (ВВЕСТИ)
S_v_O(ВСТРЕТИТЬ) // как отец встретил свой конец?
S_v_O(ПРЕКРАТИТЬ) // Новые власти Грузии прекратили начатые в стране инфраструктурные проекты (ПРЕКРАТИТЬ)
S_v_O(ПОЛОЖИТЬ)
S_v_O(ПОДРЫВАТЬ) // Берлин подрывает доверие производителей (ПОДРЫВАТЬ)
S_v_O(ШИТЬ) // заключенные сами шьют куклы и иногда выезжают с представлениями в детский дом неподалеку (ШИТЬ)
S_v_O(ВЫБИТЬ) // омоновцы выбили окна и прорвались в квартиру (ВЫБИТЬ)
S_v_O(ПРИНЯТЬ) // Ведомство приняло решение отправить продукты на проверку после резонансного случая (ПРИНЯТЬ)
S_v_O(ОСУДИТЬ) // Совбез ООН единогласно осудил теракт около американского посольства в Анкаре (ОСУДИТЬ)
S_v_O(ПРИЗНАВАТЬ) // документ признает потенциал для роста транспортировки и транзита грузов между Узбекистаном и Афганистаном (ПРИЗНАВАТЬ, ПРИЗНАТЬ)
S_v_O(ПРИЗНАТЬ)
S_v_O(ВЫПУСТИТЬ) // Посольства большинства стран выпустили памятки для граждан , которые планируют посетить Таиланд (ВЫПУСТИТЬ)
S_v_O(ВЫСТАВИТЬ) // Автогигант , стоящий на грани банкротства , выставит на торги часть своей европейской недвижимости (ВЫСТАВИТЬ)
S_v_O(ИСПОЛЬЗОВАТЬ,соверш) // Орган опеки и попечительства в данном направлении не использовал права и обязанности по защите интересов несовершеннолетних (ИСПОЛЬЗОВАТЬ)
S_v_O(ИСПОЛЬЗОВАТЬ,несоверш)
S_v_O(ПРИОБРЕСТИ) // потолок приобрёл вид звёздного неба (ПРИОБРЕСТИ)
S_v_O(ПОСАДИТЬ) // Молодые пары посадят саженцы в центре города (ПОСАДИТЬ)
S_v_O(ПРИНЯТЬ) // Парламент Приднестровья принял новый закон (ПРИНЯТЬ)
S_v_O(ВНЕСТИ) // большинство действующих акционеров внесут свои доли (ВНЕСТИ)
S_v_O(РАССМОТРЕТЬ) // Тверской суд Москвы сегодня рассмотрит вопрос о продлении ареста водителю, который сбил насмерть семь человек (РАССМОТРЕТЬ)
S_v_O(ПРОВЕСТИ) // Российские военные проведут стрельбы у сирийских берегов (ПРОВЕСТИ)
S_v_O(ПЕРЕХВАТИТЬ) // Иран перехватил иностранный беспилотник (ПЕРЕХВАТИТЬ)
S_v_O(ВЕСТИ) // Лондон и Душанбе ведут переговоры о транзите для британских войск (ВЕСТИ)
S_v_O(ПРОИЗВЕСТИ) // Метеорит произвел неожиданный психологический эффект  (ПРОИЗВЕСТИ)
S_v_O(ПРОЛИВАТЬ) // Новое исследование проливает свет на эволюцию чёрных дыр (ПРОЛИВАТЬ)
S_v_O(ПРЕВРАЩАТЬ) // эстонское государство превращает гражданство Эстонии в средство подкупа (ПРЕВРАЩАТЬ)
S_v_O(ПЕРЕДАВАТЬ) // НАСА передаёт операционный контроль над метеорологическим спутником (ПЕРЕДАВАТЬ)
S_v_O(КОМПЕНСИРОВАТЬ,соверш) // Государство компенсирует гражданам ущерб за свои действия (КОМПЕНСИРОВАТЬ)
S_v_O(КОМПЕНСИРОВАТЬ,несоверш)
S_v_O(ЗАНЯТЬ) // путь теперь сам займет ее место! (ЗАНЯТЬ)
S_v_O(выхватить) // неожиданно призрак выхватил меч из ножен
S_v_O(носить) // все носили кожаные доспехи.
S_v_O(поднять) // все подняли глаза кверху.
S_v_O(включать) // список включает семнадцать фамилий
S_v_O(бомбить) // Дипломат заявил, что израильские самолеты действительно бомбили какие-то сирийские объекты
S_v_O(задевать) // Крылья ее обвисли и развернулись, их концы задевали верхушки травы.
S_v_O(ПОДЧЕРКИВАТЬ) // Темно-серые колготки и яркие кружевные блузы рельефно подчеркивали все интересные места их статных фигур (ПОДЧЕРКИВАТЬ)
S_v_O(ПРИКРЫВАТЬ) // Юбки двух девушек едва прикрывали ягодицы. (ПРИКРЫВАТЬ)
S_v_O(РАЗРУШИТЬ) // Антенны матриц разрушат невральные связи, и разум Звонарей овладеет телами людей. (РАЗРУШИТЬ)
S_v_O(ОБВИНИТЬ) // Израиль обвинил Дамаск в применении химоружия (ОБВИНИТЬ)
S_v_O(РОЖДАТЬ) // Трение рождало очарование и полезность. (РОЖДАТЬ)
S_v_O(РАЗРАБАТЫВАТЬ) // Китай разрабатывает собственный бомбардировщик (РАЗРАБАТЫВАТЬ)
S_v_O(РАСПРАВЛЯТЬ) // Автоконцерны расправляют паруса (РАСПРАВЛЯТЬ)
S_v_O(ВЫТЯНУТЬ) // Пластырь вытянул весь гной (ВЫТЯНУТЬ)
S_v_O(СОЗДАВАТЬ) // Столкновения космических тел с Луной создавали моря из магмы (СОЗДАВАТЬ)
S_v_O(ЗАПИСАТЬ) // Замминистра транспорта Великобритании записал музыкальный альбом (ЗАПИСАТЬ)
S_v_O(УНИЧТОЖАТЬ) // Солевые и пылевые бури уничтожают урожаи и растительность
S_v_O(ОТКРЫТЬ) // Крым открыл в Москве собственный туристический офис
S_v_O(побить) // ранние морозы побили все цветы
S_v_O(относить) // Ветер относил от них дым и феромоны паники.
S_v_O(продолжать)

// Обычно дательное дополнение идет после глагола "ОБЪЯВИТЬ":
// Министр финансов Бельгии объявил об отставке.
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { rus_verbs:объявить{2}.<OBJECT>*:*{ 1 ПАДЕЖ:ДАТ } }
  then -2
}


// Наказываем небольшим штрафов за присоединение наречия к модальному в
// паттерне МОДАЛЬНЫЙ+НАРЕЧИЕ+ИНФ:
// где она могла теперь быть?
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{ МОДАЛЬНЫЙ 1 }.{
                                  наречие:*{2}
                                  инфинитив:*{3}
                                 } }
  then -1
}



// лошади всегда можно верить.

wordentry_set ИнфКакВеритьДляМожно=инфинитив:{ верить, доверять, доверить, поручить, приказать }
tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { безлич_глагол:можно{}.{
                                     *:*{ падеж:дат }
                                     ИнфКакВеритьДляМожно
                                    } }
  then -2
}
