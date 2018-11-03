CC = gcc
OPTION = -g -Wall
INCLUDES = -I /home/michael/local/include
LIBS = -lmyerr
LIBINC = -L /home/michael/local/src
OBJS = pton.o
.PHONY:all clean

all:${OBJS}
	@echo "Building..."
	${CC} ${OPTION} ${INCLUDES} ${OBJS} -o test ${LIBINC} ${LIBS}
%.o:%.c
	${CC} ${OPTION} -c $*.c ${INCLUDES}
clean:
	@echo "cleaning up.."
	-rm -f *.o
	-rm test
