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
    DataI(QString sign, QStringList header);

    QStringList AppendToFile();
    void FromFile(QString adr);

    /**Czyści strukturę danych.*/
    virtual void Clear() = 0;

    // Do tabeli
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

public slots:
    void Add();
    void Remove(int index);
    virtual void Check() = 0; //<TODO>

signals:
    /**Informuje o zmianie danych.*/
    void Changed();

protected:
    struct PureData
    {
        QStringList data;
        QStringList tip;
    };

    const int COLS;
    QList<PureData> _pureData;

private:
    const QString _sign;
    const QStringList _header;


    /**Ładuje dane z pliku (nie trzeba czyścić obiektu przed ani wysyłać sygnału zmiany, otrzymuje dane
     * wycięte z pliku na podstawie znacznika _sign).*/
    virtual void FromFileP(QStringList dat) = 0;
    /**Zwraca ciąg tekstów które należy dodać do pliku konfiguracyjnego (bez znacznika).*/
    virtual QStringList AppendToFileP() = 0;

    QStringList GetPieceOfFile(QString adr);
};

#endif
