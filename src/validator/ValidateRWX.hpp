#ifndef VALIDATERWX_HPP
#define VALIDATERWX_HPP

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
