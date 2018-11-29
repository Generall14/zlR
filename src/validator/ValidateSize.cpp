#include "ValidateSize.hpp"
#include <QStringList>
#include <QString>

const QString SizeValidator::znakiSIZE = "KMG";
const QString SizeValidator::znakiNUMS = "KMG0123456789";

SizeValidator::SizeValidator(QObject* parent):
    QValidator(parent)
{
}

QValidator::State SizeValidator::validate(QString &input, int&) const
{
    if(input.isEmpty())
        return QValidator::Acceptable;

    for(int i=0;i<input.size();i++)
    {
        if(!znakiNUMS.contains(input[i], Qt::CaseInsensitive))
            return  QValidator::Invalid;

        if(i==0&&znakiSIZE.contains(input[i], Qt::CaseInsensitive))
            return  QValidator::Invalid;

        if(znakiSIZE.contains(input[i], Qt::CaseInsensitive))
        {
            if(i!=input.size()-1)
                return  QValidator::Invalid;
        }
    }

    return QValidator::Acceptable;
}
