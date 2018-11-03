############
# makefile #
############

#target source object
SOURCE := test8.7.c
OBJS := test8.7.o
TARGET := test8.7

#compile and lib parameter
CC := gcc
LIBS := -lmyerr
LDFLAGS := -L/home/michael/local/src
INCLUDE := -I/home/michael/local/include

#link
$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

#compile
$(OBJS):$(SOURCE)
	$(CC) -g -c $^ $(INCLUDE) -o $@ 
#clean
clean:
	rm *.o
	rm $(TARGET)
