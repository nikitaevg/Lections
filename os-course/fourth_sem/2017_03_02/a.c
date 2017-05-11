Организация просессов:
завершение процесса 
elif syscall == EXIT_TAG:
	pass

Как убить снаружи

elif syscall = TAG_KILL: // убивает процесс
	which = args[0]
	processes.erase_if(lambda p: proc.proc_info.id == which) //удаляет из списка процессов процесс с нужным айдишником

is_child = fork() //информация, которая помогает узнать, является ли процесс ребенком или родителем

man 2 fork
pid_t fork(void) // тот самый айдишник

pid_t child_pid = fork()
if (child_pid == 0) {
	...
} else {
	...
}

process namespaces
их тоже можно подменять
$docker run ubuntu:16.04 ps //позволяет запускать процесс изолированно от остального окружения
ps -- список процессов
ps a процессы пользователя

$? - код возврата последней программы

zombie process

#include ...
int main()
{
	if (!fork())
		return 42;
	sleep (10);
	return 0;
}

Коды возврата только у процессов, прямым родителем которого мы являемся. 
В предыдущей программе нельзя увидеть 42. Хочется знать какой процесс вернул этот результат. Смотри фото 03.02

зомби процесс - процесс, который уже отработал, но не умер, его должен убить родитель. Пример сверху
data Zombie = Zombie {
	ppid :: PID
	pid :: PID
	ret :: RecCode
	stat :: Statistics
} 

зомби ждет, пока его закопают

S -- sleep (ожидают чего-то, пока запустят ил ввода)
R -- run. Обычно в районе числа CPU
Z -- zompie
T -- Traced
D -- disk sleep

Сохранять зомби надо, чтобы забрать код возврата. Если сказать что этот пид свободен, то кто-то другой
может запуститься с этим пид и непонятно будет какой ретерн надо взять

Как закапывать зомби
man 2 waitpid
pid_t waitpid(pid_t pid, int* wstatis, int options) -- закопали. Ждет пока процесс pid завершится и утилизирует его ресурсы
pid_t wait (&st) = waitpid(-1, &st, ...) -- первый ребенок, который завершится закопать его. wait -- депрекейтед

При убийстве процесса его дети переподвешиваются к инит

fork bomb

int main()
{
	while (1)
		if (fork())
			return 0;
}

int main()
{
	fork();
	return 0;
}

В strace будет вызов clone а не fork.

Владельцы процессов
whoami
Идентификация происходит по uid
Их можно найти в /etc/passwd

Изменить пользователя
int setuid(uid_t uid);

Различают real UID и effective UID kill смотрит на RUID а остальные на EUID (или наоборот)
setreuid

Может быть так что делаешь sudo, и все,тебе не убить этот процесс, так как он имеет права root. Для этого различают R и EUID

So, the real user id is who you really are (the one who owns the process), and the effective user id is what the operating system looks at to make a decision whether or not you are allowed to do something (most of the time, there are some exceptions).














