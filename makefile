
make : sudoku_check sudoku_solve
sudoku_io.o:	sudoku_io.c sudoku_io.h
							gcc -c sudoku_io.c
sudoku_solver.o:	sudoku_solver.c sudoku_io.h
									gcc -c sudoku_solver.c
sudoku_check:	sudoku_io.o
							gcc -o sudoku_check sudoku_io.o -lm
sudoku_solve :	sudoku_solver.o
							gcc -o sudoku_solve sudoku_solver.o -lm
clean:
			rm sudoku_io.o sudoku_solver.o
