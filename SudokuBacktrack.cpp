#include "SudokuBacktrack.hpp"

/**
 * @brief Die Funktion correctPart
 * 
 * Diese Funktion überprüft, ob die ausgewählte Zahl richtig ist. 
 * Die Parameter geben eine Teilmatrix an. Innerhalb der Teilmatrix wird überprüft, ob die Zahl bereits vorkommt. 
 * Falls ja, ist der Teil nicht korrekt, es wird "false" zurückgegeben. Ansonsten "true".
 * @param rowStart Anfangszeile
 * @param colStart Anfangsspalte
 * @param rowEnd Endzeile
 * @param colEnd Endspalte
 * @param sol ausgewählte Zahl für ein Feld
 * @param field die Matrix, die das Sudoku enthält
 * @return Korrektheit der Teilmatrix
 */
 
bool SudokuBacktrack::correctPart(int rowStart, int colStart, int rowEnd, int colEnd, int sol, int field[9][9]){
    for(int row = rowStart; row < rowEnd; row++){
        for(int col = colStart; col < colEnd; col++){
            if(field[row][col]==sol){
				//Die Zahl sol gibt es schon, sol ist falsch
                return false;			
            }
        }
    }return true;
}
/**
 * @brief Die Funktion empty
 * 
 * Die Funktion durchläuft in zwei verschachtelten Schleifen die Matrix und überprüft, 
 * ob es noch ein freies Feld gibt.
 * Falls ja, wird "true" zurückgegeben. Ansonsten "false".
 * @param field die Matrix, die das Sudoku enthält
 * @return Existenz eines freien Feldes im Sudoku
 */
bool SudokuBacktrack::empty(int field[9][9]){
	for(int row=0; row<9; row++){
		for (int col=0; col<9; col++){
			if(field[row][col] == 0){
				return true;
			}
		}
	}return false;
}

/**
 * @brief Die Funktion, die den Backtracking Algorithmus ausführt
 * 
 * Zuerst wird mit der empty Funktion überprüft, ob es noch freie Felder im Sudoku gibt.
 * Falls ja, werden die leeren Felder nacheinander ausgewählt und von 9 absteigend eine Zahl ausgewählt.
 * Mit der correctPart Funktion wird überprüft, ob die Zahl in der Zeile, Spalte und Block korrekt ist. 
 * Falls ja, wird sie eingesetzt. Falls nein, wird die nächsten Zahl überprüft.
 * Die Funktion wird rekursiv aufgerufen und durchläuft alle leeren Felder.
 * Wenn alle Felder korrekt ausgefüllt sind, wird die Funktion beendet und "true" zurückgegeben.
 * @param field die Matrix, die das Sudoku enthält
 * @return Angabe, ob Sudoku gelöst ist
 */


bool SudokuBacktrack::solveBacktracking(int field[9][9]){
	//keine 0 im Sudoku, Sudoku ist gelöst
	if(!empty(field)){ return true;}		
	
	for(int row=0; row<9; row++){
		for (int col=0; col<9; col++){
			//leeres Feld auswählen
			if(field[row][col] == 0){		
				for(int sol=9; sol >= 0; sol--){
                    //keine Lösung gefunden, 0 wird eingesetzt, Sudoku ist nicht geloest
					if (sol == 0){
                        field[row][col] = 0;
                        //cout << "no possible sol in " << "row:" << row + 1 << " col:" << col + 1 << endl << "rise 1 level" << endl;
                        return false;
                    }
					
					//Überpruefung mit correctPart Funktion
					int rowBlock = row - (row % 3);
					int colBlock = col - (col % 3);
					
					if(correctPart(row, 0, row+1, 9, sol, field) 			//row
						&& correctPart(0, col, 9, col+1, sol, field)		//col
						&&correctPart(rowBlock, colBlock, rowBlock +3, colBlock +3, sol, field)){	//block
						
						//Zahl einsetzen
						field[row][col] = sol;		
                        //cout << "row:" << row + 1 << " col:" << col + 1 << " set:" << sol << endl;                        
                        //printField();
						
						//rekursiver Aufruf der Funktion
                        if (solveBacktracking(field)) return true;
					}
				}
                //cout << "row:" << row + 1 << " col:" << col + 1 << " nonFitSol:" << field[row][col] << endl;
                //printField();
            }
		}
	} return true;
}    

    
