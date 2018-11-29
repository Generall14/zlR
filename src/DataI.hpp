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
#include <QItemDelegate>
#include <QTableView>

class Data;

class DataI : public QAbstractTableModel
{
    Q_OBJECT
public:
    DataI(QString sign, QStringList header, Data* data);

    virtual QStringList AppendToFile();
    void FromFile(QString adr);
    void ApplyDelegatesForTable(QTableView* table);
    QString GetLocalByName(int i, QString name);
    bool isOk() const;
    QString getMyName() const;

    QStringList GetNames();

    /**Czyści strukturę danych.*/
    virtual void Clear();

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
    void Check();

signals:
    /**Informuje o zmianie danych.*/
    void Changed();

protected:
    /**
     * Dane właściwe do tabeli, zawiera wartość właściwą oraz ewentualny opis błędu. Średnie rozwiązanie,
     * definiuje na stało typ wartości na string i częściowo rozdziela wartość od stanu. Średnie ale lenistwo
     * mi na to zezwala.
     */
    struct PureData
    {
        QStringList data; /**<Dane właściwe, liczba wpisów musi się zgadzać z COLS.*/
        QStringList tip; /**<Opisy błędów, string pusty będzie traktowany jako brak błędu, liczba wpisów musi
                           się zgadzać z ilością danych w data.*/
    };

    const int COLS; /**<Liczba kolumn z danymi.*/
    QList<PureData> _pureData; /**<Przechowywane dane.*/
    QList<QSharedPointer<QItemDelegate> > _delegats; /**<Lista delegatów dla kolumn*/
    QList<QSharedPointer<QValidator> > _validators; /**<Lista validatorów dla kolumn*/
    Data* _datPtr = nullptr;

    virtual QString AppendToFileL(QStringList str, int nr);
    virtual void ReadLine(QString line);

    const QString _sign; /**<Znacznik sekcji danych w pliku (//##_sign), dymbol kolejnych wpisów (#define _rown_0 ...
                             #define _rown_1 ...), nazwa w mapie w Data, nazwa w MAC_XXX.*/

private:
    const QStringList _header; /**<Lista nagłówków dla każdej kolumny w tabeli.*/

    QStringList GetPieceOfFile(QString adr);

    static const int FS_OFF = 28;
    static const int FE_INC = 13;
};

#endif
