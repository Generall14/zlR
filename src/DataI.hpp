#ifndef DATAI_HPP
#define DATAI_HPP

/**
  * @class DataI
  * @author Wojciech Kogut
  *
  * Interfejs klas przechowujących zbiór struktur danych konfiguracyjnych. Przechowuje dane w postaci listy
  * stringów, zbiór parametrów w pojedynczej strukturze jest ustalany w konstruktorze jako QStringList header.
  * Wartość parametru struktury można pobrać przez GetLocalByName(int, QString).
  *
  * Obiekty identyfikowane przez przez słowo sign - getMyName(), ustawiane w konstruktorze (według tej wartości
  * dane są identyfikowane w DATA, pobierany jest znacznik w pliku z danymi, rozpoznawane jest makro).
  *
  * Zawiera metody odczytujące i zapisujące dane do pliku konfiguracyjnego.
  *
  * Sloty Add() i Remove(int) pozwalają dodawać / usuwać struktury w zestawie.
  *
  * Posiada interfejs QAbstractTableModel umożliwiający jako model w QTableView. Metoda
  * void ApplyDelegatesForTable(QTableView*) ustawi w takiej tabeli delegaty wartości.
  *
  * Posiada listę _delegats zawierającą wskaźniki do delegatów (do tabeli) dla kolejnych parametrów, konstruktor
  * DataI wypełnia listę pustymi wskaźnikami, klasy dziedziczące muszą wypełnić listę wskaźnikami na obiekty
  * interfejsu QItemDelegate (mogę też pozostawić puste, w takim przypadku zostanie uworzony delegat standardowy).
  *
  * Posiada listę _validators zawierającą wskaźniki do validatorów (interfejs QValidator), konstruktor DataI
  * wypełnia listę pustymi wskaźnikami. Klasy dziedziczące mogą wypełnić tą listę wskaźnikami da rzeczywiste
  * obiekty QValidator (lub pozostawić je puste). Na podstawie validatorów funkcja void Check() sprawdza
  * poprawność danych. Jeżeli funkcja void Check() ma stwierdzić błąd w danej pozycji to metoda
  * QValidator::validate(QString&, int&) musi wyrzucić wyjątek std::runtime_error z opisem błędu. Funkcja Check()
  * będzie wywoływać metodę QValidator::validate(QString&, int&) z ujemnym indeksem - ma to na celu umożliwienie
  * zbudowania takiego validatora, że jednocześnie obsłuży standardowe delegaty i obiekt QdataI (tj. jeżeli
  * ideks jest prawidłowy - zwróć wartość QValidator::Acceptable lub QValidator::Invalid, jeżeli jest ujemny -
  * wyrzuć wyjątek w przypadku błędu) - tak to sobie wymyśliłem aby nie powtarzać kodu. Metoda Check() jeżeli
  * stwierdzi błędy wyrzuci raport na std:cerr.
  *
  * Obiekty DataI wyrzucają sygnał void Changed() po każdej zmianie danych.
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
    QStringList getMaxTxts() const;

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
    Data* _datPtr = nullptr;

    QList<QSharedPointer<QItemDelegate> > _delegats; /**<Lista delegatów dla kolumn*/
    QList<QSharedPointer<QValidator> > _validators; /**<Lista validatorów dla kolumn*/
    QStringList _maxTxts; /**<Teksty które posłużą do oszacowania szerokości kolumny w tabeli.*/
    QList<bool> _editable; /**<Oznaczenie czy dana kolumna może być edytowana.*/
    QString _desc; /**<Opis dodany do pliku z konfiguracją.*/


    virtual QString AppendToFileL(QStringList str, int nr);
    virtual void ReadLine(QString line);

    const QString _sign; /**<Znacznik sekcji danych w pliku (//##_sign), dymbol kolejnych wpisów (#define _rown_0 ...
                             #define _rown_1 ...), nazwa w mapie w Data, nazwa w MAC_XXX.*/

private:
    const QStringList _header; /**<Lista nagłówków dla każdej kolumny w tabeli.*/

    QStringList GetPieceOfFile(QString adr);

    static const int FS_OFF = 28;
    static const int FE_INC = 13;

    bool _dirty = false;
};

#endif
