#include "OtherShitSolver.hpp"
#include <QDebug>

const QStringList OtherShitSolver::RELS = {"==", "!=", ">=", "<=", ">", "<"};

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
    bool found = true;
    int fi, si, li;
    while(found)
    {
        found = false;
        for(int l=0;l<text.size();l++)
        {
            fi = text.at(l).indexOf("$BRA[");
            if(fi<0)
                continue;
            si = text.at(l).indexOf("]", fi);
            if(si<0)
                throw std::runtime_error("OtherShitSolver::SolveBrackets: brak domknięcia nawiasu w \""+
                                         text.at(l).toStdString()+"\"");
            li = text.at(l).indexOf("$ENDB", si);
            if(li<0)
                throw std::runtime_error("OtherShitSolver::SolveBrackets: brak symbolu $ENDB w \""+
                                         text.at(l).toStdString()+"\"");
            QString cond, meat;
            cond = text.at(l).mid(fi+5, si-fi-5);
            meat = text.at(l).mid(si+1, li-si-1);
            text[l].remove(fi, li-fi+5);
            if(GetBoleanValue(cond))
                text[l].insert(fi, cond+"("+meat+")");
            else
                text[l].insert(fi, meat);
            found = true;
            break;
        }
    }
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
 * string da w wyniku wartość fałszywą) lub dwoma słowami rozdzielonymi warunkiem (==, !=, >=, <=, >, <).
 * Słowa traktowane są jako stringi. UWAGA! Wstawienie nierozpoznanegj instrukcji relacji spowoduje
 * potraktowanie całego warunku jako pojedynczego słowa (np A=B).
 */
bool OtherShitSolver::GetBoleanValue(QString cond)
{
    if(cond.isEmpty())
        return false;

    QStringList splited;
    QString rel;
    bool found = false;

    for(auto r: RELS)
    {
        if(cond.indexOf(r)>-1)
        {
            rel = r;
            found = true;
            splited = cond.split(r);
            break;
        }
    }
    if(!found)
        return true;

    if(!rel.compare("=="))
        return !splited.at(0).compare(splited.at(1));
    else if(!rel.compare("!="))
        return splited.at(0).compare(splited.at(1));
    else if(!rel.compare(">="))
        return splited.at(0).compare(splited.at(1))>=0;
    else if(!rel.compare("<="))
        return splited.at(0).compare(splited.at(1))<=0;
    else if(!rel.compare(">"))
        return splited.at(0).compare(splited.at(1))>0;
    else if(!rel.compare("<"))
        return splited.at(0).compare(splited.at(1))<0;

    return true;
}
