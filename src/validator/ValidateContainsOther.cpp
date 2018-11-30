#include "ValidateContainsOther.hpp"
#include <QStringList>
#include <QString>

/**
 * @param name - Nazwa pola struktury w jakim musi się znaleźć wartość.
 * @param dat - Wskaźnik na obiekt z którego będą czytane wartości.
 */
ValidateContainsOther::ValidateContainsOther(QString name, DataI *dat, QObject* parent):
    QValidator(parent),
    _name(name),
    _dat(dat)
{
}

/**
 * Dopuszcza tylko wartości znajdujące się w obiekcie wyspecyfikowanym w konstruktorze.
 */
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
