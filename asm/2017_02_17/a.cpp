Introduction to x86

8086

Модель памяти

Пусть компьютер состоит из одного процессора и одной RAM

Память - набор пронумерованных ячеек

Пусть можно считывать один байт. На деле считывается по n байт

CPU
IP -- instruction pointer -- указатель на адрес в памяти где лежит команда.
Считывает команду, выполняет, сдвигает IP на длину команды.

Регистры и т.п. 
Типичные команды. 

[AX] -- значение по адресу AX

mov [x] [y] нельзя. это не mem-mem только reg-mem-2

Смотри конспект со второго курса про SUB, AND, OR итд

INC AX  ||  AX++ 
DEC AX  ||  AX--
NEG AX  ||  AX = -AX
NOT AX  ||  AX = ~AX

MUL и DIV имеют беззнковые аналоги, так как используется дополнение до двойки и эти команды различаются.
 ADD и SUB в то же время не различаются

делить 16 бит на 16. 
В беззнаковом случае достаточно занулить AX. Это делается xor dx dx. Так быстрее чем mov. 
не совсем понятно почему. Так команда короче. mov dx 0x3124 -- BA3412 А xor dx, dx -- 31D2

cwd - служит для того чтобы делить 16 на 16. sxxxxxx превращает в ssssssxxxxxx где s это sign. 

При делении на ноль управление передается операционной системе и что-то происходит.
INT_MIN/-1 - очень жесткая хрень. Бросается та же ошибка что и при делении на ноль

Инструкция LEA
MOV AX [reg+(1/2/4/8) * reg2 + integ] - одна команда. Начиная с 32-битных регистров. Можно так писать

LEA AX [reg+(1/2/4/8) * reg2 + integ] положить тот адрес в AX. Сделано чтобы не писать много раз add sub итд.

SHR SHL SAR коспект второго сема

ROL ROR - циклические сдвиги

SHL AX - сдвинуть на один

XL - младшие восемь бит регистра X

JMP
loop: 
	jmp loop
	преобразуется в EB FD, где FD - -3 значит прыгнуть на 3 назад

если label лежит дальше чем на 128 то используется длинная версия JMP которая кодируется с двумя числами - 
чтобы обозначить адрес, так как одного числа не хватит

Всякие флаги
cmp ax bx
je - jmp if equals

Для всяких сравнений исопльзуется регистр FLAGS
Разные биты FLAGS для разных нужд. Некоторые системные биты и их вроде нельзя юзать. 

ADD и SUB также меняют FLAGS.
SUB и CMP примерно то же самое только CMP не записывает результат.

JE (=JZ) потому что разность равных чисел -- 0

JA и JB смотрит на флаг переноса, который означает что из меньшего вычитали большее JA JB - беззнаковые

JB (=JC)
