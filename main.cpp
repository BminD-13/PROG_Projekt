#include <iostream>

#include "Sudoku.hpp"
#include "SudokuBacktrack.hpp"

using namespace std;

/** @brief Feld wird auf der Konsole ausgegeben und anschliessend mit Backtracking geloesst.
 *  Sofern es richtig geloesst wurde, wird das Feld erneut ausgegeben.
 */
void testRoutine(string csvName) {
    cout << "Test: " << csvName << endl;
    // Objekt erstellen
    Sudoku ObjSudoku("Sudoku/csvSudoku/" + csvName + ".csv");
    ObjSudoku.printField();
    // sudoku loesen
    ObjSudoku.solve();
    // sudoku pruefen
    ObjSudoku.checkSudoku();
    ObjSudoku.printField();
}

int main(int argc, char **argv)
{
    testRoutine("sudokuLeicht");
    testRoutine("sudokuMittel");
    testRoutine("sudokuSchwer");
    testRoutine("sudokuLeer");
	testRoutine("sudokuFehler");
}

