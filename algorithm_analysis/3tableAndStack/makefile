############
# makefile #
############

#target source object
SOURCE := 
OBJS := 
TARGET := 

#compile and lib parameter
CC := gcc
LIBS := -larray_queue
LDFLAGS := -L/home/michael/local/src
INCLUDE := -I/home/michael/local/include

#link
test:test3.26.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

#compile
test3.26.o:test3.26.c
	$(CC) -g -c $^ $(INCLUDE) -o $@ 
#clean
clean:
	rm *.o
	rm test
