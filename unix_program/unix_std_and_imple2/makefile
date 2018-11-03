############
# makefile #
############

#target source object
SOURCE := open_max.c
OBJS := open_max.o
TARGET := open_max

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
