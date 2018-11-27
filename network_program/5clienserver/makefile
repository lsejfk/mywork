CC = gcc
OPTION = -g -Wall
INCLUDES = -I /home/michael/local/include
LIBPATH = -L /home/michael/local/src
LIBS = -lunp -lmyerr
OBJS = echoserver.o 
TARGET = echoserver
.PHONY:all clean

all:${OBJS}
	@echo "Building..."
	${CC} ${OPTION} ${INCLUDES} ${OBJS} -o $(TARGET) $(LIBPATH) $(LIBS)
%.o:%.c
	${CC} ${OPTION} -c $*.c ${INCLUDES}
clean:
	@echo "cleaning up.."
	-rm -f *.o
	-rm test
