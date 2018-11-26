#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <QObject>
#include <QSharedPointer>

class DataSection;
class DataRegion;
class DataDefs;

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
    QSharedPointer<DataSection> GetSections() const;

public slots:
    void CheckAll();

private:
    void Clear();

    QSharedPointer<DataRegion> _reg;
    QSharedPointer<DataSection> _sec;
    QSharedPointer<DataDefs> _def;
};

#endif
