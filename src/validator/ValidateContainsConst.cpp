#include "ValidateContainsConst.hpp"
#include <QStringList>
#include <QString>

ValidateContainsConst::ValidateContainsConst(QStringList vals, QObject* parent):
    QValidator(parent),
    _vals(vals)
{
}

QValidator::State ValidateContainsConst::validate(QString &input, int& i) const
{
    QString state = "Niezdefiniowana wartość";

    if(!input.isEmpty())
    {
        for(auto val: _vals)
        {
            if(!input.compare(val, Qt::CaseSensitive))
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
