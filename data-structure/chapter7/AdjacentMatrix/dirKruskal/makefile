OBJ=AdjacentMatrix.o main.o
AdjacentMatrix:
	gcc -o $@ ${OBJ}
AdjacentMatrix.o:
	gcc -g -c AdjacentMatrix.c AdjacentMatrix.h
main.o:
	gcc -g -c main.c AdjacentMatrix.h
rmexe:
	rm AdjacentMatrix
clean:
	rm *.o
