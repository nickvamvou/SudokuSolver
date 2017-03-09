enum STATE {INVALID, INCOMPLETE, COMPLETE};
struct Sudoku{
  int length;
  int** sudoku;
  //int* emptyCells;
  //enum STATE state;
};
int sudokuSolver(struct Sudoku sud, int row, int col);
int cellAccepted(struct Sudoku sud, int row, int col, int temp);
void printSudoku(struct Sudoku sud);
enum STATE check_sudoku(struct Sudoku sud);
enum STATE check_list(int* array, int length);
struct Sudoku parseSudoku (const char* file_name);
void freeSudoku(struct Sudoku sud);
