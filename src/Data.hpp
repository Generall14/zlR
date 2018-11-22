#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <QObject>
#include <src/DataRegion.hpp>
#include <QSharedPointer>

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

    QSharedPointer<DataRegion> GetRegions() const;

public slots:
    void CheckAll();

private:
    void Clear();

    QSharedPointer<DataRegion> _reg;
};

#endif
