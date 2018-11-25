#ifndef VALIDATESIZE_HPP
#define VALIDATESIZE_HPP

#include <QObject>
#include <QValidator>

class SizeValidator : public QValidator
{
    Q_OBJECT
public:
    SizeValidator(QObject* parent = nullptr);

    virtual State validate(QString &input, int&) const;

private:
    static const QString znakiSIZE;
    static const QString znakiNUMS;
};

#endif
