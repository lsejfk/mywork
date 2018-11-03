obj:
	gcc -fPIC -g -c -Wall c_program_source.c -I/usr/local/include/mysql/include
share:
	gcc -shared -o libc_program_source.so c_program_source.o -L/usr/local/include/mysql/lib -lmysqlclient

