init

Его задачи -- запускать все процессы в системе и убивает зомби.

SysVInit
несколько уровней запуска (runlevel)
	0 - выключить компьютер
	1 - однопользовательский режим
	3 - многопользовательский режим
	5 - многопользовательский + GUI
	6 - перезагрузка

При запуске выбирается уровень

Настройки SysVInit
etc/inittab 
строки формата id:runlevels:action:cmd
id:список уровней на которых можно запускать:действие:команда для запуска этого действия

Действия:
initdefault -- уровень по умолчанию
respawn -- флажок "перезагружать при завершении процесса"
wait 
once -- оба похожи, оба запускают единожды процесс. Но wait ждет завершения процесса
ctraltdel -- что при Ctrl+Alt+del
...

telinit перейти на другой уровень.

etc/rc[0-9].d -- файлы сервисы
симлинк в /etc/init.d
Сервисы надо запускать в каком-то порядке
Будем писать 
KDDname
K - ничего, S - запустить
DD - приоритет 00-99
name - имя сервиса

bash-скрипты
	service ssh start
	... stop
	... restart
	... status

Эта штука не параллельно
неудобно следить за зависимостями (сервисы исполняются в порядке DD, без зависимости друг от друга)

Альтернативы:
	Upstart
	OpenRC
	systemd (все кроме Gentoo)

systemd:
следит за всем.

systemd заменил кучу всяких утилит в linux

Зависимости:
	Requires (если нужный сервис не удался, не запускаем и этот)
	Wants	(запускаем даже если не удалось)
	WantedBy
Порядок:
	After
	Before
Тип (action из init)
restart
	no
	always

Еще(что?)
journalctl
socket activation
Шаблоны