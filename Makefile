all: libsudoku.o sudoku

libsudoku.o:
	gcc -O3 -march=native -c -o libsudoku.o src/libsudoku.c

sudoku:
	gcc -O3 -march=native -o sudoku libsudoku.o src/sudoku.c
	strip sudoku

clean:
	rm libsudoku.o sudoku
