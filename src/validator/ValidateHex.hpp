#ifndef VALIDATEHEX_HPP
#define VALIDATEHEX_HPP

/**
  * @class HexValidator
  * @author Wojciech Kogut
  *
  * Walidator wartości w zapisie hexadecymanych, ogranicza długość danych (wartość specyfikowana w konstruktorze).
  */

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
