#include "ValidateName.hpp"
#include <QStringList>
#include <QString>

const QString NameValidator::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";

NameValidator::NameValidator(QString name, DataI *dat, int maxSize, QObject* parent):
    QValidator(parent),
    _name(name),
    _dat(dat),
    _maxSize(maxSize)
{
}

/**
 * Dopuszcza symbole NameValidator::znakiName, nie dopuszcza do powtórzenia nazw w całym obiekcie
 * DataI wskazanym w konstruktorze.
 */
QValidator::State NameValidator::validate(QString &input, int& i) const
{
    QString state;

    if(!input.isEmpty())
    {
        if(input.size()>_maxSize)
            state += "Zbyt długa nazwa. ";

        for(auto sign: input)
        {
            if(!znakiName.contains(sign, Qt::CaseInsensitive))
            {
                state += "Błędne znaki w nazwie. ";
                break;
            }
        }

        int f=0;
        for(int j=0;j<_dat->rowCount();j++)
        {
            if(!input.compare(_dat->GetLocalByName(j, _name), Qt::CaseInsensitive))
                f++;
        }
        if(f>1)
            state += "Nazwy się powtarzają. ";
    }

    if((i<0)&&!state.isEmpty())
        throw std::runtime_error(state.toStdString());

    if(state.isEmpty())
        return QValidator::Acceptable;
    else
        return QValidator::Invalid;
}
