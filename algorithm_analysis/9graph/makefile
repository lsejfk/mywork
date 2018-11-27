CC = gcc
OPTION = -g -Wall
INCLUDES = -I /home/michael/local/include
LIBPATH = -L /home/michael/local/src
LIBS = -larray_stack -larray_queue
OBJS = test9.21.o hashquad.o adjlist.o
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
