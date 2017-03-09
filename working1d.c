
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sudoku_io.h"




void parseSudoku (const char* file_name)
{
  FILE* file = fopen (file_name, "r"); // opens the sudoku file with read privileges
  int length = 0;
  fscanf (file, "%d", &length);
  printf("%d\n", length);
  int i = 0;
  int sudoku[(int)pow(length,4) - 1];

  while (!feof (file))
    {
      fscanf (file, "%d", &sudoku[i]);
      //printf ("%d ", sudoku[i]);
      i+= 1;
    }
  fclose (file);

}

void storeSudoku(){

}





int main (int argc, char *argv[]){

  parseSudoku(argv[1]);


}
