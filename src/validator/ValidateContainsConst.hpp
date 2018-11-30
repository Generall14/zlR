#ifndef VALIDATECONTAINSCONST_HPP
#define VALIDATECONTAINSCONST_HPP

/**
  * @class ValidateContainsConst
  * @author Wojciech Kogut
  *
  * Walidator dopuszcza tylko wartości podane w konstruktorze.
  */

#include <QObject>
#include <QValidator>
#include <src/DataI.hpp>
#include <QSharedPointer>
#include <QStringList>

class ValidateContainsConst : public QValidator
{
    Q_OBJECT
public:
    ValidateContainsConst(QStringList vals, QObject* parent = nullptr);

    virtual State validate(QString &input, int&i) const;

private:
    QStringList _vals;
};

#endif
