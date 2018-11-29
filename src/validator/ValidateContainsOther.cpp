#include "ValidateContainsOther.hpp"
#include <QStringList>
#include <QString>

ValidateContainsOther::ValidateContainsOther(QString name, DataI *dat, QObject* parent):
    QValidator(parent),
    _name(name),
    _dat(dat)
{
}

QValidator::State ValidateContainsOther::validate(QString &input, int& i) const
{
    QString state = "Niezdefiniowana wartość";

    if(!input.isEmpty())
    {
        for(int j=0;j<_dat->rowCount();j++)
        {
            if(!input.compare(_dat->GetLocalByName(j, _name), Qt::CaseSensitive))
            {
                state.clear();
                break;
            }
        }
    }

    if((i<0)&&!state.isEmpty())
        throw std::runtime_error(state.toStdString());

    if(state.isEmpty())
        return QValidator::Acceptable;
    else
        return QValidator::Invalid;
}
