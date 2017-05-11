Как компилировать из консоли.
strace показывает какие системные вызовы она сделала

Компиляция, в результате получается объектный файл
Можно компилировать по отдельности в объектные файлы а потом их линковать. И если мы изменили один файл, можно не компилировать другие, а потом слинковать старые 
объектные и новый.
Это называется статической компиляцией. Популярные библиотеки будут дублироваться. К тому же, если в популярной библиотеке нашли ошибку то надо все перекомпилировать

Статическая линковка - кидаем все файлы в одну кучу и это исполняемый файл
Динамическая - если нужна функция, идем по пути к этой самой библиотеке

функция main не вызывается первой в программе. Есть какая-то функция _start

void _start() {
	...
	res = main(...);
	exit(res);
}

.o - объектный файл
.so - готовая библиотека

Динамическая линковка
gcc -c -shared -fpic hello.c -o hello.o
gcc -shared -fpic hello.o -o libhello.so
gcc -c main.c -o main.o
gcc -L. -lhello main.o -o main

-L. где искать библиотеки. Искать в . -L/usr/
-lhello будет искать libhello.so

Но если так запустить, то библиотека не будет найдена, так как не будет искать в текущей библиотеке. -L указывает где искать библиотеки во время компиляции, а не на время запуска

Один из способов 
export LD_LIBRARY_PATH=/home/nikitaevg... Это указать где еще искать библиотеки

Есть флаги -Wl, -rpath=. записывает где искать библиотеки во время запуска. -Wl, - передать линковщику следующий аргумент

nm - информация об объектном файле

команда make цель. 

Можно сделать цикл зависимостей и хорошо бы чтобы в нем не было циклов.
Если изменили какой-то файл в дереве, обновляем все ниже вплоть до main. Смотри фото 09.02. 
Сравнивает по дате чтобы понять что обновлять.
Как примерно выглядит makefile

имя_цели: имя_зависимости_1 имя_зависимости_2
	команда компиляции

имя_функции
	команда для выполнения

В makefile $@ цель $< зависимость
make без аргументов вызывает первую цель