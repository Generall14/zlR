#include "ValidateName.hpp"
#include <QStringList>
#include <QString>

const QString NameValidator::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";

NameValidator::NameValidator(QObject* parent):
    QValidator(parent)
{
}

QValidator::State NameValidator::validate(QString &input, int&) const
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
