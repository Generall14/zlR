#ifndef VALIDATESIZE_HPP
#define VALIDATESIZE_HPP

/**
  * @class SizeValidator
  * @author Wojciech Kogut
  *
  * Walidator rozmiaru, dopuszcza wartości składające się z N...NS, gdzie N jest dowolną liczbą, S jest opcjonalnym
  * znakiem ze zbioru SizeValidator::znakiSIZE kończącym tekst.
  */

#include <QObject>
#include <QValidator>

class SizeValidator : public QValidator
{
    Q_OBJECT
public:
    SizeValidator(QObject* parent = nullptr);

    virtual State validate(QString &input, int& i) const;

private:
    static const QString znakiSIZE;
    static const QString znakiNUMS;
};

#endif
