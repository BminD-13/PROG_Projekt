#include <iostream>

using namespace std;

/**
 * @class Sudoku
 * @author benjamind
 * @date 7/17/2023
 * @file Sudoku.hpp
 * @brief Klasse fuer ein Sudoku Spiel.
 * 
 *  Die Sudoku Klasse bildet ein Sudoku Spiel ab. 
 *  Sie enthält ein Spielfeld und Informationen über dessen Zustand.
 *  Das Ausgangsfeld wird beim Erzeugen des Objekts eingelesen.
 *  Es sind Methoden zum Ueberpruefen des Feldes implementiert.
 */
class Sudoku{
private:    
// VAR
    /** @property field   
     *  Hier ist das Spielfeld in einer 9x9 Matrix gespeichert.
     *  Es darf alle Ziffern von 0-9 enthalten.
     *  Die 0 Stellt ein Leeres (zu fuellendes) Feld dar.
     */ 
    int field[9][9];
    
    // Attribute
    /** @property solved   
     *  Wird durch die Methode "checkSudoku" gesetzt und gibt an ob das Spiel geloest ist.
     */ 
    bool solved;
    /** @property zeroes
     *  Wird durch die Methode "checkSudoku" gesetzt und gibt an ob das Spiel nullen im Feld hat.
     */ 
    bool zeroes;
    /** @property mistake
     *  Wird durch die Methode "checkSudoku" gesetzt und gibt an ob fehlerhafte Zahlen im Feld stehen. 
     */
    bool mistake;

public:
// KONSTRUKTOREN / EINGABE
    Sudoku(string);
    Sudoku(int f[9][9]);
    
// VERARBEITUNG
    void solve();
    
// AUSGABE
    void printField();
    
//VALIDIERUNG
private: 
    bool checkForZeroes();
    bool checkForMistakes();
    bool checkBlock(int,int,int,int);
public:
    bool checkSudoku();
};
