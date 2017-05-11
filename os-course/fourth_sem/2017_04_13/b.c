Capabilities
Избавиться от рута
Более тонкая настройка прав
man 7 capabilities
CAP_DAC_OVERRIDE, CAP_DAC_READ_SEARCH -- читать писать файлы

CAP_KILL -- слать сигналы
Реализация
У процесса 
	permitted set
	inheritable set
	effective set
у файла
	permitted set
	inheritable set
	effective bit

Сложные формулы персчета при exec-e