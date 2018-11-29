#include "ValidateHex.hpp"
#include <QStringList>
#include <QString>

const QString HexValidator::znakiHEX = "0123456789ABCDEF";

HexValidator::HexValidator(int rozmiarSlowa, QObject* parent):
    QValidator(parent),
    _slowo(rozmiarSlowa)
{
}

QValidator::State HexValidator::validate(QString &input, int&i) const
{
    QString state;

    if(!input.isEmpty())
    {
        if(input.at(0)!='0')
            state += "Brak początkowego symbolu 0. ";
        if(input.size()>1)
        {
            if(input.at(1)!='x')
                state += "Brak początkowego symbolu x. ";
            if(input.size()>2)
            {
                for(auto sign: input.mid(2))
                {
                    if(!znakiHEX.contains(sign, Qt::CaseInsensitive))
                    {
                        state += "Nieprawidłowe znaki. ";
                        break;
                    }
                }

                if(input.size()>2+_slowo)
                    state += "Zbyt długi adres. ";
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
