#ifndef DATA_HPP
#define DATA_HPP

/**
  * @class Data
  * @author Wojciech Kogut
  *
  * Obiekt zbierający i zarządzający strukturami danych, zawiera mapę obiektów DataI identyfikowaną przez stringi
  * (ich znaczniki DataI::_sign). Łączy sygnał DataI::Changed() tych obiektów z ich slotami DataI::Check().
  *
  * Posiada metody zapisujęce i odczytujące dany konfiguracyjne z pliku (Load(...), Save(...) ) oraz przetwarzająca
  * wskazany plik szablony na podstawie zawartych w sobie danych (Make(...) ).
  */

#include <QString>
#include <QObject>
#include <QSharedPointer>
#include <QMap>

class DataI;

class Data : public QObject
{
    Q_OBJECT
public:
    Data();
    Data(QString adr);
    ~Data();

    void Load(QString adr);
    void Save(QString adr);
    void Make(QString temp, QString out);
    bool isOk() const;
    void Clear();

    QSharedPointer<DataI> GetByName(QString name) const;
    QMap<QString, QSharedPointer<DataI> > GetMap();

public slots:
    void CheckAll();

private:
    QMap<QString, QSharedPointer<DataI> > _dats;
};

#endif
