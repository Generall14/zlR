#ifndef VALIDATECONTAINSOTHER_HPP
#define VALIDATECONTAINSOTHER_HPP

#include <QObject>
#include <QValidator>
#include <src/DataI.hpp>
#include <QSharedPointer>

class ValidateContainsOther : public QValidator
{
    Q_OBJECT
public:
    ValidateContainsOther(QString name, DataI* dat, QObject* parent = nullptr);

    virtual State validate(QString &input, int&i) const;

private:
    QString _name;
    DataI* _dat;
};

#endif
