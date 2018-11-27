CC = gcc
OPTION = -g -Wall
INCLUDES = -I /home/michael/local/include
LIBPATH = -L /home/michael/local/src
LIBS = -lmyerr -lpthread
OBJS = barrier.o 
.PHONY:all clean

all:${OBJS}
	@echo "Building..."
	${CC} ${OPTION} ${INCLUDES} ${OBJS} -o test $(LIBPATH) $(LIBS)
%.o:%.c
	${CC} ${OPTION} -c $*.c ${INCLUDES}
clean:
	@echo "cleaning up.."
	-rm -f *.o
	-rm test
