#ifndef VALIDATENAME_HPP
#define VALIDATENAME_HPP

#include <QObject>
#include <QValidator>

class NameValidator : public QValidator
{
    Q_OBJECT
public:
    NameValidator(QObject* parent = nullptr);

    virtual State validate(QString &input, int&) const;

private:
    static const QString znakiName;
};

#endif
