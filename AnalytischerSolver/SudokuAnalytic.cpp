#include <iostream>

#include "SudokuAnalytic.hpp"

SudokuAnalytic::SudokuAnalytic() {
    
}

// checks if there are the numbers from 0 to 9 in this block
void Sudoku::solveBlock(int rowStart, int colStart, int rowEnd, int colEnd, int (&possibleSol)[9]){
    for(int row = rowStart; row < rowEnd; row++){
        for(int col = colStart; col < colEnd; col++){
            if(0 < field[row][col] && field[row][col] <= 9){
                possibleSol[field[row][col]-1] = 0;
            }
        }
    }
}

// gives back the int, which is not in the   row, column or block
int Sudoku::solveScalar(int row, int col){
    int possibleSol[9] = {1,2,3,4,5,6,7,8,9};
    
    // block
    // calc startrow and startcolumn of the 3x3 block
    int rowBlock = row - (row % 3);
    int colBlock = col - (col % 3);
    Sudoku::solveBlock(rowBlock, colBlock, rowBlock +3, colBlock +3, possibleSol);
    // row
    Sudoku::solveBlock(row, 0, row +1, 9, possibleSol);
    // col
    Sudoku::solveBlock(0, col, 9, col +1, possibleSol);
    
    // find sol
    // the solution, is the last number left in the possibleSol array
    int counterSol = 9;
    int solution = 0;
    for(int i = 0; i < 9; i++){
        if(possibleSol[i] == 0) counterSol--;
        else solution = possibleSol[i];
    }
    
    // return sol
    if(counterSol == 1) return solution;
    return 0;
}

// solves whole sudoku
void Sudoku::solveSudoku(){
    bool stillSolving = true;
    while(stillSolving){
        stillSolving = false;
        for(int row = 0; row < 9; row++){
            for(int col = 0; col < 9; col++){
                if (field[row][col] == 0){
                    int sol = solveScalar(row ,col);
                    if(sol != 0) {
                        field[row][col] = sol;
                        stillSolving = true;
                    }
                }
            }
        } 
    }
}
