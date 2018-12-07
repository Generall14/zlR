#ifndef OTHERSHITSOLVER_HPP
#define OTHERSHITSOLVER_HPP

/**
  * @class OtherShitSolver
  * @author Wojciech Kogut
  *
  * Obiekt przetwarzający wskazany tekst szablonu, tj. przetwarza nawiasy warunkowe, składnie warunkową.
  *
  * Pozostałe czynności są wykonywane w innych obiektach, tj. makra w Macro a zamiana definicji w DataDefs.
  *
  * Całość odbywa się w metodzie statycznej DoAllRequiredShit(QStringList&).
  */

#include <QStringList>

class OtherShitSolver
{
public:
    static void DoAllRequiredShit(QStringList& text);

private:
    OtherShitSolver() = default;

    static void SolveBrackets(QStringList& text);

    static void SolveIfs(QStringList& text);
    static bool SolveNextIfs(QStringList& text, int start=0);

    static bool GetBoleanValue(QString cond);

    static const QStringList RELS;

    struct ifSection
    {
        QString condition;
        QStringList text;
    };
};

#endif
