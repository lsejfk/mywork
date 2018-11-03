CC = gcc
OPTION = -g -Wall
INCLUDES = -I .
OBJS = test5.13a.o hashquad.o
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
