#include <stdio.h>
#include "sudoku_io.h"
#include <math.h>
#include <stdlib.h>

int solutionCounter = 0;

struct Sudoku sudCopy;

struct Sudoku parseSudoku1 (const char* file_name)
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

int cellAccepted(struct Sudoku sud, int row, int col, int temp){

  int smallLength = sqrt(sud.length);
  int startingRow = (row/smallLength) * smallLength;
  int startingCol = (col/smallLength) * smallLength;

  //printf("Number checking should be 0 %d\n", sud.sudoku[row][col]);

  for(int i = 0; i < sud.length; i++){

      if(sud.sudoku[i][col] == temp){
        //printf("%s\n", "It goes here 1st");
        return 0;
      }
      if(sud.sudoku[row][i] == temp){
        //printf("%s\n", "It goes here 2nd");
        return 0;
      }
      //printf("Values %d\n", sud.sudoku[startingRow + (i % smallLength)][startingCol + (i/smallLength)]);
      if(sud.sudoku[startingRow + (i % smallLength)][startingCol + (i/smallLength)] == temp){
        return 0;
      }
  }
  return 1;
}


void copySolutionFound(struct Sudoku sud){
  //printf("%s\n", "Does it go here?");
  //printf("Times called : \n");
  int sudokuLength = sud.length;
  int **sudokuCopy = (int**) malloc(sudokuLength * sizeof(int *));

  for(int i = 0; i < sudokuLength; i++){
    sudokuCopy[i] = (int*) malloc(sudokuLength * sizeof(int));
  }

    for(int i = 0; i < sud.length; i++){
      for(int j = 0; j < sud.length; j++){
        sudokuCopy[i][j] = sud.sudoku[i][j];
        //printf("%d\n", sudokuCopy[i][j]);
      }
    }

    sudCopy.length = sudokuLength;
    //printf("Sudoku Length %d\n", sudCopy.length);
    sudCopy.sudoku = sudokuCopy;
}


int sudokuSolver(struct Sudoku sud, int row, int col){

      if(sud.sudoku[row][col] != 0){
        if(col + 1 < sud.length){
          if(sudokuSolver(sud, row, col+1)){
            return 1;
          }
          else{
            return 0;
          }
        }
        else{
          if(row+1 < sud.length){
            if(sudokuSolver(sud, row + 1, 0)){
              return 1;
            }
            else{
              return 0;
            }
          }
            else{
              //printf("%s\n", "Found solution and last cell was non empty");
              solutionCounter += 1;
              if(solutionCounter == 1){
                copySolutionFound(sud);
              }
              /*
              for(int i = 0; i < sud.length; i++){
                for(int j = 0; j < sud.length; j++){
                  printf("%d ", sud.sudoku[i][j]);
                }
                printf("\n");
              }
              */
              return 0;
            }
          }
        }


    else{
      for(int i = 0; i < sud.length; i++){
        int valueToPass = i + 1;
        if(cellAccepted(sud, row, col, valueToPass)){
          sud.sudoku[row][col] = valueToPass;
          if(col + 1<sud.length){
            if(sudokuSolver(sud, row, col+1)){
              return 1;
            }
            else{
              sud.sudoku[row][col] = 0;
            }
          }
          else if(row+1<sud.length){
            if(sudokuSolver(sud, row + 1, 0)){
              return 1;
            }
            else{
              sud.sudoku[row][col] = 0;
            }
          }
          else{
            //printf("%s\n", "Found solution and last cell was empty");
            solutionCounter+=1;
            if(solutionCounter == 1){
              copySolutionFound(sud);
            }
            /*
            for(int m = 0; m < sud.length; m++){
              for(int n = 0; n < sud.length; n++){
                printf("%d ", sud.sudoku[m][n]);
              }
              printf("\n");
            }
            */
            return 0;
          }

        }

      }
    }
    return 0;
}

void printSimple(struct Sudoku sud){
  for(int i = 0; i < sud.length; i++){
    for(int j = 0; j < sud.length; j++){
      printf("%d ", sud.sudoku[i][j]);
    }
    printf("\n");
  }
}

void decisionToPrint(){

  if(solutionCounter == 1){
    printSimple(sudCopy);
  }
  else if(solutionCounter > 1){
    printf("%s\n", "MULTIPLE");
  }
  else{
    printf("%s\n", "UNSOLVABLE");
  }

}







int main (int argc, char *argv[]){
  //int ans = cellAccepted(parseSudoku(argv[1]), 7, 4, 25);
  //printSudoku(parseSudoku(argv[1]));
  //printf("%d\n", ans);

  int sudokuSolve = sudokuSolver(parseSudoku1(argv[1]), 0, 0);

  //printf("Solutions found %d\n", solutionCounter);

  //printf("%s\n", );

  //printf("Length : %d\n", sudCopy.length);
  //printf("%d\n", sudCopy.sudoku[0][0]);

  decisionToPrint();


}
