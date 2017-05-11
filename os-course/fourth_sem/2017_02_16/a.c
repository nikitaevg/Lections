Разделение памяти между процессами

Физическая память. Не доступна процессам. Им доступна виртуальная память.
Адресное пространство -- доступная процессу память. 
виртуальная память не совпадает с физической, где-то происходит преобразование.
Для каждого байта хранить мап на физическую память слишком жирно, поэтому память поделена на страницы - 4 Кб

Есть бит present - замаплена ли эта страница или нет. при обращении к present = 0 бросается исключение.
Бит dirty - как-то относится к swap. Изменились ли данные или нет. где-то относительно чего-то

memoryManagementUnit : VirtAddr -> PhysAddr

Ядро загружает мапу в MMU  а потом процессор обращается к памяти через MMU
Для каждого процесса свой map. При переключении на другой процесс в MMU загружается map процесса.

Это хранящаяся для каждого процесса память.
Контекст исполнения
	MMU
	регистры

credentials 
	PID, PPID, PGRP, SID
	UID, GID, EUID, EGIP

PWD, env, cmdline, ...

fork реализован с помощью copy-on-write. Раньше это было не так и fork долго работал

Переключение MMU дорогая память. 

vfork создается новый процесс сохраняя ровно ту же мапу, без copy-on-write

Файловая система

Разделения на разные устройства в линуксе нет, все подвешено к папке /, в отличие от винды

data FS = File data
	| Dir (Map String FS)
	| Mounted FSID

type MountNamespace = [ (String, FSID) ]

[ ("/home", "/dev/sdb1"), ("/tmp", tmpfs) ]

MountNamespace разные для разных процессов

mount /dev/sdb1 /mnt/ - смонтировать новое поддерево, хранящееся в sdb1. Фактически смонтировать флешку или диск с названием sdb1
chroot /mnt /bin/bash - изменить корень с / на /mnt/. К примеру если хочется переключиться на другую систему.
/mnt - новый корень. /bin/bash - процесс который нужно запустить. Относительно /mnt/

Старый корень станет невидимым.

int mount (src, trg)
int umount (trg)
это системные вызовы.

mount --bind можно сказать типа "Используй это дерево вместо того дерева" 

data FS = File Inode
	| Dir (Map String FS)
	| Mounted FSID

type MountNamespace = [ (String, FSID, Inode) ]

data Inode = Inode {
	atime :: Time,
	mtime:: Time,
	ctime :: Time, 
	uid :: UID,
	gid :: GID,
	modes :: Modes,
	data :: [Byte]
}

для разных систем Inode разная.

type AInode = (FSID, Inode) - абсолютная адресация по Inode

const char msg [] = "Hello";
write (1, msg, sizeof(msg));

1 - дескриптор файла.
type FD = Int
type FDState = Int // offset -- сколько прочитали или записали
type FDTable = Map FD (AInode, FDState)

int open (path, flags, mode) - возвращает номер файлого дескриптора
int close (fd); - 0 удалось закрыть -1 не удалось

a > b -- перенаправляет вывод a в b

Хотим взять FD log.txt и подменить его вместо стандартного потока вывода

int dup(int oldfd) -- берет минимальный файловый дескриптор.
int dup2(int oldfd, int newdf);

data Modes = Modes {
	x :: x
	owner :: RWX
	group :: RWX
	all :: RWX
}

бит x отвечает за то, чтобы можно было узнать Inodе у файлов.

data X = X {
	setuid :: Bool 
	setgid :: Bool
	stickybit :: Bool --  раньше для исполняемых файлов не выгружать из памяти как можно дольше. Теперь что из директории файл может удалять только владелец.
}

chmod 1777 /tmp. Значит что удалять чужие файлы никто не может из-за stickybit


sudo -- запустить программу от имени другого пользователя, обычно это root
у sudo повышенные привилегии чтобы узнавать пароль root-а

находится в /usr/sbin/sudo
u rwxr-xr-x
бит u позволяет выполнять команду с правами владельца файла. это setuid. setgid примерно то же самое.


int chmod (path, mode);
int chown(path, owner, gid);