#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "Sudoku.hpp"
#include "SudokuBacktrack.hpp"

using namespace std;

// KONSTRUKTOR
/**
 * @brief Spielfeld wird ueber ein zweidimensionales Array eingelesen.
 * @param f Array (9x9) welches das Spielfeld enthält. 
 */
Sudoku::Sudoku(int f[9][9]){
    for(int i=0; i < 9; i++){
        for(int j=0; j < 9; j++){
            field[i][j] = f[i][j];
        }
    }
    solved = false;
    zeroes = true;
    mistake = false;
}

/**
 * @brief Liest ein Sudoku-Feld aus einer CSV-Datei ein.
 * @param csvPath Pfad an dem die CSV-Datei gespeichert ist.
 */
Sudoku::Sudoku(string csvPath){
    ifstream csvFile;
    csvFile.open(csvPath, ios::in);
    if(csvFile){
		string line="";
        int i = 0;        
        // Zeilen einlesen
		while(getline(csvFile, line)) {
            int idxDigit=0;
            int j = 0;
            // Durch Komma getrennte Elemente in das (9x9) Array schreiben
            while(j<9){
                field[i][j] = stoi(line.substr(idxDigit, idxDigit+1));
                idxDigit = line.find(",", idxDigit) + 1;
                j++;
            }
            i++;
        }
        csvFile.close();
    }
    else{
        cerr << "Fehler beim Lesen!" << endl;
    }
}
    
// VERARBEITUNG
/**
 * @brief Loesst das Sudoku mit einem Backtracking Algorithmus
 * 
 * Der Algorithmus stammt aus der SudokuBacktrack Klasse.
 */
void Sudoku::solve(){    
    SudokuBacktrack::solveBacktracking(field);
};

// AUSGABE
/**
 * @brief Gibt das Feld auf der Konsole aus.
 */
void Sudoku::printField(){
    cout << endl;
    for(int i=0; i < 9; i++){
        for(int j=0; j < 9; j++){
            cout << to_string(field[i][j]) << " ";
            if ((j+1) % 3 == 0)cout << "   "; 
        }
        cout << endl; 
        if ((i+1) % 3 == 0)cout << endl; 
    }
    cout << endl;
}

// VALIDIERUNG
/**
 * @brief Ueberprueft das Feld auf Nullen (Spiel nicht geloesst)
 * 
 * Sind Nullen im Feld enthalten, 
 * werden die Attribute "zeroes" auf "true" und "solved" auf "false" gesetzt.
 * @return Liefert "True" zurueck wenn Nullen im Feld sind.
 */
bool Sudoku::checkForZeroes(){
    zeroes = false;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){            
            if (field[row][col] == 0){
                zeroes = true;
                solved = false;
            }
        }
    }
    if(zeroes) return true;
    else return false;
}

/**
 * @brief Ueberprueft ob die Zahlen im Feld ausserhalb {0,...,9} liegen 
 * 
 * ist dies der Fall, wird das Attribut "mistake" auf "true" gesetzt
 * @return Liefert "True" falls ein solcher Fehler gefunden wird.
 */
bool Sudoku::checkForMistakes(){
    mistake = false;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){           
            if (field[row][col] < 0 || 9 < field[row][col]){
                mistake = true;
                solved = false;
                // Fehlerausgabe auf Konsole
                cout << "number out of [0,9] in row: " << row << "  column: " << col << endl;
            }
        }
    }
    if(mistake)return true;
    else return false;
}

/**
 * @brief Ueberprueft ob eine Zeile, Spalte oder ein Block korrekt ist.
 * 
 * Es muessen alle Ziffern von 1 bis 9 in den (3x3, 1x9, 9x1) Matritzen enthalten sein.
 * Zum pruefen wird die Summe der quadrate (mit 285) verglichen.
 * @param rowStart Reihe in der gestartet wird 
 * @param colStart Spalte in der gestartet wird
 * @param rowEnd Reihe bis zu der Ueberprueft wird
 * @param colEnd Spalte bis zu der Ueberprueft wird
 * 
 * @return Liefert "true" falls alle Ziffern enthalten sind.
 */
bool Sudoku::checkBlock(int rowStart = 0, int colStart = 0, int rowEnd = 9, int colEnd = 9){
    int sumOfSquares = 0; 
    for(int row = rowStart; row < rowEnd; row++){
        for(int col = colStart; col < colEnd; col++){
            if(0 < field[row][col] && field[row][col] <= 9){
                // Summiert die Quadrate aller Felder auf
                sumOfSquares += pow(field[row][col] ,2) + 0.5;
            }
        }
    }
    // Ueberprueft ob die Summe der Quadrate 285 ergibt.
    if(sumOfSquares != 285) {
        solved = false;
        return false;
    } else return true;
}

/**
 * @brief Prueft das komplette Sudoku auf Korrektheit in allen Zeilen, Spalten und Bloecken.
 * 
 * Die Ueberpruefung erfolgt mithilfe der "checkBlock" Methode.
 * Setzt das Attribut "solved" auf true wenn das Sudoku geloest ist
 * @return Liefert "true" falls das Sudoku korrekt geloest ist.
 */
bool Sudoku::checkSudoku(){
    
    int cnt = 0; // counter of correct solutions
    
    if (!Sudoku::checkForMistakes()
    &&  !Sudoku::checkForZeroes()  ){
        
        // block
        // ueberprueft alle 3x3 bloecke und zaehlt die korrekten
        for(int row = 0; row < 9; row += 3){
            for(int col = 0; col < 9; col += 3){
                if(Sudoku::checkBlock(row, col, row +3, col +3)) cnt++;
            }
        }
        // row
        // ueberprueft alle 1x9 bloecke und zaehlt die korrekten
        for(int row = 0; row < 9; row++){
            if(Sudoku::checkBlock(row, 0, row +1, 9)) cnt++;
        }
        // columns
        // ueberprueft alle 9x1 bloecke und zaehlt die korrekten
        for(int col = 0; col < 9; col++){
            if(Sudoku::checkBlock(0, col, 9, col +1)) cnt++;
        }
        // sudoku is solved correctly if the 27 partial solutions are all correct
        if(cnt == 27){
            solved = true;
            cout << "Sudoku solved correctly: " << endl;
            cout << cnt << " correct partial sol." << endl;          
            return true;
        }
    }
    cout << "Sudoku is not solved: " << endl;
    cout << cnt << " correct partial sol." << endl;
    solved = false;
    return false;
}

