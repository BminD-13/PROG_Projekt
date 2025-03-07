#include <iostream>

using namespace std;

/**
 * @class SudokuAnalytic
 * @author benjamind
 * @date 7/18/2023
 * @file SudokuAnalytic.hpp
 * @brief Loest Sudokus Analytisch 
 * 
 * Klasse ist nicht in den Tests implementiert
 * und nicht weiter Kommentiert / Dokumentiert 
 */
class SudokuAnalytic{
private:    
    int field[9][9];
    bool solved;
    bool zeroes;
    bool mistake;
public:
    SudokuAnalytic();

    void solveBlock(int rowStart, int colStart, int rowEnd, int colEnd, int (&possibleSol)[9]);
    int solveScalar(int row, int col);
    void solveSudoku();
};
