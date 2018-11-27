#ifndef OTHERSHITSOLVER_HPP
#define OTHERSHITSOLVER_HPP

#include <QStringList>

class OtherShitSolver
{
public:
    static void DoAllRequiredShit(QStringList& text);

//private:<TODO>
    OtherShitSolver() = default;

    static void SolveBrackets(QStringList& text);
    static void SolveIfs(QStringList& text);

    static bool GetBoleanValue(QString cond);
};

#endif
