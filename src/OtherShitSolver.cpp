#include "OtherShitSolver.hpp"

/**
 * Wykonje wszystkie przewidziane w tym obiekcie czynności na wskazanym pliku:
 * 1. Rozwiązuje instrukcje warunkowe SolveIfs(...).
 * 2. Rozwiązuje warunkowe wstawianie nawiasów SolveBrackets(...).
 */
void OtherShitSolver::DoAllRequiredShit(QStringList& text)
{
    SolveIfs(text);
    SolveBrackets(text);
}

/**
 * Rozwiązuje warunkowe wstawianie nawiasów $BRA[VAL]jakiś tam tekst$ENDB na wskazanym pliku.
 */
void OtherShitSolver::SolveBrackets(QStringList& text)
{
    //<TODO>
}

/**
 * Rozwiązuje instrukcje warunkowe $IF[WARUNEK]...ble ble ble...$ELSI[WARUNEK]...ble ble ble...$ENDIF
 * we wskazanym pliku.
 */
void OtherShitSolver::SolveIfs(QStringList& text)
{
    //<TODO>
}

/**
 * Zwraca wartość logiczną wskazanego warunku, warunek może być pojedynczą wartością (wtedy tylko pusty
 * string da w wyniku wartość fałszywą) lub dwoma słowami rozdzielonymi warunkiem (==, !=, >=, <=).
 * Słowa traktowane są jako stringi. UWAGA! Wstawienie nierozpoznanegj instrukcji relacji spowoduje
 * potraktowanie całego warunku jako pojedynczego słowa (np A=B).
 */
bool OtherShitSolver::GetBoleanValue(QString cond)
{
    //<TODO>
}
