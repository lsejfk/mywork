############
# makefile #
############

#target source object
SOURCE := fwrite.c
OBJS := fwrite.o
TARGET := fwrite

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
