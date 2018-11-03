############
# makefile #
############

#target source object
SOURCE := MergSort.c
OBJS := MergSort.o
TARGET := MergSort

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
