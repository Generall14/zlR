#include "ValidateRWX.hpp"
#include <QStringList>
#include <QString>

const QString RWXValidator::znakiRWX = "RWX";

RWXValidator::RWXValidator(QObject* parent):
    QValidator(parent)
{
}

QValidator::State RWXValidator::validate(QString &input, int&) const
{
    if(input.isEmpty())
        return QValidator::Acceptable;

    for(auto sign: input)
    {
        if(!znakiRWX.contains(sign, Qt::CaseInsensitive))
            return  QValidator::Invalid;
    }

    if(input.size()>3)
        return  QValidator::Invalid;

    int r=0, w=0, x=0;
    for(auto sign: input)
    {
        if(sign=='r'||sign=='R')
            r++;
        if(sign=='w'||sign=='W')
            w++;
        if(sign=='x'||sign=='X')
            x++;
    }
    if((r>1)||(w>1)||(x>1))
        return  QValidator::Invalid;

    return QValidator::Acceptable;
}
