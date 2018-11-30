#include "ValidateRWX.hpp"
#include <QStringList>
#include <QString>

const QString RWXValidator::znakiRWX = "RWX";

RWXValidator::RWXValidator(QObject* parent):
    QValidator(parent)
{
}

/**
 * Dopuszcza tekst składający się z pojedynczych znaków ze zbioru RWXValidator::znakiRWX.
 */
QValidator::State RWXValidator::validate(QString &input, int& i) const
{
    QString state;

    if(!input.isEmpty())
    {
        for(auto sign: input)
        {
            if(!znakiRWX.contains(sign, Qt::CaseInsensitive))
            {
                state += "Nieprawidłowe znaki. ";
                break;
            }
        }

        if(input.size()>3)
            state += "Za dużo symboli. ";

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
            state += "Powtórzenia. ";
    }

    if((i<0)&&!state.isEmpty())
        throw std::runtime_error(state.toStdString());

    if(state.isEmpty())
        return QValidator::Acceptable;
    else
        return QValidator::Invalid;
}
