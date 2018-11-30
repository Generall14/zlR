#ifndef VALIDATENAME_HPP
#define VALIDATENAME_HPP

/**
  * @class NameValidator
  * @author Wojciech Kogut
  *
  * Walidator nazwy, dopuszcza symbole NameValidator::znakiName, nie dopuszcza do powtórzenia nazw w całym obiekcie
  * DataI.
  */

#include <QObject>
#include <QValidator>
#include <src/DataI.hpp>
#include <QSharedPointer>

class NameValidator : public QValidator
{
    Q_OBJECT
public:
    NameValidator(QString name, DataI* dat, QObject* parent = nullptr);

    virtual State validate(QString &input, int&i) const;

private:
    static const QString znakiName;
    QString _name;
    DataI* _dat;
};

#endif
