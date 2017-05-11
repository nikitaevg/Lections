Сигналы

signal (int signum, handler_t handler);
 См. фото
-//-

Новая штуковина --  sigaction

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);

man sigaction

struct sigaction sa;
memset (&sa, 0, sizeof(struct sigaction));

sigemtpyset(&sa.sa_mask);
sa.sa_handler = handler;
sigaction(SIGUSR1, &sa, NULL);

смотри ~os

Внутри обработчика сигнала можно вызывать только некоторые функции: список в man 7 signal
Не могут быть вызваны функции с реентрэнс(?)
SIGSTOP и какой-то еще нельзя переопределять так как он не доходить до программы а обрабатывается ядром

ИНформация о сигнале: siginfo_t

realtime signals
sigqueue (pid, sig, value);

int signalfd(fd, mask, flags) read man создает файл для сигнала.




GDB

есть backtrace, круто.
В общем там есть много всего.