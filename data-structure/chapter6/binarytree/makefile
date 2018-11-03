SRC=BinTreeStruct.c main.c LinkStack.c
OBJ=BinTreeStruct.o main.o LinkStack.o
LIB=-I./
cBinTree:
	gcc -c ${SRC}
BinTree:
	gcc -g -ggdb -o $@ ${OBJ} ${LIB}
clean:
	rm *.o
rmexe:
	rm BinTree

