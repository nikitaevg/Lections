Операционная система
Ядро дает интерфейс программисту чтобы взаимодействовать с железом. 
Другой функцией является изоляция ресурсов друг от друга для разных программ.

Многозадачность. Кооперативная многозадачность - многозадачность когда программист говорит что проргамма простаивает, а вытесняющая - прозрачный для программиста интерфейс.
Пример:
a
while True
	# yield -- для кооперативной
	a = read() 
	write(a)


b
for i = 1 to n
	# yield -- для кооперативной
	print(i)

Системный вызов
def main():
	name = read() # обращение к о.с.
	str = "Hello, "++name
	print(str) # обращение к о.с.
	exit(0) # обращение к о.с.

Это три примера системных вызовов

CPS - continuation passing style
(что_сделать_ядру, с_какимим_аргументами, откуда_продолжать)
def main():
    return (Read, [Stdin], cont_main)
def cont_main(name): #здесь мы приняли то что вернул системный вызов
    string = "Hello, " + name + "!"
    return (Write, [string], cont_main2)
def cont_main2(wr_result): 
    return (Exit, [0], NONE)


def kernel ():
	processes = [(main, [])] # список процессов (список пар - функция и ее аргументы)
	while processes:
		p, args = processes[0]
		(syscall, args, cont) = p(pargs) # получаем тройку что надо сделать аргументы и продолжаем.
	    switch(syscall):
	        case Read:
	            read_res = readln(args) #Ядро умеет обращаться с железом и читать из него
	            processes.push(cont, read_res)
	        case Write:
            ...
        # И так далее...
То есть осуществляется кооперативная многозадачность. Выполняется не один процесс постоянно, а несколько по очереди.

Создание нового процесса. 
Происходит с помощью fork. 
!! man 2 fork

	switch tag:
		...
		FORK_TAG:
			processes.push_back(cont, true)
			processes.push_back(cont, false)

Надо как-то различать новый процесс или старый.

def main():
	is_new = fork()
	if is_new:
		exec("/usr/bin/firefox") # системный вызов бинарника
	else:
		print("Hello")

!! man 3 exec


# видимо вызов нового процесса из старого с сохранением старого
def main():
	return (FORK_TAG, [], cont)

def cont(is_new):
	if is_new:
		return (EXEC_TAG, ["..."], None);
	else:
		return (WRITE, ...)


def main():
	return (READ_TAG, [stdin], cont) #а пользователь не хочет ничего вводить. И либо надо виснуть либо как-то обработать

Чтобы обрабатывать такие процессы надо добавить список заблокированных процессов, типа чтение с жесткого диска.

def kernel ():
	processes = [(main, [])] # список процессов (список пар - функция и ее аргументы)
	blocked = []
	while processes:
		p, args = processes[0]
		(syscall, args, cont) = p(pargs) # получаем тройку что надо сделать аргументы и продолжаем.
	    switch(syscall):
	        case Read:
	        	blocked.push_back(tag, args, cont)
	            #read_res = readln(args) #Ядро умеет обращаться с железом и читать из него
	            #processes.push(cont, read_res)
	        case Write:
            ...
        # И так далее...
        # после этого надо пробежаться по заблокированным процессам и проверить можно ли их выполнить. Что-то типа сигналов из плюсов
































