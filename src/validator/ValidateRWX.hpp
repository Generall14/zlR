#ifndef VALIDATERWX_HPP
#define VALIDATERWX_HPP

/**
  * @class RWXValidator
  * @author Wojciech Kogut
  *
  * Walidator praw, dopuszcza tekst składający się z pojedynczych znaków ze zbioru RWXValidator::znakiRWX.
  */

#include <QObject>
#include <QValidator>

class RWXValidator : public QValidator
{
    Q_OBJECT
public:
    RWXValidator(QObject* parent = nullptr);

    virtual State validate(QString &input, int&i) const;

private:
    static const QString znakiRWX;
};

#endif
