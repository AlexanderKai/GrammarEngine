﻿// Только некоторые глаголы могут присоединять творительное дополнение, являющееся
// названием организации. Это правило помогает устранить альтернативы в случае 
// несклоняемых аббревиатур:

// МВФ призвал Токио решиться на более амбициозную либерализацию монетарной политики


tree_scorer ВалентностьГлагола language=Russian generic
{
 if context { *:*{ ~AllowInstrName }.существительное:*{ падеж:твор <в_класс>СУЩЕСТВИТЕЛЬНОЕ:ОРГАНИЗАЦИЯ{} } }
  then -5
}