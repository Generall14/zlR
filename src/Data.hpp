#ifndef DATA_HPP
#define DATA_HPP

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
