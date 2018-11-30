#include "ValidateSize.hpp"
#include <QStringList>
#include <QString>

const QString SizeValidator::znakiSIZE = "KkMG";
const QString SizeValidator::znakiNUMS = "KkMG0123456789";

SizeValidator::SizeValidator(QObject* parent):
    QValidator(parent)
{
}

/**
 * Dopuszcza wartości składające się z N...NS, gdzie N jest dowolną liczbą, S jest opcjonalnym
 * znakiem ze zbioru SizeValidator::znakiSIZE kończącym tekst.
 */
QValidator::State SizeValidator::validate(QString &input, int& i) const
{
    QString state;

    if(!input.isEmpty())
    {
        for(int i=0;i<input.size();i++)
        {
            if(!znakiNUMS.contains(input[i], Qt::CaseSensitive))
            {
                state = "Błędna składnia rozmiaru. ";
                break;
            }

            if(i==0&&znakiSIZE.contains(input[i], Qt::CaseSensitive))
            {
                state = "Błędna składnia rozmiaru. ";
                break;
            }

            if(znakiSIZE.contains(input[i], Qt::CaseSensitive))
            {
                if(i!=input.size()-1)
                {
                    state = "Błędna składnia rozmiaru. ";
                    break;
                }
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
