Межпроцессное взаимодействие.
Фотки
Пайп
В ядре: int pipe(int pipefd[2] -- файловые дескрипторы двух концов пайпа)

pipefd[1] -> buf -> pipefd[0]
Используется только между процессами одного и того же дерева процессов

O_CLOEXEC -- флаг чтобы файловый дескриптор закрывался при окончании процесса

mkfifo? /tmp/example_fifo -- пайп, привязанный к файловой системе. 

int mkfifo (const char * pathname, mode_t mode);

Если открыть на запись, откроется один конец, в противном случае другой.

Чтобы работать с fifo, нужно чтобы оба конца были открыты.

mmap
семантика:
void* mmap(void* addr, size_t length,
	int prot, int length, int fd, off_t offset);
флаг MAP_ANONYMOUS

fd чтобы мапать файлы на виртуальную память. offset по какому смещению fd. 
флаг SHARED -- copy-on-write или нет
флаг анонимности -- выделить память, не используя файлы. Просто выделить память.
Это может быть использовано тоже только для процессов из одного дерева

shm_open выделяет shared memory. Тут можно общаться процессам из разных деревьев, так как создается ссылка на реальную память (типа того) смотри фото

kill
int kill(pid_t pid, int sig);
sig - сигналы

int sigaction (int signum, const struct sigaction* act, struct sigacion* oldact);

контекст исполнения
sigpending : vector<bool> 
sigmask : vector<bool>
proc_info {
	pid, uid, ppid, gid, sigpending, 
	sigmask, sighandler -- контекст исполнения
} -- credentials

Контекст исполнения -- mmu, регистры, и то что сверху. Неявные данные, не видные для процесса, которые позволяют ему нормально работать

man 7 signal !!! - все сигналы

sigqueue

Если процесс ждет чтения и ему приходит сигнал, то системный вызов прерывается, посылается сигнал и обработчик, не все вызовы после этого сами восстанавливаются

Сокеты. Двусторонний пайп.
Юникс-сокеты. Штука, привязанная к файловой системе. Сокеты привязываются к портам.