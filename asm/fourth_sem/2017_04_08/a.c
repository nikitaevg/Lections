gdt, сегменты
У программ был .start чтобы обращаться к глобальным переменным (?)
Сначала начало сегмента было seg*16 + ofs
Потом появилась gdt в которой были base и limit, а также появились ldt,
что позволило сделать память 16-мегабайтные памяти