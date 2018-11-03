############
# makefile #
############

#target source object
SOURCE := test2.19.c
OBJS := test2.19.o
TARGET := test2.19

#compile and lib parameter
CC := gcc
LIBS := #-lmyerr
LDFLAGS := #-L/home/michael/local/src
INCLUDE := #-I/home/michael/local/include

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
