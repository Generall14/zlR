#include "OtherShitSolver.hpp"

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
    while(SolveNextIfs(text)){}
}

bool OtherShitSolver::SolveNextIfs(QStringList& text)
{
    QList<ifSection> ifs;
    bool found = false;
    bool started = false;
    int li=-1, sl=-1, ll=-1;
    QString lcond;

    for(int l=0;l<text.size();l++)
    {
        if(!started)
        {
            if(text.at(l).startsWith("$IF["))
            {
                sl = l;
                ll = l;
                li = text.at(l).indexOf("]");
                if(li<0)
                    throw std::runtime_error("OtherShitSolver::SolveNextIfs: brak domknięcia nawiasu w \""+
                                             text.at(l).toStdString()+"\"");
                lcond = text.at(l).mid(4, li-4);
                started = true;
            }
        }
        else
        {
            if(text.at(l).startsWith("$ELSIF["))
            {
                li = text.at(l).indexOf("]");
                if(li<0)
                    throw std::runtime_error("OtherShitSolver::SolveNextIfs: brak domknięcia nawiasu w \""+
                                             text.at(l).toStdString()+"\"");
                ifs.append(ifSection{lcond, text.mid(ll+1, l-ll-1)});
                lcond = text.at(l).mid(7, li-7);
                ll = l;
            }
            else if(text.at(l).startsWith("$ELSE"))
            {
                ifs.append(ifSection{lcond, text.mid(ll+1, l-ll-1)});
                lcond = "PLRIQNDSJ";
                ll = l;
            }
            else if(text.at(l).startsWith("$ENDIF"))
            {
                ifs.append(ifSection{lcond, text.mid(ll+1, l-ll-1)});
                found = true;
                ll = l;
                break;
            }
        }
    }

    if((started)&&(!found))
        throw std::runtime_error("OtherShitSolver::SolveNextIfs: brak znacznika $ENDIF");

    if(!found)
        return false;

    for(int l=ll;l>=sl;l--)
        text.removeAt(l);

    for(int l=0;l<ifs.size();l++)
    {
        if(GetBoleanValue(ifs.at(l).condition))
        {
            for(int k=ifs.at(l).text.size()-1;k>=0;k--)
                text.insert(sl, ifs.at(l).text.at(k));
            return true;
        }
    }

    return true;
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
