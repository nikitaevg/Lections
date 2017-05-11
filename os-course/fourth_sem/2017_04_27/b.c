Уязвимости

Переполнение буфера. 
scanf("%s", buff); может записать выше buff в стек и перезаписать адрес возврата. Может вообще написать функцию в стеке

Когда сами пишем код на стеке, не знаем куда делать ret. 
Сложно выяснить точный адрес кода (можно на +-10000 байт)
Можно дописать 20000 nop-ов перед зловредным кодом.
То есть должны дать scanf-у 
addr * 50 + nop * 20000

Можно подменять записи PLT, если мы не можем менять адрес возврата. 

Разработчики осей сделали так, что нет страниц  W и X одновременно

Если не можем записанный код, будем довольствоваться имеющимся
Гаджеты -- ошметки кода, оканчивающиеся на ret или call
Напихаем в стек много адресов гаджетов
См. фото
Нужные гаджеты:
Запись нужных регистров
Запись в память
прерывания

Но у каждой функции есть эпилог. Что делать?
Фото
В x86 код расположен очень плотно и ret (c3) может встретиться посередине других команд.

Address space layout randomization
Это не работает, если мы узнали какой-то адрес. Вдруг можем как-то его достать.