CC = gcc
OPTION = -g -Wall
INCLUDES = -I .
OBJS = test4.39.o 
.PHONY:all clean

all:${OBJS}
	@echo "Building..."
	${CC} ${OPTION} ${INCLUDES} ${OBJS} -o test
%.o:%.c
	${CC} ${OPTION} -c $*.c ${INCLUDES}
clean:
	@echo "cleaning up.."
	-rm -f *.o
	-rm test
