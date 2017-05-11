Курсач

Задания:
1. git daemon. git status за O(1)
2. --
3. Прокся

Нужно чтобы обойти запрет роскомнадзор

Прокси сервер:
три компоненты (или две)
1. sockets wrapper
2. http libray
3. program

Начало. echo server.
функции:
socket(protocol IP|IPv6, type STREAM(tcp) | DGRAM(udp)) 
bind (socket s, IP:PORT)
listen(s, BACKLOCK_MAX)
while ()
{
	s2 = accept(s);
	read(s2);
	write(s2);	
	close (POSIX);

}

telnet
lsot -i 
ptrace