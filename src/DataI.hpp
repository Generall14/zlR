#ifndef DATAI_HPP
#define DATAI_HPP

/**
  * @class DataI
  * @author Wojciech Kogut
  *
  * Interfejs klas przechowujących dane konfiguracyjne. Wszystko co się powtarzało w obiektach z danymi
  * jest wpakowane tutaj.
  */

#include <QString>
#include <QObject>
#include <QAbstractTableModel>

class DataI : public QAbstractTableModel
{
    Q_OBJECT
public:
    DataI(QString sign);

    QStringList AppendToFile();
    void FromFile(QString adr);

    /**Czyści strukturę danych.*/
    virtual void Clear() = 0;

public slots:
    virtual void Check() = 0;

signals:
    /**Informuje o zmianie danych.*/
    void Changed();

private:
    QString _sign;

    /**Ładuje dane z pliku (nie trzeba czyścić obiektu przed ani wysyłać sygnału zmiany, otrzymuje dane
     * wycięte z pliku na podstawie znacznika _sign).*/
    virtual void FromFileP(QStringList dat) = 0;
    /**Zwraca ciąg tekstów które należy dodać do pliku konfiguracyjnego (bez znacznika).*/
    virtual QStringList AppendToFileP() = 0;

    QStringList GetPieceOfFile(QString adr, QString sign);
};

#endif
