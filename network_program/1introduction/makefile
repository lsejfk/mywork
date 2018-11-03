############
# makefile #
############

#target source object
SOURCE := daytime.c
OBJS := daytime.o
TARGET := daytime

#compile and lib parameter
CC := gcc
LIBS := -lmyerr -lunp 
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
