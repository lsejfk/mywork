############
# makefile #
############

#target source object
SOURCE := heapSort.c
OBJS := heapSort.o
TARGET := heapSort

#compile and lib parameter
CC := gcc
LIBS := 
LDFLAGS := 
INCLUDE :=

#link
$(TARGET):$(OBJS)
	$(CC) -o $@ $^

#compile
$(OBJS):$(SOURCE)
	$(CC) -g -c $^ -o $@ 
#clean
clean:
	rm *.o
	rm $(TARGET)
