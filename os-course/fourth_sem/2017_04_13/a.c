Мультиплекирование ввода-вывода

Много файловых дескрипторов. Некоторые на чтение, некоторые на запись

К примеру -- веб-сервер

Способы:
1. неблокирующий ввод-вывод 
	блокирующий -- 
		r = read(fd, ...)
		висит пока не придут данные
		ответ через некоторое время 
	неблокирующий --
		r = read(fd, ...)
		сразу завершается
		отвечает сразу и с ошибкой errno == EWOULDBLOCK, если данных нет
		отвечает сразу без ошибки, если данные есть
	чтобы сделать неблокирующий ввод у read, надо сделать такую хрень с флагами:
		int flags = fcntl(STDIN_FILENO, F_GETFL); // -- берем флаги для stdin
		flags |= O_NONBLOCK;
		fcntl(STDIN_FILENO, F_SETFL, flags); // -- кладем их обратно с NON_BLOCKING
		char ch;
		int r = read(STDIN_FILENO, &ch, 1);
		(man fcntl(2))
	Как решает задачу:
		int fds[] = ...; // фд с неблокирующим вводом/выводом
		for (fd : fds)
		{
			if (!read(fd))
				continue;
		}
		но это медленно и жрет процессор
2. fork
	по процессу на каждый фд
	while (true)
	{
		int client = accept();
		if (fork() == 0)
		{
			close_all(); // -- закрыть все фд кроме текущего
			process(client);
			exit();
		}
	}
	но создание большого количества процессов хреново. 
	Но зато тут нет busy-wait
	Также создадутся много зомби. Могут кончиться pid. это можно делать обработтчиком SIG_CHILD

3. select (2)
	select(int, fd_set, fd_set, fd_set, timeval);
	bitset на FD_SETSIZE ≈ 1024 элементов
	См. фото или читай man
	Можно использовать как таймер
	Работает и работает везде, но работает долго и хрен знает как и fd < 1024
	Нужно вызывать select каждый раз когда хочешь что-то получить

4. poll
	poll(pollfd, nfds_t, int); // nfds -- number of fds
	pollfd 
	{
		int fd; // file descriptor
		short events; // requested events пример -- хотим читать или писать
		short revents; // returned events -- ответ, что можно делать с этим fd
	}
	но снова бежать по списку и это долго
	игнорирует отрицательные fd
	events:
		POLLIN
		POLLOUT
		POLLRDHUP --сообщить когда socket закрют с другой стороны.
	revents: смотри man

	плюсы: работает с большими номерами
	минусы: много фд работает медленно.

5. epoll
	только для Linux
	Как poll но список в ядре хранится, и ядро отвечает за то, чтобы выдать те фд в которых что-то изменилось

	int epoll_create(size); -- возвращает fd
	epoll_ctl(epfd (файловый дескриптор из первой операции)
		, op -- операция для работы с еполлом
		, fd -- какой fd смотреть
		, epoll_event* event -- что делать с fd); -- настройка
	eopll_wait(int epfd,
		epoll_event* events -- что куда делать,
		int maxevents, int timeout);
	см ман про epoll+data и epoll_event
	события как в poll только начинаются с E
уведомления о результате:
	level_triggered -- уведомление на каждый запрос 
		select pol, epoll
	edge_triggered -- уведомление только при изменениях фд
		epoll, ввод-вывод на сигналах
	EPOLLONESHOT -- события одноразовые. Для многопоточности

Еще о O_NONBLOCK
	accept
	while (true)
	{
		int cnt = poll(...);
		for (fd : fds)
		{
			...
			accept(fd, ...);
		}
	}
	если после poll и перед accept клиент отключился, то accept будет ждать нового клиента. 
	Но можно сделать non blocking accept
Сигналы
	1. Можно добавить pipe в epoll, pipe, привязанный ко всем сигналам
	2. pselect(2)
		атомарный select
		то же и с разными другими операциями

6. Сигналы
	SIGIO, когда стало можно что-то делать
	fcntl(fd, F_SETOWN, pid);
	добавить O_ASYNC
	минусы: не понятно с каким фд работать
	Realtime-сигналы
		Несколько сообщений в сигнале
		информация о том, в каком фд что-то произошло
