#include <iostream>

using namespace std;

/**
 * @class SudokuBacktrack
 * @author annak
 * @date 7/17/2023
 * @file SudokuBacktrack.hpp
 * @brief Klasse zum Lösen von Sudokus mit Backtracking
 * 
 * Diese Klasse implementiert in der cpp Datei den Backtracking Algorithmus zum Lösen eines Sudokus. 
 * Die Funktionen correctPart, empty und solveBacktracking werden verwendet.
 */
class SudokuBacktrack{
private:
    static bool correctPart(int, int, int, int, int, int field[9][9]);
    static bool empty(int field[9][9]);
    
public:
    static bool solveBacktracking(int field[9][9]);
};