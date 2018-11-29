#ifndef VALIDATEHEX_HPP
#define VALIDATEHEX_HPP

#include <QObject>
#include <QValidator>

class HexValidator : public QValidator
{
    Q_OBJECT
public:
    HexValidator(int rozmiarSlowa = 2, QObject* parent = nullptr);

    virtual State validate(QString &input, int& i) const;

private:
    int _slowo;
    static const QString znakiHEX;
};

#endif
