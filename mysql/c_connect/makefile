OBJ=-I/usr/local/include/mysql/include
SUB=-L/usr/local/include/mysql/lib
testc:
	gcc -g -c test_connect.c ${OBJ}
test:
	gcc -o test test_connect.o ${SUB} -lmysqlclient


