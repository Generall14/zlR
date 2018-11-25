#include "ValidateName.hpp"
#include <QDebug>
#include <QStringList>
#include <QString>

const QString NameValidator::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";

NameValidator::NameValidator(QObject* parent):
    QValidator(parent)
{
}

/**
 * Obrzydliwa funkcja
 */
QValidator::State NameValidator::validate(QString &input, int& ii) const
{
    if(input.isEmpty())
        return QValidator::Acceptable;

    for(auto sign: input)
    {
        if(!znakiName.contains(sign, Qt::CaseInsensitive))
            return  QValidator::Invalid;
    }

    return QValidator::Acceptable;
}
