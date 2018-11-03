CC = gcc
OPTION = -g -Wall
INCLUDES = -I/home/michael/local/include
LIBPATH = -L/home/michael/local/src
LIBS = -lmyerr -lunp
OBJS =  printconinfo.o
.PHONY:all clean

all:${OBJS}
	@echo "Building..."
	${CC} ${OPTION} ${INCLUDES} ${OBJS} ${LIBPATH} ${LIBS} -o test
%.o:%.c
	${CC} ${OPTION} -c $*.c ${INCLUDES}
clean:
	@echo "cleaning up.."
	-rm -f *.o
	-rm test
