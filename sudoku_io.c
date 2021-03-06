
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sudoku_io.h"



struct Sudoku parseSudoku (const char* file_name)
{

  FILE* file = fopen (file_name, "r"); // opens the sudoku file with read privileges
  int length = 0;
  fscanf (file, "%d", &length);
  //printf("%d\n", length);
  int i,j = 0;



  //int sudoku[(int)pow(length,4) - 1];
  int lengthRowCol = (int)pow(length, 2);
  int **s = (int**) malloc(lengthRowCol * sizeof(int *));

  for(int i = 0; i < lengthRowCol; i++){
    s[i] = (int*) malloc(lengthRowCol * sizeof(int));
  }



//  int (*sudok)[lengthRowCol] = malloc(sizeof(int[lengthRowCol][lengthRowCol]));
  int sudoku[lengthRowCol][lengthRowCol];
  while (!feof (file))
    {
      if(j == lengthRowCol){
        //printf("The j is : %d\n", j);
          i += 1;
          j = 0;
      }
      fscanf (file, "%d", &s[i][j]);
      //printf ("%d ", sudoku[i][j]);
      j+= 1;
      //printf("%d\n", i);
    }

  fclose (file);

  struct Sudoku sud = {lengthRowCol, s};

  return sud;

}

enum STATE check_list(int* array, int length){


    int emptyCells = 0;

    for(int i = 0; i < length; i++){
      if(array[i] == 0){ //check if empty cell
        emptyCells = 1; //and changes the flag of empty cell to on (true)
        continue;
      }
      //brute forcing
      for(int j = i - 1; j >= 0; j--){ //if its not empty it compares with previous values
        if(array[j] == array[i]){
        //  printf("%s\n", "INVALID");
          return INVALID;
        }
      }
    }
    //if the flag is 1 and is not invalid return incomplete
    if(emptyCells == 1){
    //  printf("%s\n", "INCOMPLETE");
      return INCOMPLETE;
    }
    //else return complete
  //  printf("%s\n", "COMPLETE");
    return COMPLETE;


}

enum STATE check_sudoku(struct Sudoku sud){

  int array[sud.length];
  int incomplete = 0;
    int index2 = 0;

    //check for all rows

    for(int i = 0; i < sud.length; i++){
      for(int j = 0; j< sud.length; j++){


          array[index2] = sud.sudoku[i][j];
          index2+= 1;
          if(j == sud.length - 1){
            //ptr = array;

            enum STATE state = check_list(array, sud.length);

            if(state == INVALID){

              return INVALID;
            }
            else if(state == INCOMPLETE){
              incomplete = 1;
            }

          }
       }
       index2 = 0;
    }

    //check for all columns
    int index3 =0;
    for(int f = 0; f < sud.length; f++){
      for(int h = 0; h< sud.length; h++){

          array[index3] = sud.sudoku[h][f];
          index3+= 1;
          if(h == sud.length - 1){
            enum STATE stateCol = check_list(array, sud.length);
            if(stateCol == INVALID){
              return INVALID;
            }
            else if(stateCol == INCOMPLETE){
              incomplete = 1;
            }

          }
       }
       index3 = 0;
    }



    int index1 = 0;
    int smallLength = sqrt(sud.length);

    for(int section = 0; section < sud.length; section+=smallLength){
      for(int l = 0; l < sud.length; l++){
        for(int m = section; m < section+smallLength; m++){
          array[index1] = sud.sudoku[l][m];
          index1+=1;
        }
        if(l != 0 && (l+1) % smallLength == 0){
          index1=0;
          enum STATE stateBox = check_list(array, sud.length);
          if(stateBox == INVALID){
            return INVALID;
          }
          else if(stateBox == INCOMPLETE){
            incomplete = 1;
          }
        }
      }
    }

    if(incomplete == 1){
      return INCOMPLETE;
    }
    else{
      return COMPLETE;
    }
    return COMPLETE;
}

/*
  // Define a pointer to walk the rows of the 2D array.
int (*p1)[25] = test;

// Define a pointer to walk the columns of each row of the 2D array.
int *p2 = NULL;

// There are three rows in the 2D array.
// p1 has been initialized to point to the first row of the 2D array.
// Make sure the iteration stops after the third row of the 2D array.
for (; p1 != test+3; ++p1) {

    // Iterate over each column of the arrays.
    // p2 is initialized to *p1, which points to the first column.
    // Iteration must stop after two columns. Hence, the breaking
    // condition of the loop is when p2 == *p1+2
    for (p2 = *p1; p2 != *p1+2; ++p2 ) {
        printf("%d\n", *p2);
    }
}
*/

  void freeSudoku(struct Sudoku sud){
    free(sud.sudoku);
  }



void printSudoku(struct Sudoku sud){

  for(int i = 0; i < sud.length; i++){
    for(int j = 0; j < sud.length; j++){
      printf("%d ", sud.sudoku[i][j]);
    }
    printf("\n");
  }

  enum STATE state = check_sudoku(sud);

  if(state == INVALID){
    printf("%s\n", "INVALID");
  }
  else if(state == INCOMPLETE){
    printf("%s\n", "INCOMPLETE");
  }
  else{
    printf("%s\n", "COMPLETE");
  }

  //free a sudoku

  freeSudoku(sud);


}

int main (int argc, char *argv[]){
  //int ans = cellAccepted(parseSudoku(argv[1]), 7, 4, 25);
  printSudoku(parseSudoku(argv[1]));
  //printf("%d\n", ans);

  //int sudokuSolve = sudokuSolver(parseSudoku(argv[1]), 0, 0);

}
