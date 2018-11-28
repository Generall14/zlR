#ifndef OTHERSHITSOLVER_HPP
#define OTHERSHITSOLVER_HPP

#include <QStringList>

class OtherShitSolver
{
public:
    static void DoAllRequiredShit(QStringList& text);

private:
    OtherShitSolver() = default;

    static void SolveBrackets(QStringList& text);

    static void SolveIfs(QStringList& text);
    static bool SolveNextIfs(QStringList& text);

    static bool GetBoleanValue(QString cond);

    static const QStringList RELS;

    struct ifSection
    {
        QString condition;
        QStringList text;
    };
};

#endif
