#include "ValidateHex.hpp"
#include <QDebug>
#include <QStringList>
#include <QString>

const QString HexValidator::znakiHEX = "0123456789ABCDEF";

HexValidator::HexValidator(int rozmiarSlowa, QObject* parent):
    QValidator(parent),
    _slowo(rozmiarSlowa)
{
}

QValidator::State HexValidator::validate(QString &input, int&) const
{
    if(input.isEmpty())
        return QValidator::Acceptable;

    if(input.at(0)!='0')
        return  QValidator::Invalid;
    if(input.size()==1)
        return  QValidator::Acceptable;

    if(input.at(1)!='x')
        return  QValidator::Invalid;
    if(input.size()==2)
        return  QValidator::Acceptable;

    for(auto sign: input.mid(2))
    {
        if(!znakiHEX.contains(sign, Qt::CaseInsensitive))
            return  QValidator::Invalid;
    }

    if(input.size()>2+_slowo)
        return  QValidator::Invalid;

    return QValidator::Acceptable;
}
